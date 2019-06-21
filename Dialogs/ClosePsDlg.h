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
	void __fastcall LabelPSnameClick(TObject *Sender);
private:
	unsigned char timetoclose;
	TProgressBar *ProgressBar1;
	void inicProgBar();

public:
            	HWND g_HWND;
//       friend BOOL CALLBACK EnumWindowsProcMy(HWND hwnd,LPARAM lParam);														  // uchwyt do okna


public:
	virtual __fastcall TClosePS(TComponent* AOwner);
	virtual __fastcall TClosePS(TComponent* AOwner, PROCESSENTRY32 );
};


	bool FindDoublePS();
	bool IsMorePS();
	bool CloseProcess(Pointer ID);


	BOOL CALLBACK EnumWindowsProc(HWND windowHandle, LPARAM lParam);
	void BringToForeground(DWORD processId);

	//---------------------------------------------------------------------------
bool ComparePIDs( HWND *hWnd )
{
	DWORD pid = 0;
	DWORD c = GetCurrentProcessId();

	GetWindowThreadProcessId( *hWnd, &pid );
	if ( pid == c )
	return true;
	else return false;

}


HWND GetGarenaWindow()
{
HWND hWnd = FindWindowA("TFibonacciR", NULL);
while (!ComparePIDs( &hWnd))
  hWnd = FindWindowExA(NULL, hWnd, "TFibonacciR", NULL);
return hWnd;
}
bool ComparePIDs(HWND hWnd)
{
DWORD CurrentPID = GetCurrentProcessId();

DWORD TargetPID = NULL;
GetWindowThreadProcessId(hWnd, &TargetPID);

if (CurrentPID == TargetPID)
  return true;
else
  return false;
}
//----------------------------------------------------------------------------
extern PACKAGE TClosePS *ClosePS;
//----------------------------------------------------------------------------
#endif    
