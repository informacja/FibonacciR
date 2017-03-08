//---------------------------------------------------------------------------

#ifndef Point_FormH
#define Point_FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>

class TFibonacciR;
class TFormMain;        // todel


//---------------------------------------------------------------------------
class TWPoint : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	void __fastcall FormDblClick(TObject *Sender);
	void __fastcall Image1DblClick(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);


private:	// User declarations
	volatile bool move;
	RECT Rect;

	TFibonacciR* mFormMain;
	//TForm * const mFormMain;// todel

public:		// User declarations
	volatile 	int pozX, pozY;
	const unsigned ID;
	__fastcall TWPoint(TComponent* Owner);
	__fastcall TWPoint(TComponent* Owner, unsigned ID_0 );
	__fastcall TWPoint(TComponent* Owner, unsigned ID_0, int x, int y, bool CanMove = false );
};
//---------------------------------------------------------------------------

//struct pos
//{
//	int x ;
//	int y ;
//
//	TWPoint *handle ;
//	 pos():x(0),y(0),handle(NULL) { }
//};

enum ID
{
	DEFAULT = 0,
	ON_LINE,
	NORMAL_TO_LINE,
	SECTION_SPACE,
	REST
};

extern PACKAGE TWPoint *WPoint;
//---------------------------------------------------------------------------
#endif
