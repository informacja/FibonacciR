//---------------------------------------------------------------------------

#pragma hdrstop

#include "Validation.h"

#include "Singleton.h"
//class Singleton;
//extern Singleton::License;

//---------------------------------------------------------------------------

__fastcall License_validate::License_validate( bool CreateSuspended ) : TThread( CreateSuspended ) {};	// Tworzenie w¹tku

//---------------------------------------------------------------------------

__fastcall License_validate::~License_validate() {	};

//---------------------------------------------------------------------------

void __fastcall License_validate::Execute() {

	 Sleep(500);    Beep();

}

//---------------------------------------------------------------------------

int Check_License( )
{
	if( Singleton::License == NULL )		// Jeœli w¹tku nie ma, to go stwórz
	{
		S::License  = new License_validate( true );	// Tutaj tworzymy w¹tek, stworzony w¹tek jest uœpiony

		if ( 	S::License == NULL ) 		// Sprawdzamy, czy w¹tek uda³o siê stworzyæ poprawnie
		{          //Beep();
//			ShowMessage( "Nie mo¿na stworzyæ w¹tku licencji!" );
		}
		else
		{
			S::License->Start();		// Startujemy w¹tek do dzia³ania
		}
	}
	// start
//
//	License->sth();

	// przeniesione do sekcji Execute
//		if( License != NULL )			// Jeœli w¹tek istnieje, to go zamykamy (kolejne operacje)
//	{
//		License->Terminate(); 		// Wymuszamy zamkniêcie w¹tku
//		License->WaitFor();     	// Czekamy, a¿ w¹tek siê zamknie (uruchomi wszystkie destruktory, itp.)
//
//		delete License; 			// Kasujemy pamiêæ obiektu
//		License = NULL;         	// Zerujemy wskaŸnik (¿eby nastepnym razem móc znów w³¹czyæ ten w¹tek, bo po NULL sprawdzamy, czy w¹tej jest, czy go nie ma)
//	}

	return 0;
}


#pragma package(smart_init)
