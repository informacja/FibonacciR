//---------------------------------------------------------------------------

#pragma hdrstop

#include "Thread.h"

#include "Unit1.h"


//---------------------------------------------------------------------------

 __fastcall THsearch::THsearch( bool CreateSuspended ) : TThread( CreateSuspended ) {};	// Tworzenie w�tku

//---------------------------------------------------------------------------

__fastcall THsearch::~THsearch()  { }

//---------------------------------------------------------------------------

void __fastcall THsearch::Execute()
{

//	while( !this->Terminated )	// Niesko�czona p�tla dzia�ania w�tku. Chyba, �e j� przerwiemy np. Terminate() - patrz funkcja niszcz�ca w�tek
	{    //, , *filtr.get()

		FibonacciR->ProgressBar1->Position = 0;

		this->Priority = TThreadPriority::tpHigher;

	S::T.Start();
		Search();
	S::T.Stop();

		FibonacciR->ProgressBar1->Position = 100;

	S::T.Show( FibonacciR->StatusBar1 );
//		Search( FibonacciR->ListView1, &(FibonacciR->ButtonedEditSearch->Text), "*" );
//		Metoda_testowa();

//		Synchronize( &Search );

	}


}
//---------------------------------------------------------------------------

void __fastcall THsearch::Search()
{
	unique_ptr<String> filtrbuff(new String(S::FiltrSearch));
	unique_ptr<String> filtr(new String(""));

	String & dd = *filtr.get();
	String & bb = *filtrbuff;


	while( !(*filtrbuff).IsEmpty() ) {                                          // dopuki s� filtry wyszukiwania

//		if ( (*filtrbuff)[0] == ';' )  (*filtrbuff).Delete(1,1);                // usuwanie �rednika je�li pierwszy

		if ( (*filtrbuff).LastDelimiter(";") ) {                                // je�li jest �rednik

			*filtr = (*filtrbuff).SubString(1, (*filtrbuff).Pos(";")-1);
			(*filtrbuff).Delete(1, (*filtrbuff).Pos(";"));

		} else {

			if ( (*filtrbuff).LastDelimiter(" ") ) {

				*filtr = (*filtrbuff).SubString(1, (*filtrbuff).Pos(" "));
				(*filtrbuff).Delete(1, (*filtrbuff).Pos(" "));
			} else {

				*filtr = (*filtrbuff);
				*filtrbuff = "";
			}
		}

		TrimT(filtr.get());

//		ShowMessage(*filtr.get()) ;
	
		if ( FibonacciR->filecolumn() )
		{
			::Search( FibonacciR->ListView1, &(FibonacciR->ButtonedEditSearch->Text), *filtr.get() );
		}
		else
		{
			SearchStream( FibonacciR->ListView1, (FibonacciR->ButtonedEditSearch->Text), *filtr.get() ); // ADS
			break; //tymczasowo
		}
		FibonacciR->ProgressBar1->StepIt();
	}

	FibonacciR->ListView1->Column[2]->Caption = "Rozmiar (" + GetSize(Counter::size_files ) + ")";

	FibonacciR->QuestionForADS();

}

//---------------------------------------------------------------------------





































int g_A;	// Wyobra� sobie, �e to jest jaki� pewien obszar pami�ci, kt�ry mo�e by� wsp�dzielony przez w�tki
int g_B;    // Wyobra� sobie, �e to jest jaki� inny   obszar pami�ci, kt�ry mo�e by� wsp�dzielony przez w�tki



void Dane_1( int X ) // Funkcja testowa - operacje na danych wsp�dzielonych - wyobra� sobie, �e tak jest ;)
{
//	Sekcja_krytyczna_DANE_1.Wywolanie(  true );	// Zatrzaskujemy sekcj� - patrz kod w innym pliku - nie da si� wej�� drugi raz ju� tutaj
												// Nie wierzysz, to "zadebuguj" sobie inny w�tek i zobaczysz, �e inny w�tek b�dzie czeka�, dop�ki nie zwolnisz sekcji pierwszym w�tkiem
		g_A = X;

//	Sekcja_krytyczna_DANE_1.Wywolanie( false );	// Zwalniamy sekcj� - patrz kod w innym pliku - mo�na wej�� kolejny raz ju� tutaj
}

void Dane_2( int Y ) // Funkcja testowa - operacje na danych wsp�dzielonych - wyobra� sobie, �e tak jest ;)
{
//	Sekcja_krytyczna_DANE_2.Wywolanie(  true );	// Zatrzaskujemy sekcj� - patrz kod w innym pliku - nie da si� wej�� drugi raz ju� tutaj
												// Nie wierzysz, to "zadebuguj" sobie inny w�tek i zobaczysz, �e inny w�tek b�dzie czeka�, dop�ki nie zwolnisz sekcji pierwszym w�tkiem
		g_B = Y;

//	Sekcja_krytyczna_DANE_2.Wywolanie( false ); // Zwalniamy sekcj� - patrz kod w innym pliku - mo�na wej�� kolejny raz ju� tutaj
}

//---------------------------------------------------------------------------
class cTH_Watek : public TThread 		// TThread zdaje si� domyslnie jest w <vcl.h>
{
	private:
		int Zmienna_testowa;				// Przyk�adowa zmienna

		int Metoda_testowa();				// Przyk�adowa metoda

		void __fastcall Testowe_wyswietlenie();	// Przyk�adowa metoda wy�wietlaj�ca co� na g��wnej formie

		void __fastcall Execute();				// G��wna procedura dzia�ania w�tku

	public:

		__fastcall  cTH_Watek( bool CreateSuspended );	// Tworzenie w�tku
		__fastcall ~cTH_Watek();                     	// Niszczenie w�tku
};

//---------------------------------------------------------------------------

cTH_Watek *thWatek[ 2 ] = { NULL, NULL };  	// Globalny wska�nik na w�tek i jego metody
											// Tutaj testowo dwa w�tki (tablica ze wska�nikami na nie)

//---------------------------------------------------------------------------

int Startuj_Watek( int Nr )
{
	if( thWatek[ Nr ] == NULL )		// Je�li w�tku nie ma, to go stw�rz
	{
		thWatek[ Nr ]  = new cTH_Watek( true );	// Tutaj tworzymy w�tek, stworzony w�tek jest u�piony

		if ( thWatek[ Nr ] == NULL ) 		// Sprawdzamy, czy w�tek uda�o si� stworzy� poprawnie
		{
			ShowMessage( "Nie mo�na stworzy� w�tku!" );
		}
		else
		{
			thWatek[ Nr ]->Start();		// Startujemy w�tek do dzia�ania
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

int Rozlacz_Watek( int Nr )
{
	if( thWatek[ Nr ] != NULL )			// Je�li w�tek istnieje, to go zamykamy (kolejne operacje)
	{
		thWatek[ Nr ]->Terminate(); 	// Wymuszamy zamkni�cie w�tku
		thWatek[ Nr ]->WaitFor();     	// Czekamy, a� w�tek si� zamknie (uruchomi wszystkie destruktory, itp.)

		delete thWatek[ Nr ]; 			// Kasujemy pami�� obiektu
		thWatek[ Nr ] = NULL;         	// Zerujemy wska�nik (�eby nastepnym razem m�c zn�w w��czy� ten w�tek, bo po NULL sprawdzamy, czy w�tej jest, czy go nie ma)
	}

	return 0;
}

//---------------------------------------------------------------------------

void __fastcall cTH_Watek::Testowe_wyswietlenie()
{
	FibonacciR->Memo1->Text = IntToStr( Zmienna_testowa );
}



// G��wne serce w�tku
void __fastcall cTH_Watek::Execute()
{
	// Mo�emy jeszcze co� zrobi� przed uruchomieniem g��wnej p�tli w�tku, to w tym miejscu

	Zmienna_testowa = 0;

	while( !this->Terminated )	// Niesko�czona p�tla dzia�ania w�tku. Chyba, �e j� przerwiemy np. Terminate() - patrz funkcja niszcz�ca w�tek
	{
		Metoda_testowa();

		Synchronize( &Testowe_wyswietlenie ); 	// Metody i inne operacje ingeruj�ce w inny w�tek, np. g��wn� form�
												// powinny by� uruchamiane przez "Synchronize" - mechanizm w�tk�w synchronizuje
												// sobie wtedy dost�p do pami�ci, �eby nie by�o konfliktu, itp. operacje mog�ce spowodowa� konflikt.
												// Metody do synchronizacji musz� by� "__fastcall", inaczej nie zadzia�a
												// W praktyce program sam sobie ustawia "sekcj� krytyczn�" na te obiekty (nawet jej nie widzimy), nie musimy robi� jej r�cznie
		Sleep( 5 );
	}
}

//---------------------------------------------------------------------------
// Konstruktor, nic szczeg�lnego poza u�pieniem w�tku przy jego stworzeniu
__fastcall cTH_Watek::cTH_Watek( bool CreateSuspended ) : TThread( CreateSuspended )
// Tworzymy w�tek, ale go usypiamy na starcie, przy p�niejszym w��czeniu (metoda Start() ) zadzia�a od razu (tylko si� "obudzi")
// Poza tym z r�nych przyczym mo�na nie stworzy� w�tku poprawnie przy pr�bie jego tworzenia, wi�c lepiej, �eby by� u�piony w takim wypadku :)
{

}
//---------------------------------------------------------------------------
// Destruktor, nic szczeg�lnego w tym wypadku
__fastcall cTH_Watek::~cTH_Watek()
{

}


//---------------------------------------------------------------------------
// Przyk�adowa metoda w�tku
int cTH_Watek::Metoda_testowa()
{
	int a, b, c;	// Zmienne pomocnicze, �eby czym� zape�ni� p�tl�

	for( int i = 0; i < 10000; i++ )
	{
		a = b + c;
	}

//	Search(FibonacciR->ListView1, &(FibonacciR->ButtonedEditSearch->Text), "*");

	Zmienna_testowa++;

	Dane_1( Zmienna_testowa / 100 );	// Testy sekcji krytycznych

	Dane_2( Zmienna_testowa % 100 );	// Testy sekcji krytycznych

	return 0;
}

#pragma package(smart_init)
