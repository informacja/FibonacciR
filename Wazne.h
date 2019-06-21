//---------------------------------------------------------------------------

#ifndef Wa¿neH
#define Wa¿neH
//---------------------------------------------------------------------------

//#include "cspin.h"
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
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "cgauges.h"
#include "trayicon.h"
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ExtDlgs.hpp>

  #define W_OK    2       /* Test for write permission.  */

//---------------------------------------------------------------------------

	 void __fastcall increment(TCSpinButton* name);
	 void __fastcall decrement(TCSpinButton* name);
	 void __fastcall KeyD(WORD &Key, TCSpinButton* Button);
	 double __fastcall Round ( double x );
	 double Cutting ( double x );

	 
	 bool CloseProcess(DWORD ID);

	 void DuplicateAppCheckParam(wchar_t* Mutex_name, wchar_t* cmdLine);
	 void EarlierIsMinimized();
	 void BingToFront(unsigned how_many_times, unsigned interval);

	 void MakePrintScreen();

	 bool Dir_File_exist( TEdit* edit );

	 String GetPath_with_access( String * Untrusted_Path, int permission_W_OK = W_OK, String DefaultPath_C = "C:\\" );

	 void Set_me_null_BEFORE_KILL( HWND h );

	 bool Close_Points_WND();

	 void __fastcall Move_WND( HWND h, int X = -1, int Y = -400);

     inline void DeleteOrRelease(TCustomForm *f);

//	 void w1(TEdit* do_obliczeñ);  //dla double(Tryb Zaawansowany)
//	 void w2(TEdit* do_obliczeñ);
//	 void w3(TEdit* do_obliczeñ);
//	 void w4(TEdit* do_obliczeñ);
//	 void w5(TEdit* do_obliczeñ);
//	 void w6(TEdit* do_obliczeñ);

//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
#endif
