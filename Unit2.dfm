object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Add client'
  ClientHeight = 299
  ClientWidth = 276
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
  object Label1: TLabel
    Left = 8
    Top = 198
    Width = 27
    Height = 16
    Caption = 'tariff'
  end
  object LabeledEdit1: TLabeledEdit
    Left = 8
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 27
    EditLabel.Height = 16
    EditLabel.Caption = 'login'
    TabOrder = 0
  end
  object LabeledEdit2: TLabeledEdit
    Left = 144
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 55
    EditLabel.Height = 16
    EditLabel.Caption = 'password'
    TabOrder = 1
  end
  object LabeledEdit3: TLabeledEdit
    Left = 8
    Top = 72
    Width = 258
    Height = 24
    EditLabel.Width = 32
    EditLabel.Height = 16
    EditLabel.Caption = 'name'
    TabOrder = 2
  end
  object LabeledEdit4: TLabeledEdit
    Left = 8
    Top = 120
    Width = 258
    Height = 24
    EditLabel.Width = 45
    EditLabel.Height = 16
    EditLabel.Caption = 'address'
    TabOrder = 3
  end
  object LabeledEdit5: TLabeledEdit
    Left = 8
    Top = 168
    Width = 122
    Height = 24
    EditLabel.Width = 10
    EditLabel.Height = 16
    EditLabel.Caption = 'ip'
    TabOrder = 4
  end
  object Button1: TButton
    Left = 143
    Top = 260
    Width = 122
    Height = 25
    Caption = 'Add'
    TabOrder = 5
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 214
    Width = 257
    Height = 24
    TabOrder = 6
  end
  object LabeledEdit6: TLabeledEdit
    Left = 145
    Top = 168
    Width = 121
    Height = 24
    EditLabel.Width = 44
    EditLabel.Height = 16
    EditLabel.Caption = 'balance'
    TabOrder = 7
  end
  object LabeledEdit7: TLabeledEdit
    Left = 8
    Top = 261
    Width = 121
    Height = 24
    EditLabel.Width = 35
    EditLabel.Height = 16
    EditLabel.Caption = 'phone'
    TabOrder = 8
  end
end
