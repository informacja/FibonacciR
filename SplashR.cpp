//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SplashR.h"

#include <iomanip.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplash *Splash;
//---------------------------------------------------------------------------
__fastcall TSplash::TSplash(TComponent* Owner)
	: TForm(Owner)
{
end = false;
//	timer = new TTimer(0);
}
//---------------------------------------------------------------------------
TNotifyEvent __fastcall timerTimer(int a)
{
// licznik += 100;
//if (a = licznik)	Splash->~TForm4();
}
//---------------------------------------------------------------------------
void TSplash::Gleam(unsigned sleep) {

	for (int i = 0; i < 255; i++) {

		Sleep(sleep / 255);

		Application->ProcessMessages();                                         // niezbêdne

		AlphaBlendValue = i;

		if ( end ) break;                                                       // jeœli true(OnClick) koñczy wyœwietlanie

	}
}


//extern FibonacciR;
//---------------------------------------------------------------------------
int __fastcall ShowSplash(unsigned milis){

//#include "Nieznacz¹ce_polecenia.h"
//  	  Splash = new TSplash(FibonacciR);
	/* OR */
//	  Splash = new TSplash(0);
	/* OR */
	unique_ptr<TSplash> Splash(new TSplash(0));


	  Splash->Visible = true;
	  Splash->Image->Visible = true;
	  Splash->Gleam(milis); //<--

	  Splash->Close();

//	  Splash->Free();
//	  delete Splash;
}
//---------------------------------------------------------------------------
void __fastcall TSplash::FormClick(TObject *Sender)
{
//Close();
}
//---------------------------------------------------------------------------
void __fastcall TSplash::ImageClick(TObject *Sender)
{
	end = true;
}
//---------------------------------------------------------------------------

void __fastcall TSplash::FormDestroy(TObject *Sender)
{
//	delete timer;
}
//---------------------------------------------------------------------------

void __fastcall TSplash::FormClose(TObject *Sender, TCloseAction &Action)
{
Action = caFree;
//Splash->CloseModal();
for (int i = 255; i > 0; i-=4) {
Sleep(1);
	AlphaBlendValue = i;
	Application->ProcessMessages();
}

}
//---------------------------------------------------------------------------

