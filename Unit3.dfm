object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Tariff'
  ClientHeight = 144
  ClientWidth = 277
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
    EditLabel.Width = 33
    EditLabel.Height = 16
    EditLabel.Caption = 'Name'
    TabOrder = 0
  end
  object LabeledEdit2: TLabeledEdit
    Left = 144
    Top = 24
    Width = 121
    Height = 24
    EditLabel.Width = 43
    EditLabel.Height = 16
    EditLabel.Caption = 'per day'
    TabOrder = 1
  end
  object LabeledEdit3: TLabeledEdit
    Left = 8
    Top = 66
    Width = 121
    Height = 24
    EditLabel.Width = 14
    EditLabel.Height = 16
    EditLabel.Caption = 'up'
    TabOrder = 2
  end
  object LabeledEdit4: TLabeledEdit
    Left = 146
    Top = 66
    Width = 121
    Height = 24
    EditLabel.Width = 31
    EditLabel.Height = 16
    EditLabel.Caption = 'down'
    TabOrder = 3
  end
  object Button1: TButton
    Left = 146
    Top = 104
    Width = 119
    Height = 25
    Caption = 'Add'
    TabOrder = 4
    OnClick = Button1Click
  end
end
