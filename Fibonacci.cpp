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
//extern HWND TClosePS::g_HWND;
//---------------------------------------------------------------------------
 int WINAPI _tWinMain(HINSTANCE, HINSTANCE, wchar_t *cmdLine, int)
{
	try {

//	   FindControlParam();

//	   DuplicateAppCheckParam( L"FI", cmdLine );    //BUG                          	// obsіuga kolejnych wywoіaс programu z parametrem

//	   EarlierIsMinimized();													// jeњli poprzednie wyst№pienie zminimalizowane

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

			if (GetLastError() == ERROR_ALREADY_EXISTS) {                       // jeњli powyїszy muteks istnieje

//				Application->Minimize();
//				ShowWindow(Application->Handle, SW_HIDE);

				Application->ShowMainForm = false;             					// ikona programu
//
				if ( !FindDoublePS( ) )   return 0;                              // jeњli zwrуci true zamkniкcie applikacji

				// timer zamykaj№cy?

//				MessageBoxA(Application->Handle, "Aplikacja FibonacciR jest uruchomiona.", "FibonacciR Error" , MB_OK);
			}

		BringToForeground( GetCurrentProcessId() );                   						// jeњli przeїyje FindDoublePS()

		Application->Run();

	}
	catch (Exception &exception) {

		LogSave("Błąd krytyczny aplikacji: " + exception.ToString() );
		Application->ShowException(&exception);
	}
	catch (...) {

		try {
			LogSave("Nieznany błąd aplikacji. Application will throw Exception("");");
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


