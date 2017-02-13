#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <Wininet.h>
#include <Netlistmgr.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner) {

 CTrayIcon1->Visible=false;                                              //wykluczenie zapomienia (b³¹d komunikatów)
 RadioButton11->Enabled=false;
 RadioButton10->Enabled=false;
 ButtonWybierz->Enabled=false;
 RadioButtonAcctualfolder->Hint = Application->Name;
 LabeledEditNameSave->EditLabel->Caption = "Nazwa pliku";
 LabeledEditNameSave->TextHint = S::NAMEcalc;
 FibonacciR->CheckBoxGodMode->State = ExistsDir("God Mode.{ED7BA470-8E54-465E-825C-99712043E01C}");
 SpeedButtonNameNew->Enabled = false;
 SpeedButtonNamePre->Enabled = false;
 SpeedButtonNamePost->Enabled = false;
 TrackBarIconSize->Position = FibonacciR->IconList->Width;
 MutexQuietMod = NULL;
 checking = false;
 CheckBoxRound->Checked = &FibonacciR->FiFloat->round;
// CheckBoxULOG->State = 2;
// 	CheckBoxULOG->Checked = true;
 DragAcceptFiles(Handle, true); // akceptowanie upuszczanych plików
// DragAcceptFiles(Edit1->Handle, 0);
// DragAcceptFiles(EditLocalization->Handle, 1);
 Df = WindowProc;
 WindowProc = OnDropFiles;
// CheckBoxULOG->Checked = FibonacciR->CheckBoxSLOG->Checked;

 Reg = new TRegistry();

 CheckRegistry();

 CheckBoxHide->Visible = CheckBoxAutoStart->Checked;                            // musi byæ po sprawdzeniu rejestru

 FindProgramToOpenADS();

#ifdef FINAL

 EditKod->Visible = false;
 MaskEditKod->Visible = false;
 TabSheet4->TabVisible = false;
 TabSheet5->TabVisible = false;
 PageControl1->ActivePageIndex = 0;
 PageControl2->ActivePageIndex = 0;
 RadioButton2->Checked = true;                                                  // screen PNG
// ButtonWinKey->Visible = false;

#else
	 AdvancedMode( true );
//	 CheckBoxSaveToReg->Checked = false;

#endif

  MaskEditInkrem->Text = S::increment_value;
  ComboBox1->Text = S::MAX_DEPTH;
  ComboBox2->Text = S::BREAK_SEARCH;



// LPDWORD lpdwFlags;
//// DWORD   dwReserved = 0; // must by 0
// bool conected;
// NLM_CONNECTIVITY *pConnectivity;

//do {                    INetworkListManager::GetConnectivity(pConnectivity);
//    ::InternetGetConnectedState( lpdwFlags, dwReserved );
//	a = INetworkConnection::get_IsConnectedToInternet( pbIsConnected );
//	conected = InternetGetConnectedState( lpdwFlags, dwReserved );
//	Sleep(1000);   InternetCheckConnectionA(0,0,0);
//									GetConnectivity(
//0
//);

//MessageBox( 0, 0, L"sprawdzam ...", MB_OK );

//} while ( conected );

//MessageBox( 0, L"P³¹czono", L"Internet", MB_OK );



}
//---------------------------------------------------------------------------
void __fastcall TForm2::TrackBar1Change(TObject *Sender)
{
FibonacciR->ProgressBar1->Position = TrackBar1->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBox3Click(TObject *Sender)
{
//CheckBox3 domyœlnie musi byæ wy³¹czony inaczej pojawi œiê komunikat

 if (CheckBox3->Checked) {
		CTrayIcon1->Visible = true;
		FibonacciR->CloseSet(1);
		MutexQuietMod = CreateMutexA(NULL, TRUE, "FI_QUIET_MODE");                       // show ballonhint w trayu
 }	else {
		CTrayIcon1->Visible = false;
		CTrayIcon1->Hide = true;
		FibonacciR->CloseSet();
		ReleaseMutex(MutexQuietMod);

 }
}
// ---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxSaveClick(TObject *Sender)
{

	S::Save( CheckBoxSave->Checked);

	if (CheckBoxSave->Checked) {

		unique_ptr<ofstream>wyniki(new ofstream);

		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);

		(*wyniki).open("Wyniki.txt", ios::out | ios::app);

		*wyniki << setfill('0') << "[  " << setw(2)
			<< systemTime.wDay << "/" << setw(2)
			<< systemTime.wMonth << "/" << systemTime.wYear << "   |   " << setw
			(2) << systemTime.wHour << ":" << setw(2)
			<< systemTime.wMinute << "  ]" << endl;

		(*wyniki).close();

			S::Status( "Zapis w³¹czony"  );
	}
	else   	S::Status( "Zapis wy³¹czony" );
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::MaskEditInkremChange(TObject *Sender) {

	unique_ptr<unsigned> pos (new unsigned(MaskEditInkrem->SelStart));

	unique_ptr<String> s (new String);

	*s = StringReplace(MaskEditInkrem->Text, " ", "0", TReplaceFlags() << rfReplaceAll);

	S::increment_value = (*s).ToDouble();

	if ( S::increment_value == 0 ) {
		 S::Status("Wartoœæ nie mo¿e byæ równa zero (brak widzialnego efektu)");// freeze status
		 MaskEditInkrem->Color = clWebSalmon;
	} else 	MaskEditInkrem->Color = clWindow;
	MaskEditInkrem->Perform(EM_SETSEL, *pos, *pos);

	LabelWinkrem->Caption = "= " + CurrToStr(S::increment_value);

  }
// ---------------------------------------------------------------------------
void __fastcall TForm2::CheckBoxULOGClick(TObject *Sender)
{
	if (!CheckBoxULOG->Checked) {

	RadioButton11->Enabled=false;
	RadioButton10->Enabled=false;
	ButtonWybierz->Enabled=false;
	}
	else if (CheckBoxULOG->Checked) {
	RadioButton11->Enabled=true;
	RadioButton10->Enabled=true;
	ButtonWybierz->Enabled=true;
		 }
FibonacciR->CheckBoxSLOG->Checked = CheckBoxULOG->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonWybierzClick(TObject *Sender)
{
RadioButton11->Checked = false;
RadioButton10->Checked = false;
U::logpref = LOG_OTHER;

if (SaveTextFileDialog1->Execute())
   {
	 try {

		U::logpath = SaveTextFileDialog1->FileName;

	 }
	 catch (...)
	 {
		ShowError("Zapis zakoñczy³ siê niepowodzeniem!");
	 }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::EditKodChange(TObject *Sender) {

	if (EditKod->Text == "" ) return;

			 switch (EditKod->Text.ToInt()) {

			 case 999:
				 ShowMessage(StrUpper(getenv("PROCESSOR_IDENTIFIER")));
				 break;

			 default: ;
			 }
			 if (EditKod->Text == Form3->KOD) {
//				 ShowMessage("You're Winer");

				AdvancedMode( true );

			 }
	 }
	 // ---------------------------------------------------------------------------
void __fastcall TForm2::TabSheet4Enter(TObject *Sender) {
	Button2->Enabled = true;                                                    // Domyœlne
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender) {

			 FormCreate(Sender);
			 U::SavePref();
			 Button2->Enabled = false;
 }
// ---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
//DragAcceptFiles(Edit1->Handle, true);

//RadioButton4->Checked = true;    //domyœlne
RadioButton7->Checked = true;
Edit1->Text = "C:\\";
CheckBoxULOG->Checked = false;
RadioButton10->Checked = true;
Edit1->Color = clWindow;

	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;

	if ( Reg->OpenKey("Software\\" +  S::FirmName +"\\"+ S::ProductName, false) )
	{
		if ( Reg->ValueExists( "SaveToRegistry" ) )

			Form2->CheckBoxSaveToReg->Checked = Reg->ReadBool("SaveToRegistry");

		else Form2->CheckBoxSaveToReg->State = cbGrayed;

	}
	else Form2->CheckBoxSaveToReg->State = cbGrayed;
}
 // ---------------------------------------------------------------------------
void __fastcall TForm2::OnDropFiles(TMessage &Msg) {

 if(Msg.Msg == WM_DROPFILES) {

  unique_ptr<char[]> buffer(new char[512]);

   DragQueryFileA((HDROP)Msg.WParam, 0, buffer.get(), 512);
   // tutaj nale¿y umieszczaæ kod odpowiedzialny za wykonywanie operacji na upuszczonym pliku

//	   ActiveControl->Name  // jeœli kilka obiektów na jednym TabSheet

	if (PageControl1->ActivePageIndex == 3 ) Edit1->Text = (AnsiString)buffer.get(); // strumienie

	if (PageControl1->ActivePageIndex == 5) {                                  	// PageControl2


	   if (PageControl2->ActivePageIndex == 1 )                                 //konwersja pojedyncza
	   {

			if (CursorAt(EditLocalization->Handle)) EditLocalization->Text = buffer.get(); // edit zapisu

			else ImagePreview->Picture->LoadFromFile(buffer.get());             // ikona podgl¹du przy pojedynczej konwersji

	   }

	   if (PageControl2->ActivePageIndex == 2 ) ButtonedEdit1->Text = buffer.get();  // przetwarzanie wsadowe

	}

  DragFinish((HDROP)Msg.WParam);

 }
 Df(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
U::SavePref();
DragAcceptFiles (Handle, False);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBox4Click(TObject *Sender){
	copyclick = CheckBox4->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::MaskEditKodChange(TObject *Sender) {

	if (TrimT(MaskEditKod->Text) == "KOD") 	ShowMessage("eys");

	else if(TrimT(MaskEditKod->Text) == "OFF")  AdvancedMode( false );

	else if(TrimT(MaskEditKod->Text) == "ON")  AdvancedMode( true );
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::Edit1Change(TObject *Sender) {

	Form2->RadioButton9->Checked = true;
	Button2->Enabled = true;
	Edit1->Hint = Edit1->Text;

	U::SavePref();

	if (DirectoryExists(Edit1->Text) || FileExists(Edit1->Text))

			Edit1->Color = clWebGreenYellow;

	else 	Edit1->Color = clWebSalmon;
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::GroupBox3Enter(TObject *Sender){
Button2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::GroupBox4Enter(TObject *Sender){
Button2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::GroupBox2Enter(TObject *Sender){
Button2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::EditNameADSChange(TObject *Sender) {

//	if ( EditNameADS->Text.Length() == 0 ) {

		SpeedButtonNameNew->Enabled = EditNameADS->Text.Length();
		SpeedButtonNamePre->Enabled = SpeedButtonNameNew->Enabled;
		SpeedButtonNamePost->Enabled = SpeedButtonNameNew->Enabled;

	if (SpeedButtonNameNew->Enabled)
		if (SpeedButtonNameOriginal->Down) SpeedButtonNameNew->Down = true;

	if ( !SpeedButtonNameNew->Enabled ) SpeedButtonNameOriginal->Down = true;

//	}

//if ( RadioButton4->Checked ) RadioButton8->Checked = true;                      // zmiana radiobutona

//if (RadioButton5->Checked) EditNameADS->Hint = AddBeforDot("Example.txt", EditNameADS->Text);

//else if (RadioButton6->Checked) EditNameADS->Hint = EditNameADS->Text + "Example.txt";

//else   EditNameADS->Hint = "\\" + EditNameADS->Text;

	U::SavePref();
}
// ---------------------------------------------------------------
void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift) {

	if(Key == vkReturn)   {
	//	ShowMessage("Wciœniêto Enter");
		 Form2->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBoxRoundClick(TObject *Sender) {

	FibonacciR->FiFloat->round = CheckBoxRound->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
	if (ComboBox1->Text.ToInt() >= 0 && ComboBox1->Text.ToInt() <= 255 ){

		S::MAX_DEPTH = ComboBox1->Text.ToInt();
		ComboBox1->Hint = S::MAX_DEPTH;

	} else ComboBox1->Text = 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox2Change(TObject *Sender)
{
	if (ComboBox2->Text.ToInt() >= 0 && ComboBox2->Text.ToInt() <= 99999999 ) {

		S::BREAK_SEARCH = ComboBox2->Text.ToInt();
		ComboBox2->Hint = S::BREAK_SEARCH;

	} else  ComboBox2->Text = 100;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label3Click(TObject *Sender){
ComboBox1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label2Click(TObject *Sender) {
ComboBox2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Zamknij1Click(TObject *Sender) {
FibonacciR->Close();                                                            // próba noramlnego zamkniêcia która powinna byæ blokowana
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1Exit(TObject *Sender) {

	if (RadioButton9->Checked) {

	 if (!DirectoryExists(Edit1->Text) && !FileExists(Edit1->Text))
	 {
		 Edit1->Color = clBtnFace;
		 ShowMessage("Podana œcie¿ka nie istnieje popraw j¹ i zastosuj ponownie\n\nJeœli u¿yjesz niepoprawnej œcie¿ki to program spróbuje j¹ stworzyæ");

		 Edit1->SetFocus();

		 unique_ptr<String> str(new String( Edit1->Text ));
		 unique_ptr<unsigned short> pos(new unsigned short( (*str).Length() ));

		 do {

			 (*str).Delete(*pos, 1);
			 (*pos)--;

		 } while ((!DirectoryExists(*str) && !FileExists(*str)) && *pos);

		 Edit1->Perform(EM_SETSEL, *pos, Edit1->Text.Length());

	 } else  Edit1->Color = clWindow;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton11Click(TObject *Sender){
	U::logpref = LOG_HERE;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton10Click(TObject *Sender){
	U::logpref = LOG_DESKTOP;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton9Click(TObject *Sender){
U::pathpref = PATH_USER;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton8Click(TObject *Sender){
	EditNameADSChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton7Click(TObject *Sender) {
	U::pathpref = PATH_CURR;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender) {
	U::SavePref();
	Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton1Click(TObject *Sender)
{
	ComboBoxQuality->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::RadioButton2Click(TObject *Sender)
{
	ComboBoxQuality->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton3Click(TObject *Sender)
{
	ComboBoxQuality->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormPaint(TObject *Sender)
{
//	  TCanvas *CCanv = new TCanvas;
// CCanv->Handle = GetWindowDC(Handle);
// CCanv->Brush->Style = bsClear; //<-- ustawia przeŸroczyste t³o pod tekstem.
// CCanv->Font->Style = CCanv->Font->Style << fsBold; //<-- ustawia pogrubion¹ czcionkê.
// CCanv->Font->Size = 12; //<-- ustawia rozmiar czcionki.
// CCanv->TextOut(10, 2, "Przyk³adowy tekst"); //<-- rysuje tekst na obiekcie CCanv->TextOut(X, Y, AnsiString).
// ReleaseDC(Handle, CCanv->Handle); //<-- przenosi obiekt CCanv na formularz.
// delete CCanv; //<-- usuwa obiekt CCanv z pamiêci.
}
//---------------------------------------------------------------------------
//
void __fastcall TForm2::ComboBoxQualityChange(TObject *Sender)
{
ComboBoxQuality->Hint = "Compression " + ComboBoxQuality->Text.SubString(1,1) +  "0%";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonSaveIconsClick(TObject *Sender)
{
   SaveIcons();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonedEdit1Click(TObject *Sender)
{
   unique_ptr<TOpenPictureDialog> dialog(new TOpenPictureDialog(0));
	   (*dialog).Execute(Application->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonKonwertClick(TObject *Sender)
{

//	ScreenBMP( SpinEdit2->Value, CheckBoxclipkonwersja->Checked, "c:\\" );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxAutoStartClick(TObject *Sender) {

	if (CheckBoxAutoStart->Checked) {

		CheckBoxHideClick(Sender);
		CheckBoxHide->Show();
	}
	else {
		Reg->RootKey = HKEY_CURRENT_USER;                                    	// Auto uruchamianie siê programu z systemem
		Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
		Reg->DeleteValue("FibonacciR");
		CheckBoxHide->Hide();
	}
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::CheckBoxHideClick(TObject *Sender)
{

	Reg->RootKey = HKEY_CURRENT_USER;                                    		// Auto uruchamianie siê programu z systemem
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);

//	unique_ptr<String>buff(new String(Reg->ReadString("FibonacciR")));

   if ( CheckBoxHide->Checked ) Reg->WriteString("FibonacciR", ParamStr(0) + " /quiet" );

	else 	Reg->WriteString("FibonacciR", ParamStr(0) );
}
// ---------------------------------------------------------------------------

	void TForm2::CheckRegSystemGroup()
{
   checking = true;

   try {

	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;                                    		// Ukrywanie rozrzerzeñ plików
	if (Reg->KeyExists("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"))
		Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", false);
		if (Reg->ValueExists("HideFileExt"))
			FibonacciR->CheckBoxFilesExtension->Checked = (Reg->ReadInteger("HideFileExt") == 0 ) ? true : false;
		else FibonacciR->CheckBoxFilesExtension->State = cbGrayed;
//     -        -        -        -        -        -       -        -        -
	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;
	if (Reg->KeyExists("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"))                                  		// Ukrywanie plików
		Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", false);

	   if ( !Reg->ValueExists("Hidden") && !Reg->ValueExists("ShowSuperHidden") )  // obydwa nie istniej¹
			FibonacciR->CheckBoxFilesShowAll->Checked = false;
	   else if ( !Reg->ValueExists("Hidden") || !Reg->ValueExists("ShowSuperHidden"))// istnieje tylko jeden (powy¿szy warunki wykluczaj¹ instnieni 2)
			FibonacciR->CheckBoxFilesShowAll->State = cbGrayed;                             // jêœli istnieje tylko jedna wartoœæ która pokazje pliki
	   else if ( Reg->ValueExists("Hidden") && Reg->ValueExists("ShowSuperHidden" )) // istniej¹ 2
			FibonacciR->CheckBoxFilesShowAll->State = true;

	if ( FibonacciR->CheckBoxFilesShowAll->Checked ) {

	if (Reg->ValueExists("Hidden")) {
		if ( Reg->ReadInteger("Hidden") == 1 ) FibonacciR->CheckBoxFilesShowAll->Checked = true; // pliki pokazane
		if ( Reg->ReadInteger("Hidden") == 2 ) FibonacciR->CheckBoxFilesShowAll->Checked = false; // pliki ukryte
		}

	if ( Reg->ValueExists("ShowSuperHidden" ) )
		if (FibonacciR->CheckBoxFilesShowAll->Checked)	FibonacciR->CheckBoxFilesShowAll->Checked = Reg->ReadBool("ShowSuperHidden");
	}

//     -        -        -        -        -        -       -        -        -
	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;
																				// Update Close System
	if (Reg->KeyExists ("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU"))
		Reg->OpenKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", false);
		if (Reg->ValueExists("NoAutoRebootWithLoggedOnUsers"))
			FibonacciR->CheckBoxUpDateRebot->Checked = Reg->ReadBool("NoAutoRebootWithLoggedOnUsers");
		else FibonacciR->CheckBoxUpDateRebot->State = cbGrayed;
// -        -        -        -        -        -       -        -        -
	Reg->CloseKey();
	Reg->RootKey = HKEY_CLASSES_ROOT;                                           // Otwórz cmd tutaj w menu kontekstowym folderów
	if (Reg->KeyExists("Directory\\shell\\cmd") )
		Reg->OpenKey("Directory\\shell\\cmd", false);
		if (Reg->ValueExists("Extended"))
			FibonacciR->CheckBoxcomandprompt->Checked = false;
		else FibonacciR->CheckBoxcomandprompt->State = true;                              	// w tym przypadku istnienie vartoœæi jest warukiem, dlatego false zamiast cbGrayed

//     -        -        -        -        -        -       -        -        -
																				// Update Disable
	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;
	if ( Reg->KeyExists("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU"))
		Reg->OpenKey("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", false);
		if (Reg->ValueExists("NoAutoUpdate"))
			FibonacciR->CheckBoxDisableUpDate->Checked = Reg->ReadBool("NoAutoUpdate");
		else FibonacciR->CheckBoxDisableUpDate->State = cbGrayed;

//     -        -        -        -        -        -       -        -        -
																				// Blue Screen
	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;
	if (Reg->KeyExists("SYSTEM\\CurrentControlSet\\services\\kbdhid\\Parameters")) {

		Reg->OpenKey("SYSTEM\\CurrentControlSet\\services\\kbdhid\\Parameters", false);
		if (Reg->ValueExists("CrashOnCtrlScroll"))
			FibonacciR->CheckBoxBlueScreen->Checked = !Reg->ReadBool("CrashOnCtrlScroll");
		else FibonacciR->CheckBoxBlueScreen->State = cbGrayed;
	}
	else FibonacciR->CheckBoxBlueScreen->State = cbGrayed;

//     -        -        -        -        -        -       -        -        -
																				// UAC (User Account Control)
	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;

	if (Reg->KeyExists("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System")) {

		Reg->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", false);
		if (Reg->ValueExists("EnableLUA"))
			 FibonacciR->CheckBoxUAC->Checked = Reg->ReadBool("EnableLUA");
		else FibonacciR->CheckBoxUAC->State = cbGrayed;
	} else FibonacciR->CheckBoxUAC->State = cbGrayed;

//     -        -        -        -        -        -       -        -        -
																				// ADS able

		Reg->CloseKey();
		Reg->RootKey = HKEY_CURRENT_USER;

	if ( Reg->KeyExists("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Attachments") ) {

		Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Attachments", false);
		if ( Reg->ValueExists( "SaveZoneInformation" ) ) {
			   FibonacciR->CheckBoxDisableADSReg->Checked =	Reg->ReadInteger( "SaveZoneInformation" );
		} else FibonacciR->CheckBoxDisableADSReg->State = cbGrayed;
	} else FibonacciR->CheckBoxDisableADSReg->State = cbGrayed;

	}catch (Exception &exception) {
		checking = false;
		LogSave( exception.ToString() + "  in CheckRegistry()");
	}
	catch (...) {
		checking = false;
		ShowError("B³¹d przy odczycie watoœæi rejestru. CheckRegistry()");
	}
	checking = false;

}

// ---------------------------------------------------------------------------

 void TForm2::CheckRegistry() {

 checking = true;

 try {

	Reg->CloseKey();
	Reg->RootKey = HKEY_CURRENT_USER;                                    		// Auto uruchamianie siê programu z systemem
	Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);

		if ( Reg->ValueExists("FibonacciR") )
		{                                                                       // UWAGA uruchamianie z IDE do daje .(kropkê) np. D:\Builder\FibonacciR\.\Win32\Debug\Fibonacci.exe
			unique_ptr<String> buff(new String(Reg->ReadString("FibonacciR")));
																				//	MessageBoxW(0, (*buff.get()+"\n"+ParamStr(0)).c_str(),0,1);     ShowMessage(CompareStr(*buff.get(), ParamStr(0)));
			CheckBoxHide->Checked = DelParam("quiet", buff.get(), 0, true);    	// usuwanie parametrów

			CheckBoxAutoStart->Checked = ( CompareStr(*buff.get(), ParamStr(0)) == 0) ? true : false;

		} else CheckBoxAutoStart->Checked = false;

//		CheckBoxHide->Visible = false;
//     -        -        -        -        -        -       -        -        -


	CheckRegSystemGroup();

	}catch (Exception &exception) {
		checking = false;
		LogSave( exception.ToString() + "  in CheckRegistry()");
	}
	catch (...) {
		checking = false;
		ShowError("B³¹d przy odczycie watoœæi rejestru. CheckRegistry()");
	}
	checking = false;                                                           // ustawia flagê
 }
// ---------------------------------------------------------------------------
 void TForm2::FindProgramToOpenADS() {

	try {

	Reg->CloseKey();
	Reg->RootKey = HKEY_LOCAL_MACHINE;
// unistall display icon file path
 if (Reg->KeyExists("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Notepad++"))
	Reg->OpenKey("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Notepad++", false);
 if ( Reg->ValueExists("DisplayIcon") )
	LabelDefProgPath->Caption = Reg->ReadString("DisplayIcon");

	Reg->CloseKey();
// x64
 if (Reg->KeyExists("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\App Paths\\notepad++.exe"))
	Reg->OpenKey("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\App Paths\\notepad++.exe", false);
 if ( Reg->KeyExists("") )
	LabelDefProgPath->Caption = Reg->ReadString("");

	Reg->CloseKey();
// x86
 if (Reg->KeyExists("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\notepad++.exe"))
	Reg->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\notepad++.exe", false);
  if ( Reg->KeyExists("") )
	LabelDefProgPath->Caption = Reg->ReadString("");


	}catch (Exception &exception) {   // Reg->KeyExists()

		LogSave( exception.ToString() + "  in FindProgramToOpenADS()");
	} catch (...) {
		ShowError("B³¹d przy odczycie watoœæi rejestru. FindProgramToOpenADS()");
	}
 }
// ---------------------------------------------------------------------------




void __fastcall TForm2::CheckBoxUpDateRebotClick(TObject *Sender) {             // Stop rebot update


}
//---------------------------------------------------------------------------




 void __fastcall TForm2::FormDestroy(TObject *Sender) {
	Reg->Free();
 }
//---------------------------------------------------------------------------
void TForm2::AdvancedMode(bool b ) {

	FibonacciR->GroupBoxReg->Visible = b;                                                   // GroupBox Rejestru
	FibonacciR->CheckBoxGodMode->Visible = b;                                               // folder GodMode
	FibonacciR->ButtonRejestrator->Visible = b;                                             // Przycisk rejestratora
	TabSheet4->TabVisible = b;                                  				// Strumienie
	TabSheet5->TabVisible = b;                                  				// Wyszukiwanie
	FibonacciR->TabSheet5->TabVisible = b;                      				// strumienie
	FibonacciR->TabSheet1->TabVisible = b;                      				// szukaj
	ButtonSaveIcons->Visible = b;                               				// zapis ikon
	FibonacciR->FormStyle == TFormStyle::fsNormal;                 				// pozwala nie modalnie uruchomiæ okno ustawieñ
	FibonacciR->Zawszenawierzchu1->Enabled = b;									// obrazuje powy¿sze
	FibonacciR->Zawszenawierzchu1->Checked = !b;
//	FibonacciR->Zawszenawierzchu1->Click();
	CheckBoxAutoStart->Visible = b;                                             // uruchamianie z systemem
	CheckBoxHide->Visible = CheckBoxAutoStart->Checked;                         // gdy powy¿sze zaznaczone to jest widoczne (tryb cichy)
	CheckBoxSaveToReg->Checked = b;

	if ( b )
		FibonacciR->Caption = "FibonacciR " + ::GetFileVersion( ParamStr(0));
	else
		FibonacciR->Caption =  "FibonacciR Free " + ::GetFileVersion( ParamStr(0));

}
//---------------------------------------------------------------------------
void __fastcall TForm2::MaskEditInkremKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {

	if (MaskEditInkrem->SelText == ",")  return;                                // zabezpieczenia
	if (MaskEditInkrem->SelText == "")  return;
	if ( Key == vkReturn ) this->Close();

		curpos = MaskEditInkrem->SelStart;

		unique_ptr<String> buff(new String( MaskEditInkrem->Text));

		unsigned char digit = MaskEditInkrem->SelText.ToInt();

		if 		(Key == vkUp) {

			if ( digit == 9) digit = 0;
			else			 digit++;
		}
		else if (Key == vkDown) {

			if ( digit == 0) digit = 9;
			else			 digit--;
		}
		else if (Key == vkLeft) {

		   if ( curpos == 0 )                                    // przeskoki koñcowe w <-- lewo
				curpos = 9;
		}
		else if (Key == vkRight) {                                              // przeskoki koñcowe w --> prawo

			if ( curpos == 8 )
				MaskEditInkrem->Perform(EM_SETSEL, 0, 0);
				return;
		}

		(*buff).Delete( MaskEditInkrem->SelStart + 1 , 1 );
		(*buff).Insert( digit, MaskEditInkrem->SelStart + 1 );

		MaskEditInkrem->Text = *buff;

		MaskEditInkrem->Perform(EM_SETSEL, curpos, curpos +1);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonedEditLocalClick(TObject *Sender)
{
	ButtonedEdit1->LeftButton->ImageIndex = 1;
	ButtonedEdit1->LeftButton->DisabledImageIndex= 1;
	ButtonedEdit1->LeftButton->HotImageIndex = 1;
	ButtonedEdit1->LeftButton->PressedImageIndex = 1;
	Application->ProcessMessages();
	Form2->Update();
	Form2->Repaint();
	ButtonedEdit1->LeftButton->Visible  = 0;

	RadioButtonAcctualfolder->Checked = false;
	RadioButtonSourseFile->Checked = false;
	RadioButtonPulpit->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButtonSourseFileClick(TObject *Sender)
{
	ButtonedEdit1->LeftButton->ImageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButtonAcctualfolderClick(TObject *Sender)
{
	ButtonedEdit1->LeftButton->ImageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButtonPulpitClick(TObject *Sender)
{
ButtonedEdit1->LeftButton->ImageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EditLocalizationChange(TObject *Sender)
{
RadioButtonLocalization->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ImagePreviewClick(TObject *Sender)
{
	unique_ptr<TOpenPictureDialog> dialog(new TOpenPictureDialog(0));

	if ((*dialog).Execute(Application->Handle)) {

//	    Application->Cursor =  crHourGlass;//	SetCursor(crHourGlass);
//		GetMemory(filesize( AnsiString((*dialog).FileName).c_str() ));
	if ( filesize(AnsiString((*dialog).FileName).c_str()) > 1559965 ) {

		ShowMessage("Rozmiar pliku: " + GetSize(filesize( AnsiString((*dialog).FileName).c_str() )) + "\nMaksymalny rozmiar: " + GetSize(34342) );
		return;
	}

//		ImagePreview->Picture->LoadFromFile((*dialog).FileName);
//		W_ID = BeginThread(NULL, 0, LoadImage, (void*) &((*dialog).FileName), 0, W_PD);



	}
		ImagePreview->Hint = ExtractFileName((*dialog).FileName) + " \n" + ImagePreview->Picture->Height + "x" +
				ImagePreview->Picture->Width +"\n" + GetSize(filesize( AnsiString((*dialog).FileName).c_str() ));

}
//---------------------------------------------------------------------------
int __fastcall TForm2::LoadImage(Pointer Parameter)
{
  ImagePreview->Picture->LoadFromFile( *(String*) Parameter );
//												ShowMessage("za³);
//   ExitThread(GetExitCodeThread(LoadImage, NULL));
}


void __fastcall TForm2::ImagePreviewProgress(TObject *Sender, TProgressStage Stage,
		  BYTE PercentDone, bool RedrawNow, const TRect &R, const UnicodeString Msg)
{
//	unique_ptr<TProgressBar> bar(new TProgressBar(PanelImage));
//	(*bar).Parent = PanelImage;
//	(*bar).Show();
//		(*bar).Position = PercentDone;
//	(*bar).State = 	Stage;
//ShowMessage(PercentDone);
			   Application->ProcessMessages();
	PanelImage->BevelKind = bkNone;
	ButtonKonwert->SetFocus();
	ImagePreview->Repaint();

}
//---------------------------------------------------------------------------

//	DWORD WINAPI static ThreadRECV(LPVOID lpParam)
//	{
//	//tutaj piszemy co ma robic watek po utworzemiu, czyli w naszym przypadku ma nasluchiwac gniazdo sClient i przetwarzac odebrane pakiety !
////        if(recv(Nowe->sClient, Nowe->szPacked, strlen(Nowe->szPacked), 0) == SOCKET_ERROR)
//		{
//			MessageBox(NULL, "B³¹d funkcji recv() w w¹tku !", "B³ad programu", MB_OK | MB_ICONERROR);
//			return 0;
//		}
////        AnsiString do_wyslania = "0x04" + Nowe->Haslo1->Text +"$" + Nowe->Email->Text;
////        Nowe->ret = send(Nowe->sClient, do_wyslania.c_str(), do_wyslania.Length() , 0);
////    tutaj w miare postepow dopisze sie przetwarzanie odebranych pakietow !
////    return 0;
//	}
//
//	 Thread = CreateThread(NULL, 0, ThreadRECV, 0, 0, &ThreadID);
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxListVCheckBClick(TObject *Sender)
{
	FibonacciR->ListView1->Checkboxes = CheckBoxListVCheckB->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxNoDATAClick(TObject *Sender)
{
 if (!CheckBoxNoDATA->Checked) CheckBoxHideData->Checked = false;

	CheckBoxHideData->Enabled = CheckBoxNoDATA->Checked;

 if (CheckBoxNoDATA->Checked) CheckBoxHideData->Checked = true;                	// auto zaznaczanie
}
//---------------------------------------------------------------------------

void __fastcall TForm2::TabSheet5Show(TObject *Sender)
{
ComboBox1->Text = S::MAX_DEPTH;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::LabelDefProgPathClick(TObject *Sender)
{
  unique_ptr<TOpenDialog> dlg(new TOpenDialog(FibonacciR));
	(*dlg).Filter = "*.exe";
	(*dlg).FilterIndex = 2;
//	(*dlg).FileName = LinkLabelDefProgPath->Caption;
	(*dlg).Title = "Wybierz program domyœlny dla ADS";

	 (*dlg).Execute( Application->Handle);

	 if ((*dlg).FileName != "") {

		LabelDefProgPath->Hint	= (*dlg).FileName;
		LabelDefProgPath->Caption = (*dlg).FileName;
	 }
	 (*dlg).Destroying() ;
}
//---------------------------------------------------------------------------



void __fastcall TForm2::Button4Click(TObject *Sender)
{
 //kopia rejestru
 ShowMessage("Kopia rejestru znajduje siê na pulpicie z rozszerzeniem .reg");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonDelRegClick(TObject *Sender)
{
	unique_ptr<TRegistry> Reg (new TRegistry);

	Reg->DeleteKey("Software\\" +  S::FirmName );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxSaveToRegClick(TObject *Sender)
{
	S::SaveToReg = CheckBoxSaveToReg->Checked;

	  unique_ptr<TRegistry> Reg (new TRegistry);

	Reg->CloseKey();

	if ( Reg->OpenKey("Software\\" + S::FirmName +"\\"+ S::ProductName, true) )

		Reg->WriteBool( "SaveToRegistry", S::SaveToReg );
}
//---------------------------------------------------------------------------
void __fastcall TForm2::LabeledEditNameSaveChange(TObject *Sender)
{
	if ( LabeledEditNameSave->Text != "" ) {

		if ( LabeledEditNameSave->Text.LastDelimiter(".") )				// zapoiega dodawaniu rozszerzenia

			LabeledEditNameSave->Text = LabeledEditNameSave->Text.SubString(1, LabeledEditNameSave->Text.LastDelimiter(".") -1 );

		S::NAMEcalc = LabeledEditNameSave->Text;
    }
	LabeledEditNameSave->Hint = S::NAMEcalc;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpinEditFormatBeforeChange(TObject *Sender)
{
	unique_ptr<String>buff(new String(""));                                     // format w zerach

	for (int i = 0; i < SpinEditFormatBefore->Value; i++) 	(*buff) += "#";

	LabelFormatBeforeDot->Caption = *buff;
	SaveFormat();
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::SpinEditFormatAfterChange(TObject *Sender)
{
  unique_ptr<String>buff(new String(""));                                     // format w zerach

	for (int i = 0; i < SpinEditFormatAfter->Value; i++) 	(*buff) += "#";

	LabelFormatAfterDot->Caption = *buff;
	SaveFormat();
}
//---------------------------------------------------------------------------
void TForm2::SaveFormat() {

	S::Fr = LabelFormatBeforeDot->Caption + "." + LabelFormatAfterDot->Caption;
	LabelFormatDot->Hint = S::Fr;
}
//---------------------------------------------------------------------------

void TForm2::SysPref(AnsiString c) {
      char SysDir[_MAX_PATH], *CtrlDir;
 GetSystemDirectoryA(SysDir, _MAX_PATH);
 CtrlDir = ((AnsiString)SysDir + "\\rundll32.exe shell32.dll," + c).c_str();

 WinExec(CtrlDir, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Mysz1Click(TObject *Sender){
  SysPref("Control_RunDLL main.cpl @0");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Klawiatrura1Click(TObject *Sender){
  SysPref("Control_RunDLL main.cpl @1");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Ekran1Click(TObject *Sender){
  SysPref("Control_RunDLL desk.cpl");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Energia1Click(TObject *Sender){
  SysPref("Control_RunDLL powercfg.cpl");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::KontroleryGier1Click(TObject *Sender){
	 SysPref("Control_RunDLL joy.cpl");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Skaner1Click(TObject *Sender) {
	 SysPref("Control_RunDLL sticpl.cpl");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Drukarka1Click(TObject *Sender) {
	 SysPref("Control_RunDLL main.cpl @3");
}

//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------

void __fastcall TForm2::ButtontestClick(TObject *Sender)
{
ShellExecuteA(0, "open", GetSpecialFolder(CSIDL_COMMON_STARTUP).c_str() , 0,0,1);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ButtonWinHistoryClick(TObject *Sender) {

//WinExec(ToArrW( &("explorer.exe /open, " +(String) GetSpecialFolder(CSIDL_HISTORY))), SW_SHOWNORMAL);   // dont use it, too old
ShellExecuteA(0, "open", GetSpecialFolder(CSIDL_HISTORY).c_str() , 0,0,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonRecentClick(TObject *Sender) {

ShellExecuteA(0, "open", GetSpecialFolder(CSIDL_RECENT).c_str() , 0,0,1);
}
//---------------------------------------------------------------------------
//   #include <netcon.h>
void __fastcall TForm2::ButtonNetworkClick(TObject *Sender) {
//	   ShellExecuteA(this->Handle, "find", "C:\\Windows\\System32\\ncpa.cpl", "ncpa", NULL, 1);
ShellExecuteA(0, "open", "%windir%\\system32\\ncpa.cpl" , 0,0,1);
CreateShortcutLink("opis", GetSpecialFolder(CSIDL_DESKTOP)+"\\ mylinknn.lnk", "%windir%\\system32\\ncpa.cpl", ""  );
FibonacciR->StatusInfo("Utworzono skrót na pulpicie do folderu po³¹czeñ sieciowych");
//system( "start %windir%\\system32\\ncpa.cpl" );  //works
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonSendToClick(TObject *Sender) {

ShellExecuteA(0, "open", GetSpecialFolder(CSIDL_SENDTO).c_str() , 0,0,1);
}

//---------------------------------------------------------------------------

//void openProperties(char* guid, HWND window) {
//	char* path = cat(2, 0, L"::{208D2C60-3AEA-1069-A2D7-08002B30309D}\\::{7007ACC7-3202-11D1-AAD2-00805FC1270E}\\::", guid);
//	BOOL retval = ShellExecute(window, "properties", path, "", path, SW_NORMAL);
//	delete[] path;
//}
//char *ErrorMsg(DWORD errorcode)
//{
//	char *msgbuf;
//
//	if (FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL,
//		errorcode,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char *)&msgbuf,
//		0,
//		NULL) == 0) return NULL;
//
//	msgbuf[strlen(msgbuf)-2] = 0x00;
//	return msgbuf;
//}
void __fastcall TForm2::SpeedButtonNameOriginalClick(TObject *Sender)
{
	EditNameADS->TextHint = "Nazwa bez zmian";

	U::namepref = SRT_SAME;

//	SpeedButtonNameNew->Enabled = false;

}
//---------------------------------------------------------------------------


void __fastcall TForm2::SpeedButtonNameNewClick(TObject *Sender)
{
	if ( !static_cast<TSpeedButton*>(Sender)->Down ) {
//	   SpeedButtonNameNew->Down == false;
SpeedButtonNameOriginal->Down = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::MaskEditInkremKeyPress(TObject *Sender, System::WideChar &Key)
{
 if ( MaskEditInkrem->SelLength == 0 ) MaskEditInkrem->SelStart = 8;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonHostAddBlockClick(TObject *Sender)
{
	if ( EditForwardHost->Text == "" ) { EditForwardHost->SetFocus(); return; }
	if ( EditBlockDomain->Text == "" ) { EditBlockDomain->SetFocus(); return; }

	unique_ptr<ofstream> hosts (new ofstream);

	(*hosts).open( ToArrW( &(S::WinDir + "\\System32\\drivers\\etc\\hosts")), ios::out | ios::app);

	if ( !(*hosts).is_open() ) ShowError("Nie uda³o siê otworzyæ pliku hosts");

	*hosts << "\t" <<  ToArrW( &(EditForwardHost->Text) );
	*hosts << "\t\t" << ToArrW( &(EditBlockDomain->Text) ) << "\n";

	(*hosts).close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EditBlockDomainDblClick(TObject *Sender)
{
WinExec( ToArrW( &(LabelDefProgPath->Caption + " " + S::WinDir + "\\System32\\drivers\\etc\\hosts")), SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EditBlockDomainKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)  // otwiera plik
{
	if ( Key == vkReturn ) {
		Key = 0;                                                                // zapobiega dzwiêkowi
		ButtonHostAddBlock->OnClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EditBlockDomainClick(TObject *Sender)
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
// ---------------------------------------------------------------------------

void __fastcall TForm2::TrackBarIconSizeChange(TObject *Sender)
{
FibonacciR->IconList->SetSize( TrackBarIconSize->Position,TrackBarIconSize->Position );
FibonacciR->IconList->Clear();
FibonacciR->IconList->AddImages( FibonacciR->IconMain32 );
FibonacciR->StatusInfo(FibonacciR->IconList->Count);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::LabeledEditNameSaveDblClick(TObject *Sender)
{
		ShellExecuteW(0, L"open", (S::NAMEcalc + ".txt").c_str(), L"", L"", 5);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBoxLegendInFileClick(TObject *Sender)
{
  if (CheckBoxLegendInFile->Checked ) {

	string line = "";
	string comptext = "Legend";
	unique_ptr<unsigned char> l(new unsigned char(S::Fr.Length() + Form2->SpinEditFill->Value + 1) );

	fstream myfile ( (S::NAMEcalc + ".txt").c_str() , ios::in | ios::app );

	if (myfile.is_open())												// poni¿sze instrukcje wykonaj¹ siê jeœli uda siê otworzyæ plik
	{   //myfile << endl << comptext;
//		 myfile << "\n// --------------------------\n";
//		while ( myfile.eof() )		// eof() zwarca 1 gdy koniec pliku, wykrzyknik neguje wartoœæ czyli pêtla while dziala dopuki waroœæ jest równa  true czyli 1 logiczne
//		{
//			getline ( myfile, line );
//			myfile << line << endl;

			myfile << "Dla liczby  a obliczenia   " << setw(*l) << " a-a*Fi " << setw(*l) << " a*Fi " << setw(*l) <<
			" a+a*Fi " << setw(*l) << " 2a+a*Fi " << setw(*l) << " 2a*Fi " << setw(*l) << " 2a*Fi-a " << endl;

//			if ( strcmp( line.c_str(), comptext.c_str() ) )	// porównywanie zawartoœci stringów
//			   myfile << endl << comptext;
//		}
		myfile.close();
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ( Key == vkReturn ) {

		Key == 0;
		this->Close();
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button5Click(TObject *Sender)
{

CreateShortcutLink("opis", GetSpecialFolder(CSIDL_DESKTOP)+"\\ mylinknn.lnk", "%windir%\\system32\\ncpa.cpl", ""  );
ShellExecuteA(0, "open", ((AnsiString) GetSpecialFolder(CSIDL_DESKTOP)+"\\ mylinknn.lnk").c_str() , 0,0,1);
FibonacciR->StatusInfo("Utworzono skrót na pulpicie do folderu po³¹czeñ sieciowych");
}
//---------------------------------------------------------------------------







