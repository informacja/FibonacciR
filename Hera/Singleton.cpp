//---------------------------------------------------------------------------

#pragma hdrstop

#include "Singleton.h"

#include "Unit1.h"
#include "Akcje.h"
// poniøej inicjalizacja

	class License_validate;
	   // there IMAGE Exstern class Fibonacci

//---------------------------------------------------------------------------

 Singleton::Singleton () {                                                      // WSKAèNIKI

	License = NULL;

	unique_ptr<wchar_t> buffer(new wchar_t[30]);
	GetSystemWindowsDirectory(buffer.get(), 30);                                // pobieranie úcieøki do %windir%
	WinDir = buffer.get();

	iconlist_large->BkColor = clWhite;
	iconlist_small->BkColor = clWhite;

 }

//---------------------------------------------------------------------------

	String S::WinDir = GetWinDir(S::WinDir);
	TStatusBar *Singleton::ptr = NULL;

	TImageList *S::iconlist_small = NULL;
	TImageList *S::iconlist_large = NULL;

	Times  S::T(NULL);                                                          // miara czasu

	unsigned S::ICO_DATA 		= 2;
	unsigned S::ICO_ZONE_ID		= 3;

//   	bool S::NoData 				= Form2->CheckBoxNoDATA->Checked;


	String S::Fr 				= "###0.0";		// Format zapisu do pliku
	double S::increment_value	= 0.2;          // o ile bÍdzie in/dekrementowana wartoúÊ
//	bool *S::save_calc			= 0;		   	// zapis wynikÛw do pliku String S::NAMEcalc

	bool S::Activated          	= false;       	// czy aktywoano produkt
	bool S::ProVersion			= false;       	// wersja pro
	bool S::SaveToReg			= false;		// zapis do rejestru

	String S::NAMEcalc 			= "Wyniki";    	// nazwa pliku do zapisu obliczeÒ
	String S::NAMElog 			= "LogFibo";    // nazwa pliku log
	String S::NAMEscreen 		= "FiboScreen";	// nazwa pliku screena
	String S::FirmName          = "Hera";
	String S::ProductName		= "FibonacciR";

	unsigned S::BREAK_SEARCH 	= 100;	   		// kiedy przerywa wyszukiwanie i pryta czy kontynuowaÊ
	unsigned char S::MAX_DEPTH 	= 5;   			// g≥ÍbokoúÊ przeszukiwania podfolderÛw
	String S::FiltrSearch		= "*.*";       	// filtr przy wyszukiwaniu

	String S::test 				= "C:\\windows";	// nazwa pliku screena
	bool S::Del_only_one_sign  	= true;			// usuwanie po 1-nym znaku
//	int S::ImgIndexSync        	= 20;			// nr indeksu z ikonπ synchronizacji

	bool S::sDirectionSort 		= false;      	// kierunek sortowania

// public:

	License_validate *S::License	= NULL;	  	// globalny wskaünik na wπtek

//		S::point_array.push_back();
//	vector<pos> point_array[0].x = 0;     +
//	vector<pos> S::point_array[0] = { 0 } ;
//	 = {0};




//---------------------------------------------------------------------------

 void S::ProgressBarStyle(bool ver, bool mar) {

	FibonacciR->ProgressBar1->Orientation = (ver) ? pbVertical : pbHorizontal;

	FibonacciR->ProgressBar1->Style = (mar) ? pbstMarquee : pbstNormal;
 }
//---------------------------------------------------------------------------

	bool S::canData() { return Form2->CheckBoxNoDATA->Checked; 	 }
	bool S::canZID()  { return Form2->CheckBoxZoneId->Checked;	 }
	bool S::canHide() { return Form2->CheckBoxHideData->Checked; }

//---------------------------------------------------------------------------

	void S::Status(String T, unsigned I, bool h) {

		if (h)	FibonacciR->StatusBar1->Hint = T; // zmienia podpowiedü;

		else 	FibonacciR->StatusBar1->Panels->Items[I]->Text = T;
	}

//---------------------------------------------------------------------------
	AnsiString S::BreakQuest() {

		unique_ptr<AnsiString>a(new AnsiString(S::BREAK_SEARCH));
		(*a).Insert("Znaleüono ", 1);
		(*a).Insert(" plikÛw.\n\nSzukaÊ dalej?", (*a).Length() + 1);

		return *a;
	}

//---------------------------------------------------------------------------

	void S::Save( bool save )
	{
		Form2->CheckBoxSave->Checked = save;
		FibonacciR->CheckBoxZapisz->Checked = save;
		FibonacciR->CheckBoxZapiszF->Checked = save;

		Form2->CheckBoxLegendInFile->Enabled = save;
	}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


#pragma package(smart_init)
