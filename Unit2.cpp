//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

bool en;

bool getClient(AnsiString &login, AnsiString &passwd, AnsiString &name, AnsiString &phone, AnsiString &address, AnsiString &ip, AnsiString &balance, AnsiString &tariff, TStringList *tariffs){
	en=false;
	Form2->LabeledEdit1->Text=login;
	Form2->LabeledEdit2->Text=passwd;
	Form2->LabeledEdit3->Text=name;
	Form2->LabeledEdit4->Text=address;
	Form2->LabeledEdit5->Text=ip;
	Form2->LabeledEdit6->Text=balance;
    Form2->LabeledEdit7->Text=phone;
	Form2->ComboBox1->Items->Clear();
	for(int i=0; i<tariffs->Count; i++){
		Form2->ComboBox1->Items->Add(tariffs->Strings[i]);
	}
	Form2->ShowModal();
	if(en){
		login = Form2->LabeledEdit1->Text;
		passwd = Form2->LabeledEdit2->Text;
		name = Form2->LabeledEdit3->Text;
		address = Form2->LabeledEdit4->Text;
		ip = Form2->LabeledEdit5->Text;
		balance = Form2->LabeledEdit6->Text;
		phone = Form2->LabeledEdit7->Text;
        tariff = Form2->ComboBox1->Text;
	}
    return en;
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	 en=true;
     Form2->Close();
}
//---------------------------------------------------------------------------
