//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Func.h"
#include "Wazne.h"
#include "SplashR.h"
#include "Dialogs/ClosePsDlg.h"
#include "Validation.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Point_Form.cpp", WPoint);
USEFORM("SplashR.cpp", Splash);
USEFORM("Ustawienia.cpp", Form2);
USEFORM("Wprogramie.cpp", Form3);
USEFORM("Unit1.cpp", FibonacciR);
USEFORM("Dialogs\PropertiesDlg.cpp", PropetisDlg);
USEFORM("Dialogs\ClosePsDlg.cpp", ClosePS);
USEFORM("Dialogs\DialogScan.cpp", SearchPref);
//---------------------------------------------------------------------------
extern void BringToForeground(DWORD processId);
//extern HWND g_HWND;
//---------------------------------------------------------------------------
 int WINAPI _tWinMain(HINSTANCE, HINSTANCE, wchar_t *cmdLine, int)
{
	try {

//	   FindControlParam();

//	   DuplicateAppCheckParam( L"FI", cmdLine );    //BUG                          	// obs³uga kolejnych wywo³añ programu z parametrem

//	   EarlierIsMinimized();													// jeœli poprzednie wyst¹pienie zminimalizowane

//	   ShowSplash(5000);
//
		Application->Initialize();
//               Application->UseMetropolisUI();
		Application->CreateForm(__classid(TFibonacciR), &FibonacciR);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->Title = "FibonacciR";

		Check_License( );

		CreateMutexA(NULL, TRUE, "FI");

			if (GetLastError() == ERROR_ALREADY_EXISTS) {                       // jeœli powy¿szy muteks istnieje

//				Application->Minimize();
//				ShowWindow(Application->Handle, SW_HIDE);

				Application->ShowMainForm = false;             					// ikona programu
//
				if ( !FindDoublePS( ) )   return 0;                              // jeœli zwróci true zamkniêcie applikacji

				// timer zamykaj¹cy?

//				MessageBoxA(Application->Handle, "Aplikacja FibonacciR jest uruchomiona.", "FibonacciR Error" , MB_OK);
			}

		BringToForeground( GetCurrentProcessId() );                   						// jeœli prze¿yje FindDoublePS()

		Application->Run();

	}
	catch (Exception &exception) {

		LogSave("B³¹d krytyczny aplikacji: " + exception.ToString() );
		Application->ShowException(&exception);
	}
	catch (...) {

		try {
			LogSave("Nieznany b³¹d aplikacji. Application will throw Exception("");");
			throw Exception("");
		}
		catch (Exception &exception) {
			LogSave("KOTROLA CO PRZECHWYCONO: " + exception.ToString() );
			Application->ShowException(&exception);
		}
	}
	return 0;

}
//---------------------------------------------------------------------------


