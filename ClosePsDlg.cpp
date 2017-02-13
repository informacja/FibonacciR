//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClosePsDlg.h"
#include "Func.h"
//#include "Unit1.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TClosePS *ClosePS;
//---------------------------------------------------------------------
__fastcall TClosePS::TClosePS(TComponent* AOwner)
	: TForm(AOwner)
{
	timetoclose = 110;                                                          // nie wiêksze ni¿ 255
	inicProgBar();
	this->Text = "FibonacciR (" + String(GetCurrentProcessId()) + ") ";
}
//---------------------------------------------------------------------
__fastcall TClosePS::TClosePS(TComponent* AOwner, PROCESSENTRY32 ps)
	: TForm(AOwner)
{
	Parent = 0;
	inicProgBar();
	timetoclose = 110;
	LabelPSname->Caption = (String)ps.szExeFile + "  PID (" + ps.th32ProcessID + ")";
	this->Text = "FibonacciR (" + String(GetCurrentProcessId()) + ") ";
}
//---------------------------------------------------------------------
void __fastcall TClosePS::FormClose(TObject *Sender, TCloseAction &Action)
{
Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::ButtonCancelClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::Timer1Timer(TObject *Sender)
{
	if (!CursorAt(this->Handle)) { 												// jeœli kursor poza oknem

		if (timetoclose) {

			ButtonCancel->Caption = "Anuluj (" + (String)int(timetoclose/10) + ")";
			ProgressBar1->Position = 100 - (timetoclose*2)+10;
		}
		else Close();

		timetoclose--;

	}
	else {
		timetoclose = 50;
		ProgressBar1->Position = 0;
		ButtonCancel->Caption = "Anuluj";
	}
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::FormMouseEnter(TObject *Sender)
{
ButtonCancel->Caption = "Anuluj";
}

// ---------------------------------------------------------------------------
void TClosePS::inicProgBar() {

ProgressBar1 = new TProgressBar(this);
 ProgressBar1->Parent = this;
 ProgressBar1->Position = 0;
 ProgressBar1->Height = 10;
 ProgressBar1->Top = 130 ;
 ProgressBar1->Left = -2;
 ProgressBar1->Width = this->Width;
// ProgressBar1->Step = 20;
// ProgressBar1->Min = 5;
// ProgressBar1->State=  pbsPaused;
 ProgressBar1->SmoothReverse = true;                                            // bufor (poprawia p³ynnoœæ)
 ProgressBar1->DoubleBuffered = true;
 ProgressBar1->Visible = True;
}
// ---------------------------------------------------------------------------

BOOL CALLBACK EnumWindowsProcMy(HWND hwnd,LPARAM lParam)                        // znalezione
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if(lpdwProcessId==lParam)
	{
		g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}
// EnumWindows(EnumWindowsProcMy, my_ProcessId);                         		// wywo³anie  ostatni parametr to PID procesu którego uchwytu okna szukamy

// --------------------------------------------------------------------------- // jeœli false to blokuje uruchomienie tej aplikacji

int ShowQuestPS( PROCESSENTRY32 proces ) {

unique_ptr<String> text(new String("Aplikacja FibonacciR jest uruchomiona.\n\nCzy zamkn¹æ ten proces? (wczesniej uruchomiony)\n\n"));
(HWND__* )OpenProcess(PROCESS_ALL_ACCESS, true, proces.th32ProcessID);         	// dzia³a z losowym skutkiem
															   //BUG
   EnumWindows(EnumWindowsProcMy,proces.th32ProcessID);

   unique_ptr<TClosePS> pWnd(new TClosePS( 0, proces));

   pWnd->ParentWindow = g_HWND;
//   pWnd->Parent = pWnd->CreateParentedControl(g_HWND);
//  ShowMessage((int)Application->Handle); ShowMessage((int)g_HWND);

	   return	pWnd->ShowModal();

//			 pWnd->Show();
//	return MessageBoxW (  g_HWND,                                               // stara metoda
//		( (*text) +
//		proces.szExeFile + "  PID (" + proces.th32ProcessID + ")").c_str(),
//		( "FibonacciR (" + String(GetCurrentProcessId()) + ") ").c_str(),
//		MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON3);
}
//---------------------------------------------------------------------------
bool FindDoublePS() {

 void *Snap;
 PROCESSENTRY32 proces;
 bool closed = true;

 Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS , 0);
 proces.dwSize = sizeof(PROCESSENTRY32);

 if(Process32First(Snap , &proces))  {

  do {
	if (proces.szExeFile[0] == 'F')
	if (proces.szExeFile[1] == 'i')
		if (proces.th32ProcessID != GetCurrentProcessId() ) {                   // jeœli inny od aktualnego procesu

			switch( ShowQuestPS(proces) ) {

			case ID_YES:
				closed = CloseProcess((Pointer)proces.th32ProcessID);
				Application->BringToFront();         break;
//				FibonacciR->BringToFront();                   break;
//							SetForegroundWindow( Application->Handle ); break;        // przywo³uje  na pierwszy plan (póŸniej uruchomiony proces)
			case ID_NO:
				/* BringWindowToFront(gethwnd from proces);*/
//				Close();// FibonacciR->Close();/* Application->ModalFinished();*/ break;
				EndDialog((HWND__*)proces.th32ProcessID,0);

			case ID_CANCEL: CloseHandle(Snap); return 0;

			}
		}
  }  while(Process32Next(Snap , &proces));
 }

 CloseHandle(Snap);

 return (closed) ? IsMorePS() : 0;                                              // colsed to waroœc zwrócona przez CloseProces()
																				// jesli funkcja wykana³a siê pomyœlnie(1) to sprzwdzi czy nie ma innych wyst¹pieñ programu
  }
//---------------------------------------------------------------------------
bool IsMorePS() {

for (int i = 0; i < 1000; i++)  Sleep(1);                                           // wstrzymanie a¿ procesy zostan¹ zamkneiête

 void *Snap;
 PROCESSENTRY32 proces;
  Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS , 0);
 proces.dwSize = sizeof(PROCESSENTRY32);

	 if(Process32First(Snap , &proces)) {                                           // sprawdza czy s¹ inne procesy on nazwie zaczynajacej sie Fi
  do {
	if (proces.szExeFile[0] == 'F')
	if (proces.szExeFile[1] == 'i')
		if ( proces.th32ProcessID != GetCurrentProcessId() ) {                       // jeœli inny od aktualnego procesu
//		ShowMessage( String(proces.th32ProcessID) + "Diffrent PS: " + String(proces.szExeFile) );
		 CloseHandle(Snap); return 0;
		}
  }
  while(Process32Next(Snap , &proces));
 }
 CloseHandle(Snap);
 return 1;
}

//---------------------------------------------------------------------------
 bool CloseProcess(Pointer ID)
{
 DWORD ExitCode = (unsigned long) (ID);
 HWND hWnd;
 bool Result = true;

 if(ID)
 {
  hWnd = (HWND__ *)OpenProcess(PROCESS_ALL_ACCESS, true, ExitCode );
  if(hWnd)
  {

//   GetExitCodeProcess(hWnd, &ExitCode);
//	CloseProcess(hWnd);                '
//DestroyWindow(hWnd);
DefWindowProc( hWnd, WM_CLOSE,0,0);
//
SendAppMessage(ExitCode,0,0) ;
EndDialog(hWnd,0);
//WindowFromAccessibleObject() todo
	SendMessageA(hWnd, TDM_CLICK_BUTTON,2,0);
//   Result = TerminateProcess(hWnd, ExitCode);
  }
  else return false;
 }
 else return false;

 CloseHandle(hWnd);
 return Result;
}
//---------------------------------------------------------------------------
void __fastcall TClosePS::FormCreate(TObject *Sender)
{
Image1->Picture->Icon->Handle = LoadIcon(NULL, IDI_HAND);

}
//---------------------------------------------------------------------------

void __fastcall TClosePS::FormShow(TObject *Sender)
{
 MessageBeep(MB_ICONHAND);
}
//---------------------------------------------------------------------------

