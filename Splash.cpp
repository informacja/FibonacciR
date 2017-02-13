//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Splash.h"

#include <iomanip.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{

}

TNotifyEvent __fastcall timerTimer(int a)
{
// licznik += 100;
//if (a = licznik)	Form4->~TForm4();
}

void Gleam(unsigned sleep) {

//	for (int i = 0; i < 255; i++) { // 1/6
//		Sleep((int)sleep / 6 / 255);
//		Form4->AlphaBlendValue = i;
//	}
//
//	Sleep(sleep / 3); // 1/3
//
//	for (int i = 0; i < sleep / 2; i++) { // 1/2
//		Sleep
//		( (int)sleep / 2 / 255);
//		Form4->AlphaBlendValue = i;
//		}


for (int i = 0; i < 255; i++) {
	Sleep(1);
	Application->ProcessMessages();
	Form4->AlphaBlendValue = i;
//                    Form4->Image1->Perform()
	Form4->Update();
//	Image1->Perform()
//	Application->ProcessMessages();
//	ShowMessage(Form4->AlphaBlend)
}



}


//---------------------------------------------------------------------------
int __fastcall ShowSplash(unsigned milis){

	unique_ptr<TForm4> SplashScreen(new TForm4(Application));
//	unique_ptr<TTimer> timer(new TTimer(0));
//	licznik = 0;
//	 (*timer).Interval = 100;
//	(*timer).Enabled = true;

   SplashScreen->Show(); //<--
   SplashScreen->Update(); //<--
   Application->CreateForm(__classid(TForm4), &Form4);

	 Gleam(milis); //<--

	 Form4->~TForm4();
//   (*timer).OnTimer = timerTimer(milis);
//   Form4->Close();
////
////   ShowMessage("Po");
//	ExitThread(GetExitCodeThread(ShowSplash, 0));

//	GetExitCodeThread(ShowSplash, NULL);
//	ExitThread(  W_PD );
}


//---------------------------------------------------------------------------
void __fastcall TForm4::FormClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image1Click(TObject *Sender)
{
AlphaBlendValue = 50;
}
//---------------------------------------------------------------------------

