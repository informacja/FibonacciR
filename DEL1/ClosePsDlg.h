//----------------------------------------------------------------------------
#ifndef ClosePsDlgH
#define ClosePsDlgH
//----------------------------------------------------------------------------
#include <tlhelp32.h>     // procesy

#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.ComCtrls.hpp>
//----------------------------------------------------------------------------
class TClosePS : public TForm
{
__published:
	TBevel *Bevel1;
	TButton *ButtonCancel;
	TLabel *LabelCoseL;
	TTimer *Timer1;
	TButton *ButtonYes;
	TButton *ButtonNo;
	TLabel *LabelInfoL;
	TLabel *LabelPSname;
	TImage *Image1;
	TLabel *LabelporcinfoL;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormMouseEnter(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:
	unsigned char timetoclose;
	TProgressBar *ProgressBar1;
	void inicProgBar();

public:


public:
	virtual __fastcall TClosePS(TComponent* AOwner);
	virtual __fastcall TClosePS(TComponent* AOwner, PROCESSENTRY32 );
};

	HWND g_HWND;														  // uchwyt do okna

	bool FindDoublePS();
	bool IsMorePS();
	bool CloseProcess(Pointer ID);


//----------------------------------------------------------------------------
extern PACKAGE TClosePS *ClosePS;
//----------------------------------------------------------------------------
#endif    
