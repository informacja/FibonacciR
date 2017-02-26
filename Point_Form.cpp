//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Point_Form.h"
#include "Wa�ne.h"
#include "Func.h"
#include <cassert>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWPoint *WPoint;
//---------------------------------------------------------------------------
__fastcall TWPoint::TWPoint(TComponent* Owner)
	: TForm(Owner)
//	mFormMain(dynamic_cast<TFibonacciR *>(Owner))
{
	  mFormMain = (TFibonacciR*) Owner;
	assert(mFormMain!=0); //Assume cast succeeded

	move = false;
}
//---------------------------------------------------------------------------
void __fastcall TWPoint::FormDblClick(TObject *Sender)
{
	CloseModal();
}
//---------------------------------------------------------------------------
void __fastcall TWPoint::Image1DblClick(TObject *Sender)
{
   //	S::Save(1);
   //	Set_me_null_BEFORE_KILL(this->Handle);

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
//	static int a;

    POINT p;
	if (GetCursorPos(&p))
	{
		if (move)
		//if ( X>1000 )
		{
			LogSave(p.x);
			Move_WND( this->Handle, p.x, p.y );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	  move = true;
	  pozX = X;
	  pozY = Y;
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  move = false;
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::FormCreate(TObject *Sender)
{
	DoubleBuffered = true;

	if (GetWindowRect( this->Handle, &Rect) )
	{
		pozX = Rect.left;
		pozY = Rect.top;
		LogSave(pozY);
	}
	else ShowError( "B��d pobrania rozmiau okna in TWPoint::FormCreate", NULL, Sender );
}
//---------------------------------------------------------------------------


void __fastcall TWPoint::FormMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
	PixelsPerInch *= 2;
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::FormMouseLeave(TObject *Sender)
{
 	PixelsPerInch = 96;
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::FormMouseEnter(TObject *Sender)
{
    PixelsPerInch *= 2;
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::FormClick(TObject *Sender)
{
	PixelsPerInch = 50;
	this->Update();
	this->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TWPoint::FormPaint(TObject *Sender)
{
	if (GetWindowRect( this->Handle, &Rect) )
	{
		pozX = Rect.left;
		pozY = Rect.top;
		LogSave(pozY);
	}
	else ShowError( "B��d pobrania rozmiau okna in TWPoint::FormPaint", NULL, Sender );
}
//---------------------------------------------------------------------------
