#pragma hdrstop

#include "Unit1.h"
#include "Funkcje.h"
#include <memory>
#include <process.h>
//#include <boost/thread.hpp>

////////////////////////////////////////////////////////////////////////////////
//  �CIE�KI PLIK�W	//  �CIE�KI PLIK�W	//  �CIE�KI PLIK�W	//  �CIE�KI PLIK�W
////////////////////////////////////////////////////////////////////////////////
String AddBeforDot(String Name, String dopis) {         						// dodaje tekst przed kropk�

	unique_ptr<short int> pos(new short int);
//	short int *pos = new short int;
	*pos = LastDelimiter('.', Name);

	if (*pos < 1) {                          			 						//je�li mniejsze  1
		Name.Insert(dopis.c_str(), Name.Length() + 1);
	}
	else {
		Name.Insert(dopis, *pos);
	}
//	delete pos;
	return Name;
}
// ---------------------------------------------------------------------------
String Getname(String path, bool b) { 											// zwraca nazw� pliku

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

			 if (LastDelimiter('\\', path) != path.Length()) 	  				//dodawanie backslasha na ko�cu je�li nie ma
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

			 if (LastDelimiter('\\', path) != path.Length()) {  				//dodawanie backslasha na ko�cu je�li nie ma

				path.Insert("\\", path.Length()+1);

			 }
		 }

//	 delete pos;

	return path;

 }
//---------------------------------------------------------------------------
 String GetCurrPathAll(String out) {                                                // nie uda�o si� przerobi� na unique_ptr

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

		 if (dot) if (*pos) EXT.Insert(".", 1);                                 // je�li z kropk� je�li by�a kropka do j� wstawia

		 return EXT;
	 }
	 return "";
 }
 // ---------------------------------------------------------------------------
bool CompareExtension(String Ext1, String Ext2, bool lower)
{                   // zwraca true gdy idetyczne

	unique_ptr<String> EXT1(new String(GetExtension(Ext1,1)));
	unique_ptr<String> EXT2(new String(GetExtension(Ext2,1)));

	if ( *EXT1 == "*" || *EXT2 == "*" )   return 1;                 			// je�li gwiazdka to mo�e by� wszystkim

	if ( *EXT1 == ".*") if ( (*EXT2).LastDelimiter(".") ) return 1;             // sprawdza czy plik ma rozrzerzenie po kropce
	if ( *EXT2 == ".*") if ( (*EXT1).LastDelimiter(".") ) return 1;

//		if (*EXT1 == "" || *EXT2 == "") return 1;                           	// je�li jedno puste zwraca 1

	if (lower) 	return ((*EXT1).LowerCase() == (*EXT2).LowerCase()) ? 1 : 0;    // domy�lnie, wielko�c liter bez znaczenia

	else return ((*EXT1) == (*EXT2)) ? 1 : 0;                                   // z rozr�niamiem wielko�ci znak�w
}
// ---------------------------------------------------------------------------
 bool AddParam(String Param,String *Path, bool size) {
 
	if ( size ) { Param = Param.LowerCase(); (*Path).LowerCase(); }             // ujednolicenie rozmiaru tekstu
	if ((Param)[1] != '/') (Param).Insert("/", 1);                           	// dodanie slasha je�li nie ma

	size = 1;                                                                   // nowy wykorzystanie

		unique_ptr<String>com(new String(*Path));
		unique_ptr<String>buff(new String(0));
		unique_ptr<unsigned>pos(new unsigned((*com).Pos("/")));
		unique_ptr<unsigned>ph(new unsigned((Param).Length()));                	// Param lengtH


	while ( *pos ) {
		 *pos = (*com).LastDelimiter("/");
		 *buff = (*com).SubString(*pos, *ph);
		  if (CompareStr(*buff, Param) == 0 && size)  { size = 0; continue; }   // je�li ju� jest ten parametr w �cie�ce uruchamiania
		  (*com).Delete(*pos,*ph);
	}

	if (size) {	*Path += " " + Param;  return 1; }
	return 0;	
 }
// ---------------------------------------------------------------------------
 bool DelParam(String Param,String *Path, bool size, bool slash) {

	if ( size ) { Param = Param.LowerCase(); (*Path).LowerCase(); }             // ujednolicenie rozmiaru tekstu
	if ( Param[1] != '/') Param.Insert("/", 1);                            	// dodanie slasha je�li nie ma
								
		unique_ptr<String>com(new String(*Path));
		unique_ptr<String>buff(new String(0));
		unique_ptr<unsigned>pos(new unsigned((*com).LastDelimiter("/")));
		unique_ptr<unsigned>ph(new unsigned((Param).Length()));                	// Param lengtH
		unique_ptr<bool> b(new bool(0));                                        // je�li co� usunie przyjmuje warto�� 1
		
	while ( *pos ) {

		 *buff = (*com).SubString(*pos, *ph);
		  if (!CompareStr(*buff, Param)) {
			*b = 1;
			(*com).Delete(*pos,*ph);
			(*Path).Delete(*pos,*ph);
		  }  																	// je�li ju� jest ten parametr w �cie�ce uruchamiania
		  else (*com).Delete(*pos ,*ph);

		  *pos = (*com).LastDelimiter("/");
	}

	*pos =  (*Path).LastDelimiter("/");

	if (slash) if (*pos) (*Path).Delete(*pos, 255);

//		ShowMessage( "|"+(*Path)[(*Path).Length()]);
	  while ( (*Path)[(*Path).Length()] == ' ') (*Path).Delete((*Path).Length(),1);

	return *b;                                                                  // true je�li co� usun��
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

		if ((*s).SubString((*s).Length() - 2, 1) == '_')                        // sprawdza czy 3 znak od ko�ca == "_"
		{

			try {
				*cp = (*s).SubString((*s).Length() - 1, 2).ToInt();             // czy ostatnie dwie cyfry to int


			} catch (...) {;}    												//zapobiega wy�wietlaniu komunikatu o b�edzie

			if (*cp) {

				do {
					(*cp)++;
					path = (*s).Delete((*s).Length() - 2, 3) + '_' + FormatFloat("00", *cp);                                 // usuwa poprzedni numer kopi i dodaje nowy

					*s += "_" + FormatFloat("00", *cp);

				} while (FileExists(path));

			} else 	*s += "_01";

		} else 	*s += "_01";

		path = *s + *ext;

		return path;         													//zwraca nazw� pliku
 }
//---------------------------------------------------------------------------
 void EditPathValid(TEdit * Edit1) {

	 if (!DirectoryExists(Edit1->Text) && !FileExists(Edit1->Text)) {
		 Edit1->Color = clBtnFace;
		 // ShowMessage("Podana �cie�ka nie istnieje popraw j� i zastosuj ponownie\n\nJe�li u�yjesz niepoprawnej �cie�ki program b�dzie mia� problem, a je�li m�j program ma problem to ty masz problem\nProblem ");

		 Edit1->SetFocus();

		 unique_ptr<String> str(new String(Edit1->Text) );
		 unique_ptr<short int > pos(new short int( (*str).Length() ));

		 do {

			 (*str).Delete(*pos, 1);
			 (*pos)--;

		 }
		 while ((!DirectoryExists(*str) && !FileExists(*str)) && *pos);

		 Edit1->Perform(EM_SETSEL, *pos, Edit1->Text.Length());
//         throw Exception ("Niepoprawna �cie�ka");
	 }
	 else 	 Edit1->Color = clWindow;
}
////////////////////////////////////////////////////////////////////////////////
// STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  // STRINGI  																			  ///
////////////////////////////////////////////////////////////////////////////////
 String TrimT(AnsiString w) {                                                   // Trim Total (usuwa wszystkie puste pola z stringa)

	unique_ptr<short int> rd(new short int);

	  do { 	*rd = w.LastDelimiter(" ");

			w.Delete(*rd, 1);

	  } while (*rd);

   return w;
 }
//---------------------------------------------------------------------------

 
//---------------------------------------------------------------------------
bool Find(String *where,char* w)  {

	do {



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
AnsiString DigitRewrite(AnsiString w, char e, short a ) {   //przerobi� by zwraca�o double  /* By w pe�ni wyko�ysta� mo�liwo�ci   	(przes�wanie przecinka w prawo)	*/
																					/* tej funkcji nale�y PRZED u�ycim  	*/
	if ( w == "" )	return 0;                                                       /* umie�ci� wywo�anie fukcji addtoh() 	kt�ra zapami�tuje podane wyniki	*/

	unique_ptr<AnsiString> p(new AnsiString);                                   // warto�� zwracana

 try {

	w = StringReplace( w, ".", ",", TReplaceFlags() << rfReplaceAll);           // zamiana kropek na przecinki

	register unique_ptr<char> znak(new char );                     				// komparator, wsp�pracuje z *buff[]
	unique_ptr<short> indekscomma(new short);                                   // pozycja przecinka      (od prawej)
	unique_ptr<short> isdelim(new short);                             			// czy jast delimiter (,) (od lewej)
	unique_ptr<unsigned short> era(new unsigned short(w.Length() )); 	        // do indeks ile do usuni�cia, przypisanie w celu oszcz�dno�ci zasob�w
	unique_ptr<unsigned short> wyj(new unsigned short(0));                      // pozycja pierwszego od lewej przecinka, bez przpisania zawiera losowe warto�ci
	unique_ptr<unsigned short> Lrindx(new unsigned short(0));                      // pozycja przecinka przy porzednim wywo�aniu funkcji
	unique_ptr<char[]> buff(new char[ *era ]);                              	// bufor tabicy char�w do sprawdzenia

	register char tab[] = { ',', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	 StrToUniqueArr( w, buff );													// (w) jest kopiowane do *buff[]

		for (int i = 0; i < *era; i++) { 										// nie jest ' <= ' bo ostatni znak to \0 (ko�cowy) oraz liczone od 0

			*znak = buff[i];

			for (int h = 0; h <= 11; h++) {                                     // por�wnanie wej�cia z zawato�ci� *tab[]

				if ( *znak == tab[h]) {

					(*p).Insert(*znak, (*p).Length() + 1);	break;

				} else if (h == 11)	(*wyj)++;                                   // potrzebne do zachowania pozycji przecinka
			}
		}

		*isdelim = (*p).AnsiPos(',');

		*indekscomma = (*p).LastDelimiter(",");

				if (*indekscomma) { 											// usuwanie przecink�w

					(*p).Delete(*indekscomma, 1);

					*era = (*p).LastDelimiter(",");

					while (*era) {                                        		// nie mo�e by� do while bo niemo�e nast�pi� inkrementacja wej

						(*wyj)++;                                               // *wyj jest p�niej odejmowany przy ustalaniu pozycji przecinka
						*era = (*p).LastDelimiter(",");
						(*p).Delete(*era , 1);
					}
				}

		if ( e ) *Lrindx = lastreslut[1].LastDelimiter(","); 				 // je�li ostatnio byla u�yta funkcja addtoh()

		if (w.LastDelimiter(",")) {                                             // je�li by� przecinek to ta sekcja go doda

			if (*Lrindx) {

				if (*isdelim > *Lrindx)  {                                     	// je�li pozycja przecinka(*isdelim) jest wi�ksza od poprzedniej(*Lrindx)
ShowError("lastreslut zarejestrowano w DigitalRewrite \n0: " + lastreslut[0] +" \n1: "+ lastreslut[1]);
					 (*p).Insert(',', *indekscomma - *wyj );   //usun��em + 1
										  }
				else if (*isdelim < *Lrindx)

					 (*p).Insert(',', *isdelim);

				else if (*indekscomma) 											//je�li �adne z powy�szych a w prierszym argumencie by� przecinek

					(*p).Insert(',',  *indekscomma - *wyj + 1);

			} else if (*indekscomma) {										    // je�li funkcja addtoh prawdopodobnie jest wy��czona

			static unique_ptr<unsigned short> last_pos(new unsigned short(0));  // zmienna pami�taj�ca pozycj� ostatniego przcinka

					if ( !*wyj )	(*p).Insert(',', *indekscomma - *wyj );     // je�li by� tylko jeden przecinek

					else if ( *last_pos > *isdelim) (*p).Insert(',', *isdelim );

					else if ( *last_pos < *isdelim) (*p).Insert(',', *indekscomma - *wyj );

					else  (*p).Insert(',', *indekscomma - *wyj +1 );

				if ( !*Lrindx )                                                 // je�li lastreslut[1] ustawiane przez funkcj� addtoh nie zawiera przecinka (czyli zachodzi mo�liwo�� �e ta funkcja nie zosta�a wywo�ana)

					*last_pos = (*p).LastDelimiter(",");                        // przypisanie zmiennej statycznej pozycji przecinka liczby kt�r� zwraca ta funkcja

			}
		}
	} catch (Exception &exception)	{
			// or throw exception
		ShowError("Wyj�tek DigitRewrite()",&exception);
		throw &exception;

	} catch (...) {
		ShowError("Error		noname exception\n\nFunkcje.cpp  DigitRewrite()") ;
	}

	return *p;
	                                               				//brak r�nicy pomi�dzy *p.get()
//		if ( (p) != 0 )  return *p;         // przez unique_ptr niema dost�pu do adresu
//
//		else {
//
//			ShowError("Funcje.cpp DigitalRewrite(); zwraca 0\n\nSkontaktuj si� a Admistratorem");
//			return 0;
//		}
}
//---------------------------------------------------------------------------
void addtoh(TEdit *wsk) {

	if (lastreslut[0] != lastreslut[1])  lastreslut[1] = lastreslut[0];         //je�li !s� identyczne

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

//		  (*DT).ToInt();               // wyj�tek

	} catch (Exception &exception)	{
		ShowError(exception.ToString());
	}

	catch(...) {

		ShowError("Nieznany b��d funkcji GetDataTime()");
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
	else if (Clipboard()->HasFormat(CF_HDROP))		return "lista plik�w (drop)";
	else if (Clipboard()->HasFormat(CF_DSPMETAFILEPICT))return "obraz2";
	else if (Clipboard()->HasFormat(CF_DSPBITMAP))return "bitmap";
//	else if (Clipboard()->HasFormat(CF_METAFILEPICT))return "obraz";
//	CF_HDROP

	else return "Zawarto�� showka nieznana";

}
bool CursorAt(HWND hWnd) {

	 unique_ptr<POINT>Cur_Pos(new POINT); 										// pozycja kursora
	 unique_ptr<RECT>Wnd(new RECT); 											// pozycje rog�w Edita

	 GetCursorPos(Cur_Pos.get());
	 GetWindowRect( hWnd, Wnd.get());

	 if ((*Wnd).left <= (*Cur_Pos).x) {
		 if ((*Cur_Pos).x <= (*Wnd).right) {

			 (*Cur_Pos).x = true; 											   	// nowe zastosowanie

	 if ((*Wnd).top <= (*Cur_Pos).y) {
		 if ((*Cur_Pos).y <= (*Wnd).bottom) {

			 (*Cur_Pos).y = true; 												// nowe zastosowanie

	 if ((*Cur_Pos).x == 1 && (*Cur_Pos).y == 1)                               	// je�li obydwa warunki spe�nione
		 return true;

	 }}}}                                                                       // je�li kt�ry� z powy�szych warunk�w nie jest spe�niony odrazu przechodzi do zwracania false

	 return false;
}

////////////////////////////////////////////////////////////////////////////////
// DATA SEARCH  // DATA SEARCH  // DATA SEARCH  // DATA SEARCH  // DATA SEARCH//
////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
 String Search(TListView *lista, String *Dir, String typ, unsigned n, unsigned char m) {    // n to stan licznika przy wywo�ywaniu rekurencyjnym
																						   // m to g��boko�� przekukiwania podfolder�w
	if (m > FibonacciR->MAX_DEPTH && 0 != FibonacciR->MAX_DEPTH) return "Too depth";

	TListItem *ListIt;
	unique_ptr<TSearchRec> sr(new TSearchRec);
	unique_ptr<Counter> c(new Counter(n));                                      // licznik plik�w

	if (FindFirst( Getpath(*Dir) + typ , faAnyFile, *sr) == 0) {

		do {
		

	if ((((*sr).Attr & faDirectory) > 0) && ((*sr).Name != ".") && 	((*sr).Name != ".."))

//	LogSave((Getpath(*Dir) + (*sr).Name));
//	LogSave(typ);
//	LogSave(lista->Name);
//	LogSave((*c).get());
//	LogSave(m);
							   
				 
			  Search(lista, &(Getpath(*Dir) + (*sr).Name) , typ, (*c).get(), m + 1); // przeszukiwanie podfolder�w

//				 ListView_SetImageList( lista, himl, LVSIL_SMALL );
						 if ("BOOTSECT.BAK" == (*sr).Name )  ShowMessage(0);  
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
		if ((*c).get() == FibonacciR->BREAK_SEARCH)
		{

			FibonacciR->StatusInfo("Ostatni plik: " + *Dir + " (" + (*c).get() + ")");

			switch ( MessageBoxA(Application->Handle, FibonacciR->BreakQuestion().c_str(),
				 "Fibonacci Searching Question", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)) {
			case 6: ; 	break;
			case 7:
				ProgressBarStyle(0, 0);
				FibonacciR->ListView1->Column[2]->Caption =
							"Rozmiar (" + GetSize(Counter::size_files) + ")";
				throw Exception("Przerwanie");
			}
		}
				}
		}
		while (FindNext(*sr) == 0);

		FibonacciR->StatusBar1->Hint = "Ostatni plik: " + *Dir + " (" + (*c).get() + ")";

		FindClose(*sr);

		return "Znaleziono plik: " + *Dir + (*sr).Name + "  (" + (*c).get() + ")";       //+ c.get()
	}
	else {
		return "Taki plik nie istnieje :(";
		}

 }
// ---------------------------------------------------------------------------
   unsigned	SearchaRecursivelyAndReview(TListView *list, String Dir, String typ, unsigned *n, unsigned char m) {

	if (m > FibonacciR->MAX_DEPTH &&  0 != FibonacciR->MAX_DEPTH ) return *n;

	unique_ptr<TSearchRec> sr(new TSearchRec);
	unique_ptr<AnsiString> buff(new AnsiString);
	WIN32_FIND_DATAW Wfd = {0};

	if( Dir.IsEmpty()) return *n;

	if(Dir[Dir.Length()] != '\\') 	Dir += "\\";

	unique_ptr<String> File(new String( Dir + L"*.???" ));

	*n = FindStream(list, &Dir , n );                                          	// przeszukiwanie podanej scie�ki a poni�ej tego co si� w niej znajduje

	HANDLE hFind = FindFirstFileW( (*File).c_str(), &Wfd);

	if( hFind == INVALID_HANDLE_VALUE ) return *n;

	do {

		String FileName = Wfd.cFileName;

		if( faDirectory == Wfd.dwFileAttributes && FileName != L"." && FileName != L"..")      // != nie wiem czemu ale r�wnierz foldery                         // FILE_ATTRIBUTE_DIRECTORY == Wfd.dwFileAttributes &&
		{
			   *n =	SearchaRecursivelyAndReview(list, Dir + FileName, "", n, m + 1); // wyszkukiwanie w podfolderach
		}
		*n = FindStream(list, &(Getpath(Dir,1) + FileName), n );

	} while(FindNextFileW(hFind, &Wfd));

	FindClose(hFind);

	 return *n;
	}
// ---------------------------------------------------------------------------
 String SearchStream(TListView *list, String Dir, String typ, unsigned n, unsigned char m) {

	if( Dir.IsEmpty()) return "�cie�ka pusta";

	if ( Dir.LastDelimiter(".") -1 > Dir.LastDelimiter("\\") ) 	FindStream(list, &Dir, &n); // jesli �cie�ka mo�e by� do pliku

	n = SearchaRecursivelyAndReview(list, Dir , "", &n, m + 1);

	// There you can use Counter::size_files (all memory of found ADS) rema

	return "Znaleziono ADS " + Dir + "  (" + n + ")";

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

	if( (*Path)[(*Path).Length()] == '.'  ) if( (*Path)[(*Path).Length() -1 ] == '\\'  )  continue;    // *\.
																							// pomija w tych przypadkach
	if( (*Path)[(*Path).Length() - 1] == '.')  if( (*Path)[(*Path).Length() -2 ] == '\\'  ) continue;  // *\..

	if (Form2->CheckBoxNoDATA->Checked)  if ( String(stream.cStreamName) == "::$DATA" )  continue; // pomija strumienie DATA

	unique_ptr<String> name(new String(stream.cStreamName));
//							 ShowMessage(*name);
	if ( CompareStr( String(stream.cStreamName).SubString( String(stream.cStreamName).Length()-5, 6 ), ":$DATA") == 0 ) // je�li comparestr zwr�ci 0 czyli brak r�nic

		(*name).Delete( (*name).Length() -5, 6);                                // usuwa tylko ko�c�wk� ":$DATA"

	else (*name).Delete( (*name).LastDelimiter(":"), 255);                    	// usuwa wszystko po ostatnim :(dwukropku)

	if (Form2->CheckBoxZoneId->Checked) if ( *name == ":Zone.Identifier") continue;  // pomija idetyfikatory systemowe

				   { //proces wypisywania
					 ListIt = list->Items->Add();
					 ListIt->Caption = *Path;

	if (Form2->CheckBoxHideData->Checked) ListIt->SubItems->Add( *name.get() ); // warunek musi by� po list->Items->Add()

	else			 ListIt->SubItems->Add( stream.cStreamName);
								  LogSave(*name.get());						    // sprawdzi� czy wcze�ciej niezeuje
					 ListIt->ImageIndex = TypeFileIcon( &(Getpath(*Path,1)+ *name.get()), list ,1);
					 ListIt->SubItems->Add( GetSize(stream.StreamSize.QuadPart));
					 Counter::size_files  += stream.StreamSize.QuadPart;
					 (*n)++;
				   }

			if ( *n == FibonacciR->BREAK_SEARCH) {                              // zapytanie czy szuka� nadal (warto��)

				FibonacciR->StatusInfo("Ostatni plik: " + *Path + " (" + *n + ")");
				switch ( MessageBoxA(Application->Handle, (const char*)FibonacciR->BreakQuestion().c_str(), "Fibonacci Searching Question",  MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) )
			  {
				case 6:  break;
				case 7: ProgressBarStyle(0,0);    
				FibonacciR->ListView1->Column[2]->Caption = "Rozmiar (" + GetSize(Counter::size_files) + ")";
				throw Exception("Przerwanie"); break;
			  }
			}

		} while (FindNextStreamW(file, &stream) != 0);

	  FindClose(file);
	}
	return *n;
}

//---------------------------------------------------------------------------
unsigned short TypeFileIcon( String *path, TListView *list, bool ext) {

if ( (*path).IsEmpty() ) ICO_EMPTY;     

try {

	unique_ptr<TImage> img(new TImage(NULL));
	HICON ico;	WORD idx;

	if (ext) {
					  
			(*path).Delete( 1, (*path).LastDelimiter0("\\") +1);

		if ( *path == ":") return 0;
		if ( *path == ":Zone.Identifier") return ICO_ZONE_ID;
		if ( *path == "::$DATA" ) return ICO_DATA;

			*path = "TEMP" + GetExtension( *path,1);

			// bez closehanle po zamkni�ciu aplikacji automatycznie si� usun�
			CloseHandle( CreateFileW( (*path).c_str(), 0, 0, NULL, CREATE_ALWAYS, 258, 0 	)  );     // 256 tymczasowy, 2 ukryty
			ico = ExtractAssociatedIcon(HInstance, (*path).c_str(), &idx);
			(*img).Picture->Icon->Handle = ico;
			DeleteFileW( (*path).c_str() );

	} else	{
//		   try {
//		   if (GetExtension(*path) == "dll") { ShowMessage(*path);
			   
//		   }
						   ico = ExtractAssociatedIcon(HInstance, (*path).c_str(), &idx);
//		   } catch (...) { nothrow;
//		   }

		(*img).Picture->Icon->Handle = ico;
	}
		list->SmallImages->AddIcon( (*img).Picture->Icon);

	return list->SmallImages->Count-1;

} catch (...) {  ShowMessage(*path);
}
}
////////////////////////////////////////////////////////////////////////////////
// OBS�UGA B��D�W  // OBS�UGA B��D�W  // OBS�UGA B��D�W  // OBS�UGA B��D�W  ////
////////////////////////////////////////////////////////////////////////////////
void LogSave( AnsiString komunikat ) /* throw (AnsiString) */ {                 // przyczyna wstawiania dodatkowego nawiasu

 try {

	unique_ptr<ofstream> LOG( new ofstream );

		(*LOG).open( (FibonacciR->NAMElogfile + ".log").c_str(), ios::out | ios::app);

		(*LOG) << "[  " << GetDataTime().c_str() << "  ]" << komunikat.c_str()
			<< endl;

		(*LOG).close();

	} catch (...) {
		throw "B��d przy pr�bie zapisu LOGa o tre�ci :\n" + komunikat;
	}
}
// ---------------------------------------------------------------------------
void ShowError(AnsiString kom, Exception *exception, TObject *Sender) {

	static unique_ptr<AnsiString> lastkom(new AnsiString);
	static unique_ptr<unsigned char> showtimes(new unsigned char);

	if(kom == *lastkom) { *lastkom = kom; *showtimes = 0; } else (*showtimes)++;       //je�li s� r�ne inkrementuje licznik showtimes;

	if (*showtimes > 2) //przerwaie dzia�ania ?? sender?
	{
		switch (MessageBoxA(0, "Wykryto zap�tlenie si� funkcji. Co robi�?\n\nPrzerwij - wyrzuca wyj�tek i zerue licznik\nPon�w pr�b� - zeruje licznik wyst�pie�\nIgnoruj - brak reakcji", "Fibonaci ShowError",  mbOK | MB_TASKMODAL | MB_ICONERROR | MB_DEFBUTTON3))
		{
/*IDIGNORE	*/ case 5 : break;                                              	// nie robi nic
/*IDABORT 	*/ default: case 3 : throw Exception ("Loop in ShowError( this interrupt it )"); // wyrzuca wyj�tek  i nast�pne
/*IDTRYAGAIN*/ case 4 : *showtimes = 0; break;                             		// resetuje licznik

		}
	}

	unique_ptr<String> info(new String(""));

	if (exception) *info += "Exception :  " + exception->ToString() + "\n"; //je�li jest to dopisuje wyj�tek

	if (Sender) *info += "Object    :  " + Sender->ToString() + "  (" + Sender->QualifiedClassName() + ")\n";       //je�li adres objectu jest r�ny od zera to dopisuje jego nazw�

	if (GetLastError()) *info += "LastError :  " +  ErrorToText( GetLastError() ) + "\n";

	if (ExceptAddr()) *info += "ExceptAddr :  " + CurrToStr((int)ExceptAddr()) + "\n";

//		ShowMessage( kom + "\n\n" + *info );
		MessageBoxA(  Application->Handle, ( kom + "\n\n" + *info ).c_str(), "FibonacciR Error" , MB_OK);

	try {

		LogSave(kom +"	"+ *info);

	} catch (Exception &exception)	{
		ShowError( "Przechwycone w ShowError() : " + exception.ToString() );

	} catch (...) {
		ShowMessage("Pr�ba zapisu Loga przez ShowError() si� nie powiod�a");
	}
 }
// ------------		---------------------------------------------------------------
AnsiString ErrorToText(int LastError, bool code, bool save) {                   // opisuje tylko wybrane kody b��d�w

	unique_ptr<AnsiString> e(new AnsiString(" Error 0x" + (String)IntToHex(LastError, 2) + " (" + LastError + ")"));

	if (save) LogSave(ErrorToText(LastError,1,0));                              // zapisuje do pliku

	if ( !code )  *e = "";                                                      // je�li bez zwracania kodu przy opisie

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

////////////////////////////////////////////////////////////////////////////////
// Time  // Time  // Time  // Time  // Time  // Time  // Time  // Time  // Time
////////////////////////////////////////////////////////////////////////////////
void Times::FormatMilisec(String* __inout f,bool __in hint) {

	unique_ptr<unsigned char> pos(new unsigned char((*f).LastDelimiter(",")) );

	if ( !*pos) {  *f = "Brak przecinka FormatMilisec()";  }

	while( *pos < 4) {                                        					// e.g. "000,0"

	   (*f).Insert("0", 1);
		*pos = (*f).LastDelimiter(",");
	}

	for (int i = 7; i < 0; i--) {

		(*f).Insert(" ", i*3);
	}

}
// ---------------------------------------------------------------------------
void Times::Calculate(){

//   f = 0; s = 0;

	result = second - first;

	unique_ptr<String>mils(new String(result));

	unsigned sec = (int)( result / 1000);

	if ( result < 1001 ) {

	 while (QueryPerformanceFrequency(&lpFrequency) == 0) {
			QueryPerformanceFrequency(&lpFrequency) == 0;
	 }

		double Frequency= lpFrequency.QuadPart;
		double End 	  	= lpEnd.QuadPart;
		double Start  	= lpStart.QuadPart;

		Frequency = (End - Start) / Frequency;
//		ShowMessage(Frequency);
		// Frequency przechowuje wynik bo nie jest ju� potrzebne
		if (Frequency == 0) {
			Sleep(1);Sleep(1);
			ShowMessage(lpEnd.QuadPart+lpStart.QuadPart+lpFrequency.QuadPart);
//			ShowMessage(lpEnd.QuadPart);
//			ShowMessage(lpStart.QuadPart);
		}

		seconds = Frequency;
			  
		if ( p & c) { Frequency = starttopaused + seconds; }  	                        // je�li wywo�ano funkcje Pause i Continue
		seconds = Frequency;
		Frequency = Frequency * 1000;                                           // z sekund na milisekundy
//		 seconds = Frequency/1000;
		*mils = FloatToStrF(Frequency, ffFixed, 15, 15);                        // dok�adno�� do sekundo do -18 pot�gi (attosecond)
//		ShowMessage((String)seconds + "\n" + (*mils).ToDouble()/1000 ) ;
//		seconds = (*mils).ToDouble()/1000;

		FormatMilisec(mils.get());

	}  else {

		(*mils).Delete(1, (*mils).Length() - 3);
		seconds = result / 1000;
	}

	formated = FormatFloat("00", sec / 3600) + ":" + // godziny (ilo�� nie ograniczona, maksymalna jednostka)
			FormatFloat("00", (sec /60/60 >= 1 ) ? sec /60 %60 : sec /60 )+ ":" + 	// minuty
			FormatFloat("00", (sec /60 >= 1) ? sec % 60 : sec ) + "." + 			// sekundy
			*mils.get();                                   							// milisekundy

}
// ---------------------------------------------------------------------------
void Times::Show(TObject *Sender) {

	if ( !s )	Stop();                                                         // je�lin nie wywo�ano funkcji Stop()

//	FibonacciR->StatusBar1->Panels->Items[1]->Text = Result();
	if ( Sender != NULL ) {

//	try {

//		(reinterpret_cast< TControl *>	(Sender))->Hint 	= ResultHint();
		(reinterpret_cast< TControl *>	(Sender))->ShowHint = true;
//		(reinterpret_cast< TEdit *>		(Sender))->Text 	= Result();        	// dla odpowiedniego componentu wykona si� tylko jeden z poni�szych
//		(reinterpret_cast< TButton*>	(Sender))->Caption 	= Result();
		(reinterpret_cast< TStatusBar *>(Sender))->Panels->Items[1]->Text = Result();

//	} catch (...) {	}
	}
}
// ---------------------------------------------------------------------------
 void Times::Show( String *s, String *h ) {

	if ( !s )	Stop();                                                         // je�lin nie wywo�ano funkcji Stop()

	if (s) *s = Result();
	if (h) *h = ResultHinted();

 }
// ---------------------------------------------------------------------------
 void Times::checkuse() {

	if ( f & s ) Calculate();                                                   // je�li obydwa warunki spe�nione

	if ( !f ) formated = "You forgot use Start() method";
	if ( !s ) formated = "You forgot use Stop() method";
	if ( p && !c )  formated = ("You forgot use Continue method");
	if ( !p && c )  formated = ("You forgot use Pause method");

//	if ( p && !c )  ShowMessage("You forgot use Continue method");
//	if ( !p && c )  ShowMessage("You forgot use Pause method");
	

 }
// ---------------------------------------------------------------------------
 String Times::Result() {

	checkuse();

   return formated;
 }
// ---------------------------------------------------------------------------
  String Times::ResultHinted() {

	checkuse();

   return formated;
 }
// ---------------------------------------------------------------------------
 String Times::ResultInSeconds() {

	checkuse();

	if ( !f || !s ) return formated;                                          	// je�li jeden warunek niespe�niony

   return seconds;
 }
// ---------------------------------------------------------------------------
 void Times::lpPause() {

	if (p == 1) ShowMessage("Pause method already use");

	QueryPerformanceCounter(&lpEnd);

	p = 1;

	unique_ptr<double> Frequency(new double(lpFrequency.QuadPart));
	unique_ptr<double> Start(new double(lpStart.QuadPart));
	unique_ptr<double> End(new double(lpEnd.QuadPart));

	starttopaused = (*End - *Start) / *Frequency;
	//ShowMessage(starttopaused);

}
// ---------------------------------------------------------------------------
 void Times::lpcontinue() {

	if ( p == 0 ) ShowMessage("You forgot use Pause() method");
	if ( c == 1 ) ShowMessage("Continue method already use");

	c = 1;
	   QueryPerformanceCounter(&lpStart);

   }
// ---------------------------------------------------------------------------
 void Times::ResultToFile(String Name) {

	checkuse();
//	ofs(new ofstream());
	ofs = new ofstream;         seconds   =ResultInSeconds().ToDouble() ;
//				ShowMessage(seconds);
	(*ofs).open( (Name + ".txt").c_str() , ios::out | ios::app);

	*ofs  << //setprecision(27)  <<
	( (AnsiString)FloatToStrF( seconds,ffFixed, 18, 18 ) ).c_str() <<
	endl;

	(*ofs).close();

	delete ofs;
 }




// TComponent *Temp;
// for(int i = ComponentCount - 1; i >= 0; i--)
// {
//  Temp = Components[i];
//  if(!Temp->ClassNameIs("TLabel"))
//  {
//   reinterpret_cast<TEdit *>(Temp)->Text = "Jaki� tekst"; // rzutowanie mo�na by r�wnie dobrze wykona� na klas� TMemo, poniewa� ona r�wnie� posiada w�a�ciwo�� Text
//  }
// }

//SHFILEOPSTRUCT fos;   // z przeniesieniem do kosza
//  fos.hwnd = Handle;
//  fos.wFunc = FO_DELETE;
//  fos.pFrom = (ExtractFileDir(Application->ExeName) + "\\nazwapliku.xxx").c_str();  //nazwa kasowanego pliku, trzeba poda� pe�n� �cie�k� dost�pu
//	  fos.fFlags = FOF_ALLOWUNDO;
//  SHFileOperation(&fos);
// ---------------------------------------------------------------------------
// AnsiString DigitRewriteOLD(AnsiString w, int a ) {                           // wersja nie uko�czona
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
//		 char* buff = new char[w.Length()];     //LAST WRONG??FIND   //nie wiem czy mo�e by� dynamicznie alokowany
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
//		w.printf(buff);   	//nie dzia�a
//		buff = w.c_str();   //bug przy trzecim wywo�aniu funkcji
//
//			 for (int i = 0; i < w.Length(); i++) {			              		// nie jest ' <= ' bo ostatni znak to \0 (ko�cowy)
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
//			 if (indekscomma) { // usuwanie przecink�w
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
//					 (*p).Insert(',', indekscomma - wyj + a );        // by�o ...a- wyj  + 1)
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
//		if ((*p) != 0) { return *p;	}         // b��d??
//
//		else {  	 	  return 0;	}
//
//	 }
//
//	 __finally {
////
//		if (buff != NULL) {
//		free(l);
//		delete[] buff;    //NIErozwi�zany  //dlaczego wyrzuca b�ad??// jest to zwi�zane z d�ugo�ci� od 8 znak�w
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
