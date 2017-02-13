#pragma hdrstop

#include "Singleton.h"

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <shellapi.h>
#include <Vcl.Samples.Spin.hpp>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <String>
#include <math.h>
#include <iomanip.h>
#include <fstream.h>
#include <windows.h>
#include <Mmsystem.h>    // timeGetTime()
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shellapi.h>
#include <winbase.h>
#include <memory>
#include <clipbrd.hpp>
#include "adCpuUsage.hpp"
#include <shlobj.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <filectrl.hpp>
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include "cspin.h"
#include <System.ImageList.hpp>
#include <Vcl.FileCtrl.hpp>

  #ifndef FuncH
#define FuncH
//---------------------------------------------------------------------------
															//TODO   class Iniclaize to remowe incluede main project heder file
	// ŒCIE¯KI PLIKÓW

	String AddBeforDot( String FileName, String dopis = "_Kopia" );             // dodaje tekst przed kropk¹

	String Getname( String Path, bool withoutExtension_0 = false );             // zwraca nazwê pliku

	String Getpath( String Path, bool backslash_1 = true );                     // zwraca œcie¿kê do folderu, bool decyduje czy ma byæ backslash na koñcu

	String GetCurrPathAll( String file_name_to_generate = "." );                // zwraca pe³n¹ œciezkê, aktualny katalog (bez backslasha)

	String GetExtension( String FileName, bool with_dot_0 = 0,                  // zwraca rozszerzenie pliku
						  unsigned char MAX_Ext_LENGTH_5 = 35 );

	bool AddParam(String Param_name, String *Path_to_search, bool size_compare_1 = 1); // zapobiega redundancji parametrów

	bool DelParam(String Param_name, String *Path_to_search,           // usuwa wyszystkie wyst¹pieia wybranego parametru
			bool size_compare_1 = 1,bool Delete_all_params_after_slash_0 = 0);  // mo¿liwoœc usuniêcia wszystkiego po pierwszym znaleŸonym slashu

	bool CompareExtension( String Ext1, String Ext2, bool SmartCompare_1 = 1 );	// porównuje rozszerzenia plików, (bool = 1) wielkoœc znaków bez znaczenia

	bool ExistsDir(const String dirName_in);                                    // sprawdza czy podana œcie¿ka to folder

	String IncremFileName( String path );                                       // dopisuje numer do nazwy pliku (przydatne przy kopiowaniu)

	void EditPathValid( TEdit * objectTEdit );                                  // sprawdza czy podana œcie¿ka istnieje

	ifstream::pos_type filesize(char* filename) {                               // rozmiar pliku

		ifstream in( filename, ios::binary | ios::ate);		return in.tellg();
	}

	int Shel(HWND__ * hWnd, const char * lpOperation, const char * lpFile,     // poœredniczy, wyœwietla komunikaty w razie niepowodzenia
				const char * lpParameters, const char * lpDirectory, int nShowCmd);

	AnsiString __fastcall GetSpecialFolder(int iFolder);						// funkcja zwraca nazwê katalogu Pulpit, Menu Start itp.

    bool __fastcall CreateShortcutLink(AnsiString LinkDesc,
	  AnsiString LinkPath, AnsiString TargetPath, AnsiString TargetArgs); 		//funkcja tworz¹ca skróty.

	// STRINGI

	String TrimT( AnsiString to_erase_space );                             		// usuwa wszystkie spacje (TrimTotal)

//	void TrimTptr( AnsiString *to_erase_space );                                   // jak powy¿ej ale przez wskaŸnik

	bool Find(String *where, char* what);

//	int FindOut(String where, String what, ... );
		 #include <cstdio>

// wg standardu C++ nalezy uzywac tego naglowka jesli chce
// sie pracowac z va_start & co.
#include <cstdarg>
                                double srednia( int liczba,...)
{
    va_list argumenty;
    double suma = 0;

    va_start( argumenty, liczba );
    for( int x = 0; x < liczba; x++ )
         suma += va_arg( argumenty, double );

	va_end( argumenty );

	return suma / liczba;
}

int sumuj(int n, ...) {
  // Zmienna pomocnicza typu va_list - za jej pomoca sie
  // odwolujesz to opcjonalnych parametrow.
  va_list parametry;

  // Inicjuje sie ta zmienna za pomoca makra va_start.
  // W drugim parametrze podaje sie ostatnia nie-opcjonalna
  // zmienna (w skrocie, ten kod mowi: "parametry beda
  // opisywac wszystkie zmienne po "n").
  va_start(parametry, n);

  // Teraz mozna z tych zmiennych korzystac.
  int suma = 0;
  for(int i = 0; i < n; i++) {
    // Dodajemy do "sumy" kolejne wartosci opcjonalnych parametrow.
	// Problem jest taki, ze nie jest explicit powiedziane w
	// prototypie funkcji jakie one maja miec typy, wiec musimy
    // ta informacje tutaj przemycic (drugi parametr va_arg).
    // Samo va_arg zwraca wartosc opcjonalnego parametru i
    // przeskakuje na nastepny (czyli przy kolejnym wywolaniu
    // zwroci kolejny parametr).
    suma += va_arg(parametry, int);
  }

  // I na koncu wypada po sobie posprzatac.
  va_end(parametry);

  // Koniec. Zwracamy wynik.
  return suma;
}

int mnozenie(int liczba1, ...) {

    va_list arg;
	int iloczyn = 1;
	int tmp = liczba1;
	va_start (arg, liczba1);

	while(tmp != '\0') {                      //tmp != 0                                     // problem z warunkiem
	ShowMessage(tmp);
        iloczyn *= tmp;
		tmp = va_arg(arg, int);
	}

	va_end (arg);
    return iloczyn;
}

	// INNE PRZYDATNE

	int Toint( double to_rounding );                							// zwraca inta

	AnsiString DigitRewrite( AnsiString ToCleanText, char extended_0 = 0,       // zaawansowana funkcja zwracaj¹ca poprawn¹ wartoœæ liczbow¹
							 short allways_0_Exception_wej_1 = 0 ); 			// Wa¿ne: u¿ywaæ razem z addtoch() przy pracy na TEdit w kolejnoœæi addtoh() póŸniej DigitRewrite(*,1) z wartosci¹ niezerow¹ dla drugiego argumentu

	void addtoh( TEdit *którgo_doda_do_kolejki );                               // funkcja obs³uguj¹ca historiê wprowadzeñ

	static String lastreslut[2];                                                // potrzebne dla powy¿szych funkcji

	void StrToUniqueArr( AnsiString to_copy, unique_ptr<char[]> &buffArray );   // kopiowanie stringa do tablicy unique

	AnsiString GetDataTime( bool data_1=1, bool time_1=1, bool seconds_1=1 );   // zwraca czas okreslony parametrami

	AnsiString GetSize( float SizeInByte, bool Bits_0 = false );                // zwraca rozmiar z skrótowym opisem rozmiaru

	void Wait( unsigned liczba_milisekund );                                  // funkcja wstrzymuj¹ca

	String WhatInClipboard();

	bool CursorAt(HWND hWnd);                                                   // czy kursor nad danym komponentem

	void BringWindowToFront(HWND hWnd);

	void ExecuteApp(String sFileName);

	// DATA SEARCH

	String Search(TListView *lista, String *Dir, String typ = "",                // wyœwietla pliki na liœcie z podanym typem(rozszerzenie),
		unsigned counter = 0, unsigned char depth_subfolder_searching = 0);     // dwóch ostatnich parametrów siê nie u¿ywa(rekursja funkcji)

	unsigned FindStream(TListView *list,String *Patch, unsigned *n);            // szuka strumieni alternatywnych(ADS)

	String SearchStream(TListView *lista, String Dir, String typ = "",          // przeszukuje rekurencyjnie wartoœæ Dir
		unsigned counter = 0, unsigned char depth_subfolder_searching = 0);     // i wywo³uje powy¿sz¹ funkcjê

	unsigned short TypeFileIcon(String *Path, TListView *List, bool ExstensionOnly_0 = 0); // szuka ikon do plików ostatni parametr na potrzeby strumieni alternatywnych (dopasowanie ikony na podstawie rozszerzenia)                                                      // zwraca numer ikony do rozszerzenia jeœli nie znajdzie -1

	// OBS£UGA B£ÊDÓW

	void LogSave( AnsiString komunikat );                    					// zapisuje komunikat do pliku o nazwie zdefiniowaniej przy inicjalizacji programu

	void ShowError( AnsiString statement, Exception *exception = 0,             // automatycznie zapisuje loga i
											TObject *Sender = 0 );              // wyœwietla informacje o b³êdzie

	AnsiString ErrorToText(int LastError, bool ErrorCode_1 = 1,                 // opisuje kod wybranych b³êdów
										  bool SaveLOGfile_0 = 0);              // ErrorCode_1 warunkuje czy w zwarcanej wartoœæi umieszcony bêdziekod szesnastkowy i dzieœêtny

	// Counter

	class Counter {                                                             // klasa przydatna przy zliczaniu (ka¿dy obiekt zaczyna od zera)

//	unsigned ret;

	static unique_ptr<unsigned>b;

	public:

	Counter() { *b = 0; };                                                      // konstruktor

//	~Counter() { *b = 0; };

	Counter(unsigned a) { *b = a; };                                            // konstruktor

	void inkrement()	{ (*b)++; };

	void set( unsigned a) {  *b.get()  = a; }

	unsigned get()	{ return  *b; };

	static long long size_files;

//	void reset() { ret += b; b = 0; };

	};

	unique_ptr<unsigned> Counter::b(new unsigned (0));

	long long Counter::size_files = 0;



	AnsiString GetProductKey();
	void ShowProperties(String FileName);


template <class T> void GetAllFileVersionInformation(char *ModulePath, T *Memo)
{
 const AnsiString KeyName[] = {"CompanyName", "FileDescription", "FileVersion",
       "InternalName", "LegalCopyright", "LegalTradeMarks", "OriginalFileName",
                        "ProductName", "ProductVersion", "Comments", "Cyfbar"};

 const AnsiString plInfoStr[] = {"Firma", "Opis", "Wersja pliku",
                "Nazwa wewnêtrzna", "Prawa autorskie", "Prawne znaki towarowe",
    "Oryginalna nazwa pliku", "Nazwa Produktu", "Wersja Produktu", "Komentarz",
                                             "Pole dodatkowe o nazwie Cyfbar"};

 LPVOID lpStr1 = NULL, lpStr2 = NULL;
 WORD* wTmp;
 DWORD dwHandlev = NULL;
 UINT dwLength;
 char sFileName[1024] = {0};
 char sTmp[1024] = {0};
 LPVOID* pVersionInfo;

 if(ModulePath == NULL) GetModuleFileNameA(NULL, sFileName, 1024); // je¿eli NULL pobierz œcie¿kê dostêpu do tego pliku
 else strcpy(sFileName, ModulePath);
	   strcpy(sFileName, "D:\\Builder\\FibonacciR\\Win32\\Debug\\Fibonacci.exe");
 DWORD dwInfoSize = GetFileVersionInfoSizeA((LPSTR)sFileName, &dwHandlev);
 if(dwInfoSize)
 {
  pVersionInfo = new LPVOID[dwInfoSize];
  if(GetFileVersionInfoA((char*)(LPCTSTR)sFileName, dwHandlev, dwInfoSize, pVersionInfo))
  {
   if(VerQueryValueA( pVersionInfo, "\\VarFileInfo\\Translation", &lpStr1, &dwLength))
   {
    wTmp = (WORD*)lpStr1;

    for(int i = 0; i < 11; i++)
    {
     sprintf(sTmp, ("\\StringFileInfo\\%04x%04x\\" + KeyName[i]).c_str(), *wTmp, *(wTmp + 1));

	 if(VerQueryValueA(pVersionInfo, sTmp, &lpStr2, &dwLength))
	 {
	  TVarRec vr[] = {plInfoStr[i], (LPSTR)lpStr2};
	  LogSave(plInfoStr[i] + (LPSTR)lpStr2);
//	  Memo->Add(Format("%s: %s", vr, 2));
     }
    }

   }
  }
  delete[] pVersionInfo;
 }
}















	#endif
