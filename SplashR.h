//---------------------------------------------------------------------------

#ifndef SplashRH
#define SplashRH
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <memory>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TSplash : public TForm
{
public:
	TTimer *timer;

__published:	// IDE-managed Components
	TImage *Image;
	void __fastcall FormClick(TObject *Sender);
	void __fastcall ImageClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
bool end;
public:		// User declarations
void Gleam(unsigned sleep);

	__fastcall TSplash(TComponent* Owner);
};

	TNotifyEvent __fastcall timerTimer();


	int __fastcall ShowSplash(unsigned Milisecond = 500);

//	unsigned licznik;

//    int W_ID;
//	unsigned int W_PD;


//---------------------------------------------------------------------------
extern PACKAGE TSplash *Splash;
//---------------------------------------------------------------------------
#endif
