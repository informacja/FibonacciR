#pragma hdrstop

#include "Unit1.h"

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Button1Click(TObject *Sender) {

	StatusInfo(ParamStr(0));
//
	if( IsDebuggerPresent() )                                                   // czy proces jest debugowany

		WinExec((AnsiString("explorer.exe /select, " + Application->ExeName)).c_str(), SW_SHOWNORMAL);
		// gdy jest debugowany œcie¿ka zawiera . (kropkê) w miejscu gdzie jest projekt
	else
		OpenFolderSelectFile( ParamStr(0).c_str() );

	// StatusBar1->Panels->Items[0]->Text = "Gotowe";
	// PageControl2->Pages->TabVisible->;
	// PageControl2->Hide();
	// Edit1->Text=PageControl2->ActivePage->TabIndex;

}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Kopiuj1Click(TObject *Sender) {
	wej->SelectAll(); // pobieranie uchwytu!!!
	wej->CopyToClipboard();
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Joe2Click(TObject *Sender) {
	ShellExecuteA(0, "open", "http://joemonster.org", "", "", 5);
}

////---------------------------------------------------------------------------
void __fastcall TFibonacciR::Mistrzowie1Click(TObject *Sender) {
	ShellExecuteA(0, "open", "http://mistrzowie.org", "", "", 0);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Zeruj1Click(TObject *Sender) {
	wej1->Clear();
	wyj1->Clear();
	wyj2->Clear();
	wyj3->Clear();
	wyj4->Clear();
	wyj5->Clear();
	wyj6->Clear();

	wej->Clear();
	wy1->Clear();
	wy2->Clear();
	wy3->Clear();
	wy4->Clear();
	wy5->Clear();
	wy6->Clear();

	ProgressBarStyle();
	ProgressBarMax();
	StatusInfo("Wyzerowano wartoœci");
}

// ---------------------------------------------------------------------------
void TFibonacciR::TryShowForm2() {

	if (FibonacciR->FormStyle == TFormStyle::fsStayOnTop)

		try {
		Form2->ShowModal();
		}
	catch (...) {
		Form2->Close();
		Form2->ShowModal();
	} // obs³uga w przypadku gdy okno jest otwarte niemodalnie

	else
		Form2->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Ustawienia1Click(TObject *Sender) {
	TryShowForm2();
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Wersja1Click(TObject *Sender) {

	unique_ptr < wchar_t[] > buff(new wchar_t[255]);
	unique_ptr < DWORD > size(new DWORD(sizeof(buff)));

	GetUserNameW( buff.get(), size.get()); 										// get user name
	Form3->Label1->Caption = buff.get();

	if (FibonacciR->FormStyle == TFormStyle::fsStayOnTop)

	try {
		Form3->ShowModal();
	}
	catch (...) {
		Form3->Close();
		Form3->ShowModal();
	} // obs³uga w przypadku gdy okno jest otwarte niemodalnie

	else
		Form3->Show();
}

// ---------------------------------------------------------------------------
double EditToDouble(TEdit *Edit) {

	try {
		return Edit->Text.ToDouble();

	}
	catch (...) {
		return DigitRewrite(Edit->Text).ToDouble();
	}
} // Sekcja

// ---------------------------------------------------------------------------   //  Ustawienia
void __fastcall TForm2::CheckBox2Click(TObject *Sender) {

	FibonacciR->ProgressBar1->Visible = CheckBox2->Checked;
}
// ---------------------------------------------------------------------------

// TIntFI o1; //na potrzeby poni¿szych funkcji

void __fastcall TFibonacciR::wyj1Click(TObject *Sender) {
	wej1->Value = o1.toint((wyj1->Value) / FI / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj1KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj1->Value) / FI / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj2KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj2->Value) / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj2Click(TObject *Sender) {

	wej1->Value = o1.toint((wyj2->Value) / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj3KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj3->Value) / FI - (wyj3->Value));

	// if(o1.bufor_do_obliczeñ-1 || o1.bufor_do_obliczeñ+1==(int)wyj3->Value) {
	// o1.lpobrana=o1.bufor_do_obliczeñ/FI-o1.bufor_do_obliczeñ;    // otrzymywanie wartoœci wej1
	// wej1->Value=o1.lpobrana;
	// Edit1->Text=static_cast<float>(o1.lpobrana);
	// }
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj3Click(TObject *Sender) {

	wej1->Value = o1.toint((wyj3->Value) / FI - (wyj3->Value));

	// if(o1.bufor_do_obliczeñ-1 || o1.bufor_do_obliczeñ+1!=(int)wyj3->Value) { ; }
	//
	// else{
	// o1.lpobrana=o1.bufor_do_obliczeñ/FI-o1.bufor_do_obliczeñ;    // otrzymywanie wartoœci wej1
	// wej1->Value=o1.toint(o1.lpobrana); //do wykonania
	// Edit1->Text=static_cast<float>(o1.lpobrana);
	// }
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj4KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj4->Value) * FI * FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj4Click(TObject *Sender) {

	wej1->Value = o1.toint((wyj4->Value) * FI * FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj5KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj5->Value) / 2 / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj5Click(TObject *Sender) {

	wej1->Value = o1.toint((wyj5->Value) / 2 / FI);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj6KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej1->Value = o1.toint((wyj6->Value) / FI * 2 + (wyj6->Value));
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wyj6Click(TObject *Sender) {

	wej1->Value = o1.toint((wyj6->Value) / FI * 2 + (wyj6->Value));
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton1DownClick(TObject *Sender) {
	decrement(CSpinButton1);
}

//// ---------------------------------------------------------------------------
//void __fastcall TFibonacciR::CSpinButton2DownClick(TObject *Sender) {
////	decrement(CSpinButton2);
//
//FibonacciR->FiFloat->decerment( (TCSpinButton*) Sender);
//}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton3DownClick(TObject *Sender) {
	decrement(CSpinButton3);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton4DownClick(TObject *Sender) {
	decrement(CSpinButton4);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton5DownClick(TObject *Sender) {
	decrement(CSpinButton5);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton6DownClick(TObject *Sender) {
	decrement(CSpinButton6);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton7DownClick(TObject *Sender) {
	decrement(CSpinButton7);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton1UpClick(TObject *Sender) {
	increment(CSpinButton1);
}

//// ---------------------------------------------------------------------------
//void __fastcall TFibonacciR::CSpinButton2UpClick(TObject *Sender) {
//	increment(CSpinButton2);
//}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton3UpClick(TObject *Sender) {
	increment(CSpinButton3);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton4UpClick(TObject *Sender) {
	increment(CSpinButton4);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton5UpClick(TObject *Sender) {
	increment(CSpinButton5);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton6UpClick(TObject *Sender) {
	increment(CSpinButton6);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CSpinButton7UpClick(TObject *Sender) {
	increment(CSpinButton7);
}

// ---------------------------------------------------------------------------   // ZAAWANSOWANE
//void __fastcall TFibonacciR::wejKeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
//	KeyD(Key, CSpinButton1);
//}

// ---------------------------------------------------------------------------
// void __fastcall TFibonacciR::wy1KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
//
//
//
//	if (Key == vkUp)		FibonacciR->FiFloat->incerment( (TEdit*) Sender );
//
//	else if (Key == vkDown)	FibonacciR->FiFloat->decerment( (TEdit*) Sender );
//
//	else                   	FibonacciR->FiFloat->Key_Down( (TEdit*) Sender );
// }

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy2KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
	KeyD(Key, CSpinButton3);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy3KeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	KeyD(Key, CSpinButton4);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy4KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
	KeyD(Key, CSpinButton5);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy5KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
	KeyD(Key, CSpinButton6);
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy6KeyDown(TObject *Sender, WORD &Key,	TShiftState Shift) {
	KeyD(Key, CSpinButton7);

	// wej->Text = (wy6->Text.ToDouble()) /FI*2 + (wy6->Text.ToDouble());

}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Screen1Click(TObject *Sender) {
	Sleep(300); // opóŸnienie

	MakePrintScreen();

}

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ButtonSettingsClick(TObject *Sender)
{
switch (PageControl2->ActivePageIndex) {

//	case 0: Form2->PageControl1->ActivePageIndex = 0; break;                    // ca³kowite->ogólne

	case 1: Form2->PageControl1->ActivePageIndex = 2; break;                    // zaawansowany->zaawansowany

	case 2: Form2->PageControl1->ActivePageIndex = 3; break;                    // strumienie->strumienie

	case 3: Form2->PageControl1->ActivePageIndex = 4; break;                    // szukaj->wyszukiwanie

	default:                                     ;
//        Form2->PageControl1->ActivePageIndex = 0;
	}

   if ( S::Activated || S::ProVersion ) Form2->Show();                          // zwyk³e otwarcie okna
   else
   try { Form2->ShowModal(); } catch (...)
   {
	Form2->Close();
	Form2->ShowModal();                                                         // przypadku gdy okno jest otwarte niemodalnie
   }
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::CheckBoxSLOGClick(TObject *Sender) {
	Form2->CheckBoxULOG->Checked = CheckBoxSLOG->Checked;
	if ( !CheckBoxSLOG->Checked ) {                                             // przy wy³¹czaniu
		ShowMessage("W przypadku b³êdu oprogramowania, naprawa i diagnoza problemu mo¿e byæ utrudniona");
	}
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Usu1Click(TObject *Sender) {
	// ListBox1->Items->Delete(ListBox1->ItemIndex);
	ListBox1->DeleteSelected();
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Edit3Change(TObject *Sender) { // wyszukaj

	short int *index = new short int;
	*index = ListBox1->Perform(LB_FINDSTRING, -1, (LPARAM)Edit3->Text.c_str());
	if (*index != -1) {
		ListBox1->ItemIndex = *index;
		ListBox1->Color = clCream;
	}
	else {
		ListBox1->Selected[*index] = false;

	}
	// ShowMessage(ListBox1->Items->Text);

	// ShowMessage(ListBox1->GetEnumerator());

	delete index;
}

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::wy2KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {

	wej->Text = (DigitRewrite(wy2->Text).ToDouble()) / FI; // bug
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::wy3KeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	wej->Text = (DigitRewrite(wy3->Text).ToDouble()) / FI -
		(wy3->Text).ToDouble();
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::wy4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift) {

	wej->Text = (DigitRewrite(wy4->Text).ToDouble()) * FI * FI;
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::wy5KeyUp(TObject *Sender, WORD &Key, TShiftState Shift) {

	wej->Text = (DigitRewrite(wy5->Text).ToDouble()) / 2 / FI;
}
// ---------------------------------------------------------------------------

void __fastcall TFibonacciR::wy6KeyUp(TObject *Sender, WORD &Key,	TShiftState Shift) {

	unique_ptr<AnsiString>buff (new AnsiString(DigitRewrite(wy6->Text).ToDouble()));

	wej->Text = (*buff).ToDouble() / FI * 2 + (*buff).ToDouble();
}

// ---------------------------------------------------------------------------
//void __fastcall TFibonacciR::EditSciezkaszukanaKeyPress(TObject *Sender,
//	System::WideChar &Key) {
//
//
//}
// ---------------------------------------------------------------------------
void TFibonacciR::ExecuteFiltrSearch(String a) {

	S::FiltrSearch = a;
	LabelEXT->Caption = a;
	ButtonSzukajClick(this);
	return;
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Wszystko1Click(TObject *Sender) { // filter

	ExecuteFiltrSearch("*");
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Plikitekstowetxt1Click(TObject *Sender) {

	ExecuteFiltrSearch("*.txt");
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Dowolne1Click(TObject *Sender) {

	ExecuteFiltrSearch("*.*");
}

// ---------------------------------------------------------------------------
void TFibonacciR::StatusInfo(AnsiString Text, unsigned panel) {

	StatusBar1->Panels->Items[panel]->Text = Text;
}

// ---------------------------------------------------------------------------
AnsiString TFibonacciR::BreakQuestion() {

	unique_ptr<AnsiString>a(new AnsiString(S::BREAK_SEARCH));
	(*a).Insert("ZnaleŸono ", 1);
	(*a).Insert(" plików.\n\nSzukaæ dalej?", (*a).Length() + 1);

	return *a;
}

// ---------------------------------------------------------------------------

void TFibonacciR::sortListVby_size ( bool top_bigger )
{
//     FibonacciR->ListView1->Item[i]->SubItems->Strings[2];
}

void TFibonacciR::calcSizeOfList (  )
{
	unique_ptr<unsigned long> files_size (new unsigned long (0) );

	for ( int i = 0; i < ListView1->Items->Count; i++) {

		*files_size += ListView1->Items->Item[i]->SubItems->Strings[2].ToInt();

	}
	ListView1->Column[2]->Caption = "Rozmiar (" + GetSize( *files_size.get() ) + ")";
}
