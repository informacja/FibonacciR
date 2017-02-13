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
#include <Vcl.Mask.hpp>
#include <Registry.hpp>
#include <stdio.h>
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
	TButton *ZastosujBtn;
	TImage *ImageEXE;
	TLabel *LabelFileTypeL;
	TLabel *LabelOpenWithL;
	TLabel *Label1;
	TEdit *EditFileName;
	TLabel *Label2;
	TLabel *LabelPathL;
	TLabel *LabelSizeL;
	TLabel *LabelSizeOnDiskL;
	TImage *ImageOpenWith;
	TLabel *LabelCreatedL;
	TLabel *Label4;
	TLabel *LabelAttribL;
	TCheckBox *CheckBoxReadOnly;
	TCheckBox *CheckBoxHide;
	TLabel *LabelEditedL;
	TLabel *Label5;
	TLabel *LabelLastUseL;
	TLabel *Label3;
	TEdit *EditCreatedDate;
	TEdit *LabelEditedData;
	TEdit *LabelLastUseData;
	TEdit *EditOpenWith;
	TEdit *EditPath;
	TEdit *EditSize;
	TEdit *EditFileType;
	TEdit *EditCreatedDay;
	TEdit *LabelEditedDay;
	TEdit *LabelLastUseDay;
	TEdit *EditSizeOnDisk;
	TDateTimePicker *DateTimePickerCreateTime;
	TDateTimePicker *DateTimePickerCreateDate;
	TCheckBox *CheckBoxSys;
	TCheckBox *CheckBoxArch;
	TDateTimePicker *DateTimePickerAccessDate;
	TDateTimePicker *DateTimePickerWriteDate;
	TDateTimePicker *DateTimePickerAccessTime;
	TDateTimePicker *DateTimePickerWriteTime;
	TListView *ListView1;
	TCheckBox *CheckBoxAllSame;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall CheckBoxHideClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall ZastosujBtnClick(TObject *Sender);
	void __fastcall LabelLastUseDataMouseLeave(TObject *Sender);
	void __fastcall LabelEditedDataMouseLeave(TObject *Sender);
	void __fastcall LabelEditedDataMouseEnter(TObject *Sender);
	void __fastcall EditCreatedDateMouseEnter(TObject *Sender);
	void __fastcall EditCreatedDateMouseLeave(TObject *Sender);
	void __fastcall LabelLastUseDataMouseEnter(TObject *Sender);
	void __fastcall EditCreatedDateClick(TObject *Sender);
	void __fastcall LabelEditedDataClick(TObject *Sender);
	void __fastcall LabelLastUseDataClick(TObject *Sender);
	void __fastcall EditCreatedDateKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall LabelEditedDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall LabelLastUseDataKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall LabelAttribLClick(TObject *Sender);
	void __fastcall CheckBoxAllSameClick(TObject *Sender);

private:

	WIN32_FILE_ATTRIBUTE_DATA fileAttrData;
	TRegistry *Reg;

	const String *Path;
	const String  path;
	void FillWnd();
	void LoadImg();
	void LoadDescriptionFromExtension();
	void LoadDescrypOpenWithProgrm( String path);
	void LoadSize();
	void LoadTime();
	void LoadAttrib();

	void SetAttr();
	void SetTime();
	void GetEditedTime( SYSTEMTIME *screate, SYSTEMTIME *saccess, SYSTEMTIME *swrite );

	ULONG_PTR m_gdiplusToken;
	String initial_value_of_path( String* s) {	return *s; };					// zwracana wartoœæ jest przypisywana do const path

	unsigned short  Attributes, NewAttributes;

public:

	TPropetisDlg(TComponent* AOwner, String* FilePath, bool ADS_1 = 1 );

//	virtual __fastcall TPropetisDlg(TComponent* AOwner);
};


/***************************************************************************/

	bool Properties( String* File_Path, bool ADS );                             // wywo³ywanie okna w³aœciwoœci

	bool Properties( String* File_Path, String* File_Name, bool ADS );         	// wywo³ywanie okna w³aœciwoœci

	String AddSpace( String text, unsigned pos );                               // przy formatowaniu wyœwietania bitów (rozmiar pliku)

	String GetFileVersionInfo( wchar_t *ModulePath, String KeyName );

//----------------------------------------------------------------------------
extern PACKAGE TPropetisDlg *PropetisDlg;
//----------------------------------------------------------------------------
#endif    
