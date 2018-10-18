# To test the serial comunication between PC and Arduino.

User Interface VB.net 2015
---

![serial](https://user-images.githubusercontent.com/38030453/47060128-821e8b80-d1f6-11e8-8ebb-6f7466a076db.JPG)

User Interface element
---

### Public Class
```
Imports System.Diagnostics.Eventing
Imports System.IO.Ports
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Public Class Form1
    Dim receivedData As String = ""
    Dim comPORT As String
```

### Form Source Code
```
 Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        'ComboBox_AvailableSerialPorts.Items.Add(AvailableSerialPorts)

        'ComboBox_AvailableSerialPorts.Text = AvailableSerialPorts

        Timer1.Enabled = False
        comPORT = ""
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox_AvailableSerialPorts.Items.Add(sp)
        Next

        Button_Connect.Visible = True
        Button_Disconnect.Visible = False

        RichTextBox1.ScrollBars = ScrollBars.Vertical

        ComboBox1.Items.Add("4800")
        ComboBox1.Items.Add("9600")
        ComboBox1.Items.Add("14400")
        ComboBox1.Items.Add("19200")
        ComboBox1.Items.Add("28800")
        ComboBox1.Items.Add("38400")
        ComboBox1.Items.Add("57600")
        ComboBox1.Items.Add("115200")
        ComboBox1.Items.Add("2000000")

 End Sub
```
**1. Combo box for COM Port and BaudRate:**

![ui_1](https://user-images.githubusercontent.com/38030453/47128671-6a113f80-d2bc-11e8-9dd7-0fbf19f6fc53.JPG)

- COM Port name: `ComboBox_AvailableSerialPorts`
- Baudrate name: `ComboBox1`

```
 Private Sub ComboBox_AvailableSerialPorts_SelectedIndexChanged(sender As Object, e As EventArgs) Handles     ComboBox_AvailableSerialPorts.SelectedIndexChanged
        If (ComboBox_AvailableSerialPorts.SelectedItem <> "") Then
            comPORT = ComboBox_AvailableSerialPorts.SelectedItem
        End If
 End Sub
```

**2. Connect and Disconnect Button**

![ui_2](https://user-images.githubusercontent.com/38030453/47129241-b65d7f00-d2be-11e8-9f41-d6ebbbe8f24d.JPG)

- Button Connect name: `Button_Connect`
- Button Disconnect name: `Button_Disconnect`

#### Connect Button source code

```
 Private Sub Button_Connect_Click(sender As Object, e As EventArgs) Handles Button_Connect.Click

        SerialPort1.BaudRate = (ComboBox1.Text)
        SerialPort1.DataBits = 8
        SerialPort1.Parity = Parity.None
        SerialPort1.StopBits = StopBits.One
        SerialPort1.Handshake = Handshake.None
        SerialPort1.Encoding = System.Text.Encoding.Default 'very important!
        'SerialPort1.ReadTimeout = 10000
        SerialPort1.PortName = ComboBox_AvailableSerialPorts.SelectedItem

        Button_Connect.Visible = False
        Button_Disconnect.Visible = True

        Timer1.Enabled = True

        If SerialPort1.IsOpen = False Then
            SerialPort1.Open()
        End If
 End Sub
```
#### Disconnect Button source code
```
 Private Sub Button_Disconnect_Click(sender As Object, e As EventArgs) Handles Button_Disconnect.Click
        If SerialPort1.IsOpen = True Then
            SerialPort1.Close()
        End If

        Button_Connect.Visible = True
        Button_Disconnect.Visible = False
        Timer1.Enabled = False
 End Sub
```

**3. Serial Monitor**

![ui_3](https://user-images.githubusercontent.com/38030453/47129527-cb86dd80-d2bf-11e8-9b9f-0353a0892d06.JPG)

- Serial Monitor name: `RichTextBox1`

**4. Serial Write**

![ui_4](https://user-images.githubusercontent.com/38030453/47129852-3be22e80-d2c1-11e8-863f-c5db003a20d2.JPG)

- TextBox1
- Send Button: `Send_Button`

#### Send Button source code
```
 Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Send_Button.Click
        SerialPort1.WriteLine(TextBox1.Text)
        'TextBox1.Text = "\n"
        TextBox1.Text = ""
 End Sub
```

**5. Button Command Group**

![ui_5](https://user-images.githubusercontent.com/38030453/47130089-33d6be80-d2c2-11e8-984e-a18a9cf9aa03.JPG)

- Controller 1: `Controller1_Button`
```
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Controller1_Button.Click
        Controller1_Button.BackColor = Color.OrangeRed
        Reset_Button.BackColor = Color.GreenYellow
        SerialPort1.WriteLine("1EN")

    End Sub
```
- Controller 2: `Controller2_Button`
```
    Private Sub Controller2_Button_Click(sender As Object, e As EventArgs) Handles Controller2_Button.Click
        Controller2_Button.BackColor = Color.OrangeRed
        Reset_Button.BackColor = Color.GreenYellow
        SerialPort1.WriteLine("2EN")
    End Sub
```
- Controller 3: `Controller3_Button`
```
    Private Sub Controller3_Button_Click(sender As Object, e As EventArgs) Handles Controller3_Button.Click
        Controller3_Button.BackColor = Color.OrangeRed
        Reset_Button.BackColor = Color.GreenYellow
        SerialPort1.WriteLine("3EN")
    End Sub
```
- Controller 4: `Controller4_Button`
```
    Private Sub Controller4_Button_Click(sender As Object, e As EventArgs) Handles Controller4_Button.Click
        Controller4_Button.BackColor = Color.OrangeRed
        Reset_Button.BackColor = Color.GreenYellow
        SerialPort1.WriteLine("4EN")
    End Sub
```

**6. Exit Button**

![ui_6](https://user-images.githubusercontent.com/38030453/47130358-6d5bf980-d2c3-11e8-814f-5ef5ed5e699a.JPG)

- Exit Button name: `Button4`
```
    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        Dim minta As MsgBoxResult

        If Button_Disconnect.Visible = True Then
            minta = MsgBox("Please disconnect before exit !")
            Exit Sub
        End If

        If Button_Disconnect.Visible = False Then
            Me.Close()
        End If
    End Sub
```
---
How to open .exe file without opening Visual Studio:
---
- You must installed Microsoft Visual Studio 2015.
- Download this file over github.
- Extract zip file.
- Open folder serial comunications test RS48.
- Open "again" serial comunications test RS48.
- Open bin folder.
- Open Debug folder.
- Right click serial comunications test RS48.exe, Run as administrator.

How to open trought Microsoft Visual Studio:
---
- Open Visual Studio 2015.
- Click open file
- Find the folder that you have been saved serial comunications test RS48 project.
- file name: serial comunications test RS48.vbproj

Programming of this user interface based on Visual Basic language.
