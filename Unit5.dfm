object Form5: TForm5
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'bank'
  ClientHeight = 186
  ClientWidth = 322
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
    Left = 16
    Top = 3
    Width = 27
    Height = 16
    Caption = 'bank'
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 19
    Width = 145
    Height = 24
    TabOrder = 0
    Items.Strings = (
      'privat')
  end
  object LabeledEdit1: TLabeledEdit
    Left = 184
    Top = 19
    Width = 121
    Height = 24
    EditLabel.Width = 10
    EditLabel.Height = 16
    EditLabel.Caption = 'id'
    TabOrder = 1
  end
  object LabeledEdit2: TLabeledEdit
    Left = 16
    Top = 64
    Width = 289
    Height = 24
    EditLabel.Width = 19
    EditLabel.Height = 16
    EditLabel.Caption = 'key'
    PasswordChar = '*'
    TabOrder = 2
  end
  object LabeledEdit3: TLabeledEdit
    Left = 16
    Top = 112
    Width = 289
    Height = 24
    EditLabel.Width = 25
    EditLabel.Height = 16
    EditLabel.Caption = 'card'
    PasswordChar = '*'
    TabOrder = 3
  end
  object Button1: TButton
    Left = 230
    Top = 152
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 136
    Top = 152
    Width = 75
    Height = 25
    Caption = 'test'
    TabOrder = 5
    OnClick = Button2Click
  end
end
