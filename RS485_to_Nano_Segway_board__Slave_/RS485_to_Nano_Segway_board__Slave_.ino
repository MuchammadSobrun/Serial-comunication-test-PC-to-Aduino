#include <SoftwareSerial.h> 

#define SSerialRX        10   
#define SSerialTX        11  

#define SSerialTxControl 3    

#define RS485Transmit    HIGH 
#define RS485Receive     LOW  

#define Pin13LED         13 

int speedInput  = 5;
int brake       = 6;
int enableInput = 7;
int dir         = 8;

int AC;
int DECE;
int x=0;

int maxpwm;// = 255;
int minpwm;// = -255;

String inputString = "";
boolean stringComplete = false;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX);

void setup() {
  // put your setup code here, to run once:
pinMode(speedInput, OUTPUT);
pinMode(brake, OUTPUT);
pinMode(enableInput, OUTPUT);
pinMode(dir, OUTPUT);

pinMode(Pin13LED, OUTPUT);
pinMode(SSerialTxControl, OUTPUT);
digitalWrite(SSerialTxControl, RS485Receive);

RS485Serial.begin(115200);
inputString.reserve(200);
}

void sobsegway(int a)
{

if (a > maxpwm){
   a = maxpwm;
  }
else if(a < minpwm){
   a = minpwm;
  }
 
if( a < 0 )
  {
    int c = a*-1;
    analogWrite(speedInput,c);
    digitalWrite(dir,LOW);     
  }
  else
  {
    analogWrite(speedInput,a);
    digitalWrite(dir,HIGH);   
  }

  digitalWrite(brake,HIGH);
}

void stoped()
{
    digitalWrite(brake,LOW);
}

void activated()
{
    digitalWrite(enableInput,LOW);
}

void deactivated()
{
    digitalWrite(enableInput,HIGH);
}

void setpwm(int pwmmax)
{
  maxpwm = pwmmax;
  minpwm = -pwmmax;
}

void gsp()
{
  RS485Serial.println(maxpwm);
}

void setAC(int A)
{
  AC = A;
}

void setDEC(int D)
{
  DECE = D;
}

void serialEvent() {
  while (RS485Serial.available()) {
    char inChar = (char)RS485Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
      digitalWrite(SSerialTxControl, RS485Transmit);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
if (RS485Serial.available() > 0 ){
    inputString = RS485Serial.readString();

    String Start = inputString.substring(0,2);
    int Start_int = Start.toInt();
    
 if(Start_int == 1){
    digitalWrite(SSerialTxControl, RS485Transmit);
    RS485Serial.println("OK");
    RS485Serial.print("ID : ");
    RS485Serial.println(Start_int);
    digitalWrite(SSerialTxControl, RS485Receive);

  if (inputString.substring(1,3) == "EN"){
    activated();
    digitalWrite(SSerialTxControl, RS485Transmit);
    RS485Serial.println("ENABLED");
    digitalWrite(SSerialTxControl, RS485Receive);
  }
  else if (inputString.substring(1,3) == "DI"){
    deactivated();
    digitalWrite(SSerialTxControl, RS485Transmit);
    RS485Serial.println("DISABLED");
    digitalWrite(SSerialTxControl, RS485Receive);
  }
  else if (inputString.substring(1,2) == "V"){
  String speedM = inputString.substring(2,7);
  int speedMotor = speedM.toInt();
  digitalWrite(SSerialTxControl, RS485Transmit);
  RS485Serial.print("speed:  ");
  RS485Serial.println(speedMotor);
  digitalWrite(SSerialTxControl, RS485Receive);
  
    if (speedMotor > x){//||speedMotor < 0){
        digitalWrite(SSerialTxControl, RS485Transmit);
        RS485Serial.print("Last speed: ");
        RS485Serial.println(x);
        digitalWrite(SSerialTxControl, RS485Receive);
        if (speedMotor > 0){
         digitalWrite(SSerialTxControl, RS485Transmit);
         RS485Serial.print("FORWARD AC"); 
         RS485Serial.print("\n");
         digitalWrite(SSerialTxControl, RS485Receive);
         for (int i = x; i <= speedMotor; i++){
            delay(AC);
            sobsegway(i);
            //Serial.println(i);
          }
        }
        else if (speedMotor < 0 || speedMotor > x){
         digitalWrite(SSerialTxControl, RS485Transmit);
         RS485Serial.print("BACKWARD DEC");
         RS485Serial.print("\n");
         digitalWrite(SSerialTxControl, RS485Receive);
         for (int i = x; i >= 1; i++){
            delay(DECE);
            sobsegway(i);
            //Serial.println(i);
             if (i == speedMotor){
               break;
             }
         }
        }
    }
    x
    = speedMotor;
  }
  else if (inputString.substring(1,3) == "SP"){
    String speedM = inputString.substring(3,8);
    int speedMotor = speedM.toInt();
    setpwm(speedMotor);
  }
  else if (inputString.substring(1,3) == "AC"){
    String speedM = inputString.substring(3,8);
    int speedMotor = speedM.toInt();
    setAC(speedMotor);
  }
  else if (inputString.substring(1,4) == "DEC"){
    String speedM = inputString.substring(4,10);
    int speedMotor = speedM.toInt();
    setDEC(speedMotor);
  }
 }
 else if (Start_int =! 1){
    digitalWrite(SSerialTxControl, RS485Receive);
 }

}
}
