//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Dialogs/DialogScan.h"
#include "Unit1.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TSearchPref *SearchPref;
//---------------------------------------------------------------------
__fastcall TSearchPref::TSearchPref(TComponent* AOwner)
	: TForm(AOwner)
{
EditPath->Text = FibonacciR->ButtonedEditSearch->Text;
ComboBoxDepth->Text = S::MAX_DEPTH;
ComboBoxEXT->Text = FibonacciR->LabelEXT->Caption;

}
//---------------------------------------------------------------------

void __fastcall TSearchPref::Button1Click(TObject *Sender)
{
	String Dir = EditPath->Text;
	if (SelectDirectory("Otwórz", String("2").w_str(), Dir,
	   TSelectDirExtOpts() << sdNewUI << sdNewFolder << sdShowShares << sdShowFiles))
		EditPath->Text = Dir;
		FibonacciR->ButtonedEditSearch->Text = Dir;
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::OKBtnClick(TObject *Sender)
{
	this->Hide();
	FibonacciR->ButtonedEditSearch->Text = EditPath->Text;
	FibonacciR->LabelEXT->Caption = ComboBoxEXT->Text;
	S::FiltrSearch = ComboBoxEXT->Text;
	FibonacciR->ButtonSzukajClick(0);
	this->CloseModal();
	//FibonacciR->CloseScanPrefWnd();//todo
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::CheckBoxScanDepthClick(TObject *Sender)
{
 ComboBoxDepth->Enabled = CheckBoxScanDepth->Checked;

 if ( ComboBoxDepth->Enabled ) {

	ComboBoxDepth->Text = bufforDepth;
  }
 else {
	bufforDepth = ComboBoxDepth->Text;
	ComboBoxDepth->Text = 1;
 }
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::EditPathChange(TObject *Sender)
{
FibonacciR->ButtonedEditSearch->Text = EditPath->Text;
EditPath->Hint = EditPath->Text;
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::ComboBoxDepthChange(TObject *Sender)
{

 if ( ComboBoxDepth->Text == "Unlimited" ) {

	S::MAX_DEPTH = 0;
 }
 else if (ComboBoxDepth->Text.ToInt() >= 0 && ComboBoxDepth->Text.ToInt() <= 255 ){

		S::MAX_DEPTH = ComboBoxDepth->Text.ToInt();

 } else ComboBoxDepth->Text = 5;

 ComboBoxDepth->Hint = S::MAX_DEPTH;

}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::ComboBoxEXTChange(TObject *Sender)
{
	S::FiltrSearch = ComboBoxEXT->Text;
	ComboBoxEXT->Hint = S::FiltrSearch;
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::CancelBtnClick(TObject *Sender)
{
	CloseModal();
}
//---------------------------------------------------------------------------
void __fastcall TSearchPref::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSearchPref::LabelEXTClick(TObject *Sender)  {

	ComboBoxEXT->Text = "*.*";
	ComboBoxEXT->Perform(EM_SETSEL, 1, 1);
	ComboBoxEXT->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TSearchPref::ComboBoxEXTDblClick(TObject *Sender)
{
	ComboBoxEXT->Text = "*.";
	ComboBoxEXT->Perform(EM_SETSEL, 2, 2 );
}
//---------------------------------------------------------------------------

