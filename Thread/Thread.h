//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------

#include <Classes.hpp>

 class THsearch : public TThread
		 {
			 int Zmienna_testowa; 				// Przyk�adowa zmienna
			 TNotifyEvent __fastcall OnbtClick(TObject *Sender);

			 void __fastcall Search();

		//	 int monitor();                      // numer seryjny monitora
		//	 int bios();                         // data biosu
		//	 int drive();						// numer seryjny dysku

			 void __fastcall Execute();				// G��wna procedura dzia�ania w�tku

		 public:

		//	 void sth();
			 __fastcall THsearch(bool CreateSuspended); // Tworzenie w�tku
			 __fastcall ~THsearch();                     	// Niszczenie w�tku
		 };


int Startuj_Watek( int );
int Rozlacz_Watek( int );

//---------------------------------------------------------------------------

#endif
