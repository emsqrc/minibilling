object Form4: TForm4
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'MikroTik'
  ClientHeight = 108
  ClientWidth = 394
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object LabeledEdit1: TLabeledEdit
    Left = 8
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 10
    EditLabel.Height = 16
    EditLabel.Caption = 'ip'
    TabOrder = 0
  end
  object LabeledEdit2: TLabeledEdit
    Left = 135
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 27
    EditLabel.Height = 16
    EditLabel.Caption = 'login'
    TabOrder = 1
  end
  object LabeledEdit3: TLabeledEdit
    Left = 262
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 55
    EditLabel.Height = 16
    EditLabel.Caption = 'password'
    PasswordChar = '*'
    TabOrder = 2
  end
  object Button1: TButton
    Left = 262
    Top = 66
    Width = 122
    Height = 25
    Caption = 'OK'
    TabOrder = 3
    OnClick = Button1Click
  end
  object LabeledEdit4: TLabeledEdit
    Left = 8
    Top = 68
    Width = 121
    Height = 24
    EditLabel.Width = 71
    EditLabel.Height = 16
    EditLabel.Caption = 'client side ip'
    TabOrder = 4
  end
end
