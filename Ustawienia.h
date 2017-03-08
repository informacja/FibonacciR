//---------------------------------------------------------------------------

#ifndef UstawieniaH
#define UstawieniaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "trayicon.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.ValEdit.hpp>
#include <FireDAC.VCLUI.Controls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.Samples.DirOutln.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TCheckBox *CheckBox2;
	TTrackBar *TrackBar1;
	TMaskEdit *MaskEditKod;
	TCheckBox *CheckBox3;
	TTabSheet *TabSheet2;
	TCheckBox *CheckBox4;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBoxZ1;
	TTabSheet *TabSheet3;
	TMaskEdit *MaskEditInkrem;
	TTabSheet *TabSheet4;
	TButton *Button2;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TGroupBox *GroupBox2;
	TRadioButton *RadioButton7;
	TRadioButton *RadioButton9;
	TEdit *Edit1;
	TGroupBox *GroupBox3;
	TCheckBox *CheckBoxULOG;
	TButton *ButtonWybierz;
	TRadioButton *RadioButton10;
	TRadioButton *RadioButton11;
	TGroupBox *GroupBox4;
	TCheckBox *CheckBoxZ3;
	TCheckBox *CheckBoxZ2;
	TCheckBox *CheckBoxZ4;
	TCheckBox *CheckBoxZ6;
	TCheckBox *CheckBoxZ5;
	TLabel *Label1;
	TLabel *LabelWinkrem;
	TEdit *EditNameADS;
	THotKey *HotKey1;
	TCheckBox *CheckBoxRound;
	TTabSheet *TabSheet5;
	TComboBox *ComboBox1;
	TLabel *Label2;
	TComboBox *ComboBox2;
	TLabel *Label3;
	TPopupMenu *PopupMenu1;
	TMenuItem *Zamknij1;
	TCheckBox *CheckBoxNoDATA;
	TButton *Button1;
	TTabSheet *TabSheet6;
	TPageControl *PageControl2;
	TTabSheet *TabSheet7;
	TGroupBox *GroupBox6;
	TRadioButton *RadioButtonSForeground;
	TRadioButton *RadioButtonSCheckW;
	TRadioButton *RadioButtonSALL;
	TGroupBox *GroupBox5;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton1;
	TComboBox *ComboBoxQuality;
	TCheckBox *CheckBoxSaveClipboard;
	TTabSheet *TabSheet8;
	TTabSheet *TabSheet9;
	TGroupBox *GroupBox7;
	TRadioButton *RadioButtonAcctualfolder;
	TRadioButton *RadioButtonSourseFile;
	TValueListEditor *ValueListEditor1;
	TButtonedEdit *ButtonedEdit1;
	TSpinEdit *SpinEdit1;
	TCheckBox *CheckBoxAutoStart;
	TCheckBox *CheckBoxHide;
	TLabel *Label4;
	TSpinEdit *SpinEdit2;
	TCheckBox *CheckBoxclipkonwersja;
	TButton *ButtonKonwert;
	TRadioButton *RadioButtonPulpit;
	TImageList *ImageList1;
	TRadioButton *RadioButtonLocalization;
	TEdit *EditLocalization;
	TPanel *PanelImage;
	TCheckBox *CheckBoxHideData;
	TCheckBox *CheckBoxZoneId;
	TCheckBox *CheckBoxListVCheckB;
	TCheckBox *CheckBox5;
	TTrayIcon *TrayIcon1;
	TButtonedEdit *EditKod;
	TLabel *LabelDefProgDescript;
	TLabel *LabelDefProgPath;
	TLabeledEdit *LabeledEditNameSave;
	TCheckBox *CheckBoxSave;
	TGroupBox *GroupBoxSaveFormat;
	TLabel *LabelSaveFormatL;
	TLabel *LabelFormatDot;
	TLabel *LabelFormatAfterDot;
	TLabel *LabelFormatBeforeDot;
	TSpinEdit *SpinEditFormatBefore;
	TSpinEdit *SpinEditFormatAfter;
	TSpinEdit *SpinEditFill;
	TLabel *LabelFillL;
	TPopupMenu *PopupMenuSysPref;
	TMenuItem *Mysz1;
	TMenuItem *Klawiatrura1;
	TMenuItem *Ekran1;
	TMenuItem *Energia1;
	TMenuItem *KontroleryGier1;
	TMenuItem *Skaner1;
	TCheckBox *CheckBoxGlobal;
	TTabSheet *TabSheet11;
	TButton *Button4;
	TButton *ButtonDelReg;
	TCheckBox *CheckBoxSaveToReg;
	TButton *ButtonWinHistory;
	TButton *ButtonSaveIcons;
	TButton *Button3;
	TButton *ButtonNetwork;
	TButton *ButtonSendTo;
	TButton *ButtonRecent;
	TButton *Buttontest;
	TSpeedButton *SpeedButtonNamePre;
	TSpeedButton *SpeedButtonNameNew;
	TSpeedButton *SpeedButtonNamePost;
	TSpeedButton *SpeedButtonNameOriginal;
	TEdit *EditBlockDomain;
	TEdit *EditForwardHost;
	TButton *ButtonHostAddBlock;
	TTrackBar *TrackBarIconSize;
	TLabel *LabelIconSizeL;
	TCheckBox *CheckBoxLegendInFile;
	TImage *ImagePreview;
	TButton *Button5;
	TButton *ButtonClose;
	TCheckBox *CheckBoxPointTop;
	TLabel *Label5;
	TCheckBox *CheckBoxCanMove;
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall CheckBoxSaveClick(TObject *Sender);
	void __fastcall MaskEditInkremChange(TObject *Sender);
	void __fastcall CheckBoxULOGClick(TObject *Sender);
	void __fastcall ButtonWybierzClick(TObject *Sender);
	void __fastcall EditKodChange(TObject *Sender);
	void __fastcall TabSheet4Enter(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

//	void __fastcall OnDropFiles(TMessage &Msg);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall MaskEditKodChange(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall GroupBox3Enter(TObject *Sender);
	void __fastcall GroupBox4Enter(TObject *Sender);
	void __fastcall GroupBox2Enter(TObject *Sender);
	void __fastcall EditNameADSChange(TObject *Sender);
	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CheckBoxRoundClick(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall Label3Click(TObject *Sender);
	void __fastcall Label2Click(TObject *Sender);
	void __fastcall Zamknij1Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall RadioButton11Click(TObject *Sender);
	void __fastcall RadioButton10Click(TObject *Sender);
	void __fastcall RadioButton9Click(TObject *Sender);
	void __fastcall RadioButton8Click(TObject *Sender);
	void __fastcall RadioButton7Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall ComboBoxQualityChange(TObject *Sender);
	void __fastcall ButtonSaveIconsClick(TObject *Sender);
	void __fastcall ButtonedEdit1Click(TObject *Sender);
	void __fastcall ButtonKonwertClick(TObject *Sender);
	void __fastcall CheckBoxAutoStartClick(TObject *Sender);
	void __fastcall CheckBoxHideClick(TObject *Sender);
//	void __fastcall ButtonBlueScreenClick(TObject *Sender);
	void __fastcall CheckBoxUpDateRebotClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall MaskEditInkremKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonedEditLocalClick(TObject *Sender);
	void __fastcall RadioButtonSourseFileClick(TObject *Sender);
	void __fastcall RadioButtonAcctualfolderClick(TObject *Sender);
	void __fastcall RadioButtonPulpitClick(TObject *Sender);
	void __fastcall EditLocalizationChange(TObject *Sender);
	void __fastcall ImagePreviewClick(TObject *Sender);
	void __fastcall ImagePreviewProgress(TObject *Sender, TProgressStage Stage, BYTE PercentDone,
		  bool RedrawNow, const TRect &R, const UnicodeString Msg);
	int __fastcall LoadImage(Pointer Parameter);
	void __fastcall CheckBoxListVCheckBClick(TObject *Sender);
	void __fastcall CheckBoxNoDATAClick(TObject *Sender);
	void __fastcall TabSheet5Show(TObject *Sender);
	void __fastcall LabelDefProgPathClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ButtonDelRegClick(TObject *Sender);
	void __fastcall CheckBoxSaveToRegClick(TObject *Sender);
	void __fastcall LabeledEditNameSaveChange(TObject *Sender);
	void __fastcall SpinEditFormatBeforeChange(TObject *Sender);
	void __fastcall SpinEditFormatAfterChange(TObject *Sender);
	void __fastcall Mysz1Click(TObject *Sender);
	void __fastcall Klawiatrura1Click(TObject *Sender);
	void __fastcall Ekran1Click(TObject *Sender);
	void __fastcall Energia1Click(TObject *Sender);
	void __fastcall KontroleryGier1Click(TObject *Sender);
	void __fastcall Skaner1Click(TObject *Sender);
	void __fastcall Drukarka1Click(TObject *Sender);
	void __fastcall ButtonWinHistoryClick(TObject *Sender);
	void __fastcall ButtonNetworkClick(TObject *Sender);
	void __fastcall ButtonSendToClick(TObject *Sender);
	void __fastcall ButtonRecentClick(TObject *Sender);
	void __fastcall ButtontestClick(TObject *Sender);
	void __fastcall SpeedButtonNameOriginalClick(TObject *Sender);
	void __fastcall SpeedButtonNameNewClick(TObject *Sender);
	void __fastcall MaskEditInkremKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ButtonHostAddBlockClick(TObject *Sender);
	void __fastcall EditBlockDomainDblClick(TObject *Sender);
	void __fastcall EditBlockDomainKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditBlockDomainClick(TObject *Sender);
	void __fastcall TrackBarIconSizeChange(TObject *Sender);
	void __fastcall LabeledEditNameSaveDblClick(TObject *Sender);
	void __fastcall CheckBoxLegendInFileClick(TObject *Sender);
	void __fastcall ComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall MaskEditKodClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonCloseKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall TrayIcon1Click(TObject *Sender);






private:	// User declarations

	TWndMethod Df;
	TRegistry *Reg;

	void __fastcall OnDropFiles(TMessage &Msg);
	void CheckRegistry();

	void AdvancedMode(bool b );
	void FindProgramToOpenADS();
	void SaveFormat();
//	bool CursorInEditLocal();
	unsigned W_PD;                                                              // pseudoidentyfikator
	int W_ID;


public:
	HANDLE MutexQuietMod;
	void SysPref(AnsiString command);
	void CheckRegSystemGroup();
	bool checking;
	bool copyclick;
//bool Ustchange;


	__fastcall TForm2(TComponent* Owner);

};

//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
