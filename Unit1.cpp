//---------------------------------------------------------------------------

#include <vcl.h>
#include <winuser.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "mstr.h"
#include "mikrotik.h"
#include <vector>
#include "md5.h"
#include "sha1.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define DATAPATH "blite.db"
#define STATUS_INDEX 6
#define ONLINE_INDEX 7

TForm1 *Form1;

Tdb db;

#include "tariff.h"
#include "clients.h"
#include "routers.h"
#include "clientonline.h"
#include "privatapi.h"


extern bool getClient(AnsiString &login, AnsiString &passwd, AnsiString &name, AnsiString &phone, AnsiString &address, AnsiString &ip, AnsiString &balance, AnsiString &tariff, TStringList *tariffs);
extern bool getTariff(AnsiString &name, AnsiString &sum, AnsiString &up, AnsiString &down);
extern bool getRouter(AnsiString &ip, AnsiString &login, AnsiString &passwd, AnsiString &csip);
extern bool getBank(AnsiString &name, AnsiString &id, AnsiString &key, AnsiString &card);

bool MSG_delete(){
	return MessageBox(NULL,(LPCWSTR)L"delete client?",(LPCWSTR)L"selected",MB_OKCANCEL)==1;
}

bool MSG_delete_all(){
	return MessageBox(NULL,(LPCWSTR)L"delete clients?",(LPCWSTR)L"selected",MB_OKCANCEL)==1;
}

bool MSG_close(){
	return MessageBox(NULL,(LPCWSTR)L"close app?",(LPCWSTR)L"bLite",MB_OKCANCEL)==1;
}


void clientsShow(){
	db.select("clients");
	Form1->ListView1->Items->BeginUpdate();
    Form1->ListView1->Items->Clear();
	for(int i=0; i<db.countL(); i++){
		TListItem *l = Form1->ListView1->Items->Add();
		l->Caption = db.get_value(i,"login");
		l->SubItems->Add(db.get_value(i,"passwd"));
		l->SubItems->Add(db.get_value(i,"name"));
		l->SubItems->Add(db.get_value(i,"phone"));
		l->SubItems->Add(db.get_value(i,"address"));
		l->SubItems->Add(db.get_value(i,"ip"));
		l->SubItems->Add(db.get_value(i,"balance"));
		l->SubItems->Add(db.get_value(i,"status"));
        l->SubItems->Add("offline");
		l->ImageIndex=1;
	}
    Form1->ListView1->Items->EndUpdate();
    Form1->StatusBar1->Panels->Items[3]->Text="registered: "+IntToStr(Form1->ListView1->Items->Count);
    Form1->Timer1->Enabled=true;
}

void tariffsShow(){
	db.select("tariffs");
	Form1->ListView2->Items->Clear();
	Form1->ListView2->Items->BeginUpdate();
	for(int i=0; i<db.countL(); i++){
		TListItem *l = Form1->ListView2->Items->Add();
		l->Caption = db.get_value(i,"name");
		l->SubItems->Add(db.get_value(i,"sum"));
		l->SubItems->Add(db.get_value(i,"up"));
		l->SubItems->Add(db.get_value(i,"down"));
        l->ImageIndex=0;
	}
    Form1->ListView2->Items->EndUpdate();
}

void routerShow(){
	Trouter r;
	if(r.name!=""){
		Form1->StatusBar1->Panels->Items[0]->Text="connected:  "+r.ip+"  "+r.name+"  "+r.model+"  "+r.firmware;
        Form1->StatusBar1->Panels->Items[1]->Text="client side ip: "+r.csip;
	}
}


bool findOnline(TStringList *s,AnsiString login){
	for(int i=0; i<s->Count; i++){
		if(s->Strings[i]==login) return true;
	}
    return false;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Add1Click(TObject *Sender)
{
	Tclient c;
	AnsiString trname="";
	Ttariff tr;
	if(getClient(c.login, c.passwd, c.name, c.phone, c.address, c.ip, c.balance, trname, tr.getAllName())){
	   if(trname=="") ShowMessage("no tariff"); else{
		tr.load_name(trname);
		c.create(tr.trid);
		Trouter r;
        r.add(c);
        clientsShow();
       }
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Add2Click(TObject *Sender)
{
	Ttariff tr;
	if(getTariff(tr.name, tr.sum, tr.up, tr.down)){
		tr.create();
        tariffsShow();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
    Add1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton2Click(TObject *Sender)
{
    if(GroupBox2->Visible) GroupBox2->Visible=false; else GroupBox2->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
	if(!FileExists(DATAPATH)){
		ShowMessage("no database file");
        Application->Terminate();
	}
	db.open(DATAPATH);
	tariffsShow();
	clientsShow();
	routerShow();
}
//---------------------------------------------------------------------------

void testBankPrivat(){
	Tprivat p;
	ShowMessage(p.get("11.01.2022","11.02.2022"));
}


void __fastcall TForm1::ToolButton3Click(TObject *Sender)
{
	Trouter r;
	if(getRouter(r.ip, r.login, r.passwd, r.csip)){
		r.create();
		r.load();
        routerShow();
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ListView1Click(TObject *Sender)
{
	if(ListView1->SelCount>0) Form1->StatusBar1->Panels->Items[2]->Text="selected: "+ListView1->Selected->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Delete1Click(TObject *Sender)
{
	if((ListView1->SelCount>0)&&(MSG_delete())){
		AnsiString lg=ListView1->Selected->Caption;
		Tclient c(lg);
		Trouter r;
		if(r.del(c)){
			c.del();
			clientsShow();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item,
		  TCustomDrawState State, bool &DefaultDraw)
{
	if(Item->SubItems->Strings[STATUS_INDEX]=="disable"){
	  Sender->Canvas->Brush->Color = TColor(0xddddff);
	}else if(Item->SubItems->Strings[ONLINE_INDEX]=="offline"){
	  Sender->Canvas->Brush->Color = TColor(0xeeeeee);
	}

}
//---------------------------------------------------------------------------



void __fastcall TForm1::ToolButton6Click(TObject *Sender)
{
	if(ListView1->SelCount>0){
		AnsiString lg=ListView1->Selected->Caption;
		Tclient c(lg);
		Trouter r;
		if(r.enable(c)){
			c.enable(true);
			clientsShow();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton7Click(TObject *Sender)
{
	if(ListView1->SelCount>0){
		AnsiString lg=ListView1->Selected->Caption;
		Tclient c(lg);
		Trouter r;
		if(r.disable(c)){
			c.enable(false);
			clientsShow();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Run1Click(TObject *Sender)
{
    ToolButton6Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Payse1Click(TObject *Sender)
{
    ToolButton7Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Uptime1Click(TObject *Sender)
{
    if(ListView1->SelCount>0){
		AnsiString lg=ListView1->Selected->Caption;
		Tclient c(lg);
		Trouter r;
		AnsiString u=r.uptime(c);
		if(u!=""){
			ShowMessage("uptime: "+u);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose=MSG_close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton9Click(TObject *Sender)
{
	if(!MSG_delete_all()) return;
	std::vector<Tclient> cls;
	Tclient c;
	for(int i=0; i<Form1->ListView1->Items->Count; i++){
		if(Form1->ListView1->Items->Item[i]->Selected){
			c.load(Form1->ListView1->Items->Item[i]->Caption);
			cls.push_back(c);
		}
	}
	Trouter r;
	r.del(cls);
	for(int i=0; i<cls.size(); i++){
        cls[i].del();
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::disconnect1Click(TObject *Sender)
{
    if(ListView1->SelCount>0){
		AnsiString lg=ListView1->Selected->Caption;
		Tclient c(lg);
		Trouter r;
		AnsiString u=r.discon(c);
	}
}
//---------------------------------------------------------------------------






void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled=false;
	Trouter r;
	TStringList *s=new TStringList();
	r.onlineAll(s);
	TListItem *t;
	Form1->ListView1->Items->BeginUpdate();
	Form1->StatusBar1->Panels->Items[4]->Text="online: "+IntToStr(s->Count);
	for(int i=0; i<ListView1->Items->Count; i++){
	   t=ListView1->Items->Item[i];
	   if(findOnline(s,t->Caption)){
		t->SubItems->Strings[ONLINE_INDEX]="online";
	   }else{
		t->SubItems->Strings[ONLINE_INDEX]="offline";
	   }
	}
    Form1->ListView1->Items->EndUpdate();
    ListView1->Repaint();
	delete s;
    Timer1->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToolButton11Click(TObject *Sender)
{
	Tprivat p;
	AnsiString name="privat";
	if(getBank(name,p.id,p.key,p.card)){
		if(name=="privat") p.create();
	}
}
//---------------------------------------------------------------------------


