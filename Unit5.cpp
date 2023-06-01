//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern void testBankPrivat();

TForm5 *Form5;

bool en=false;


bool getBank(AnsiString &name, AnsiString &id, AnsiString &key, AnsiString &card){
    en=false;
	Form5->ComboBox1->Text=name;
	Form5->LabeledEdit1->Text=id;
	Form5->LabeledEdit2->Text=key;
	Form5->LabeledEdit3->Text=card;
	Form5->ShowModal();
	if(en){
	   name=Form5->ComboBox1->Text;
	   id=Form5->LabeledEdit1->Text;
	   key=Form5->LabeledEdit2->Text;
	   card=Form5->LabeledEdit3->Text;
	}
    return en;
}

//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
    en=true;
	Form5->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button2Click(TObject *Sender)
{
    testBankPrivat();
}
//---------------------------------------------------------------------------
