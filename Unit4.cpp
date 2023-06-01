//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
bool en=false;

bool getRouter(AnsiString &ip, AnsiString &login, AnsiString &passwd, AnsiString &csip){
	en=false;
	Form4->LabeledEdit1->Text=ip;
	Form4->LabeledEdit2->Text=login;
	Form4->LabeledEdit3->Text=passwd;
	Form4->LabeledEdit4->Text=csip;
    Form4->ShowModal();
	if(en){
		ip=Form4->LabeledEdit1->Text;
		login=Form4->LabeledEdit2->Text;
		passwd=Form4->LabeledEdit3->Text;
		csip=Form4->LabeledEdit4->Text;
	}
    return en;
}

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	en=true;
    Form4->Close();
}
//---------------------------------------------------------------------------

