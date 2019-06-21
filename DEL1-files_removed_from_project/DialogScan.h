//----------------------------------------------------------------------------
#ifndef DialogScanH
#define DialogScanH
//----------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ScreenTips.hpp>
//----------------------------------------------------------------------------
class TSearchPref : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TLabel *LabelEXT;
	TLabel *LabelSUBFOLD;
	TCheckBox *CheckBoxScanDepth;
	TEdit *EditPath;
	TButton *Button1;
	TComboBox *ComboBoxEXT;
	TComboBox *ComboBoxDepth;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall CheckBoxScanDepthClick(TObject *Sender);
	void __fastcall EditPathChange(TObject *Sender);
	void __fastcall ComboBoxDepthChange(TObject *Sender);
	void __fastcall ComboBoxEXTChange(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LabelEXTClick(TObject *Sender);
	void __fastcall ComboBoxEXTDblClick(TObject *Sender);


private:
	String bufforDepth;

public:
	virtual __fastcall TSearchPref(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TSearchPref *SearchPref;
//----------------------------------------------------------------------------
#endif    
