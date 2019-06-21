//----------------------------------------------------------------------------
#ifndef TabPgDlgH
#define TabPgDlgH
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
	TImage *Image1;
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
	TImage *Image2;
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

private:
public:
	virtual __fastcall TPropetisDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TPropetisDlg *PropetisDlg;
//----------------------------------------------------------------------------
#endif    
