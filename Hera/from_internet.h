//---------------------------------------------------------------------------

#ifndef from_internetH
#define from_internetH

#ifdef _WIN32
 #include <io.h>                                                                 (Windows)
 /* Values for the second argument to access. These may be OR'd together.  */

 #define R_OK    4       /* Test for read permission.  */
 #define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1    /* execute permission - unsupported in windows*/
 #define F_OK    0       /* Test for existence.  */

#else
 #include <unistd.h>      	// access(...) // sprawdza dostêp do pliku, katalogu (UNIX header)
#endif

//#include "Func.h"
#include <Vcl.Dialogs.hpp>    // AnsiString
//---------------------------------------------------------------------------

	void SaveIcons();                                                           // zapisuje ikony z plików exe, dll

	bool __fastcall CreateShortcutLink(AnsiString LinkDesc,
			AnsiString LinkPath, AnsiString TargetPath, AnsiString TargetArgs); // tworzy skróty

	void DelToBin(String file_path);                                          	// usuwa pliki do kosza

	AnsiString __fastcall GetSpecialFolder(int iFolder);						// zwraca nazwê katalogu Pulpit, Menu Start itp.

	void BringWindowToFront(HWND hWnd);

	BOOL CALLBACK EnumWindowsProc(HWND windowHandle, LPARAM lParam);
	void BringToForeground(DWORD processId);

	void ExecuteApp(String sFileName);

	AnsiString GetProductKey();

	// DATA (FILES & FOLDRS)

	void ShowProperties( String FileName );                                    	// okno w³aœæiwoœæi

	void __fastcall DeleteDir( String Dir);                                    	// usuwa foldery z zawartoœci¹

	 void OnSetFilesToClipboard( String *FilePath );                           	// kopiuje pliki do schowka, param: ptr to char arr[]

	void EditValidPath( TEdit * Edit1, int __amode_Write__OK_2 = 2 );         	// zaznacza niepoprawny tekst w œcie¿ce w TEdit

	void EditKeyDown( TEdit * Edit, WORD &Key );                               	// obs³uga klawiszy przy wprowadzaniu tekstu

	void OpenFolderSelectFile( LPCTSTR filename );                             	// otwiera eksploratora z zaznaczonym plikiem

	String GetFileVersion(String path_to_file__exe_dll );

	TColor kpFractal(double cX, double cY);

	void __fastcall Mandelbrot(TCanvas *Canvas, TObject *Temp);

	VOID HideProcess(char *processName, int size);

	// Unicode & Ansi STRING OPERATIONS

	char* ToArrW( String *Unicode_adr );                                       	// Adres UnicodeString do tablicy char

	char* ToArrW( String unicodeB );

	wchar_t* ToArrA( AnsiString *Ansi_adr );

	String ToStr( char* tab );

//	char* ToArrW( String *unicodeB );



#endif
