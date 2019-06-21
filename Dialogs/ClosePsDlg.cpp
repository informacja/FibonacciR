//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ClosePsDlg.h"
#include "Hera/Func.h"
#include "Unit1.h"
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
	LabelPSname->Hide();
}

//---------------------------------------------------------------------

__fastcall TClosePS::TClosePS(TComponent* AOwner, PROCESSENTRY32 ps)
	: TForm(AOwner)
{
	Parent = (TWinControl*)GetWindowLong(g_HWND, 0);// = ;

	inicProgBar();
	timetoclose = 110;

	this->Text = "FibonacciR (" + String( GetCurrentProcessId() ) + ") ";
	LabelPSname->Caption = (String)ps.szExeFile + "  PID (" + ps.th32ProcessID + ")";
}
//---------------------------------------------------------------------

void __fastcall TClosePS::FormClose(TObject *Sender, TCloseAction &Action) {

Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::ButtonCancelClick(TObject *Sender) {

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

void __fastcall TClosePS::FormMouseEnter(TObject *Sender) {

ButtonCancel->Caption = "Anuluj";
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::FormCreate(TObject *Sender) {

Image1->Picture->Icon->Handle = LoadIcon(NULL, IDI_HAND);
}
//---------------------------------------------------------------------------

void __fastcall TClosePS::FormShow(TObject *Sender) {

 MessageBeep(MB_ICONHAND);
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
//---------------------------------------------------------------------------

 BOOL TerminateProcess(DWORD dwProcessId, UINT uExitCode)
{
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle  = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);    // or PROCESS_TERMINATE zamiast dwDesiredAccess
	if (hProcess == NULL)
		return FALSE;

	BOOL result = TerminateProcess(hProcess, uExitCode);

	CloseHandle(hProcess);

	return result;
}
// --------------------------------------------------------------------------- // jeœli false to blokuje uruchomienie tej aplikacji
 BOOL CALLBACK EnumWindowsProcMy(HWND hwnd,LPARAM lParam)                        // znalezione
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if(lpdwProcessId==(unsigned long)lParam)
	{
		ClosePS->g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}
//---------------------------------------------------------------------------
//		  [DllImport("user32.dll", EntryPoint="GetWindowLong")]
//static extern IntPtr GetWindowLongPtr(IntPtr hWnd, int nIndex);

int ShowQuestPS( PROCESSENTRY32 proces ) {

//HWND h = (HWND__* )OpenProcess(PROCESS_ALL_ACCESS, true, proces.th32ProcessID);         	// dzia³a z losowym skutkiem



EnumWindows(EnumWindowsProcMy, proces.th32ProcessID );

	   ClosePS = new TClosePS(  0, proces );    //   FindControl(  )

//	unique_ptr<TClosePS> pWnd = make_unique( TClosePS( FibonacciR , proces) );	// doesn't work
//	unique_ptr<TClosePS> pWnd(new TClosePS( FibonacciR , proces));
//					   pWnd->SetParentComponent(0);
//	pWnd->ParentWindow = g_HWND;                                                // modalnie nad nowym procesem(to okno)
//ClosePS->ParentWindow = GetGarenaWindow();

// if (ClosePS->ParentWindow)  ShowMessage((int) ClosePS->ParentWindow);
//DWORD pid = 0;
//	GetWindowThreadProcessId( ClosePS->ParentWindow , &pid );
//ClosePS->Parent = FindControl( ClosePS->ParentWindow );


//				   FindControl(g_HWND);
//LONG lStyle = GetWindowLong(g_HWND, GWL_STYLE);
//lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
//SetWindowLong(g_HWND, GWL_STYLE, lStyle);
//
		 SetWindowTheme( GetGarenaWindow(),NULL,NULL);
//									   ShowMessage((int)g_HWND)  ;
// pWnd->ParentWindow = GetParent(g_HWND);       	  ShowMessage(  (int)GetParent(g_HWND) );
// pWnd->ParentWindow = g_HWND;
// GetParentForm(pWnd->Parent,1);
//	  SetParent( pWnd->ParentWindow,  g_HWND);
// pWnd->ParentWindow = g_HWND;
//	  ShowMessage((int)  pWnd->ParentWindow );




return ClosePS->ShowModal();
//			 pWnd->Show();

//unique_ptr<String> text(new String("Aplikacja FibonacciR jest uruchomiona.\n\nCzy zamkn¹æ ten proces? (wczesniej uruchomiony)\n\n"));
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

 Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS , 0);                     // inna metoda
 proces.dwSize = sizeof(PROCESSENTRY32);

 if(Process32First(Snap , &proces))  {

  do {
	if (proces.szExeFile[0] == 'F')
	if (proces.szExeFile[1] == 'i')
		if (proces.th32ProcessID != GetCurrentProcessId() ) {                   // jeœli inny od aktualnego procesu

			switch( ShowQuestPS(proces) ) {

			case ID_YES:
				closed = TerminateProcess( proces.th32ProcessID, 0 );
				SetForegroundWindow( Application->Handle );  break;        		// przywo³uje  na pierwszy plan (póŸniej uruchomiony proces)

			case ID_NO:
//				ShowWindow(g_HWND, SW_SHOW);
				BringToForeground( proces.th32ProcessID );
				Application->Minimize();                     // minimalizje okno na okres poszukiwañ procesów zombie
				IsMorePS();

			case ID_CANCEL:
				CloseHandle(Snap);
				BringToForeground( proces.th32ProcessID );
				TerminateProcess( GetCurrentProcessId(), 0 );   return 0;       // teoretycznie return nie potrzebny

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
 {                      									//   PROCESS_TERMINATE zamiast PROCESS_ALL_ACCESS
  hWnd = (HWND__ *)OpenProcess(PROCESS_TERMINATE, true, ExitCode );
  if(hWnd)
  {
//				  ShowMessage(  ExitCode  );
//   GetExitCodeProcess(hWnd, &ExitCode);
//	CloseProcess(hWnd);                '
DestroyWindow(hWnd);
DefWindowProc( hWnd, WM_CLOSE,0,0);
//

SendMessage( Application->Handle, WM_DESTROY, 0, 0 );
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

// This gets called by winapi for every window on the desktop
BOOL CALLBACK EnumWindowsProc(HWND windowHandle, LPARAM lParam)  {
	DWORD searchedProcessId = (DWORD)lParam;  // This is the process ID we search for (passed from BringToForeground as lParam)
	DWORD windowProcessId = 0;
	GetWindowThreadProcessId(windowHandle, &windowProcessId); // Get process ID of the window we just found
	if (searchedProcessId == windowProcessId)  {  // Is it the process we care about?
//	ShowMessage((int)windowHandle);
	  SetForegroundWindow(windowHandle);  // Set the found window to foreground
      return FALSE;  // Stop enumerating windows
    }
    return TRUE;  // Continue enumerating
}

//---------------------------------------------------------------------------

void BringToForeground(DWORD processId)  {
   EnumWindows(&EnumWindowsProc, (LPARAM)processId);
}




//---------------------------------------------------------------------------

void __fastcall TClosePS::LabelPSnameClick(TObject *Sender)
{
   MessageBoxA( GetGarenaWindow(), "dcla","cc",1 );
// ShowMessage( (int)GetGarenaWindow());

}
//---------------------------------------------------------------------------

