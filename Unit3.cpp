//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
bool en=false;

bool getTariff(AnsiString &name, AnsiString &sum, AnsiString &up, AnsiString &down){
    en=false;
	Form3->LabeledEdit1->Text=name;
	Form3->LabeledEdit2->Text=sum;
	Form3->LabeledEdit3->Text=up;
	Form3->LabeledEdit4->Text=down;
	Form3->ShowModal();
	if(en){
	   name=Form3->LabeledEdit1->Text;
	   sum=Form3->LabeledEdit2->Text;
	   up=Form3->LabeledEdit3->Text;
       down=Form3->LabeledEdit4->Text;
	}
    return en;
}

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	en=true;
    Form3->Close();
}
//---------------------------------------------------------------------------

