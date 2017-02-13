//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------

#include <Classes.hpp>

 class THsearch : public TThread
		 {
			 int Zmienna_testowa; 				// Przyk³adowa zmienna
			 TNotifyEvent __fastcall OnbtClick(TObject *Sender);

			 void __fastcall Search();

		//	 int monitor();                      // numer seryjny monitora
		//	 int bios();                         // data biosu
		//	 int drive();						// numer seryjny dysku

			 void __fastcall Execute();				// G³ówna procedura dzia³ania w¹tku

		 public:

		//	 void sth();
			 __fastcall THsearch(bool CreateSuspended); // Tworzenie w¹tku
			 __fastcall ~THsearch();                     	// Niszczenie w¹tku
		 };


int Startuj_Watek( int );
int Rozlacz_Watek( int );

//---------------------------------------------------------------------------

#endif
