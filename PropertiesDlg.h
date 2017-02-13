//----------------------------------------------------------------------------
#ifndef PropertiesDlgH
#define PropertiesDlgH
//----------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//----------------------------------------------------------------------------
class TPropetisDlg : public TForm
{
__published:
	TPanel *Panel1;
	TPanel *Panel2;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TButton *OKBtn;
	TButton *CancelBtn;
	TButton *HelpBtn;
	TImage *ImageEXE;
	TLabel *LabelFileTypeL;
	TLabel *LabelOpenWithL;
	TLabel *Label1;
	TEdit *EditFileName;
	TLabel *Label2;
	TLabel *LabelPathL;
	TLabel *LabelPath;
	TLabel *LabelSizeL;
	TLabel *LabelSize;
	TLabel *LabelSizeOnDiskL;
	TLabel *LabelSizeOnDisk;
	TLabel *LabelFileType;
	TLabel *LabelOpenWith;
	TImage *ImageOpenWith;
	TLabel *LabelCreatedL;
	TLabel *Label4;
	TLabel *LabelAttribL;
	TCheckBox *CheckBoxReadOnly;
	TCheckBox *CheckBoxHide;
	TLabel *LabelEditedL;
	TLabel *LabelEdited;
	TLabel *LabelCreated;
	TLabel *Label5;
	TLabel *LabelLastUseL;
	TLabel *LabelLastUse;
	TLabel *Label3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OKBtnClick(TObject *Sender);

private:

	String *Path;
	void FillWnd();
	void LoadImg();
	void LoadSize();
	void LoadTime();

public:
	TPropetisDlg(TComponent* AOwner, String* FilePath, bool ADS_1 = 1 );
	String GetFileVersionInfo(char *ModulePath, String KeyName);

//	virtual __fastcall TPropetisDlg(TComponent* AOwner);
};

	bool Properties(String* File_Path, bool ADS);

//----------------------------------------------------------------------------
extern PACKAGE TPropetisDlg *PropetisDlg;
//----------------------------------------------------------------------------
#endif    
