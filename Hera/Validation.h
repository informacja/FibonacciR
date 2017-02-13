//---------------------------------------------------------------------------

#ifndef ValidationH
#define ValidationH
// 	#include "ClosePsDlg.h"
#include <Classes.hpp>

//---------------------------------------------------------------------------

 int Check_License( );                 	// Funkcja wywo³ywana z zewn¹trz automatycznie sprz¹ta po w¹tku

//---------------------------------------------------------------------------

 class License_validate : public TThread
 {
	 int Zmienna_testowa; 				// Przyk³adowa zmienna

//	 int monitor();                      // numer seryjny monitora
//	 int bios();                         // data biosu
//	 int drive();						// numer seryjny dysku

	 void __fastcall Execute();				// G³ówna procedura dzia³ania w¹tku

 public:

//	 void sth();
	 __fastcall License_validate(bool CreateSuspended); // Tworzenie w¹tku
	 __fastcall ~License_validate();                     	// Niszczenie w¹tku
 };

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#endif
