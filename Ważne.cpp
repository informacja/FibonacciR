#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------

void __fastcall increment(TCSpinButton* name) {

	curpos = FibonacciR->wej->SelStart;

	try {

		reinterpret_cast<TEdit*>(name->FocusControl)->Text =
			reinterpret_cast<TEdit*>(name->FocusControl)->Text.ToDouble() + S::increment_value;

	} catch (...) {

		try {

		reinterpret_cast<TEdit*>(name->FocusControl)->Text =
		(DigitRewrite(reinterpret_cast<TEdit*>(name->FocusControl)->Text)).ToDouble() + S::increment_value;

		} catch (...) {

			LogSave("B³¹d inkrementacji");
			reinterpret_cast<TEdit*>(name->FocusControl)->Text = FibonacciR->w_default;
		}
	}

	FibonacciR->wej->Perform(EM_SETSEL, curpos + 1, curpos + 1);
}

void __fastcall decrement(TCSpinButton* name) {

	curpos = FibonacciR->wej->SelStart;

	try {

		reinterpret_cast<TEdit*>(name->FocusControl)->Text =
			reinterpret_cast<TEdit*>(name->FocusControl)->Text.ToDouble() - S::increment_value;

//		unique_ptr<double> x(new double(reinterpret_cast<TEdit*>(name->FocusControl)->Text.ToDouble()));
//		*x -= FibonacciR->w_in;
	}
	catch (...) {

		try {

			reinterpret_cast<TEdit*>(name->FocusControl)->Text =
			(DigitRewrite(reinterpret_cast<TEdit*>(name->FocusControl)->Text)).ToDouble() - S::increment_value;

		} catch (...) {

			LogSave("B³¹d dekrementacji");
			reinterpret_cast<TEdit*>(name->FocusControl)->Text = FibonacciR->w_default;
		}
	}

	FibonacciR->wej->Perform(EM_SETSEL, curpos - 1, curpos - 1);
}
//---------------------------------------------------------------------------
 void __fastcall KeyD(WORD &Key, TCSpinButton* Button) {

	 if (Key == vkUp)  	 		increment(Button);

	 else if (Key == vkDown)	decrement(Button);

 }

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::OnDropFiles(TMessage &Msg) {

	if(Msg.Msg == WM_DROPFILES)
	 {
		ListBox1->Items->Clear();
		TListItem *ListIt;

		short nFiles;
		unique_ptr<char> buffer(new char[256]);

// int fileCount = DragQueryFile((HDROP)Msg.WParam, 0xFFFFFFFF, NULL, 0);

		nFiles = DragQueryFile((HDROP)Msg.WParam, 0xFFFFFFFF, NULL, 0);

		switch ( PageControl3->ActivePageIndex ) {

		case 0:                                                                 // FI
		{

		}
		break;

		case 1:                                                                 // ADS
		{
			if (PageControl4->ActivePageIndex == 1) {                               // Szukaj ADS

		   DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get() , 256);
			   // tutaj nale¿y umieszczaæ kod odpowiedzialny za wykonywanie operacji na upuszczonym pliku
			   ButtonedEditSearch->Text = buffer.get();
		}
		else if (PageControl4->ActivePageIndex == 0) {

		  if ( !CursorAt( FibonacciR->EditADSSave->Handle )) {                          // jeœli poza EditADSSave

			unique_ptr<String> Drive(new String);

			for(int i = 0; i < nFiles; i++)
			  {
			   DragQueryFileA((HDROP)Msg.WParam, i, buffer.get() , 256);
			   // tutaj nale¿y umieszczaæ kod odpowiedzialny za wykonywanie operacji na upuszczonym pliku

				ListIt = ListViewDrop->Items->Add();
				ListIt->Caption = ExtractFileDir( buffer.get() );     			// œcie¿ka pliku
				ListIt->SubItems->Add( ExtractFileName(buffer.get())); 			// nazwa pliku
				ListIt->SubItems->Add(GetSize( filesize(buffer.get()) ));

				ListIt->ImageIndex = TypeFileIcon((String*) &(ToStr( buffer.get())), ListViewDrop);

//				ListIt->SubItems->Add( *Drive.get() + " " + ( GetVolumeName( ( *Drive.get() + "\\").c_str())) );
		//						 Counter::size_files  += (*sr).Size;
//
//ListViewDrop->Items->Add();
			   ListBox1->Items->Add(buffer.get());
			  }

			  *Drive = ExtractFileDrive(buffer.get()) ;

//			  ComboBox1->Text = *Drive + " " + (GetVolumeName((*Drive + "\\").c_str()));
//			  ComboBox1Change(NULL);

			}	else {
				DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get() , 256);
				FibonacciR->EditADSSave->Text = buffer.get();
			}
		   }
		}
		break;

		case 2:																   	// System
		{

			if (PageControl5->ActivePage == TabSheetWindows ) {

				DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get() , 256);
				EditFileManger->Text = buffer.get();

			}

		}
		break;

		case 3:																	// Grafika
		{
		   if (PageControl3->ActivePage == TabSheetGraph)                        	// grafika GDI+
		   {
			if (PageControl1->ActivePage == TabSheetConvert)
			{
				  DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get() , 256);

				  if ( !CursorAt( FibonacciR->EditLocalization->Handle ))      	// jeœli poza Editem z œcie¿k¹ eksportu
				  {
					Loading_image_success( GdiPlus->Load_Image( ImagePreview, &((String)buffer.get()) ) ); // ³aduje ikonkê grafiki
				  }
				  else
				  {
					EditLocalization->Text = buffer.get();                     	// œcie¿ka eksportu grafiki
				  }
			}
			else if ( PageControl1->ActivePage == TabSheetBatchConvert)
			{
				if ( !CursorAt( FibonacciR->EditBatchOut->Handle )) {          	// jeœli poza Editem z œcie¿k¹ eksportu

					for(int i = 0; i < nFiles; i++)
					{
						DragQueryFileA((HDROP)Msg.WParam, i, buffer.get() , 256);
						ValueListEditorBatch->InsertRow( buffer.get(), GetSize( filesize(buffer.get())), 0);
					}
				}
				  else
				  {
					DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get() , 256);
					EditBatchOut->Text = buffer.get();
				  }
			}
		   }

		}
		break;

		default:

            ;
		}

		DragFinish((HDROP)Msg.WParam);
	 }
	 Df(Msg);
   }
//---------------------------------------------------------------------------
 void __fastcall TFibonacciR::DoShowHint(UnicodeString &HintStr, bool &CanShow, THintInfo &HintInfo)
{
//  if (HintInfo.HintControl == StatusBar1)
//  {
//    HintInfo.HintColor = clAqua;// Changes only for this hint
//    HintInfo.HintMaxWidth = 120; // Hint text word wraps if width is greater than 120
////	HintInfo.HintPos.x += Button9->Width; // Move hint to right edge
////	  if (HintInfo.HintControl == Button10)
//	HintInfo.HideTimeout = 30000;
////	Application->HintHidePause = 30000;
//  }
////	  StatusBar1->Panels->Items[0]->Text =  *HintStr;
//  StatusBar1->Panels->Items[1]->Text =
//		GetLongHint(Application->Hint);
}

void __fastcall TFibonacciR::FormCreate(TObject *Sender) {

try {
	Application->ShowHint = true;
//	Application->OnShowHint = DoShowHint;

	if(!ParamStr(1).IsEmpty())	Memo1->Lines->LoadFromFile(ParamStr(1));        // œcie¿ka, parametr programu

	OldPathFile = ParamStr(1);

//	unique_ptr<TCHAR> buffer(new TCHAR[MAX_PATH]);
//	SHGetSpecialFolderPath(NULL, buffer.get(), CSIDL_DESKTOPDIRECTORY , 0);
//	ButtonedEditSearch->Text = buffer.get();
	ButtonedEditSearch->Color = clWindow;

	ListViewDrop->SmallImages = IconList;

	EditADSSave->Text = GetPath_with_access( &(GetCurrentDir()), W_OK );        // ustawianie œcie¿ki tworzenia strumieni na katalog
	CheckFileSystem( EditADSSave );
	EditADSSave->OnClick( EditADSSave );                                        // zdarzenie on clik eliminuje podœwietlenie, przy uruchomieniu programu
	ButtonedEditSearch->OnClick( ButtonedEditSearch );

	unique_ptr<TRegistry> Reg (new TRegistry);
									//Hera         //FibonacciR
	if ( Reg->OpenKey("Software\\" +  S::FirmName +"\\"+ S::ProductName, false) )
   {
	  if (Reg->ValueExists("Left"))		Left   = Reg->ReadInteger("Left");
	  if (Reg->ValueExists("Top"))		Top    = Reg->ReadInteger("Top");
	  if (Reg->ValueExists("Width"))	Width  = Reg->ReadInteger("Width");
	  if (Reg->ValueExists("Height"))	Height = Reg->ReadInteger("Height");
   }

   Reg->CloseKey();
   Reg->RootKey = HKEY_CURRENT_USER;
	if ( Reg->OpenKey("Software\\MPC-HC\\MPC-HC", false ) )
	{
	if (Reg->ValueExists("ExePath"))
		MPC_HC_Player_path 	 = Reg->ReadString("ExePath");
		Odtwarzacz1->Hint 	 = MPC_HC_Player_path;
		Odtwarzacz1->Visible = true;											// domyœlnie nie widzialny
	}

   } catch (...) {
   ShowError("B³¹d FormCreate() przy próbie pobrania wartoœci z rejestru");
 }
}
//---------------------------------------------------------------------------
double Two2One(double z) {

	unique_ptr<AnsiString> add(new AnsiString(z));

	(*add).Insert(",", 2);

//           if ( (*w).SubString(1,1) >= 5) {                                   //pirerwszy znak jest wiêkszy od 5 to *buff +1
//			  (*buff) += FibonacciR->w_in;
//		  }

	z = Toint((*add).ToDouble());                                               //zaokr¹glane np 1,5 zwróci 2

	return z;
}
//---------------------------------------------------------------------------
double __fastcall Round(double x) {

 try {

	if ( ((String)(S::increment_value)).LastDelimiter(",")) {                     //w przypadku gdy inkrementacja jest z przecinkiem

	unique_ptr<AnsiString> buff(new AnsiString);
	unique_ptr<unsigned char> lenght(new unsigned char);                        //zakres(0-4) iloœæ miejsc po przecinku waroœæi inktementacji
	unique_ptr<AnsiString> w(new AnsiString (AnsiString(S::increment_value)) ); // z przypisaniem wartoœci inkrementacji
	unique_ptr<unsigned short> commapos(new unsigned short ((*w).LastDelimiter(",")) ); //z ustaleniem pozycji przecinka

		if ( *commapos ) {                                                      // sekcja okreœlaj¹ca d³ugoœæ wyrazu inkrementacji

			(*w).Delete(  1, *commapos );

			 *lenght = (*w).Length();

		} else   *lenght = 0;

		*w = x;                                                                 // *w jest wolne po ustaleniu dlugoœæi inkrementacji

//		if ( (*w).LastDelimiter(",") == (*w).Length() -2) { throw w;}

	//maksymalna d³ugoœæ to 16 znaków inaczej zawsze siê wykona
	if ( (*w).LastDelimiter(",") ) {                                            // jeœli jest przecinek

		*buff = (*w).SubString(0, (*w).Pos(",") -1 + (*lenght) );			   	// kopiuj od lewej razem z przecinkiem

		(*w).Delete(1, (*w).LastDelimiter(",") +(*lenght) -1  );                // usuwanie tego co wy¿ej skopiowano jest w *buff
		(*w).Delete(3, 100);													// 0 nie mo¿e byæ pierwszym parametrem funkcji bo siê nie wykona

		*buff += ( Two2One((*w).ToDouble()) );                                  // zaokr¹glanie 2 cyfr do jednej tak jakby pomiêdzy nimi by³przecinek

		x = (*buff).ToDouble();

	}

//		AnsiString format;

//		format = "0,";
//			while (*lenght) {
//		(*lenght)--;
//		format += "0";
//		}
//		FibonacciR->StatusBar1->Panels->Items[0]->Text = format;

	} else    																	//jeœli w wartoœci inkrementacji niema przecinka

		x = Cutting( x );

  } catch (...) {

		LogSave("Nieznany b³¹d Round(double x) zwracana wartoœæ x wynosi: " + CurrToStr(x));
		return x;
	}

	return x;
}
//---------------------------------------------------------------------------
double Cutting ( double x ) {                                                   // obcina od przecinka w prawo

	unique_ptr<AnsiString> buff(new AnsiString(x));

	x = (*buff).LastDelimiter(",");

	(*buff).Delete( x, (*buff).Length() - x );

	x = (*buff).ToDouble();

	return x;
}
//---------------------------------------------------------------------------
String __fastcall TFibonacciR::GetVolumeName(LPCTSTR FindDrive) {

	TCHAR lpVolumeName[MAX_PATH];
	char szVolumeName[MAX_PATH];

	if (GetVolumeInformation(FindDrive, lpVolumeName, sizeof(lpVolumeName),	NULL, NULL, NULL, NULL, 0) == 0) {

		strcpy(szVolumeName, "Brak Nazwy");                                     // by³o szVolumeName teraz lpVolumeName

		return (String)szVolumeName;
	}
	else
		// sprintf(szVolumeName, "[%s]", lpVolumeName); 						//uwa¿am za niepotrzebe
		// zmieniono zwracan¹ wartiœæ z szVolumeName
			return (AnsiString)lpVolumeName;
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::EnumDrivers(TStrings *EnumList) {

 char DriveName[4] = "A:\\";

 for (char Drive = 'A'; Drive <= 'Z'; Drive++) {

  DriveName[0] = Drive;                                                         //zmiana litery

  switch(GetDriveTypeA(DriveName)) {

   case DRIVE_UNKNOWN:
                        DriveName[1] = '\0';
						EnumList->Add(" Nieznany " + (String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
						DriveName[1] = ':';
						break;

   case DRIVE_REMOVABLE:
						DriveName[1] = '\0';
						EnumList->Add((String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
						DriveName[1] = ':';
						break;
   case DRIVE_FIXED:
						DriveName[1] = '\0';
						EnumList->Add((String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
						DriveName[1] = ':';
						break;
//   case DRIVE_CDROM:
//						DriveName[1] = '\0';
//						EnumList->Add((String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
//						DriveName[1] = ':';
//						break;
   case DRIVE_REMOTE:
						DriveName[1] = '\0';
						EnumList->Add((String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
						DriveName[1] = ':';
						break;
//   case DRIVE_RAMDISK:
//						DriveName[1] = '\0';
//						EnumList->Add((String)Drive + ": " + GetVolumeName(((String)Drive + ":\\").c_str()));
//						DriveName[1] = ':';
//						break;
  }
 }
}
//
//void __cdecl ThreadProc( void * Args )
//{
//
//
////	_endthread();
//}


// --------------------------------------------------------------------------- bool CloseProcess(DWORD ID)
{
 DWORD ExitCode;
 HWND hWnd;
 bool Result = true;

 if(ID)
 {
  hWnd = (HWND__ *)OpenProcess(PROCESS_TERMINATE, true, ID);
  if(hWnd)
  {
   GetExitCodeProcess(hWnd, &ExitCode);
   Result = TerminateProcess(hWnd, ExitCode);
  }
  else return false;
 }
 else return false;

 CloseHandle(hWnd);
 return Result;
}
// ---------------------------------------------------------------------------
TNotifyEvent __fastcall BirngFront(unsigned *a)
{
	Application->BringToFront();
	*a += 1;
//	return;
}
// ---------------------------------------------------------------------------
void BingToFront(unsigned t, unsigned i) {

	unique_ptr<TTimer> timer(new TTimer(0));
	unique_ptr<unsigned> count(new unsigned(0));

	(*timer).Interval = i;
	(*timer).Enabled = true;

	(*timer).OnTimer = BirngFront(count.get());

	if (*count >= t ) 	(*timer).Enabled = false;
 }

// ---------------------------------------------------------------------------



//---------------------------------------------------------------------------
 void MakePrintScreen() {

 try {

if     (Form2->RadioButton1->Checked)
			FibonacciR->StatusInfo( ScreenJPG( GetQualityJPEG(), Form2->CheckBoxSaveClipboard->Checked)); 	//JPG


else if(Form2->RadioButton3->Checked)
			FibonacciR->StatusInfo( ScreenBMP( 0, Form2->CheckBoxSaveClipboard->Checked) );	//BMP   //lossles


else  		FibonacciR->StatusInfo( ScreenPNG( GetQualityPNG(),	Form2->CheckBoxSaveClipboard->Checked) );  	//PNG

	}catch (Exception &exception) {

		ShowError("Nie uda³o siê zapisaæ screena",  &exception );
		Application->ShowException(&exception);
	}
	catch (...) {

		LogSave("Nie uda³o siê zapisaæ screena");
		FibonacciR->StatusInfo("Nie uda³o siê zapisaæ screena");
	}
}

//---------------------------------------------------------------------------
 void DuplicateAppCheckParam(wchar_t* M_name, wchar_t* cmd) {
//			HANDLE hMutex ;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, M_name);                      // BUG    mo¿e try cath
//								  ShowMessage( ErrorToText( GetLastError() ))     ;

	if ( (long)hMutex == ERROR_FILE_NOT_FOUND ) ShowMessage("B³¹d mutex nie odnaleziony");

	if( hMutex ){                      											// jeœli jest mutex
//				  ShowMessage(9);
		HWND hWnd = FindWindow( L"TFibonacciR", L"FibonacciR (beta)");
		SetForegroundWindow(hWnd);

//		cmd = L"123";

		char * test = ( (AnsiString)cmd ).c_str();


			if(strlen((char*)cmd) != 0) {

				COPYDATASTRUCT cds;
//				ShowMessage(strlen( (AnsiString(cmd)).c_str() ) + 1);
				cds.cbData = strlen( (AnsiString(cmd)).c_str() ) + 1;
//				cds.lpData = ( StringReplace(cmd, "\"", "", TReplaceFlags() << rfReplaceAll) ).c_str();
				cds.lpData = test;
//				   ShowMessage( *(String*)cds.lpData );                         // bug
//				   FibonacciR->Edit2->Text =  *(String*)cds.lpData;

				SendMessage(	hWnd, WM_COPYDATA, 0, (LPARAM)&cds);
				ReleaseMutex(hMutex);
//				Application->Terminate();                                       // nie u¿ywaæ blokuje wszystkie wyst¹pienia (zawiesza)
				exit(0);

			} else {	ReleaseMutex(hMutex); }
		}
 }
//---------------------------------------------------------------------------
void EarlierIsMinimized(__out) {

//	unique_ptr<HANDLE> hMutex(new HANDLE( 0));
//
//	if( *hMutex.get() ){                     // jeœli jest mutex
//				ShowMessage(Application->Title);
//		HWND hWnd = FindWindow(L"TFibonacciR", L"FibonacciR (beta)");
//		SetForegroundWindow(hWnd);
//
////		COPYDATASTRUCT cds;
//		// cds.cbData = strlen((char*)cmd) + 1;
//		// cds.lpData = StringReplace(cmd, "\"", "", TReplaceFlags() << rfReplaceAll).c_str();
//		SendMessage(hWnd, WM_COPYDATA, (LPARAM)"Zrób coœ", (LPARAM)L"zrób coœ");
//		ReleaseMutex(*hMutex);
//		// Application->Terminate();                                       		// nie u¿ywaæ blokuje wszystkie wyst¹pienia (zawiesza)
//		exit(0);
//
//	}
//
//	ReleaseMutex(hMutex.get());
}
// ---------------------------------------------------------------------------

 bool Dir_File_exist( TEdit* edit ) {

	if ( DirectoryExists(edit->Text) )   return 1;
	if ( FileExists(edit->Text) )        return 1;

	return 0;
}


// ---------------------------------------------------------------------------

String GetPath_with_access(String * s, int permission, String DefaultPath ) {

	if ( access( ToArrW( s ), permission ) == 0) return *s;

	else
	{
		unique_ptr<unsigned short> pos(new unsigned short( (*s).Length() ));

		do {

			(*s).Delete(*pos, 1);
			(*pos)--;
			if ( !*pos) break;                                                 	// zabezpieczenie przed usuwaniem z pustego stringa

		} while ( access( ToArrW( s ), permission ) != 0 );
	}

	if ( (*s).IsEmpty() ) return DefaultPath;
}

// ---------------------------------------------------------------------------
void Set_me_null_BEFORE_KILL( HWND h )
{
	for ( int i = 0; i < FibonacciR->point_array.size(); i++) {
		if( h == FibonacciR->point_array[i]->Handle )
			if ( FibonacciR->point_array[i]->Handle != NULL ) {
				 DeleteOrRelease(FibonacciR->point_array[i]);
				 FibonacciR->point_array[i] = NULL;
			}
	}

}
//---------------------------------------------------------------------------
bool Close_Points_WND()        // TO DO DONT WORK
{
	bool good = false;

	for ( int i = FibonacciR->point_array.size() - 1 ; i >= 0; i--) {
	if ( NULL != FibonacciR->point_array[i] )
		if ( IsWindow (FibonacciR->point_array[i]->Handle) )
			if ( FibonacciR->point_array[i]->Handle != NULL ) {
				FibonacciR->point_array[i]->Destroying();
				DeleteOrRelease(FibonacciR->point_array[i]);
			}
	}

	FibonacciR->point_array.resize(0);
	good = true;

	return good;
}

//---------------------------------------------------------------------------

void __fastcall Move_WND( HWND h, int X, int Y)
{
	if ( X != -1 && Y != -400 )
	{
		MoveWindow( h,X,Y,0,0,true);
	}

	int x, y, Xmax, Ymax = 0;

	Xmax = GetSystemMetrics( SM_CXVIRTUALSCREEN);
	Ymax = GetSystemMetrics( SM_CYVIRTUALSCREEN);
	//Sleep(10);

	//MoveWindow( h,x,y,0,0,true);
}

//---------------------------------------------------------------------------
 inline void DeleteOrRelease(TCustomForm *f)
{
  if (f->HandleAllocated()) {
    f->Release();
  } else {
    delete f;
  }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma package(smart_init)
