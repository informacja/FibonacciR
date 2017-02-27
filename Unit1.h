
#ifndef Unit1H
#define Unit1H

	#define FINAL

#define NO_WIN32_LEAN_AND_MEAN 													// zapobieganie wyst¹pienia b³êdów z <shlobj.h>

#include "cspin.h"
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.BandActn.hpp>
#include <Vcl.Touch.GestureMgr.hpp>
#include <Vcl.ExtActns.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.CustomizeDlg.hpp>
#include <Vcl.DockTabSet.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.CheckLst.hpp>

//---------------------------------------------------------------------------

#ifdef _WIN32
 #include <io.h>                                                                // (Windows)
 /* Values for the second argument to access. These may be OR'd together.  */

 #define R_OK    4       /* Test for read permission.  */
 #define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1    /* execute permission - unsupported in windows */
 #define F_OK    0       /* Test for existence.  */

#else
 #include <unistd.h>      	// access(...) // sprawdza dostêp do pliku, katalogu (UNIX header)
#endif

//---------------------------------------------------------------------------

#include <cmath>
#include <cstdio>
#include <cstring>
#include <String>
#include <math.h>
#include <iomanip.h>
#include <fstream.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shellapi.h>
#include <winbase.h>
#include <vector>
#include <stdio.h>     	// for FILE, fopen, fstat, fileno, fread and fclose
#include <sys\stat.h>  	// for fstat and the stat struct
//#include <Math.hpp> 	// for Min
#include <memory>     	// for STL auto_ptr class
#include <psapi.h>  	// Wprogramie.cpp
//#include "adCpuUsage.hpp"
#include <shlobj.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <filectrl.hpp>
#include <tlhelp32.h>        // procesy
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <pnglang.hpp>
#include <ScreenTips.hpp>
#include <clipbrd.hpp>
#include <Registry.hpp>
#include <Classes.hpp>
//#include <limits.h>
#include <mapi.h>
#include <Gdiplus.h>

#include "Enum.h"
#include "integrity.h"                     										// obliczenia fi dla int    (zwyk³e, ca³kowite)
#include "floating.h"                     										// obliczenia fi dla double (zaawansowane)
#include "Wa¿ne.h"
#include "Akcje.h"
#include "Func.h"
#include "Ustawienia.h"
#include "Wprogramie.h"
#include "Nieznacz¹ce_polecenia.h"
#include "Times.h"
#include "Picture.h"
#include "Generic.h"
//#include "Singleton.h"
#include "from_internet.h"
#include "Dialogs/DialogScan.h"                                                         // na potrzeby dynamicznego wywo³ania
#include "Dialogs/PropertiesDlg.h"
//#include "Common/Error.hpp"
// #include "Common/Base.hpp"
#include "Thread/Thread.h"
#include "Thread/TGdiPlus.h"
#include "Messages.rh"
#include "Point_Form.h"

//#include "Laboratory.hpp"
//#include "Security.hpp"

using namespace std;

//---------------------------------------------------------------------------

#include <Vcl.Forms.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ToolWin.hpp>
#include "cgauges.h"
#include "trayicon.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <System.ImageList.hpp>
#include <Vcl.FileCtrl.hpp>


 class 	TFloatFI;					// deklaracja istnienia dla poinformowania klasy TFibonacciR

//---------------------------------------------------------------------------
class TFibonacciR : public TForm
{

public:

	TFloatFI *FiFloat;
	TIntFI  *FiInt;
	TProgressBar *ProgressBar1;
	TImage *ImageSave;
	TTimer *timer;
	TEdit *edit;

	void __fastcall MyFunction(TObject *Sender);
	void __fastcall editExit(TObject *Sender);
	void __fastcall editOnChange(TObject *Sender);
	String __fastcall GetVolumeName(LPCTSTR FindDrive);
	void __fastcall EnumDrivers(TStrings *EnumList);


__published:	// IDE-managed Components
	TPopupMenu *PopupMenuForm;
	TMainMenu *MainMenu;
	TActionList *ActionList1;
	TStatusBar *StatusBar1;
	TTimer *Timer1;
	TMenuItem *NOEy1;
	TMenuItem *Zamknij1;
	TMenuItem *Plik1;
	TMenuItem *Zeruj1;
	TMenuItem *Screen1;
	TMenuItem *Zamknij2;
	TMenuItem *Opcje1;
	TMenuItem *Ustawienia1;
	TMenuItem *Jzyk1;
	TMenuItem *Oprogramie1;
	TMenuItem *Pomoc1;
	TMenuItem *Strony1;
	TMenuItem *Wersja1;
	TAction *Action1;
	TMenuItem *Kopiuj1;
	TMenuItem *N1;
	TMenuItem *PL1;
	TMenuItem *EN1;
	TMenuItem *UpdateApp;
	TMenuItem *Joe2;
	TMenuItem *Mistrzowie1;
	TPopupMenu *PopupMenuTray;
	TMenuItem *MenuItem3;
	TMenuItem *MenuItem4;
	TMenuItem *Oprogramie2;
	TMenuItem *arcik1;
	TSaveDialog *SaveDialog1;
	TFindDialog *FindDialog1;
	TImageList *ImageList1;
	TPopupMenu *PopupMDroped;
	TMenuItem *Usu1;
	TPopupMenu *PopupMenuSzukaj;
	TMenuItem *Plikitekstowetxt1;
	TMenuItem *Zdjcia1;
	TMenuItem *Inne1;
	TBalloonHint *BalloonHint1;
	TMenuItem *Dowolne1;
	TMenuItem *Wszystko1;
	TMenuItem *podpowiedzi1;
	TMenuItem *Zawszenawierzchu1;
	TSavePictureDialog *SavePictureDialog1;
	TCustomizeActionBars *CustomizeActionBars1;
	TWindowClose *WindowClose1;
	TMenuItem *N2;
	TPopupMenu *PopupMenuListView;
	TMenuItem *Podglad;
	TMenuItem *Waciwoi1;
	TMenuItem *Otwrz1;
	TMenuItem *Zaawansowane1;
	TMenuItem *DopiszADS1;
	TMenuItem *Otwrzz1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *Usu2;
	TButton *ButtonSettings;
	TMenuItem *Zapisz1;
	TMenuItem *N5;
	TMenuItem *Kopiujdoschowka1;
	TMenuItem *SzukajADS1;
	TMenuItem *Usuzaznaczone1;
	TMenuItem *Usuwszystko1;
	TMenuItem *N6;
	TMenuItem *naStatusBarze1;
	TMenuItem *Email1;
	TMenuItem *Utwrzskrt1;
	TMenuItem *Pulpit1;
	TMenuItem *Pulpit2;
	TMenuItem *Kopiujciek1;
	TMenuItem *Eksportujlist1;
	TAction *Action7;
	TEditSelectAll *EditSelectAll1;
	TAction *Action2;
	TAction *Action3;
	TAction *Action4;
	TSendMail *InternetSendBugInfoMail;
	TPreviousTab *TabPreviousTab1;
	TNextTab *TabNextTab1;
	TMenuItem *SpeedMode1;
	TMenuItem *Waciwoci1;
	TMenuItem *Notepad1;
	TMenuItem *Wybierz1;
	TMenuItem *Odtwarzacz1;
	TPageControl *PageControl3;
	TTabSheet *TabSheetFI;
	TImageList *ImageListMenu;
	TTabSheet *TabSheetADS;
	TTabSheet *TabSheetSystem;
	TTabSheet *TabSheetGraph;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox2;
	TSpinEdit *wyj1;
	TSpinEdit *wyj2;
	TSpinEdit *wyj3;
	TSpinEdit *wyj4;
	TSpinEdit *wej1;
	TGroupBox *GroupBox1;
	TSpinEdit *wyj5;
	TSpinEdit *wyj6;
	TCheckBox *CheckBoxZapisz;
	TGroupBox *GroupBox5;
	TButton *Button2;
	TButton *Button1;
	TMemo *Memo1;
	TButton *Button3;
	TTabSheet *TabSheet4;
	TEdit *wej;
	TCSpinButton *CSpinButton1;
	TGroupBox *GroupBox3;
	TEdit *wy1;
	TEdit *wy2;
	TEdit *wy3;
	TEdit *wy4;
	TCSpinButton *CSpinButton5;
	TCSpinButton *CSpinButton4;
	TCSpinButton *CSpinButton3;
	TCSpinButton *CSpinButton2;
	TGroupBox *GroupBox4;
	TEdit *wy5;
	TCSpinButton *CSpinButton6;
	TEdit *wy6;
	TCSpinButton *CSpinButton7;
	TCheckBox *CheckBoxZapiszF;
	TTabSheet *TabSheet5;
	TEdit *Edit3;
	TCheckBox *CheckBoxSLOG;
	TListBox *ListBox1;
	TPanel *PanelSaveBy;
	TButtonedEdit *EditADSSave;
	TListView *ListViewDrop;
	TTabSheet *TabSheet1;
	TButton *ButtonSzukaj;
	TListView *ListView1;
	TPanel *Panel1;
	TLabel *LabelEXT;
	TButtonedEdit *ButtonedEditSearch;
	TTabSheet *TabSheetWindows;
	TEdit *EditForwardHost;
	TEdit *EditBlockDomain;
	TButton *ButtonHostAddBlock;
	TPageControl *PageControl1;
	TTabSheet *TabSheet7;
	TGroupBox *GroupBox6;
	TRadioButton *RadioButtonSForeground;
	TRadioButton *RadioButtonSCheckW;
	TRadioButton *RadioButtonSALL;
	TGroupBox *GroupBox7;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton1;
	TCheckBox *CheckBoxSaveClipboard;
	TTabSheet *TabSheetConvert;
	TGroupBox *GroupBox8;
	TLabel *Label4;
	TRadioButton *RadioButtonAcctualfolder;
	TRadioButton *RadioButtonSourseFile;
	TSpinEdit *SpinEdit2;
	TCheckBox *CheckBoxclipkonwersja;
	TRadioButton *RadioButtonPulpit;
	TRadioButton *RadioButtonLocalization;
	TEdit *EditLocalization;
	TPanel *PanelImage;
	TImage *ImagePreview;
	TTabSheet *TabSheetBatchConvert;
	TValueListEditor *ValueListEditorBatch;
	TPanel *Panelwsadowe;
	TButtonedEdit *EditBatchOut;
	TSpinEdit *SpinEdit1;
	TPageControl *PageControl4;
	TPageControl *PageControl5;
	TTabSheet *TabSheetRejestr;
	TGroupBox *GroupBoxReg;
	TCheckBox *CheckBoxFilesExtension;
	TCheckBox *CheckBoxFilesShowAll;
	TCheckBox *CheckBoxUpDateRebot;
	TCheckBox *CheckBoxBlueScreen;
	TCheckBox *CheckBoxcomandprompt;
	TButton *ButtonWMPContMenu;
	TButton *ButtonRepair;
	TCheckBox *CheckBoxDisableUpDate;
	TButton *ButtonRestetRegSettings;
	TCheckBox *CheckBoxUAC;
	TCheckBox *CheckBoxDisableADSReg;
	TBitBtn *ButtonKonwertuj;
	TBitBtn *OpenCurrFolder;
	TButton *ButtonRejestrator;
	TCheckBox *CheckBoxGodMode;
	TRadioButton *RadioButton4;
	TRadioButton *RadioButton5;
	TRadioButton *RadioButton6;
	TComboBox *ComboBoxQuality;
	TTabSheet *TabSheetCMD;
	TLabeledEdit *EditConsoleTextSize;
	TLabeledEdit *EditConsoleBGColor;
	TTabSheet *TabSheetInne;
	TGroupBox *GroupBoxcurTryb;
	TRadioButton *RadioButtonParent;
	TRadioButton *RadioButtonRoot;
	TRadioButton *RadioButtonOwner;
	TCheckBox *CheckBoxTimer;
	TButton *Button5;
	TButton *Button6;
	TEdit *EditCurrsor;
	TButton *Button4;
	TLabeledEdit *EditFileManger;
	TEdit *EditDomain;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button7;
	TImageList *ImageListCursors;
	TButton *ButtonRandom;
	TCheckBox *CheckBoxClearP;
	TButton *ButtonP1;
	TButton *ButtonP2;
	TButton *ButtonLinFunc;
	TCheckListBox *CheckListPoints;
	void __fastcall Zamknij1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Kopiuj1Click(TObject *Sender);
	void __fastcall Joe2Click(TObject *Sender);
	void __fastcall Mistrzowie1Click(TObject *Sender);
	void __fastcall Action1Execute(TObject *Sender);
	void __fastcall Zamknij2Click(TObject *Sender);
	void __fastcall wejChange(TObject *Sender);
	void __fastcall Zeruj1Click(TObject *Sender);
	void __fastcall wej1Change(TObject *Sender);
	void __fastcall Screen1Click(TObject *Sender);
	void __fastcall Wersja1Click(TObject *Sender);
	void __fastcall Ustawienia1Click(TObject *Sender);
	void __fastcall wyj2Click(TObject *Sender);
	void __fastcall wyj2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj3KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj3Click(TObject *Sender);
	void __fastcall wyj5KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj5Click(TObject *Sender);
	void __fastcall wyj6KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj6Click(TObject *Sender);
	void __fastcall wyj4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wyj4Click(TObject *Sender);
	void __fastcall CSpinButton1DownClick(TObject *Sender);
	void __fastcall CSpinButton1UpClick(TObject *Sender);
	void __fastcall CSpinButton2DownClick(TObject *Sender);
	void __fastcall CSpinButton3DownClick(TObject *Sender);
	void __fastcall CSpinButton4DownClick(TObject *Sender);
	void __fastcall CSpinButton5DownClick(TObject *Sender);
	void __fastcall CSpinButton6DownClick(TObject *Sender);
	void __fastcall CSpinButton7DownClick(TObject *Sender);
	void __fastcall CSpinButton2UpClick(TObject *Sender);
	void __fastcall CSpinButton3UpClick(TObject *Sender);
	void __fastcall CSpinButton4UpClick(TObject *Sender);
	void __fastcall CSpinButton5UpClick(TObject *Sender);
	void __fastcall CSpinButton6UpClick(TObject *Sender);
	void __fastcall CSpinButton7UpClick(TObject *Sender);
	void __fastcall wey1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy5KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy3KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy4KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy6KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

	void __fastcall OnDropFiles(TMessage &Msg);
	void __fastcall ListBox1DblClick(TObject *Sender);
	void __fastcall CheckBoxSLOGClick(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall Usu1Click(TObject *Sender);
	void __fastcall CheckBoxZapiszClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall wy2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy3KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy5KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall wy6KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ButtonSzukajClick(TObject *Sender);
	void __fastcall Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Plikitekstowetxt1Click(TObject *Sender);
	void __fastcall Dowolne1Click(TObject *Sender);
	void __fastcall ListView1KeyPress(TObject *Sender, System::WideChar &Key);
//	void __fastcall EditSciezkaszukanaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Wszystko1Click(TObject *Sender);
	void __fastcall ListView1ColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall podpowiedzi1Click(TObject *Sender);
	void __fastcall wyj1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Zawszenawierzchu1Click(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AppIdle(System::TObject *Sender, bool &Done);
	void __fastcall ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall WindowClose1Execute(TObject *Sender);
	TNotifyEvent __fastcall OnTimer(TObject *Sender);
	void __fastcall ListView1Click(TObject *Sender);
	void __fastcall PopupMenuListViewPopup(TObject *Sender);
	void __fastcall Waciwoi1AdvancedDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect, TOwnerDrawState State);
	void __fastcall PodgladClick(TObject *Sender);
	void __fastcall Waciwoi1Click(TObject *Sender);
	void __fastcall Otwrz1Click(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Zdjcia1Click(TObject *Sender);
	void __fastcall Usu2Click(TObject *Sender);
	void __fastcall Memo1Change(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall ButtonSettingsClick(TObject *Sender);
	void __fastcall Kopiujdoschowka1Click(TObject *Sender);
	void __fastcall Inne1Click(TObject *Sender);
	void __fastcall PopupMenuSzukajPopup(TObject *Sender);
	void __fastcall LabelEXTClick(TObject *Sender);
	void __fastcall LabelEXTDblClick(TObject *Sender);
	void __fastcall Usuzaznaczone1Click(TObject *Sender);
	void __fastcall Usuwszystko1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall CheckBoxTimerClick(TObject *Sender);
	void __fastcall ListView1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditCurrsorClick(TObject *Sender);
	void __fastcall naStatusBarze1Click(TObject *Sender);
	void __fastcall Email1Click(TObject *Sender);
	void __fastcall StatusBar1Resize(TObject *Sender);
	void __fastcall Pulpit2Click(TObject *Sender);
	void __fastcall Kopiujciek1Click(TObject *Sender);
	void __fastcall Pulpit1Click(TObject *Sender);
	void __fastcall Zapisz1Click(TObject *Sender);
	void __fastcall EditADSSaveChange(TObject *Sender);
	void __fastcall EditADSSaveDblClick(TObject *Sender);
	void __fastcall EditADSSaveClick(TObject *Sender);
	void __fastcall EditADSSaveKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListViewDropDblClick(TObject *Sender);
	void __fastcall Eksportujlist1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall InternetSendBugInfoMailUpdate(TObject *Sender);
	void __fastcall wy1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditADSSaveRightButtonClick(TObject *Sender);
	void __fastcall ButtonedEditSearchChange(TObject *Sender);
	void __fastcall ButtonedEditSearchRightButtonClick(TObject *Sender);
	void __fastcall ButtonedEditSearchDblClick(TObject *Sender);
	void __fastcall ButtonedEditSearchKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonedEditSearchKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StatusBar1CreatePanelClass(TCustomStatusBar *Sender, TStatusPanelClass &PanelClass);
	void __fastcall SzukajADS1Click(TObject *Sender);
	void __fastcall UpdateAppClick(TObject *Sender);
	void __fastcall ImagePreviewClick(TObject *Sender);
	void __fastcall RadioButtonSourseFileClick(TObject *Sender);
	void __fastcall ImagePreviewProgress(TObject *Sender, TProgressStage Stage, BYTE PercentDone,
          bool RedrawNow, const TRect &R, const UnicodeString Msg);
	void __fastcall EditLocalizationChange(TObject *Sender);
	void __fastcall CheckBoxclipkonwersjaClick(TObject *Sender);
	void __fastcall Waciwoci1Click(TObject *Sender);
	void __fastcall PopupMDropedPopup(TObject *Sender);
	void __fastcall Notepad1Click(TObject *Sender);
	void __fastcall Wybierz1Click(TObject *Sender);
	void __fastcall Odtwarzacz1Click(TObject *Sender);
	void __fastcall ButtonHostAddBlockClick(TObject *Sender);
	void __fastcall EditForwardHostDblClick(TObject *Sender);
	void __fastcall EditForwardHostKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditForwardHostClick(TObject *Sender);
	void __fastcall CheckBoxFilesExtensionClick(TObject *Sender);
	void __fastcall CheckBoxFilesShowAllClick(TObject *Sender);
	void __fastcall CheckBoxcomandpromptClick(TObject *Sender);
	void __fastcall CheckBoxUACClick(TObject *Sender);
	void __fastcall CheckBoxUpDateRebotClick(TObject *Sender);
	void __fastcall CheckBoxBlueScreenClick(TObject *Sender);
	void __fastcall CheckBoxDisableADSRegClick(TObject *Sender);
	void __fastcall CheckBoxDisableUpDateClick(TObject *Sender);
	void __fastcall ButtonRepairClick(TObject *Sender);
	void __fastcall ButtonWMPContMenuClick(TObject *Sender);
	void __fastcall TabSheetRejestrShow(TObject *Sender);
	void __fastcall OpenCurrFolderClick(TObject *Sender);
	void __fastcall ButtonKonwertujClick(TObject *Sender);
	void __fastcall EditLocalizationKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonRejestratorClick(TObject *Sender);
	void __fastcall CheckBoxGodModeClick(TObject *Sender);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall ComboBoxQualityChange(TObject *Sender);
	void __fastcall EN1Click(TObject *Sender);
	void __fastcall PL1Click(TObject *Sender);
	void __fastcall SpinEdit1Change(TObject *Sender);
	void __fastcall CheckBoxSaveClipboardClick(TObject *Sender);
	void __fastcall EditConsoleBGColorChange(TObject *Sender);
	void __fastcall EditConsoleTextSizeChange(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall EditFileMangerChange(TObject *Sender);
	void __fastcall ButtonRandomClick(TObject *Sender);
	void __fastcall ButtonRandomMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonLinFuncClick(TObject *Sender);
	void __fastcall ButtonP2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonP1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonP2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ButtonP2MouseEnter(TObject *Sender);
	void __fastcall ButtonP2MouseLeave(TObject *Sender);
	void __fastcall ButtonP2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonP1MouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y, int HitTest, TMouseActivate &MouseActivate);
	void __fastcall ButtonP1MouseEnter(TObject *Sender);
	void __fastcall ButtonP1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ButtonP1MouseLeave(TObject *Sender);
	void __fastcall DoShowHint(UnicodeString &HintStr, bool &CanShow, THintInfo &HintInfo);
	void __fastcall Button10Click(TObject *Sender);




















private:

 #define FI 0.6180339887498948482

	bool __fastcall Kopiuj(String FileNameA_Sourse, String Path, String newFileNameB);
	int W_ID;
	unsigned W_PD;
	bool showwaring;

	TSearchPref *Pref_ptr;
	void sortListVby_size ( bool top_bigger );
	void calcSizeOfList (  );

	TWndMethod Df;
	TWndMethod KeyApp;

//	void __fastcall GetKeyApp(TMessage &Msg);
	void __fastcall WmCopyData(TWMCopyData& Message);
	void SearchMultiThread();
	void ItemAble(bool enable);

	void ExecuteFiltrSearch(String filtr);

	bool CheckFileSystem( TButtonedEdit* edit );
	void IsDir_noFile_Path( TButtonedEdit* edit );

	String OldPathFile;
	TTimer *tim;
	TGdiplus *GdiPlus;
	String MPC_HC_Player_path;
	RECT rect;
	int Xmax, Ymax;                     // max (aktualna) rozdzielczoœæ ekranów

	TWPoint *P1;
	TWPoint *P2;


	THsearch *thWatek[ 9 ]; //= { NULL };  	//  wskaŸnik na w¹tki i jego metody


//	void __fastcall SendMail(char * Adress, char * Title, char * Note, String FileName);

//	String Path_to_save, FileName;

//----------------------------------------------------------------------------
public:
		bool filecolumn();
		void QuestionForADS();
		void ResetIconList( unsigned size_0 = 0);
//		gd::TGdiplus *gd;
	void closeTH( Number );
		TRegistry *Reg;

	TImageList *IconList;
	TImageList *IconMain32;
	TNotifyEvent  TFibonacciR::IconMain32Change( TObject *Sender );

	void StatusInfo(AnsiString TextInfo, unsigned PanelIndex_0 = 0);            // wywœwietla Info na statusbarze

	void Loading_image_success( bool yes );
//	String filter;           // jakie rozszrzena bêd¹ uwzgledniane "" (puste) dla wszystkich plików

	double w_default;   	 // wartoœæ zwracana w przypadku niepowodzenia (np.litera w liczbie)

	bool close;            	 // minimalizuje aplikacjê gdy 1 zamiast zamkn¹æ

	void CloseScanPrefWnd(); // zamyka okno preferencji dynamicznie alokowane

	String FirmName;         // nazwa firmy np. w rejestrze

	bool reg_save_data;    	 // zezwala na zapis ustawieñ przez program

	vector<TWPoint*> point_array; // tablica okienek ze wskaŸnikami [0] to celownik

	void set_main_point_pos( TWPoint *, TForm * ); // ustawia now¹ pozycjê Punktu ( P1 lub P2 )

	__fastcall TMyAss(TComponent* Owner);

//    HOOKPROC ConnectHook(int iCode, WPARAM wParam, LPARAM lParam);


BEGIN_MESSAGE_MAP
MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, WmCopyData)
END_MESSAGE_MAP(TForm)


	void Porogresbar();

	void CloseSet(bool No = 0) {close = No;};                                   // przy trybie cichym

	AnsiString BreakQuestion();                                                 // przy limicie wyszukiwanych plików

	void TryShowForm2();

	__fastcall TFibonacciR(TComponent* Owner);
};

	static unsigned short curpos;

	static WIN32_FIND_DATA File_Data;

	static TIntFI o1;
//    Doubcl *ss;


//---------------------------------------------------------------------------
extern PACKAGE TFibonacciR *FibonacciR;
//---------------------------------------------------------------------------
#endif
