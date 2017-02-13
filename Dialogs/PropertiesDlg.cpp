//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Dialogs/PropertiesDlg.h"
#include "Unit1.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPropetisDlg *PropetisDlg;

//---------------------------------------------------------------------

 TPropetisDlg::TPropetisDlg(TComponent* AOwner, String* FilePath, bool ADS_1)
					: TForm(AOwner), path( initial_value_of_path(FilePath) )
 {
	Path = &path;                                      							// dla zabezpieczenia zmiennej œcie¿ki tworzymy referencje zmiennej typu const

	this->Text = "W³aœciwoœci: " + ExtractFileName(*FilePath);                  // nazwa okna

	Reg = new TRegistry;

//	if ( ZastosujBtn != NULL )
		ZastosujBtn->Enabled = true;                                               // przycisk zastosuj
//	ZastosujBtn->Hide();
	FillWnd();
 }

//---------------------------------------------------------------------

 void TPropetisDlg::FillWnd() {

	EditFileName->Text = ExtractFileName(*Path);
	EditPath->Text = ExtractFileDir(*Path);

	LoadImg();                                                                  // kolejnoœc funkcji jes wa¿na !!

	LoadDescriptionFromExtension();
	LoadSize();
	LoadTime();
	LoadAttrib();
 }

//---------------------------------------------------------------------

 void TPropetisDlg::LoadImg(){

	HICON ico;
	WORD idx;

	ico = ExtractAssociatedIcon( HInstance, (*Path).c_str(), &idx );

	if ( !ico ) {
		ShowError("B³¹d ikony LoadImg() " + *Path);
	}
	ImageEXE->Picture->Icon->Handle = ExtractAssociatedIcon(HInstance, (*Path).c_str(), &idx);

	wchar_t Exec[255];
	FindExecutableW( (*Path).c_str(), 0, Exec);
	ico = 0;																   	// ponowne u¿ycie ico
	ico = ExtractIconW(HInstance, Exec, 0);//ExtractIconExW( Exec, 1,0,&ico,0);
	//		 ico = LoadIcon( HInstance, IDI_WINLOGO );
	//		 ico = LoadIconW( HInstance, IDI_WINLOGO );
	ImageOpenWith->Picture->Icon->Handle = ico;

//	FibonacciR->StatusInfo((Exec));
	//						 ShowMessage(Exec);

	LoadDescrypOpenWithProgrm( Exec );

	Gdiplus::Bitmap *gdimg;
	gdimg = gdimg->FromHICON(ico);

	if( ImageOpenWith->Picture->Bitmap->Width == 0 )
			ImageOpenWith->Picture->Assign( NULL );

	Gdiplus::Graphics *grphx_hwnd;
	grphx_hwnd = grphx_hwnd->FromHDC( ImageOpenWith->Canvas->Handle );
	grphx_hwnd->DrawImage( gdimg, 0, 0, 18, 18 );

 }

//---------------------------------------------------------------------

void TPropetisDlg::LoadDescriptionFromExtension()
{
/*
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.flac\OpenWithProgids
HKEY_LOCAL_MACHINE\SOFTWARE\Classes\.docx
HKEY_LOCAL_MACHINE\SOFTWARE\Classes\.docx\OpenWithProgIDs

Opis rozszerzenia pl
HKEY_LOCAL_MACHINE\SOFTWARE\Classes\OpenOffice.Docx

Kind map
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\KindMap
HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\explorer\KindMap

cuœ
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\PropertySystem\PropertyHandlers\.docx
Domyœlna {993BE281-6695-4BA5-8A2A-7AACBFAAB69E}


HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows Portable Devices\FormatMap\.docx

HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\OpenOffice\OpenOffice\4.1.2\Capabilities\FileAssociations



*/
		Reg->RootKey = HKEY_CLASSES_ROOT;
		Reg->RootKey = HKEY_CLASSES_ROOT;
		Reg->OpenKey( ExtractFileExt(*Path), false);

		if ( Reg->ValueExists( "" ) )
		{
			String buff = Reg->ReadString( "" );
			Reg->CloseKey();
			Reg->RootKey = HKEY_CLASSES_ROOT;
			Reg->OpenKey( buff , false);

			if ( Reg->ValueExists( "" ) ) {
				EditFileType->Text = Reg->ReadString( "" ) + " (" + ExtractFileExt(*Path) + ")";                     // opis pliku
			}
		}
		Reg->CloseKey();
}

//---------------------------------------------------------------------

 void TPropetisDlg::LoadDescrypOpenWithProgrm( String path )
 {
	if (path == "") {

	   ShowError("Brak opisu string TPropetisDlg::LoadDescryp()");
	   return;
	}

	Reg->RootKey = HKEY_CLASSES_ROOT;

	Reg->OpenKey("Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache", false);

	if ( Reg->ValueExists( path ) )
	{
		EditOpenWith->Text = Reg->ReadString( path );                       // aplikacja otwieraj¹ca
	}
	else if ( !CompareStr( ExtractFileExt(*Path).LowerCase(), ".exe") )             	// dla Aplikacji
	{
//	String ExeName = "D:\\Builder\\FibonacciR\\Win32\\Debug\\Fibonacci.exe";
//
// GetAllFileVersionInformation(ExeName.c_str(), Memo1->Lines); // wersja pliku ACDSee8.exe
//	  EditFileType->Text = "Wersja pliku: " + ::GetFileVersionInfo( AnsiString(path).c_str(), "Opis");
		ImageOpenWith->Hide();
		EditOpenWith->Left = EditFileType->Left;
		LabelOpenWithL->Caption = "Opis:";
		EditOpenWith->Text = ::GetFileVersionInfo( (*Path).c_str(),  "FileDescription");

	   GetAllFileVersionInformation( ToArrW(*Path), ListView1);
//	   return;

	}
	else
	{
		EditOpenWith->Text = "Nieznana aplikacja";
		EditOpenWith->Left = EditFileType->Left;
		ShowError("Brak opisu w rejestrze dla: "+ (String)path);
	}
	Reg->CloseKey();
 }

//---------------------------------------------------------------------

void TPropetisDlg::LoadSize()
{
	unique_ptr<String> size(new String( filesize( ((AnsiString)*Path ).c_str()) ));

	EditSize->Text = GetSize( (*size).ToInt()) + "  (bajtów: "+ AddSpace(*size,3) +")";

	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;

	if ( GetDiskFreeSpaceW( ( ExtractFileDrive(*Path) ).c_str(),
		&dwSectPerClust,                                                                // sektorów na klaster
		&dwBytesPerSect,                                                                // bajtów na sektor
		&dwFreeClusters,
		&dwTotalClusters))
	{
	dwFreeClusters =  (*size).ToInt();

	dwTotalClusters =  dwFreeClusters % ( dwBytesPerSect * dwSectPerClust );    // reszta z dzielenia (modulo) z jednostki alokacji plików
	if ( dwTotalClusters != 0 )
    	*size =  (( dwBytesPerSect * dwSectPerClust ) - dwTotalClusters) + dwFreeClusters;  // jednostka alodacji (np.4096 bajtów) - modulo
	}
	EditSizeOnDisk->Text = GetSize( (*size).ToInt() ) + "  (bajtów: "+ AddSpace(*size,3) +")";
}

//---------------------------------------------------------------------

TIME_ZONE_INFORMATION* get_zone(TIME_ZONE_INFORMATION *tzi) {

	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken);  // WYMAGANE UPRAWNIENIA
	LookupPrivilegeValue(NULL, SE_TIME_ZONE_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	/* dwRet = */ GetTimeZoneInformation(tzi);

//	if(dwRet == TIME_ZONE_ID_STANDARD || dwRet == TIME_ZONE_ID_UNKNOWN)
//	  ShowMessage( tziOld.StandardName);
//   else if( dwRet == TIME_ZONE_ID_DAYLIGHT )
//	  ShowMessage(tziOld.DaylightName);
//   else
   {
//	  ShowError("Nie uda³o siê pobraæ strefy czasowej");
//      return 0;
   }
   	 // Disable the privilege

	tkp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);

	return tzi;
}

//---------------------------------------------------------------------
void  FileTimeZonedToDateTime( FILETIME* f, TDateTime &DT ) {

	SYSTEMTIME stFileTime = {0};
	TIME_ZONE_INFORMATION tzi = {0};

	FileTimeToSystemTime( f, &stFileTime);          // WRITE, MODIFY
	SystemTimeToTzSpecificLocalTime( get_zone( &tzi ), &stFileTime, &stFileTime);
	DT = SystemTimeToDateTime(stFileTime);
  }

//---------------------------------------------------------------------

 void TPropetisDlg::LoadTime() {

	TDateTime DT = 0;

	GetFileAttributesExA( ToArrW(*Path), GetFileExInfoStandard, &fileAttrData); // pobieramy info o pliku

	FileTimeZonedToDateTime( &fileAttrData.ftLastWriteTime, DT );    // WRITE, MODIFY

	LabelEditedData->Text = FormatDateTime("dddddd, hh:nn:ss", DT);
//	LabelEditedTime->Text = FormatDateTime("hh:nn:ss", DT);
	LabelEditedDay->Text  = FormatDateTime("(dddd)", DT);

	FileTimeZonedToDateTime( &fileAttrData.ftCreationTime, DT );     // CREATE TIME

	EditCreatedDate->Text = DT.FormatString("dddddd, hh:nn:ss");
//	EditCreatedTime->Text = FormatDateTime("hh:nn:ss", DT);
	EditCreatedDay->Text  = FormatDateTime("(dddd)", DT);

	FileTimeZonedToDateTime( &fileAttrData.ftLastAccessTime, DT );																			// ACCESS

	LabelLastUseData->Text = FormatDateTime("dddddd, hh:nn:ss", DT);            // LAST ACCESS TIME
//	LabelLastUseTime->Text = FormatDateTime("hh:nn:ss", DT);
	LabelLastUseDay->Text  = FormatDateTime("(dddd)", DT);
}

//---------------------------------------------------------------------

 void TPropetisDlg::LoadAttrib() {

	Attributes = FileGetAttr(*Path);

	CheckBoxReadOnly->Checked = Attributes & faReadOnly;
	CheckBoxArch->Checked = Attributes & faArchive;
	CheckBoxSys->Checked = Attributes & faSysFile;
	CheckBoxHide->Checked = Attributes & faHidden;

	if ( CheckBoxArch->Checked ) 	CheckBoxArch->Show();
	if ( CheckBoxSys->Checked  ) 	CheckBoxSys->Show();
 }

//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::OKBtnClick(TObject *Sender)
{
	if ( ZastosujBtn->Enabled )
		 ZastosujBtn->Click();

	if (CompareStr( EditFileName->Text, ExtractFileName(*Path) ))               // zmiana nazwy pliku
	{
		RenameFile( *Path, ToArrW(ExtractFilePath(*Path) + "\\" + EditFileName->Text) );
	}

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::CheckBoxHideClick(TObject *Sender)
{
	ZastosujBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::FormCreate(TObject *Sender)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup( &m_gdiplusToken, &gdiplusStartupInput, NULL);
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::FormDestroy(TObject *Sender)
{
	Gdiplus::GdiplusShutdown( m_gdiplusToken );
	delete Reg;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::CancelBtnClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void TPropetisDlg::SetAttr()
{
	 NewAttributes = Attributes;

	 if (CheckBoxReadOnly->Checked)
	   NewAttributes = NewAttributes | faReadOnly;
	 else
		NewAttributes = NewAttributes & ~faReadOnly;

	 if (CheckBoxArch->Checked)
	   NewAttributes = NewAttributes | faArchive;
	 else
	   NewAttributes = NewAttributes & ~faArchive;

	 if (CheckBoxSys->Checked)
	   NewAttributes = NewAttributes | faSysFile;
	 else
	   NewAttributes = NewAttributes & ~faSysFile;

	 if (CheckBoxHide->Checked)
	   NewAttributes = NewAttributes | faHidden;
     else
	   NewAttributes = NewAttributes  & ~faHidden;

	 if (NewAttributes != Attributes)
	   FileSetAttr( *Path, NewAttributes);
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::ZastosujBtnClick(TObject *Sender)
{
	SetAttr();
	SetTime();
	ZastosujBtn->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelLastUseDataMouseLeave(TObject *Sender)       // wyœwietla dzieñ tygodnia po najechaniu na date
{
	LabelLastUseDay->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelEditedDataMouseLeave(TObject *Sender)
{
	LabelEditedDay->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelEditedDataMouseEnter(TObject *Sender)
{
	LabelEditedDay->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::EditCreatedDateMouseEnter(TObject *Sender)
{
	EditCreatedDay->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::EditCreatedDateMouseLeave(TObject *Sender)
{
	EditCreatedDay->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelLastUseDataMouseEnter(TObject *Sender)
{
	LabelLastUseDay->Visible = true;
}
//---------------------------------------------------------------------------
void TPropetisDlg::GetEditedTime(SYSTEMTIME *create, SYSTEMTIME *access, SYSTEMTIME *write)
{

	if ( DateTimePickerCreateDate->Visible ) {
		DateTimeToSystemTime( (DateTimePickerCreateDate->DateTime), *create );
		TzSpecificLocalTimeToSystemTime( NULL, create, create);
	}else {
		FileTimeToSystemTime( &(fileAttrData.ftCreationTime), create );
//		SystemTimeToTzSpecificLocalTime( NULL, create, create);
	}

	if ( DateTimePickerAccessDate->Visible ) {
		DateTimeToSystemTime( (DateTimePickerAccessDate->DateTime), *access );
		TzSpecificLocalTimeToSystemTime( NULL, access, access);
	} else {
		FileTimeToSystemTime( &(fileAttrData.ftLastAccessTime), access );
//		SystemTimeToTzSpecificLocalTime( NULL, access, access);
	}

	if ( DateTimePickerWriteDate->Visible ) {
		DateTimeToSystemTime( (DateTimePickerWriteDate->DateTime),  *write  );
		TzSpecificLocalTimeToSystemTime( NULL, write, write);
	} else {
		FileTimeToSystemTime( &(fileAttrData.ftLastWriteTime), write );
//		SystemTimeToTzSpecificLocalTime( NULL, write, write);
	}
}

//---------------------------------------------------------------------------

void TPropetisDlg::SetTime()
{
//	if ( !DateTimePickerCreateDate->Visible )
//		if ( !DateTimePickerAccessDate->Visible )
//			if ( !DateTimePickerWriteDate->Visible )
//				return;

	SYSTEMTIME	screate, saccess, swrite = {0};
	FILETIME	fcreate, faccess, fwrite = {0};

	DateTimePickerCreateDate->Time = DateTimePickerCreateTime->Time;
	DateTimePickerAccessDate->Time = DateTimePickerAccessTime->Time;
	DateTimePickerWriteDate->Time  = DateTimePickerWriteTime->Time;

	HANDLE hFile = CreateFileW( (path).c_str(), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE){

		GetEditedTime( &screate, &saccess, &swrite );

//		if(sTime.wDay > 0 && sTime.wDay < 31 || sTime.wMonth > 0 && sTime.wMonth < 13 || sTime.wHour > -1 && sTime.wHour < 24 || sTime.wMinute > -1 && sTime.wMinute < 60 || sTime.wSecond > -1 && sTime.wSecond < 60)
		{
			if(SystemTimeToFileTime(&screate, &fcreate) != NULL &&
			   SystemTimeToFileTime(&saccess, &faccess) != NULL &&
			   SystemTimeToFileTime(&swrite,  &fwrite )	!= NULL )
			{
				if(SetFileTime(hFile, &fcreate, &faccess, &fwrite) != NULL){    // dwa ostatnie parametry zamienione miejscami nie wiem czemu ale dzia³a

				}else{
					ShowError("Unable to set the specified time!\n");
				}
			}else{
				ShowError("Unable to convert the system time\n");
			}
		}
//		else{
//				ShowError("Input not accepted!\n");
//		}
	}else{
		ShowError("\nUnable to open: %s\n");
	}
	CloseHandle(hFile);
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::EditCreatedDateClick(TObject *Sender)
{
	DateTimePickerCreateDate->Date = DateTimePickerCreateDate->DateTime.CurrentDate();
	DateTimePickerCreateTime->Time = DateTimePickerCreateTime->DateTime.CurrentTime();
	DateTimePickerCreateDate->Show();
	DateTimePickerCreateTime->Show();
	EditCreatedDate->Hide();
	CheckBoxAllSame->Show();
	ZastosujBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelEditedDataClick(TObject *Sender)
{
	DateTimePickerAccessDate->Date = DateTimePickerAccessDate->DateTime.CurrentDate();
	DateTimePickerAccessTime->Time = DateTimePickerAccessTime->DateTime.CurrentTime();
	DateTimePickerAccessDate->Show();
	DateTimePickerAccessTime->Show();
	LabelEditedData->Hide();
	CheckBoxAllSame->Show();
	ZastosujBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelLastUseDataClick(TObject *Sender)
{
	DateTimePickerWriteDate->Date = DateTimePickerWriteDate->DateTime.CurrentDate();
	DateTimePickerWriteTime->Time = DateTimePickerWriteTime->DateTime.CurrentTime();
	DateTimePickerWriteDate->Show();
	DateTimePickerWriteTime->Show();
	LabelLastUseData->Hide();
	CheckBoxAllSame->Show();
	ZastosujBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::EditCreatedDateKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	EditCreatedDateClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelEditedDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	LabelEditedDataClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelLastUseDataKeyDown(TObject *Sender, WORD &Key,
		  TShiftState Shift)
{
	LabelLastUseDataClick(Sender);
}

/***************************************************************************/

bool Properties(String* file_path, bool ADS)
{
//	unique_ptr<TPropetisDlg> DLG(new TPropetisDlg( FibonacciR, file_path, ADS ));

	TPropetisDlg *d = new TPropetisDlg( FibonacciR, file_path, ADS );
}

//---------------------------------------------------------------------------

bool Properties( String* path, String* name, bool ADS )
{
//	unique_ptr<TPropetisDlg> DLG(new TPropetisDlg( FibonacciR, &(Getpath(*path, 1) + *name), ADS ));

	TPropetisDlg *d = new TPropetisDlg( FibonacciR, &(Getpath(*path, !ADS) + *name),  ADS); // decyduje czy dodaæ slasha
}

//---------------------------------------------------------------------------

String AddSpace( String text, unsigned pos )
 {
	for ( int i = text.Length()-2; i > 0; i -= pos )
	{
		text.Insert(" ", i);
	}
	return text;
 }

//---------------------------------------------------------------------------

String GetFileVersionInfo(wchar_t *ModulePath, String KeyName)
{
 LPVOID lpStr1 = NULL, lpStr2 = NULL;
 WORD* wTmp;
 DWORD dwHandlev = NULL;
 UINT dwLength;
 wchar_t sFileName[1024] = {0};
 wchar_t sTmp[1024] = {0};
 String sInfo;
 LPBYTE *pVersionInfo;

 if(ModulePath == NULL) GetModuleFileName( NULL, sFileName, 1024);
 else wcscpy(sFileName, ModulePath);

 DWORD dwInfoSize = GetFileVersionInfoSize(sFileName, &dwHandlev);

 if(dwInfoSize)
 {
  pVersionInfo = new LPBYTE[dwInfoSize];
  if(GetFileVersionInfo(sFileName, dwHandlev, dwInfoSize, pVersionInfo))
  {
   if(VerQueryValue(pVersionInfo, L"\\VarFileInfo\\Translation", &lpStr1, &dwLength))
   {
		wTmp = (WORD*)lpStr1;
		swprintf(sTmp, ("\\StringFileInfo\\%04x%04x\\" + KeyName).w_str(), *wTmp, *(wTmp + 1));
		if(VerQueryValue(pVersionInfo, sTmp, &lpStr2, &dwLength)) sInfo = (LPCTSTR)lpStr2;
   }
  }
  delete[] pVersionInfo;
 }
 KeyName = sInfo;
 return KeyName;
}

//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::LabelAttribLClick(TObject *Sender)
{
	CheckBoxReadOnly->Show();
	CheckBoxArch->Show();
	CheckBoxSys->Show();
	CheckBoxHide->Show();
}
void __fastcall TPropetisDlg::CheckBoxAllSameClick(TObject *Sender)
{
	if (CheckBoxAllSame->Checked) {
		DateTimePickerCreateDate->Show();
	  DateTimePickerCreateTime->Show(); }
//	DateTimePickerCreateDate->Visible 	= CheckBoxAllSame->Checked;
//	DateTimePickerCreateTime->Visible 	= CheckBoxAllSame->Checked;
	DateTimePickerAccessDate->Enabled 	= !CheckBoxAllSame->Checked;
	DateTimePickerAccessTime->Enabled 	= !CheckBoxAllSame->Checked;
	DateTimePickerWriteDate->Enabled  	= !CheckBoxAllSame->Checked;
	DateTimePickerWriteTime->Enabled  	= !CheckBoxAllSame->Checked;
	EditCreatedDate->Visible  			= !CheckBoxAllSame->Checked;
	LabelEditedData->Visible  			= !CheckBoxAllSame->Checked;
	LabelLastUseData->Visible  			= !CheckBoxAllSame->Checked;
}
//---------------------------------------------------------------------------

