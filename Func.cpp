#pragma hdrstop
 #undef s
#include "Func.h"
//#include "Unit1.h"
#include "Enum.h"
#include <memory>
#include <process.h>
//#include <boost/thread.hpp>
	#include <Vcl.Dialogs.hpp>

//  #define s ShowMessage
////////////////////////////////////////////////////////////////////////////////
//  ŒCIE¯KI PLIKÓW	//  ŒCIE¯KI PLIKÓW	//  ŒCIE¯KI PLIKÓW	//  ŒCIE¯KI PLIKÓW
////////////////////////////////////////////////////////////////////////////////
String AddBeforDot(String Name, String dopis) {         						// dodaje tekst przed kropk¹

	unique_ptr<short int> pos(new short int);
//	short int *pos = new short int;
	*pos = LastDelimiter('.', Name);

	if (*pos < 1) {                          			 						//jeœli mniejsze  1
		Name.Insert(dopis.c_str(), Name.Length() + 1);
	}
	else {
		Name.Insert(dopis, *pos);
	}
//	delete pos;
	return Name;
}
// ---------------------------------------------------------------------------
String Getname(String path, bool b) { 											// zwraca nazwê pliku

	unique_ptr<short int>pos(new short int(LastDelimiter('\\', path)));

	path.Delete(1, *pos);                                                       // usuwanie ostatniego backslasha

	if (b) { 																	// usuwanie rozszerzenia
		*pos = LastDelimiter('.', path);
		path.Delete(*pos, path.Length() - *pos + 1);
	}

	return path;
}
// ---------------------------------------------------------------------------
 String Getpath( String path, bool b){

 if (DirectoryExists(path)) {

		if (b) {

			 if (LastDelimiter('\\', path) != path.Length()) 	  				//dodawanie backslasha na koñcu jeœli nie ma
			 {
				path.Insert("\\", path.Length()+1);
			 }
		 }
	return path;
 }

	  unique_ptr<short int> pos(new short int);
//	  short int* pos = new short int;

	 *pos = LastDelimiter('\\', path);
	 path.Delete(*pos, 255);      //LUB -1
		 if (b) {                                								//dodawanie backslasha

			 if (LastDelimiter('\\', path) != path.Length()) {  				//dodawanie backslasha na koñcu jeœli nie ma

				path.Insert("\\", path.Length()+1);

			 }
		 }

//	 delete pos;

	return path;

 }
//---------------------------------------------------------------------------
 String GetCurrPathAll(String out) {                                                // nie uda³o siê przerobiæ na unique_ptr

	TCHAR  *buffer = new TCHAR[4096];
//	unique_ptr<TCHAR> buffer(TCHAR[4096]));
//	TCHAR  *b= new TCHAR;

//	b = out.c_str();

	GetFullPathName( out.c_str(),  4096, buffer, 0 );
	out = buffer;

//	delete b;
	delete [] buffer;

	return out;
}
// ---------------------------------------------------------------------------
 String GetExtension(String EXT, bool dot, unsigned char MAX_Ext_LENGTH) {

	 unique_ptr<unsigned int>pos(new unsigned int(EXT.LastDelimiter(".")));      // pozycja kropki

	 if ((EXT.Length() - (*pos)) <= MAX_Ext_LENGTH) {

		 EXT.Delete(1, *pos);

		 if (dot) if (*pos) EXT.Insert(".", 1);                                 // jeœli z kropk¹ jeœli by³a kropka do j¹ wstawia

		 return EXT;
	 }
	 return "";
 }
 // ---------------------------------------------------------------------------
bool CompareExtension(String Ext1, String Ext2, bool lower)
{                   // zwraca true gdy idetyczne

	unique_ptr<String> EXT1(new String(GetExtension(Ext1,1)));
	unique_ptr<String> EXT2(new String(GetExtension(Ext2,1)));

	if ( *EXT1 == "*" || *EXT2 == "*" )   return 1;                 			// jeœli gwiazdka to mo¿e byæ wszystkim

	if ( *EXT1 == ".*") if ( (*EXT2).LastDelimiter(".") ) return 1;             // sprawdza czy plik ma rozrzerzenie po kropce
	if ( *EXT2 == ".*") if ( (*EXT1).LastDelimiter(".") ) return 1;

//		if (*EXT1 == "" || *EXT2 == "") return 1;                           	// jeœli jedno puste zwraca 1

	if (lower) 	return ((*EXT1).LowerCase() == (*EXT2).LowerCase()) ? 1 : 0;    // domyœlnie, wielkoœc liter bez znaczenia

	else return ((*EXT1) == (*EXT2)) ? 1 : 0;                                   // z rozró¿niamiem wielkoœci znaków
}
// ---------------------------------------------------------------------------
 bool AddParam(String Param,String *Path, bool size) {

	if ( size ) { Param = Param.LowerCase(); (*Path).LowerCase(); }             // ujednolicenie rozmiaru tekstu
	if ((Param)[1] != '/') (Param).Insert("/", 1);                           	// dodanie slasha jeœli nie ma

	size = 1;                                                                   // nowy wykorzystanie

		unique_ptr<String>com(new String(*Path));
		unique_ptr<String>buff(new String(0));
		unique_ptr<unsigned>pos(new unsigned((*com).Pos("/")));
		unique_ptr<unsigned>ph(new unsigned((Param).Length()));                	// Param lengtH


	while ( *pos ) {
		 *pos = (*com).LastDelimiter("/");
		 *buff = (*com).SubString(*pos, *ph);
		  if (CompareStr(*buff, Param) == 0 && size)  { size = 0; continue; }   // jeœli ju¿ jest ten parametr w œcie¿ce uruchamiania
		  (*com).Delete(*pos,*ph);
	}

	if (size) {	*Path += " " + Param;  return 1; }
	return 0;
 }
// ---------------------------------------------------------------------------
 bool DelParam(String Param,String *Path, bool size, bool slash) {

	if ( size ) { Param = Param.LowerCase(); (*Path).LowerCase(); }             // ujednolicenie rozmiaru tekstu
	if ( Param[1] != '/') Param.Insert("/", 1);                            	// dodanie slasha jeœli nie ma

		unique_ptr<String>com(new String(*Path));
		unique_ptr<String>buff(new String(0));
		unique_ptr<unsigned>pos(new unsigned((*com).LastDelimiter("/")));
		unique_ptr<unsigned>ph(new unsigned((Param).Length()));                	// Param lengtH
		unique_ptr<bool> b(new bool(0));                                        // jeœli coœ usunie przyjmuje wartoœæ 1

	while ( *pos ) {

		 *buff = (*com).SubString(*pos, *ph);
		  if (!CompareStr(*buff, Param)) {
			*b = 1;
			(*com).Delete(*pos,*ph);
			(*Path).Delete(*pos,*ph);
		  }  																	// jeœli ju¿ jest ten parametr w œcie¿ce uruchamiania
		  else (*com).Delete(*pos ,*ph);

		  *pos = (*com).LastDelimiter("/");
	}

	*pos =  (*Path).LastDelimiter("/");

	if (slash) if (*pos) (*Path).Delete(*pos, 255);

//		ShowMessage( "|"+(*Path)[(*Path).Length()]);
	  while ( (*Path)[(*Path).Length()] == ' ') (*Path).Delete((*Path).Length(),1);

	return *b;                                                                  // true jeœli coœ usun¹³
 }
// ---------------------------------------------------------------------------
 bool ExistsDir(const String dirName_in) {

	unique_ptr<DWORD> ftyp(new DWORD( GetFileAttributesW( dirName_in.w_str()) ));
//  DWORD ftyp = GetFileAttributesW( dirName_in.w_str());
  if (*ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (*ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
 }
// ---------------------------------------------------------------------------
 String IncremFileName(String path) { 											// do przerobiena na wsk

	unique_ptr<String> ext(new String);											// rozszerzenie
	unique_ptr<String> s(new String( ExtractFileName(path) ));                  // nazwa pliku  Or Getpath
	unique_ptr<unsigned int> cp(new unsigned int( LastDelimiter('.', (*s)) ));  // numer kopii

		if (*cp) {

			*ext = ((*s).SubString((*cp), (*s).Length() - (*cp) + 1));
			(*s).Delete(*cp, (*s).Length() - (*cp) + 1);

			*cp = 0;
		}

		if ((*s).SubString((*s).Length() - 2, 1) == '_')                        // sprawdza czy 3 znak od koñca == "_"
		{

			try {
				*cp = (*s).SubString((*s).Length() - 1, 2).ToInt();             // czy ostatnie dwie cyfry to int


			} catch (...) {;}    												//zapobiega wyœwietlaniu komunikatu o b³edzie

			if (*cp) {

				do {
					(*cp)++;
					path = (*s).Delete((*s).Length() - 2, 3) + '_' + FormatFloat("00", *cp);                                 // usuwa poprzedni numer kopi i dodaje nowy

					*s += "_" + FormatFloat("00", *cp);

				} while (FileExists(path));

			} else 	*s += "_01";

		} else 	*s += "_01";

		path = *s + *ext;

		return path;         													//zwraca nazwê pliku
 }
//---------------------------------------------------------------------------
 void EditPathValid(TEdit * Edit1) {

	 if (!DirectoryExists(Edit1->Text) && !FileExists(Edit1->Text)) {
		 Edit1->Color = clBtnFace;
		 // ShowMessage("Podana œcie¿ka nie istnieje popraw j¹ i zastosuj ponownie\n\nJeœli u¿yjesz niepoprawnej œcie¿ki program bêdzie mia³ problem, a jeœli mój program ma problem to ty masz problem\nProblem ");

		 Edit1->SetFocus();

		 unique_ptr<String> str(new String(Edit1->Text) );
		 unique_ptr<short int > pos(new short int( (*str).Length() ));

		 do {

			 (*str).Delete(*pos, 1);
			 (*pos)--;

		 }
		 while ((!DirectoryExists(*str) && !FileExists(*str)) && *pos);

		 Edit1->Perform(EM_SETSEL, *pos, Edit1->Text.Length());
//         throw Exception ("Niepoprawna œcie¿ka");
	 }
	 else 	 Edit1->Color = clWindow;
}
//---------------------------------------------------------------------------
DelToBin(String d){

  SHFILEOPSTRUCT fos;
	fos.hwnd = Application->Handle;
	fos.wFunc = FO_DELETE;
	fos.pFrom = (ExtractFileDir(d).c_str()); 	// nazwa kasowanego pliku, trzeba podaæ pe³n¹ œcie¿kê dostêpu
	fos.fFlags = FOF_ALLOWUNDO; SHFileOperation(&fos);}

// ---------------------------------------------------------------------------

 int Shel(HWND__ * hWnd, const char * lpOperation, const char * lpFile,
				const char * lpParameters, const char * lpDirectory, int nShowCmd) {

	unique_ptr<String> ErrSpec(new String(""));
	unique_ptr<int> ret(new int(0));
//  ShellExecute();

	*ret = (int)ShellExecuteA(hWnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	switch( *ret ) { // Zwyk³y plik

		case 0:                     *ErrSpec = "zabrak³o pamiêci i/lub zasobów systemowych"; break;
		case ERROR_FILE_NOT_FOUND:	*ErrSpec = "plik nie zosta³ znaleziony"; break;
		case ERROR_PATH_NOT_FOUND:  *ErrSpec = "œcie¿ka nie zosta³a odnaleziona"; break;
		case ERROR_BAD_FORMAT:      *ErrSpec = "plik wykonywalny jest nieprawid³owy"; break;
		case SE_ERR_ACCESSDENIED:   *ErrSpec = "dostêp do pliku jest zabroniony"; break;
		case SE_ERR_ASSOCINCOMPLETE:*ErrSpec = "skojarzenie rozszerzenia jest niekompletne lub nieprawid³owe"; break;
		case SE_ERR_DDEBUSY:        *ErrSpec = "zg³oszenie DDE nie mog³o zostaæ przetworzone z powodu zajêtoœci"; break;
		case SE_ERR_DDEFAIL:        *ErrSpec = "wyst¹pi³ b³¹d DDE"; break;
		case SE_ERR_DDETIMEOUT:     *ErrSpec = ""; break;
//		case SE_ERR_FNF:            *ErrSpec = "plik nie zosta³ znaleziony"; break;
		case SE_ERR_DLLNOTFOUND:    *ErrSpec = "nie odnaleziono biblioteki DLL"; break;
		case SE_ERR_OOM:            *ErrSpec = "zabrak³o pamiêci"; break;
		case SE_ERR_NOASSOC:        *ErrSpec = "rozszerzenie nie zosta³o skojarzone z aplikacj¹"; break;
//		case SE_ERR_PNF:            *ErrSpec = "nie odnaleziono œcie¿ki"; break;
		case SE_ERR_SHARE:          *ErrSpec = "nast¹pi³o naruszenie zasad wspó³u¿ytkowania"; break;

		default: ;
	}

	return *ret;
 }
//---------------------------------------------------------------------------

 AnsiString __fastcall GetSpecialFolder(int iFolder)
{
 char Path[MAX_PATH];
 ZeroMemory(Path, MAX_PATH);

 LPMALLOC lpMalloc;
 if(SUCCEEDED(SHGetMalloc(&lpMalloc)))
 {
  LPITEMIDLIST lpidl;
  if(SUCCEEDED(SHGetSpecialFolderLocation(Application->Handle,
                     iFolder, &lpidl)))
  {
	  SHGetPathFromIDListA(lpidl, Path);
      lpMalloc->Free(lpidl);
  }
  lpMalloc->Release();
 }

 return AnsiString(Path);
}
//---------------------------------------------------------------------------

bool __fastcall CreateShortcutLink(AnsiString LinkDesc,
	  AnsiString LinkPath, AnsiString TargetPath, AnsiString TargetArgs) //funkcja tworz¹ca skróty.
{
 CoInitialize(NULL);

 bool retval = false;
 HRESULT hres = 0;
 IShellLink* psl = NULL;
 SetLastError(0);

 LPCLASSFACTORY pcf = NULL;
 hres = CoGetClassObject(CLSID_ShellLink,
                         CLSCTX_INPROC_SERVER,
						 NULL,
                         IID_IClassFactory,
                         (LPVOID*)&pcf);

 if(SUCCEEDED(hres))
 {
  hres = pcf->CreateInstance(NULL,
                             IID_IShellLink,
                             (LPVOID*)&psl);
							 pcf->Release();
 }
 if(SUCCEEDED(hres))
 {
  IPersistFile* ppf = NULL;
	// Ustawianie œcie¿ki, katalogu roboczego i opisu skrótu
  psl->SetPath( ((String)TargetPath).c_str());
  psl->SetArguments( ((String)TargetArgs).c_str());
  psl->SetDescription( ((String)LinkDesc).c_str());
  psl->SetWorkingDirectory( ExtractFilePath(TargetPath).c_str());
  hres = psl->QueryInterface(IID_IPersistFile, &(void*)ppf);

  if(SUCCEEDED(hres))
  {
   wchar_t wsz[MAX_PATH];
   MultiByteToWideChar(CP_ACP, 0, LinkPath.c_str(), -1, wsz, MAX_PATH);
   hres = ppf->Save(wsz, TRUE);
   ppf->Release();
  }
  psl->Release();
  retval = SUCCEEDED(hres);
 }

 switch(hres)
 {
  case S_OK:                  ShowMessage("Utworzono skrót.");                       break;
  case REGDB_E_CLASSNOTREG:   ShowMessage("Niezarejestrowana klasa."); break;
  case E_OUTOFMEMORY:         ShowMessage("Za ma³o miejsca w pamiêci.");             break;
  case E_INVALIDARG:          ShowMessage("Nieprawid³owy parametr.");                break;
  case E_UNEXPECTED:          ShowMessage("Nieoczekiwany b³¹d.");                    break;
  case CLASS_E_NOAGGREGATION: ShowMessage("Nie mo¿na utworzyæ klasy.");              break;
  case E_FAIL:                ShowMessage("Nie mo¿na utworzyæ skrótu.");             break;
  case E_NOTIMPL:             ShowMessage("Nieobs³ugiwany interfejs.");               break;
  default:                    ShowMessage("Nieznany b³¹d.");
 }
 CoUninitialize();
 return retval;
}

////////////////////////////////////////////////////////////////////////////////
// STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  																			  ///
////////////////////////////////////////////////////////////////////////////////
 String TrimT(AnsiString w) {                                                   // Trim Total (usuwa wszystkie puste pola z stringa)

	unique_ptr<unsigned short> rd(new unsigned short( w.LastDelimiter(" ") ));

	  while ( *rd ) {

		w.Delete(*rd, 1);

		*rd = w.LastDelimiter(" ");

	  }

   return w;
 }
//---------------------------------------------------------------------------

 void TrimTptr( AnsiString *w ) {

	unique_ptr<unsigned short> rd(new unsigned short((*w).LastDelimiter(" ") ));

	  while ( *rd ) {

			(*w).Delete(*rd, 1);

			*rd = (*w).LastDelimiter(" ");

	  }
 }

//---------------------------------------------------------------------------
bool Find(String *where,char* w)  {

	do {

//         StrToUniqueArr()

	}while(*where != NULL);

}
//---------------------------------------------------------------------------
 int Toint(double nm) {

  if( nm -static_cast<int>(nm) < 0.5) 	nm = static_cast<int>(nm);

								   else	nm = static_cast<int>(nm)+ 1;

  return nm;

}
//---------------------------------------------------------------------------
// template<typename typ>
//int ToInt(typ liczba) {
//
//	liczba = (liczba -static_cast<int>(liczba) >= 0.5) ?
//
//		static_cast<int>(liczba) + 1 : static_cast<int>(liczba);
//
//	return liczba;
//}

////////////////////////////////////////////////////////////////////////////////
//  INNE PRZYDATNE  //  INNE PRZYDATNE  //  INNE PRZYDATNE  //  INNE PRZYDATNE
////////////////////////////////////////////////////////////////////////////////
AnsiString DigitRewrite(AnsiString w, char e, short a ) {   //przerobiæ by zwraca³o double  /* By w pe³ni wyko¿ystaæ mo¿liwoœci   	(przesówanie przecinka w prawo)	*/
																					/* tej funkcji nale¿y PRZED u¿ycim  	*/
	if ( w == "" )	return 0;                                                       /* umieœciæ wywo³anie fukcji addtoh() 	która zapamiêtuje podane wyniki	*/

	unique_ptr<AnsiString> p(new AnsiString);                                   // wartoœæ zwracana

 try {

	w = StringReplace( w, ".", ",", TReplaceFlags() << rfReplaceAll);           // zamiana kropek na przecinki

	register unique_ptr<char> znak(new char );                     				// komparator, wspó³pracuje z *buff[]
	unique_ptr<short> indekscomma(new short);                                   // pozycja przecinka      (od prawej)
	unique_ptr<short> isdelim(new short);                             			// czy jast delimiter (,) (od lewej)
	unique_ptr<unsigned short> era(new unsigned short(w.Length() )); 	        // do indeks ile do usuniêcia, przypisanie w celu oszczêdnoœci zasobów
	unique_ptr<unsigned short> wyj(new unsigned short(0));                      // pozycja pierwszego od lewej przecinka, bez przpisania zawiera losowe wartoœci
	unique_ptr<unsigned short> Lrindx(new unsigned short(0));                      // pozycja przecinka przy porzednim wywo³aniu funkcji
	unique_ptr<char[]> buff(new char[ *era ]);                              	// bufor tabicy charów do sprawdzenia

	register char tab[] = { ',', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	 StrToUniqueArr( w, buff );													// (w) jest kopiowane do *buff[]

		for (int i = 0; i < *era; i++) { 										// nie jest ' <= ' bo ostatni znak to \0 (koñcowy) oraz liczone od 0

			*znak = buff[i];

			for (int h = 0; h <= 11; h++) {                                     // porównanie wejœcia z zawatoœci¹ *tab[]

				if ( *znak == tab[h]) {

					(*p).Insert(*znak, (*p).Length() + 1);	break;

				} else if (h == 11)	(*wyj)++;                                   // potrzebne do zachowania pozycji przecinka
			}
		}

		*isdelim = (*p).AnsiPos(',');

		*indekscomma = (*p).LastDelimiter(",");

				if (*indekscomma) { 											// usuwanie przecinków

					(*p).Delete(*indekscomma, 1);

					*era = (*p).LastDelimiter(",");

					while (*era) {                                        		// nie mo¿e byæ do while bo niemo¿e nast¹piæ inkrementacja wej

						(*wyj)++;                                               // *wyj jest póŸniej odejmowany przy ustalaniu pozycji przecinka
						*era = (*p).LastDelimiter(",");
						(*p).Delete(*era , 1);
					}
				}

		if ( e ) *Lrindx = lastreslut[1].LastDelimiter(","); 				 // jeœli ostatnio byla u¿yta funkcja addtoh()

		if (w.LastDelimiter(",")) {                                             // jeœli by³ przecinek to ta sekcja go doda

			if (*Lrindx) {

				if (*isdelim > *Lrindx)  {                                     	// jeœli pozycja przecinka(*isdelim) jest wiêksza od poprzedniej(*Lrindx)
ShowError("lastreslut zarejestrowano w DigitalRewrite \n0: " + lastreslut[0] +" \n1: "+ lastreslut[1]);
					 (*p).Insert(',', *indekscomma - *wyj );   //usun¹³em + 1
										  }
				else if (*isdelim < *Lrindx)

					 (*p).Insert(',', *isdelim);

				else if (*indekscomma) 											//jeœli ¿adne z powy¿szych a w prierszym argumencie by³ przecinek

					(*p).Insert(',',  *indekscomma - *wyj + 1);

			} else if (*indekscomma) {										    // jeœli funkcja addtoh prawdopodobnie jest wy³¹czona

			static unique_ptr<unsigned short> last_pos(new unsigned short(0));  // zmienna pamiêtaj¹ca pozycjê ostatniego przcinka

					if ( !*wyj )	(*p).Insert(',', *indekscomma - *wyj );     // jeœli by³ tylko jeden przecinek

					else if ( *last_pos > *isdelim) (*p).Insert(',', *isdelim );

					else if ( *last_pos < *isdelim) (*p).Insert(',', *indekscomma - *wyj );

					else  (*p).Insert(',', *indekscomma - *wyj +1 );

				if ( !*Lrindx )                                                 // jeœli lastreslut[1] ustawiane przez funkcjê addtoh nie zawiera przecinka (czyli zachodzi mo¿liwoœæ ¿e ta funkcja nie zosta³a wywo³ana)

					*last_pos = (*p).LastDelimiter(",");                        // przypisanie zmiennej statycznej pozycji przecinka liczby któr¹ zwraca ta funkcja

			}
		}
	} catch (Exception &exception)	{
			// or throw exception
		ShowError("Wyj¹tek DigitRewrite()",&exception);
		throw &exception;

	} catch (...) {
		ShowError("Error		noname exception\n\nFunkcje.cpp  DigitRewrite()") ;
	}

	return *p;
	                                               				//brak ró¿nicy pomiêdzy *p.get()
//		if ( (p) != 0 )  return *p;         // przez unique_ptr niema dostêpu do adresu
//
//		else {
//
//			ShowError("Funcje.cpp DigitalRewrite(); zwraca 0\n\nSkontaktuj siê a Admistratorem");
//			return 0;
//		}
}
//---------------------------------------------------------------------------
void addtoh(TEdit *wsk) {

	if (lastreslut[0] != lastreslut[1])  lastreslut[1] = lastreslut[0];         //jeœli !s¹ identyczne

	lastreslut[0] = wsk->Text;

}
//---------------------------------------------------------------------------
void StrToUniqueArr (AnsiString w, unique_ptr<char[]> &buff )  {

	 unique_ptr<int> lenght (new int( w.Length() ));							//jest tu bo byly problemy w for()

//  unique_ptr<char[]> buff(new char[*lenght]);

	for (int i = 0; i < *lenght; i++) {

		buff[i] = w.operator [] (1);
		w.Delete(1,1);
	}
//	  ShowMessage( buff.get());
}
// ---------------------------------------------------------------------------
 AnsiString GetDataTime(bool data, bool time, bool sec ) {

	unique_ptr<AnsiString> DT (new AnsiString);

	try {

		*DT = DateTimeToStr(TDateTime::CurrentDateTime());

			if (!sec) 	(*DT).Delete(16, 3);

			if (!time) 	(*DT).Delete(11, 9);

			if (!data)	(*DT).Delete(1, 11);

//		  (*DT).ToInt();               // wyj¹tek

	} catch (Exception &exception)	{
		ShowError(exception.ToString());
	}

	catch(...) {

		ShowError("Nieznany b³¹d funkcji GetDataTime()");
	}

	 return (*DT);
}
// ---------------------------------------------------------------------------
AnsiString GetSize(float SizeInByte, bool Bits) {

	if (Bits) if (SizeInByte >8) SizeInByte /= 8;                               // na bajty

	else return FormatFloat("0.##", SizeInByte) + " b";                         //bity

	unique_ptr<unsigned char> c(new unsigned char(0));
	unique_ptr<String> buff(new String);

	while ( SizeInByte > 1024 && *c < 6) {

		SizeInByte /= 1024;
		(*c)++;
	}

	switch ( *c ) {

	case 0: *buff = "B";  break;                                                // bajty
	case 1: *buff = "KB"; break;                                                // kilobity
	case 2: *buff = "MB"; break;                                                // megabajty
	case 3: *buff = "GB"; break;                                                // gigabajty
	case 4: *buff = "TB"; break;                                                // terabajty
	case 5: *buff = "PB"; break;                                                // petabajty

	default:
	*buff = (Bits) ? "b" : "B";
	}
	  return FormatFloat("0.##", SizeInByte) + " " + *buff;
}
// ---------------------------------------------------------------------------

void __cdecl ThreadProc( void * Args )
{HANDLE hThread ;                          WaitForSingleObject(hThread ,INFINITE );
//Sleep(9999999999999);
//	_endthread();
}

void Wait( unsigned liczba_milisekund ) {

HANDLE hThread =( HANDLE ) _beginthread( ThreadProc, 0, NULL );
//Sleep(500);
WaitForSingleObject( hThread, liczba_milisekund );
//  clock_t a;
//
//  Times b ;  b.Start();
//
//  b.Stop();
//  if (b.Result() > 1000)
//
//  a = clock () + liczba_milisekund /1000 * CLOCKS_PER_SEC ;
//
//  while (clock() < a) {}
}
String WhatInClipboard() {

	if (Clipboard()->HasFormat(CF_TEXT))	  		return "tekst";
	else if (Clipboard()->HasFormat(CF_BITMAP)) 	return "bitmapa";
	else if (Clipboard()->HasFormat(CF_PICTURE))    return "TPicture";
	else if (Clipboard()->HasFormat(CF_WAVE))       return "audio";
	else if (Clipboard()->HasFormat(CF_TIFF))       return "Tiff";
	else if (Clipboard()->HasFormat(CF_SYLK))       return "link symboliczny";
	else if (Clipboard()->HasFormat(CF_METAFILEPICT))return "obraz";
	else if (Clipboard()->HasFormat(CF_HDROP))		return "lista plików (drop)";
	else if (Clipboard()->HasFormat(CF_DSPMETAFILEPICT))return "obraz2";
	else if (Clipboard()->HasFormat(CF_DSPBITMAP))return "bitmap";
//	else if (Clipboard()->HasFormat(CF_METAFILEPICT))return "obraz";
//	CF_HDROP

	else return "Zawartoœæ showka nieznana";

}
// ---------------------------------------------------------------------------

bool CursorAt(HWND hWnd) {

	 unique_ptr<POINT>Cur_Pos(new POINT); 										// pozycja kursora
	 unique_ptr<RECT>Wnd(new RECT); 											// pozycje rogów Edita

	 GetCursorPos(Cur_Pos.get());
	 GetWindowRect( hWnd, Wnd.get());

	 if ((*Wnd).left <= (*Cur_Pos).x) {
		 if ((*Cur_Pos).x <= (*Wnd).right) {

			 (*Cur_Pos).x = true; 											   	// nowe zastosowanie

	 if ((*Wnd).top <= (*Cur_Pos).y) {
		 if ((*Cur_Pos).y <= (*Wnd).bottom) {

			 (*Cur_Pos).y = true; 												// nowe zastosowanie

	 if ((*Cur_Pos).x == 1 && (*Cur_Pos).y == 1)                               	// jeœli obydwa warunki spe³nione
		 return true;

	 }}}}                                                                       // jeœli któryœ z powy¿szych warunków nie jest spe³niony odrazu przechodzi do zwracania false

	 return false;
}
// ---------------------------------------------------------------------------
void BringWindowToFront(HWND hWnd)
{
 bool Result;
 DWORD ForegroundWindowThreadID;
 DWORD WindowThreadID;
 if(hWnd != GetForegroundWindow())
 {
  ForegroundWindowThreadID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
  WindowThreadID = GetWindowThreadProcessId(hWnd, NULL);
  if(ForegroundWindowThreadID != WindowThreadID)
  {
   AttachThreadInput(ForegroundWindowThreadID, WindowThreadID, true);
   SetForegroundWindow(hWnd);
   AttachThreadInput(ForegroundWindowThreadID, WindowThreadID, false);
  }
  else
   SetForegroundWindow(hWnd);
  ShowWindow(hWnd, SW_RESTORE);
 }
}
// ---------------------------------------------------------------------------

void ExecuteApp(String sFileName)
{
    STARTUPINFO StartupInfo;
    ZeroMemory( &StartupInfo, sizeof(STARTUPINFO));
    StartupInfo.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION ProcessInfo;

	if(CreateProcess(NULL,
        sFileName.c_str(), // tutaj nastêpuje uruchomienie proramu przekazanego funkcji:
        NULL,
        NULL,
        TRUE,
        NORMAL_PRIORITY_CLASS,
        NULL,
        NULL,
        &StartupInfo,
        &ProcessInfo))
    {
    CloseHandle(ProcessInfo.hProcess);
	CloseHandle(ProcessInfo.hThread);
	}
	else   ShowError("B³¹d tworzenia procesu z œcie¿ki: " + sFileName);
}

////////////////////////////////////////////////////////////////////////////////
// DATA SEARCH  // DATA SEARCH  // DATA SEARCH  // DATA SEARCH  // DATA SEARCH//
////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
 String Search(TListView *lista, String *Dir, String typ, unsigned n, unsigned char m) {    // n to stan licznika przy wywo³ywaniu rekurencyjnym
																						   // m to g³êbokoœæ przekukiwania podfolderów
	if (m > S::MAX_DEPTH && 0 != S::MAX_DEPTH) return "Too depth";

	TListItem *ListIt;
	unique_ptr<TSearchRec> sr(new TSearchRec);
	unique_ptr<Counter> c(new Counter(n));                                      // licznik plików

	if (FindFirst( Getpath(*Dir) + typ , faAnyFile, *sr) == 0) {

		do {

	if ((((*sr).Attr & faDirectory) > 0) && ((*sr).Name != ".") && 	((*sr).Name != ".."))

			  Search(lista, &(Getpath(*Dir) + (*sr).Name) , typ, (*c).get(), m + 1); // przeszukiwanie podfolderów

				if (((*sr).Attr & faDirectory) == 0) {

					if (typ.IsEmpty())
					{
						ShowError("Puste search()" + (*c).get() );
						 ListIt = lista->Items->Add();
						 ListIt->Caption = *Dir;
						 ListIt->GroupID = 0;
						 ListIt->SubItems->Add((*sr).Name);
						 (*c).inkrement();
					}
					else if ( CompareExtension( (*sr).Name, typ) )
					{
					//	ShowMessage(ExtractFileExt((*sr).Name).SubString(2, 7));
						 ListIt = lista->Items->Add();
//						 ListIt->GroupID = 1;
						 ListIt->Caption = *Dir;
						 ListIt->SubItems->Add((*sr).Name);
						 ListIt->SubItems->Add(GetSize((*sr).Size));
						 Counter::size_files  += (*sr).Size;
						 ListIt->ImageIndex = TypeFileIcon( &( Getpath(*Dir,1) + (*sr).Name), lista);
						 (*c).inkrement();
					}
				if ((*c).get() == S::BREAK_SEARCH)
				{
					S::T.Pause();
					S::Status("Ostatni plik: " + *Dir + " (" + (*c).get() + ")");

					switch ( MessageBoxA(Application->Handle, S::BreakQuest().c_str(),
							"Fibonacci Searching Question", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)) {
						case idYes: S::T.Continue(); break;
						case idNo: 	S::T.Continue(); S::T.Show();

						lista->Column[2]->Caption = "Rozmiar (" + GetSize(Counter::size_files) + ")"; // MUSI ZOSTAÆ ZMIENIONE, DOPISYWANIE ROZMIARU DO KARZDEGO W B LUB bitach

						throw Exception("Przerwanie"); break;                                 // w trybie debug to wlicza siê do pomiaru czasu
					}
				}
			}
		}
		while (FindNext(*sr) == 0);

		FindClose(*sr);

		S::Status("Ostatni plik: " +  Getpath(*Dir,1) + " (" + (*c).get() + ")", 0, true);   // hint

		return (*c).get();
	}
	else {

		S::Status("Nie znaleziono plików w: " + *Dir,0 , true);
		return 0;
	}
 }

// ---------------------------------------------------------------------------
   unsigned	SearchaRecursivelyAndReview(TListView *list, String Dir, String typ, unsigned *n, unsigned char m) {

	if (m > S::MAX_DEPTH &&  0 != S::MAX_DEPTH ) return *n;

	unique_ptr<TSearchRec> sr(new TSearchRec);
	unique_ptr<AnsiString> buff(new AnsiString);
	WIN32_FIND_DATAW Wfd = {0};

	if( Dir.IsEmpty()) return *n;

	if(Dir[Dir.Length()] != '\\') 	Dir += "\\";

	unique_ptr<String> File(new String( Dir + L"*.???" ));

	*n = FindStream(list, &Dir , n );                                          	// przeszukiwanie podanej scie¿ki a poni¿ej tego co siê w niej znajduje

	HANDLE hFind = FindFirstFileW( (*File).c_str(), &Wfd);

	if( hFind == INVALID_HANDLE_VALUE ) return *n;

	do {

		String FileName = Wfd.cFileName;

		if( faDirectory == Wfd.dwFileAttributes && FileName != L"." && FileName != L"..")      // != nie wiem czemu ale równierz foldery                         // FILE_ATTRIBUTE_DIRECTORY == Wfd.dwFileAttributes &&
		{
			   *n =	SearchaRecursivelyAndReview(list, Dir + FileName, "", n, m + 1); // wyszkukiwanie w podfolderach
		}
		*n = FindStream(list, &(Getpath(Dir,1) + FileName), n );

	} while(FindNextFileW(hFind, &Wfd));

	FindClose(hFind);

	S::Status("Ostatni ADS: " + Dir  + " (" + list->Items->Count + ")", 0, true);

	 return *n;
	}
// ---------------------------------------------------------------------------
 String SearchStream(TListView *list, String Dir, String typ, unsigned n, unsigned char m) {

//	Singleton::T.Start();

	if( Dir.IsEmpty()) {

		S::Status("Œcie¿ka pusta");
		return -1;
	}

	if ( Dir.LastDelimiter(".") -1 > Dir.LastDelimiter("\\") ) 	FindStream(list, &Dir, &n); // jesli œcie¿ka mo¿e byæ do pliku

	n = SearchaRecursivelyAndReview(list, Dir , "", &n, m + 1);

	// There you can use Counter::size_files (all memory of found ADS) rema

//	Singleton::T.Show();
//	S::Status("Ostatni ADS: " + Dir + " (" + list->Items->Count + ")");

	return n;

}
/*
	+---------------------------------------------------------------------------+
	|																			|
	|	FindStream																|
	|	==============================											|
	|																			|
	|	Inputs:		TListView *list			   prints results  					|
	|				String *Path               where search                  	|
	|				unsigned *n				   count of ADS  					|
	|																			|
	|	Returns:	unsigned													|
	|																			|
	|	Notes:															|
	+---------------------------------------------------------------------------+
*/
unsigned FindStream(TListView *list, String *Path, unsigned *n) {

	TListItem *ListIt;
	WIN32_FIND_STREAM_DATA stream;
	HANDLE file;

	file = FindFirstStreamW( (*Path).c_str(), FindStreamInfoStandard, &stream, 0);

	if (file == INVALID_HANDLE_VALUE) {

		FindClose(file);
		return *n;
//		return ErrorToText(GetLastError());

	} else {

			do {

	if( (*Path)[(*Path).Length() - 0] == '.') if( (*Path)[(*Path).Length() -1 ] == '\\'  ) continue;  // *\.
																									  // pomija w tych przypadkach
	if( (*Path)[(*Path).Length() - 1] == '.') if( (*Path)[(*Path).Length() -2 ] == '\\'  ) continue;  // *\..

	if ( S::canData() )  if ( String(stream.cStreamName) == "::$DATA" )  continue; // pomija strumienie DATA (Zwyk³e dane, pliki)

	unique_ptr<String> name(new String(stream.cStreamName));

	if ( CompareStr( String(stream.cStreamName).SubString( String(stream.cStreamName).Length()-5, 6 ), ":$DATA") == 0 ) // jeœli comparestr zwróci 0 czyli brak ró¿nic

		(*name).Delete( (*name).Length() -5, 6);                                // usuwa tylko koñcówkê ":$DATA"

	else (*name).Delete( (*name).LastDelimiter(":"), 255);                    	// usuwa wszystko po ostatnim :(dwukropku)

	if ( S::canZID() ) if ( *name == ":Zone.Identifier") continue;  			// pomija idetyfikatory systemowe
//						 ShowMessage(*name.get());
//						 ShowMessage((String)stream.cStreamName );
				   { //proces wypisywania
					 ListIt = list->Items->Add();
					 ListIt->Caption = *Path;
					 ListIt->SubItems->Add( ( S::canHide() ) ? *name.get() : (String)stream.cStreamName );    // warunek musi byæ po list->Items->Add()
  if ( String(stream.cStreamName) == "::$DATA")                                 // jeœli to strumieñ pliku
		ListIt->ImageIndex = TypeFileIcon( Path , list, 0);                     // œcie¿ka do pliku przez którego strumieñ widaæ na liœcie
  else 	ListIt->ImageIndex = TypeFileIcon( &(Getpath(*Path,1) + *name.get()), list ,1);  // gdy to strumieñ alternatywny

					 ListIt->SubItems->Add( GetSize(stream.StreamSize.QuadPart));
					 Counter::size_files  += stream.StreamSize.QuadPart;
					 (*n)++;
				   }

			if ( *n == S::BREAK_SEARCH) {                              // zapytanie czy szukaæ nadal (wartoœæ)

				S::T.Pause();
				S::Status("Ostatni plik: " + *Path + " (" + *n + ")");
				switch ( MessageBoxA(Application->Handle, S::BreakQuest().c_str(),
					"Fibonacci Searching Question",  MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) )
			  {
				case idYes:
					S::T.Continue(); break;
				case idNo:
					S::ProgressBarStyle(0,0);
					list->Column[2]->Caption = "Rozmiar (" + GetSize(Counter::size_files) + ")";
					S::T.Continue();
					throw Exception("Przerwanie"); break;
			  }
			}

		} while (FindNextStreamW(file, &stream) != 0);

	  FindClose(file);
	}

	return *n;
}
//---------------------------------------------------------------------------
  template <typename Tail>
void foobar(const std::string& head, Tail&& tail)
{
	// do something with head
	std::cout << head << '\n';
	// call foobar recursively with remaining arguments
	foobar(std::forward<Tail>(tail)...);
}
//---------------------------------------------------------------------------
unsigned short TypeFileIcon( String *path, TListView *list, bool ext) {

	if ( (*path).IsEmpty() ) icons::ICO_ZONE_ID;

	 static HANDLE ic;                                                     		// zapamiêtuje ostanio u¿wywan¹ ikone

try {

	unique_ptr<TImage> img(new TImage(NULL));
	HICON ico;	WORD idx;

	if (ext) {

			(*path).Delete( 1, (*path).LastDelimiter0("\\") +1);

		if ( *path == ":") return S::ICO_DATA;
//		if ( *path == ":Zone.Identifier") return S::ICO_ZONE_ID;
		if ( *path == "::$DATA" ) (*path).Delete( (*path).Length()-7, (*path).Length());
		 *path = Getpath(*path,0);                     // to daje œcie¿kê do pliku (usuwa strumieñ)
//		if ( (*path)[(*path).Length()] == ":")
//					  ShowMessage(*path);
			*path = "TEMP" + GetExtension( *path,1,10);

			// bez closehanle pliki po zamkniêciu aplikacji automatycznie siê usun¹
			CloseHandle( CreateFileW( (*path).c_str(), 0, 0, NULL, CREATE_ALWAYS, 258, 0));     // 256 tymczasowy + 2 ukryty (atrybuty pliku)
			ico = ExtractAssociatedIcon(HInstance, (*path).c_str(), &idx);
			(*img).Picture->Icon->Handle = ico;
			DeleteFileW( (*path).c_str() );

	} else	{
		   try {
//		   if (GetExtension(*path) == "dll") { ShowMessage(*path);


						   ico = ExtractAssociatedIcon(HInstance, (*path).c_str(), &idx);

		   } catch (...) { nothrow;
		   }

		(*img).Picture->Icon->Handle = ico;
		}

		if ( ic != (*img).Picture->Icon->Handle ) {                             // jeœli uchwyty do ikon s¹ ró¿ne

			list->SmallImages->AddIcon((*img).Picture->Icon);
			ic = (*img).Picture->Icon->Handle;
		}
		// jeœli poprzednia ikona nie jest identyczna

		return list->SmallImages->Count-1;

	} catch (...) {  ShowError("Dopasowanie ikon "+*path);
	}
}
////////////////////////////////////////////////////////////////////////////////
// OBS£UGA B£ÊDÓW  // OBS£UGA B£ÊDÓW  // OBS£UGA B£ÊDÓW  // OBS£UGA B£ÊDÓW  ////
////////////////////////////////////////////////////////////////////////////////
void LogSave( AnsiString komunikat ) /* throw (AnsiString) */ {                 // przyczyna wstawiania dodatkowego nawiasu

 try {

	unique_ptr<ofstream> LOG( new ofstream );

		(*LOG).open( ( S::NAMElog+ ".log").c_str(), ios::out | ios::app);

		(*LOG) << "[  " << GetDataTime().c_str() << "  ]" << komunikat.c_str()
			<< endl;

		(*LOG).close();

	} catch (...) {
		throw "B³¹d przy próbie zapisu LOGa o treœci :\n" + komunikat;
	}
}
// ---------------------------------------------------------------------------
void ShowError(AnsiString kom, Exception *exception, TObject *Sender) {

	static unique_ptr<AnsiString> lastkom(new AnsiString);
	static unique_ptr<unsigned char> showtimes(new unsigned char);

	if(kom == *lastkom) { *lastkom = kom; *showtimes = 0; } else (*showtimes)++;       //jeœli s¹ ró¿ne inkrementuje licznik showtimes;

	if (*showtimes > 2) //przerwaie dzia³ania ?? sender?
	{
		switch (MessageBoxA(0, "Wykryto zapêtlenie siê funkcji. Co robiæ?\n\nPrzerwij - wyrzuca wyj¹tek i zerue licznik\nPonów próbê - zeruje licznik wyst¹pieñ\nIgnoruj - brak reakcji", "Fibonaci ShowError",  mbOK | MB_TASKMODAL | MB_ICONERROR | MB_DEFBUTTON3))
		{
/*IDIGNORE	*/ case 5 : break;                                              	// nie robi nic
/*IDABORT 	*/ default: case 3 : throw Exception ("Loop in ShowError( this interrupt it )"); // wyrzuca wyj¹tek  i nastêpne
/*IDTRYAGAIN*/ case 4 : *showtimes = 0; break;                             		// resetuje licznik

		}
	}

	unique_ptr<String> info(new String(""));

	if (exception) *info += "Exception :  " + exception->ToString() + "\n"; //jeœli jest to dopisuje wyj¹tek

	if (Sender) *info += "Object    :  " + Sender->ToString() + "  (" + Sender->QualifiedClassName() + ")\n";       //jeœli adres objectu jest ró¿ny od zera to dopisuje jego nazwê

	if (GetLastError()) *info += "LastError :  " +  ErrorToText( GetLastError() ) + "\n";

	if (ExceptAddr()) *info += "ExceptAddr :  " + CurrToStr((int)ExceptAddr()) + "\n";

//		ShowMessage( kom + "\n\n" + *info );
		MessageBoxA(  Application->Handle, ( kom + "\n\n" + *info ).c_str(), "FibonacciR Error" , MB_OK);

	try {

		LogSave(kom +"	"+ *info);

	} catch (Exception &exception)	{
		ShowError( "Przechwycone w ShowError() : " + exception.ToString() );

	} catch (...) {
		ShowMessage("Próba zapisu Loga przez ShowError() siê nie powiod³a");
	}
 }
// ------------		---------------------------------------------------------------
AnsiString ErrorToText(int LastError, bool code, bool save) {                   // opisuje tylko wybrane kody b³êdów

	unique_ptr<AnsiString> e(new AnsiString(" Error 0x" + (String)IntToHex(LastError, 2) + " (" + LastError + ")"));

	if (save) LogSave(ErrorToText(LastError,1,0));                              // zapisuje do pliku

	if ( !code )  *e = "";                                                      // jeœli bez zwracania kodu przy opisie

	switch (LastError) {

		case  0: return "The operation completed successfully" + *e;
		case  1: return "Incorrect function" + *e;
		case  2: return "The system cannot find the file specified" + *e;
		case  3: return "The system cannot find the path specified" + *e;
		case  4: return "The system cannot open the file" + *e;
		case  5: return "Access is denied" + *e;
		case  6: return "The handle is invalid" + *e;
		case  7: return "The storage control blocks were destroyed" + *e;
		case 10: return "The environment is incorrect" + *e;
		case 12: return "The access code is invalid" + *e;
		case 16: return "The directory cannot be removed" + *e;
		case 17: return "The system cannot move the file to a different disk drive" + *e;
		case 18: return "There are no more files" + *e;
		case 19: return "The media is write protected" + *e;
		case 21: return "The device is not ready" + *e;
		case 24: return "The program issued a command but the command length is incorrect" + *e;
		case 29: return "The system cannot write to the specified device" + *e;
		case 30: return "The system cannot read from the specified device" + *e;
		case 31: return "A device attached to the system is not functioning" + *e;
		case 32: return "The process cannot access the file because it is being used by another process" + *e;
		case 33: return "The process cannot access the file because another process has locked a portion of the file" + *e;
		case 38: return "Reached the end of the file" + *e;
		case 80: return "The file exists" + *e;
		case 82: return "The directory or file cannot be created." + *e;
		case 85: return "The local device name is already in use" + *e;
		case 87: return "The parameter is incorrect" + *e;
		case 107: return "The program stopped because an alternate diskette was not inserted" + *e;
		case 108: return "The disk is in use or locked by another process" + *e;
		case 109: return "The pipe has been ended" + *e;
		case 110: return "The system cannot open the device or file specified" + *e;
		case 111: return "The file name is too long" + *e;
		case 112: return "There is not enough space on the disk" + *e;
		case 113: return "No more internal file identifiers available" + *e;
		case 114: return "The target internal file identifier is incorrect" + *e;
		case 119: return "The system does not support the command requested" + *e;
		case 120: return "This function is not supported on this system" + *e;
		case 122: return "The data area passed to a system call is too small" + *e;
		case 123: return "The filename, directory name, or volume label syntax is incorrect" + *e;
		case 124: return "The system call level is not correct" + *e;
		case 125: return "The disk has no volume label" + *e;
		case 129: return "The %1 application cannot be run in Win32 mode" + *e;
		case 131: return "An attempt was made to move the file pointer before the beginning of the file" + *e;
		case 132: return "The file pointer cannot be set on the specified device or file" + *e;
		case 134: return "The system cannot join or substitute a drive to or for a directory on the same drive" + *e;
		case 144: return "The directory is not a subdirectory of the root directory" + *e;
		case 145: return "The directory is not empty" + *e;
		case 148: return "The path specified cannot be used at this time" + *e;
		case 155: return "Cannot create another thread" + *e;
		case 159: return "The address for the thread ID is not correct" + *e;
		case 161: return "The specified path is invalid" + *e;
		case 164: return "No more threads can be created in the system" + *e;
		case 167: return "Unable to lock a region of a file" + *e;
		case 168: return "The requested resource is in use" + *e;
		case 183: return "Cannot create a file when that file already exists" + *e;
		case 192: return "The operating system cannot run %1" + *e;
		case 206: return "The filename or extension is too long" + *e;
		case 222: return "The file type being saved or retrieved has been blocked" + *e;
		case 223: return "The file size exceeds the limit allowed and cannot be saved" + *e;
		case 240: return "The session was canceled" + *e;
		case 254: return "The specified extended attribute name was invalid" + *e;
		case 258: return "The wait operation timed out" + *e;
		case 259: return "No more data is available" + *e;
		case 266: return "The copy functions cannot be used" + *e;
		case 267: return "The directory name is invalid" + *e;
		case 302: return "The volume is too fragmented to complete this operation" + *e;
		case 305: return "Short names are not enabled on this volume" + *e;
		case 318: return "The scope specified was not found" + *e;
		case 321: return "The device is unreachable" + *e;
		case 335: return "An operation is not supported on a compressed file" + *e;
		case 336: return "An operation is not supported on a directory" + *e;
		case 337: return "The specified copy of the requested data could not be read" + *e;
		case 350: return "No action was taken as a system reboot is required" + *e;

	default:
		return ("Error 0x" + (String)IntToHex(LastError, 6) + " (" + LastError + ")");
	}
}

////////////////////////////////////////////////////////////////////////////////
// Counter  // Counter  // Counter  // Counter  // Counter  // Counter  // Counter
////////////////////////////////////////////////////////////////////////////////

// TComponent *Temp;
// for(int i = ComponentCount - 1; i >= 0; i--)
// {
//  Temp = Components[i];
//  if(!Temp->ClassNameIs("TLabel"))
//  {
//   reinterpret_cast<TEdit *>(Temp)->Text = "Jakiœ tekst"; // rzutowanie mo¿na by równie dobrze wykonaæ na klasê TMemo, poniewa¿ ona równie¿ posiada w³aœciwoœæ Text
//  }
// }

//SHFILEOPSTRUCT fos;   // z przeniesieniem do kosza
//  fos.hwnd = Handle;
//  fos.wFunc = FO_DELETE;
//  fos.pFrom = (ExtractFileDir(Application->ExeName) + "\\nazwapliku.xxx").c_str();  //nazwa kasowanego pliku, trzeba podaæ pe³n¹ œcie¿kê dostêpu
//	  fos.fFlags = FOF_ALLOWUNDO;
//  SHFileOperation(&fos);
// ---------------------------------------------------------------------------
// AnsiString DigitRewriteOLD(AnsiString w, int a ) {                           // wersja nie ukoñczona
//
//	 AnsiString *p = new AnsiString;
//
//	 char* znak = new char;
//	 char* buff = new char[256];
//
//	 float wyj = 0;
//	 int indekscomma = 0, isdelim = 0, era = 0;
////
/////////////////////////////////////////////////////////////////////////////
////
//		 AnsiString *p = new AnsiString;
//		 char* znak = new char;
//		 char **l = (char**)malloc(20*sizeof(char*));
//		 char* buff = new char[w.Length()];     //LAST WRONG??FIND   //nie wiem czy mo¿e byæ dynamicznie alokowany
//		 short  *indekscomma = new short;
//		 short  *isdelim = new short;
//		 unsigned short  *era = new unsigned short;
//		 unsigned short 	*wyj = new unsigned short;
//		 /*static*/ unsigned short *Lrindx= new unsigned short;
//		 	*Lrindx=0;
////
//////////////////////////////////////////////////////////////////////////////
////
//	 char tab[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ','};
//
//	 try {
//
//		w.printf(buff);   	//nie dzia³a
//		buff = w.c_str();   //bug przy trzecim wywo³aniu funkcji
//
//			 for (int i = 0; i < w.Length(); i++) {			              		// nie jest ' <= ' bo ostatni znak to \0 (koñcowy)
//
//				 *znak = buff[i];
////
////				(AnsiString)*znak = w.SubString(1,1);
////				w.Delete(1,1);
////
//
//				 for (int h = 0; h <= 11; h++) {
//
//					 if (*znak == tab[h]) {
//
//						 (*p).Insert(*znak, (*p).Length() + 1);
//					 }
//				 }
//			 }
//
//		 isdelim = (*p).AnsiPos(',');
//
//		 indekscomma = (*p).LastDelimiter(",");
//
//			 if (indekscomma) { // usuwanie przecinków
//
//				 (*p).Delete(indekscomma, 1);
//
//				 era = (*p).LastDelimiter(",");
//
//				 while (era) {
//
//					 wyj++;
//					 era = (*p).LastDelimiter(",");
//
//					 (*p).Delete(era, 1);
//				 }
//			 }
//
//		 int Lrindx = lastreslut[0].LastDelimiter(",");
//
//			 if (Lrindx) {
//
//				 if (isdelim > Lrindx) {
//
//					 (*p).Insert(',', indekscomma - wyj + 1);
//				 }
//
//				 else if (isdelim < Lrindx) {
//
//					 (*p).Insert(',', isdelim);
//				 }
//
//				 else if (indekscomma) {
//
//					 (*p).Insert(',', indekscomma - wyj + a );        // by³o ...a- wyj  + 1)
//				 }
//			 }
//
//			 else if (indekscomma) { // w przypadku kropki zamiast przecinka
//
//				 (*p).Insert(',', indekscomma - wyj);
//			 }
//
//
//
//		if ((*p) != 0) { return *p;	}         // b³¹d??
//
//		else {  	 	  return 0;	}
//
//	 }
//
//	 __finally {
////
//		if (buff != NULL) {
//		free(l);
//		delete[] buff;    //NIErozwi¹zany  //dlaczego wyrzuca b³ad??// jest to zwi¹zane z d³ugoœci¹ od 8 znaków
//			}
//////////////////////////////////////////////////////////////////////////////
//			delete  znak, p, znak, indekscomma, wyj, isdelim, era, Lrindx;
//////////////////////////////////////////////////////////////////////////////
//
//	} catch (Exception &exception)	{
//
//		Application->ShowException(&exception);
//
//	} catch (...) {
//		ShowMessage("Error		noname exception\n\nFunkcje.cpp  DigitRewrite()") ;
//	}
//  }
#pragma package(smart_init)
