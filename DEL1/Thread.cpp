//---------------------------------------------------------------------------

#pragma hdrstop

#include "Thread.h"

#include "Unit1.h"


//---------------------------------------------------------------------------

 __fastcall THsearch::THsearch( bool CreateSuspended ) : TThread( CreateSuspended ) {};	// Tworzenie w¹tku

//---------------------------------------------------------------------------

__fastcall THsearch::~THsearch()  { }

//---------------------------------------------------------------------------

void __fastcall THsearch::Execute()
{

//	while( !this->Terminated )	// Nieskoñczona pêtla dzia³ania w¹tku. Chyba, ¿e j¹ przerwiemy np. Terminate() - patrz funkcja niszcz¹ca w¹tek
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


	while( !(*filtrbuff).IsEmpty() ) {                                          // dopuki s¹ filtry wyszukiwania

//		if ( (*filtrbuff)[0] == ';' )  (*filtrbuff).Delete(1,1);                // usuwanie œrednika jeœli pierwszy

		if ( (*filtrbuff).LastDelimiter(";") ) {                                // jeœli jest œrednik

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





































int g_A;	// WyobraŸ sobie, ¿e to jest jakiœ pewien obszar pamiêci, który mo¿e byæ wspó³dzielony przez w¹tki
int g_B;    // WyobraŸ sobie, ¿e to jest jakiœ inny   obszar pamiêci, który mo¿e byæ wspó³dzielony przez w¹tki



void Dane_1( int X ) // Funkcja testowa - operacje na danych wspó³dzielonych - wyobraŸ sobie, ¿e tak jest ;)
{
//	Sekcja_krytyczna_DANE_1.Wywolanie(  true );	// Zatrzaskujemy sekcjê - patrz kod w innym pliku - nie da siê wejœæ drugi raz ju¿ tutaj
												// Nie wierzysz, to "zadebuguj" sobie inny w¹tek i zobaczysz, ¿e inny w¹tek bêdzie czeka³, dopóki nie zwolnisz sekcji pierwszym w¹tkiem
		g_A = X;

//	Sekcja_krytyczna_DANE_1.Wywolanie( false );	// Zwalniamy sekcjê - patrz kod w innym pliku - mo¿na wejœæ kolejny raz ju¿ tutaj
}

void Dane_2( int Y ) // Funkcja testowa - operacje na danych wspó³dzielonych - wyobraŸ sobie, ¿e tak jest ;)
{
//	Sekcja_krytyczna_DANE_2.Wywolanie(  true );	// Zatrzaskujemy sekcjê - patrz kod w innym pliku - nie da siê wejœæ drugi raz ju¿ tutaj
												// Nie wierzysz, to "zadebuguj" sobie inny w¹tek i zobaczysz, ¿e inny w¹tek bêdzie czeka³, dopóki nie zwolnisz sekcji pierwszym w¹tkiem
		g_B = Y;

//	Sekcja_krytyczna_DANE_2.Wywolanie( false ); // Zwalniamy sekcjê - patrz kod w innym pliku - mo¿na wejœæ kolejny raz ju¿ tutaj
}

//---------------------------------------------------------------------------
class cTH_Watek : public TThread 		// TThread zdaje siê domyslnie jest w <vcl.h>
{
	private:
		int Zmienna_testowa;				// Przyk³adowa zmienna

		int Metoda_testowa();				// Przyk³adowa metoda

		void __fastcall Testowe_wyswietlenie();	// Przyk³adowa metoda wyœwietlaj¹ca coœ na g³ównej formie

		void __fastcall Execute();				// G³ówna procedura dzia³ania w¹tku

	public:

		__fastcall  cTH_Watek( bool CreateSuspended );	// Tworzenie w¹tku
		__fastcall ~cTH_Watek();                     	// Niszczenie w¹tku
};

//---------------------------------------------------------------------------

cTH_Watek *thWatek[ 2 ] = { NULL, NULL };  	// Globalny wskaŸnik na w¹tek i jego metody
											// Tutaj testowo dwa w¹tki (tablica ze wskaŸnikami na nie)

//---------------------------------------------------------------------------

int Startuj_Watek( int Nr )
{
	if( thWatek[ Nr ] == NULL )		// Jeœli w¹tku nie ma, to go stwórz
	{
		thWatek[ Nr ]  = new cTH_Watek( true );	// Tutaj tworzymy w¹tek, stworzony w¹tek jest uœpiony

		if ( thWatek[ Nr ] == NULL ) 		// Sprawdzamy, czy w¹tek uda³o siê stworzyæ poprawnie
		{
			ShowMessage( "Nie mo¿na stworzyæ w¹tku!" );
		}
		else
		{
			thWatek[ Nr ]->Start();		// Startujemy w¹tek do dzia³ania
		}
	}

	return 0;
}
//---------------------------------------------------------------------------

int Rozlacz_Watek( int Nr )
{
	if( thWatek[ Nr ] != NULL )			// Jeœli w¹tek istnieje, to go zamykamy (kolejne operacje)
	{
		thWatek[ Nr ]->Terminate(); 	// Wymuszamy zamkniêcie w¹tku
		thWatek[ Nr ]->WaitFor();     	// Czekamy, a¿ w¹tek siê zamknie (uruchomi wszystkie destruktory, itp.)

		delete thWatek[ Nr ]; 			// Kasujemy pamiêæ obiektu
		thWatek[ Nr ] = NULL;         	// Zerujemy wskaŸnik (¿eby nastepnym razem móc znów w³¹czyæ ten w¹tek, bo po NULL sprawdzamy, czy w¹tej jest, czy go nie ma)
	}

	return 0;
}

//---------------------------------------------------------------------------

void __fastcall cTH_Watek::Testowe_wyswietlenie()
{
	FibonacciR->Memo1->Text = IntToStr( Zmienna_testowa );
}



// G³ówne serce w¹tku
void __fastcall cTH_Watek::Execute()
{
	// Mo¿emy jeszcze coœ zrobiæ przed uruchomieniem g³ównej pêtli w¹tku, to w tym miejscu

	Zmienna_testowa = 0;

	while( !this->Terminated )	// Nieskoñczona pêtla dzia³ania w¹tku. Chyba, ¿e j¹ przerwiemy np. Terminate() - patrz funkcja niszcz¹ca w¹tek
	{
		Metoda_testowa();

		Synchronize( &Testowe_wyswietlenie ); 	// Metody i inne operacje ingeruj¹ce w inny w¹tek, np. g³ówn¹ formê
												// powinny byæ uruchamiane przez "Synchronize" - mechanizm w¹tków synchronizuje
												// sobie wtedy dostêp do pamiêci, ¿eby nie by³o konfliktu, itp. operacje mog¹ce spowodowaæ konflikt.
												// Metody do synchronizacji musz¹ byæ "__fastcall", inaczej nie zadzia³a
												// W praktyce program sam sobie ustawia "sekcjê krytyczn¹" na te obiekty (nawet jej nie widzimy), nie musimy robiæ jej rêcznie
		Sleep( 5 );
	}
}

//---------------------------------------------------------------------------
// Konstruktor, nic szczególnego poza uœpieniem w¹tku przy jego stworzeniu
__fastcall cTH_Watek::cTH_Watek( bool CreateSuspended ) : TThread( CreateSuspended )
// Tworzymy w¹tek, ale go usypiamy na starcie, przy póŸniejszym w³¹czeniu (metoda Start() ) zadzia³a od razu (tylko siê "obudzi")
// Poza tym z ró¿nych przyczym mo¿na nie stworzyæ w¹tku poprawnie przy próbie jego tworzenia, wiêc lepiej, ¿eby by³ uœpiony w takim wypadku :)
{

}
//---------------------------------------------------------------------------
// Destruktor, nic szczególnego w tym wypadku
__fastcall cTH_Watek::~cTH_Watek()
{

}


//---------------------------------------------------------------------------
// Przyk³adowa metoda w¹tku
int cTH_Watek::Metoda_testowa()
{
	int a, b, c;	// Zmienne pomocnicze, ¿eby czymœ zape³niæ pêtlê

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
