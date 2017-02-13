//---------------------------------------------------------------------------

#pragma hdrstop

#include "Validation.h"

#include "Singleton.h"
//class Singleton;
//extern Singleton::License;

//---------------------------------------------------------------------------

__fastcall License_validate::License_validate( bool CreateSuspended ) : TThread( CreateSuspended ) {};	// Tworzenie w�tku

//---------------------------------------------------------------------------

__fastcall License_validate::~License_validate() {	};

//---------------------------------------------------------------------------

void __fastcall License_validate::Execute() {

	 Sleep(500);    Beep();

}

//---------------------------------------------------------------------------

int Check_License( )
{
	if( Singleton::License == NULL )		// Je�li w�tku nie ma, to go stw�rz
	{
		S::License  = new License_validate( true );	// Tutaj tworzymy w�tek, stworzony w�tek jest u�piony

		if ( 	S::License == NULL ) 		// Sprawdzamy, czy w�tek uda�o si� stworzy� poprawnie
		{          //Beep();
//			ShowMessage( "Nie mo�na stworzy� w�tku licencji!" );
		}
		else
		{
			S::License->Start();		// Startujemy w�tek do dzia�ania
		}
	}
	// start
//
//	License->sth();

	// przeniesione do sekcji Execute
//		if( License != NULL )			// Je�li w�tek istnieje, to go zamykamy (kolejne operacje)
//	{
//		License->Terminate(); 		// Wymuszamy zamkni�cie w�tku
//		License->WaitFor();     	// Czekamy, a� w�tek si� zamknie (uruchomi wszystkie destruktory, itp.)
//
//		delete License; 			// Kasujemy pami�� obiektu
//		License = NULL;         	// Zerujemy wska�nik (�eby nastepnym razem m�c zn�w w��czy� ten w�tek, bo po NULL sprawdzamy, czy w�tej jest, czy go nie ma)
//	}

	return 0;
}


#pragma package(smart_init)
