//---------------------------------------------------------------------------

#ifndef ValidationH
#define ValidationH
// 	#include "ClosePsDlg.h"
#include <Classes.hpp>

//---------------------------------------------------------------------------

 int Check_License( );                 	// Funkcja wywo�ywana z zewn�trz automatycznie sprz�ta po w�tku

//---------------------------------------------------------------------------

 class License_validate : public TThread
 {
	 int Zmienna_testowa; 				// Przyk�adowa zmienna

//	 int monitor();                      // numer seryjny monitora
//	 int bios();                         // data biosu
//	 int drive();						// numer seryjny dysku

	 void __fastcall Execute();				// G��wna procedura dzia�ania w�tku

 public:

//	 void sth();
	 __fastcall License_validate(bool CreateSuspended); // Tworzenie w�tku
	 __fastcall ~License_validate();                     	// Niszczenie w�tku
 };

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#endif
