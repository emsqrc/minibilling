//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdAuthentication.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TListView *ListView1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Add1;
	TListView *ListView2;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TPopupMenu *PopupMenu2;
	TMenuItem *Add2;
	TImageList *ImageList1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TImageList *ImageList2;
	TMenuItem *Delete1;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TMenuItem *Payse1;
	TMenuItem *Run1;
	TMenuItem *Uptime1;
	TToolButton *ToolButton9;
	TMenuItem *disconnect1;
	TToolButton *ToolButton10;
	TIdHTTP *IdHTTP1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TMemo *Memo2;
	TToolButton *ToolButton11;
	TTimer *Timer1;
	void __fastcall Add1Click(TObject *Sender);
	void __fastcall Add2Click(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall ListView1Click(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw);
	void __fastcall ToolButton6Click(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall Run1Click(TObject *Sender);
	void __fastcall Payse1Click(TObject *Sender);
	void __fastcall Uptime1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ToolButton9Click(TObject *Sender);
	void __fastcall disconnect1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ToolButton11Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
