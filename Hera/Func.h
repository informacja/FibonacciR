#pragma hdrstop

#include "Singleton.h"
#include "from_internet.h"

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
#include <Mmsystem.h>    // timeGetTime()
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shellapi.h>
//#include <winbase.h>
#include <memory>
#include <clipbrd.hpp>
//#include "adCpuUsage.hpp"
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

	bool Copyfile2(String ExistFilePath, String NewFilePath);                   // kopiuje pliki

	// STRINGI

	String TrimT( AnsiString to_erase_space );                             		// usuwa wszystkie spacje (TrimTotal)

//	void TrimTptr( AnsiString *to_erase_space );                                   // jak powy¿ej ale przez wskaŸnik

	bool Find(String *where, char* what);

	int FindOut(String where, String what, ... );

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



	// DATA SEARCH

	String Search(TListView *lista, String *Dir, String typ = "",                // wyœwietla pliki na liœcie z podanym typem(rozszerzenie),
		unsigned counter = 0, unsigned char depth_subfolder_searching = 0);     // dwóch ostatnich parametrów siê nie u¿ywa(rekursja funkcji)

	unsigned FindStream(TListView *list,String *Patch, unsigned *n);            // szuka strumieni alternatywnych(ADS)

	String SearchStream(TListView *lista, String Dir, String typ = "",          // przeszukuje rekurencyjnie wartoœæ Dir
		unsigned counter = 0, unsigned char depth_subfolder_searching = 0);     // i wywo³uje powy¿sz¹ funkcjê

	unsigned short TypeFileIcon(String *Path, TListView *List,  bool ExstensionOnly_0 = 0); // szuka ikon do plików ostatni parametr na potrzeby strumieni alternatywnych (dopasowanie ikony na podstawie rozszerzenia)                                                      // zwraca numer ikony do rozszerzenia jeœli nie znajdzie -1

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


//---------------------------------------------------------------------

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
//	   strcpy(sFileName, "D:\\Builder\\FibonacciR\\Win32\\Debug\\Fibonacci.exe");
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
//	Memo->Add(Format("%s: %s", vr, 2));
	 }
	}

   }
  }
  delete[] pVersionInfo;
 }
}

 //---------------------------------------------------------------------

 void GetAllFileVersionInformation(char *ModulePath, TListView *list)
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
 TListItem *ListIt;

 if(ModulePath == NULL) GetModuleFileNameA(NULL, sFileName, 1024); // je¿eli NULL pobierz œcie¿kê dostêpu do tego pliku
 else strcpy(sFileName, ModulePath);
//	   strcpy(sFileName, "D:\\Builder\\FibonacciR\\Win32\\Debug\\Fibonacci.exe");
 DWORD dwInfoSize = GetFileVersionInfoSizeA((LPSTR)sFileName, &dwHandlev);
 if(dwInfoSize)
 {
  pVersionInfo = new LPVOID[dwInfoSize];
  if(GetFileVersionInfoA((char*)(LPCTSTR)sFileName, dwHandlev, dwInfoSize, pVersionInfo))
  {
   if(VerQueryValueA( pVersionInfo, "\\VarFileInfo\\Translation", &lpStr1, &dwLength))
   {
	wTmp = (WORD*)lpStr1;

	for(int i = 0; i < 10; i++)
	{
	 sprintf(sTmp, ("\\StringFileInfo\\%04x%04x\\" + KeyName[i]).c_str(), *wTmp, *(wTmp + 1));
//	 showme(sTmp, ("\\StringFileInfo\\%04x%04x\\" + KeyName[i]).c_str(), *wTmp, *(wTmp + 1))
	 if(VerQueryValueA(pVersionInfo, sTmp, &lpStr2, &dwLength))
	 {
//	  TVarRec vr[] = {plInfoStr[i], (LPSTR)lpStr2};
	  LogSave(plInfoStr[i] + (LPSTR)lpStr2);
//	  Memo->Add(Format("%s: %s", vr, 2));
int size_needed = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpStr2, -1, NULL, 0);
wchar_t *buffer = new wchar_t[size_needed];
MultiByteToWideChar(CP_UTF8, 0, (LPCCH)lpStr2, -1, buffer, size_needed);

	ListIt = list->Items->Add();
	ListIt->Caption = plInfoStr[i] ;
	ListIt->SubItems->Add(  buffer );
//	ListIt->SubItems->AddStrings( (TStrings*)lpStr2 ) ;

//	Memo->Add(Format("%s: %s", vr, 2));
	 }
	}

   }
  }
  delete[] pVersionInfo;
 }
}

//---------------------------------------------------------------------

//String GetFileVersionInfo(char *ModulePath, String KeyName)
//{
// LPVOID lpStr1 = NULL, lpStr2 = NULL;
// WORD* wTmp;
// DWORD dwHandlev = NULL;
// UINT dwLength;
// char sFileName[1024] = {0};
// char sTmp[1024] = {0};
// String sInfo;
// LPVOID* pVersionInfo;
//
// if(ModulePath == NULL) GetModuleFileNameA(NULL, sFileName, 1024);
// else strcpy(sFileName, ModulePath);
//
// DWORD dwInfoSize = GetFileVersionInfoSizeA((char*)(LPCTSTR)sFileName, &dwHandlev);
// if(dwInfoSize)
// {
//  pVersionInfo = new LPVOID[dwInfoSize];
//  if(GetFileVersionInfoA((char*)(LPCTSTR)sFileName, dwHandlev, dwInfoSize, pVersionInfo))
//  {
//   if(VerQueryValueA(pVersionInfo, "\\VarFileInfo\\Translation", &lpStr1, &dwLength))
//   {
//	wTmp = (WORD*)lpStr1;
//	sprintf(sTmp, AnsiString("\\StringFileInfo\\%04x%04x\\" + KeyName).c_str(), *wTmp, *(wTmp + 1));
//	if(VerQueryValueA(pVersionInfo, sTmp, &lpStr2, &dwLength)) sInfo = (LPSTR)lpStr2;
//   }
//  }
//  delete[] pVersionInfo;
// }
// return sInfo;
//}	
  namespace my
{

//extern "C" __declspec(dllimport) bool FindNextStreamW(HANDLE hFindStream, LPVOID lpFindStreamData);
//--------------------------------
bool FindNextStreamW_Linked( HANDLE hFindStream, LPVOID lpFindStreamData )
{
 HANDLE DLLHandle = LoadLibraryA("kernel32.dll"); // Nale¿y podaæ œcie¿kê dostêpu do biblioteki, mo¿e byæ wzglêdna lub bezwzglêdna, nie musi znajdowaæ siê w tym samym katalogu co program
 int y;
 if(DLLHandle != NULL) // jeœli biblioteka istnieje zostanie wykonane odpowiednie dzia³anie.
 {
  typedef bool(*aAbout)( HANDLE, LPVOID ); // Deklaracja wskaŸnika do funkcji.
  /*
   1. Jeœli funkcja, któr¹ wywo³ujemy jest typu woid, czyli nie zwraca ¿adnej wartoœci, jak w przyk³adzie
   void About(AnsiString pName) to deklaracjê wskaŸnika do tej funkcji poprzedzamy tylko s³owem typedef,
   jeœli jest to funkcja zwracaj¹ca np. wartoœæ typu int to równie¿ wystarczy tylko typedef, jeœli jednak
   mamy tak¹ funkcjê AnsiString AddFile()to po s³owie typedef nale¿y podaæ typ zwracanej przez funkcjê
   wartoœci, czyli np: typedef AnsiString(aAddFile)();
   2. W nawiasie wystêpuj¹cym po deklaracji funkcji podajemy typ pobieranych przez funkcjê argumentów,
   czyli jak w przyk³adzie void About(AnsiString pName) podana zostaje wartoœæ AnsiString:
   typedef (*aAbout)(AnsiString).
  */

  aAbout About = (aAbout)GetProcAddress( (HINSTANCE__*)DLLHandle, "_FindNextStreamW");

  if(About != NULL) // jeœli funkcja istnieje to jest wywo³ywana.
	y = About( hFindStream, lpFindStreamData );
 }
 else // jeœli nie znaleziono biblioteki.
 {
  ShowError("Nie znaleziono wymaganej biblioteki 'kernel32.dll'");
 }
 FreeLibrary((HINSTANCE__*)DLLHandle); // usuniêcie biblioteki z pamiêci, gdy jest ju¿ zbêdna.
 return y;
}


//--------------------------------

//extern "C" __declspec(dllimport) HANDLE  FindFirstStreamW( LPCWSTR 				,
//														STREAM_INFO_LEVELS 		,
//														LPVOID             		,
//														DWORD
//													  );


HANDLE  FindFirstStreamW_Linked( LPCWSTR lpFileName, STREAM_INFO_LEVELS InfoLevel, LPVOID lpFindStreamData, DWORD dwFlags )
{

 HANDLE DLLHandle = LoadLibraryA("kernel32.dll"); // Nale¿y podaæ œcie¿kê dostêpu do biblioteki, mo¿e byæ wzglêdna lub bezwzglêdna, nie musi znajdowaæ siê w tym samym katalogu co program
 HANDLE y;
 if(DLLHandle != NULL) // jeœli biblioteka istnieje zostanie wykonane odpowiednie dzia³anie.
 {
  typedef HANDLE(*aAbout)( LPCWSTR, STREAM_INFO_LEVELS, LPVOID, DWORD ); // Deklaracja wskaŸnika do funkcji.
  /*
   1. Jeœli funkcja, któr¹ wywo³ujemy jest typu woid, czyli nie zwraca ¿adnej wartoœci, jak w przyk³adzie
   void About(AnsiString pName) to deklaracjê wskaŸnika do tej funkcji poprzedzamy tylko s³owem typedef,
   jeœli jest to funkcja zwracaj¹ca np. wartoœæ typu int to równie¿ wystarczy tylko typedef, jeœli jednak
   mamy tak¹ funkcjê AnsiString AddFile()to po s³owie typedef nale¿y podaæ typ zwracanej przez funkcjê
   wartoœci, czyli np: typedef AnsiString(aAddFile)();
   2. W nawiasie wystêpuj¹cym po deklaracji funkcji podajemy typ pobieranych przez funkcjê argumentów,
   czyli jak w przyk³adzie void About(AnsiString pName) podana zostaje wartoœæ AnsiString:
   typedef (*aAbout)(AnsiString).
  */

  aAbout About = (aAbout)GetProcAddress( (HINSTANCE__*)DLLHandle, "_FindFirstStreamW");

  if(About != NULL) // jeœli funkcja istnieje to jest wywo³ywana.
	y = About( lpFileName, InfoLevel, lpFindStreamData, dwFlags );
 }
 else // jeœli nie znaleziono biblioteki.
 {
  ShowError("Nie znaleziono wymaganej biblioteki 'kernel32.dll'");
 }
 FreeLibrary((HINSTANCE__*)DLLHandle); // usuniêcie biblioteki z pamiêci, gdy jest ju¿ zbêdna.
 return y;
}

}







	#endif
