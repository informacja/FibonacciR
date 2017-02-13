//---------------------------------------------------------------------------

#ifndef SplashH
#define SplashH
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
class TForm4 : public TForm
{
public:
void Gleam(unsigned sleep);
__published:	// IDE-managed Components
	TAnimate *Animate1;
	TImage *Image1;
	void __fastcall FormClick(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations

	__fastcall TForm4(TComponent* Owner);
};

	TNotifyEvent __fastcall timerTimer();


	int __fastcall ShowSplash(unsigned Milisecond = 500);

//	unsigned licznik;

//    int W_ID;
//	unsigned int W_PD;


//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
