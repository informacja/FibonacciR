//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Picbutton.h"
#pragma resource "Picbutton.res"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TPicbutton *)
{
        new TPicbutton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TPicbutton::TPicbutton(TComponent* Owner)
        : TPaintBox(Owner)
{
 ATransp = true;
 this->Parent = dynamic_cast<TWinControl*>(Owner);
 APicMove = new TPicture;
 APicUp = new TPicture;
 APicDown = new TPicture;
 AGlyph = new TPicture;
 Kludka = new Graphics::TBitmap;

 APicMove->Bitmap->LoadFromResourceName((int)HInstance, "1_MOVE");
 APicUp->Bitmap->LoadFromResourceName((int)HInstance, "1_UP");
 APicDown->Bitmap->LoadFromResourceName((int)HInstance, "1_DOWN");
 AGlyph->Bitmap->LoadFromResourceName((int)HInstance, "GLYPH");
 Kludka->LoadFromResourceName((int)HInstance, "KLUDKA");

 Kludka->Transparent = true;
 Kludka->TransparentColor = clLime;

 AGlyph->Bitmap->Transparent = true;
 AGlyph->Bitmap->TransparentColor = clLime;

 OldPicBtn = this->WindowProc;
 this->WindowProc = NewPicBtn;

 dp = false;
 updp = false;

 Width = 23;
 Height = 23;
 Color = clSilver;
 ATranspColor = clLime;
 AGlyphATC = true;
 ABtype = btOrange;
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAToggle(bool togle)
{
 AToggle = togle;
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAStatus(bool aStat)
{
  AStatus = aStat;
  Paint();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetASound(bool aSound)
{
  ASound = aSound;
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::NewPicBtn(TMessage &Msg)
{
    if(Msg.Msg == CM_MOUSEENTER)
	{
	 if(Enabled)
	 {
	  updp = true;
	  DrawPicButtonMove();
     }
	 else
	 {
	  DrawPicButtonUp();
	  DrawText();
	  DrawKludka();
     }
    }
    else if (Msg.Msg == CM_MOUSELEAVE)
	{
	 if(Enabled)
	 {
	  dp = true;
	  updp = false;
	  if(AToggle == false)
	   DrawPicButtonUp();
	  else
	   if(AStatus == true)
		DrawPicButtonDown();
	   else
		DrawPicButtonUp();
	 }
	 else
	 {
	  DrawPicButtonUp();
	  DrawText();
	  DrawKludka();
     }
    }
    OldPicBtn(Msg);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetACaption(String c)
{
 ACaption = c;
 Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAPicDown(TPicture *pic)
{
  APicDown->Assign(pic);
  ButtonType = btPicture;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAPicUp(TPicture *pic)
{
  APicUp->Assign(pic);
  ButtonType = btPicture;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAPicMove(TPicture *pic)
{
  APicMove->Assign(pic);
  ButtonType = btPicture;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAGlyph(TPicture *glyph)
{
 AGlyph->Assign(glyph);
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetAGlyphATC(bool atc)
{
 AGlyphATC = atc;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetABtype(TPicType FType)
{
 ABtype = FType;
 switch(ABtype)
 {
   case btOrange:
   {
	APicMove->Bitmap->LoadFromResourceName((int)HInstance, "1_MOVE");
	APicUp->Bitmap->LoadFromResourceName((int)HInstance, "1_UP");
	APicDown->Bitmap->LoadFromResourceName((int)HInstance, "1_DOWN");
	break;
   }
   case btSilver:
   {
	APicMove->Bitmap->LoadFromResourceName((int)HInstance, "2_MOVE");
	APicUp->Bitmap->LoadFromResourceName((int)HInstance, "2_UP");
	APicDown->Bitmap->LoadFromResourceName((int)HInstance, "2_DOWN");
	break;
   }
   case btBlue:
   {
	APicMove->Bitmap->LoadFromResourceName((int)HInstance, "3_MOVE");
	APicUp->Bitmap->LoadFromResourceName((int)HInstance, "3_UP");
	APicDown->Bitmap->LoadFromResourceName((int)HInstance, "3_DOWN");
	break;
   }
   case btBlack:
   {
	APicMove->Bitmap->LoadFromResourceName((int)HInstance, "4_MOVE");
	APicUp->Bitmap->LoadFromResourceName((int)HInstance, "4_UP");
	APicDown->Bitmap->LoadFromResourceName((int)HInstance, "4_DOWN");
	break;
   }
 }
 if(ABtype != btPicture)
 {
  ATransp = true;
  ATranspColor = clLime;
 }
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetATranspColor(TColor tc)
{
 ATranspColor = tc;
 Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SetATransp(bool at)
{
 ATransp = at;
 Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawText(void)
{
 Canvas->Brush->Style = bsClear;
 Canvas->Font->Assign(Font);
 __int16 TxtHeight = (Height - Canvas->TextHeight(ACaption)) / 2;
 __int16 TxtWidth  = (Width  - Canvas->TextWidth(ACaption)) / 2;
 Canvas->TextOut(TxtWidth, TxtHeight, ACaption);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawGlyph(__int8 c)
{
 if(Caption.IsEmpty() && Glyph != NULL && Enabled)
 {
  if(ATransp)
  {
   AGlyph->Bitmap->Transparent = ATransp;
   if(AGlyphATC)
	AGlyph->Bitmap->TransparentColor = Glyph->Bitmap->Canvas->Pixels[0][0];
   else
    AGlyph->Bitmap->TransparentColor = ATranspColor;
  }
  else
   AGlyph->Bitmap->Transparent = false;

  __int8 w = (Width  - AGlyph->Bitmap->Width) / 2;
  __int8 h = (Height - AGlyph->Bitmap->Height) / 2;
  Canvas->Draw(w + c, h + c, AGlyph->Bitmap);
 }
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawKludka(void)
{
  __int8 w = (Width  - Kludka->Width) / 2;
  __int8 h = (Height - Kludka->Height) / 2;
  Canvas->Draw(w, h, Kludka);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawPicButtonMove(void)
{
 if(ButtonType == btPicture)
 {
  if(ATransp)
  {
   APicMove->Bitmap->Transparent      = ATransp;
   APicMove->Bitmap->TransparentColor = ATranspColor;
  }
  else
   APicMove->Bitmap->Transparent      = false;
 }
 else
 {
  APicMove->Bitmap->Transparent      = true;
  APicMove->Bitmap->TransparentColor = clLime;
 }

 Canvas->StretchDraw(Rect(0, 0, Width, Height), APicMove->Bitmap);
 DrawText();
 DrawGlyph(0);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawPicButtonDown(void)
{
 if(ButtonType == btPicture)
 {
  if(ATransp)
  {
   APicDown->Bitmap->Transparent      = ATransp;
   APicDown->Bitmap->TransparentColor = ATranspColor;
  }
  else
   APicDown->Bitmap->Transparent      = false;
 }
 else
 {
  APicDown->Bitmap->Transparent      = true;
  APicDown->Bitmap->TransparentColor = clLime;
 }

 Canvas->StretchDraw(Rect(0, 0, Width, Height), APicDown->Bitmap);

 DrawText();
 DrawGlyph(1);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::DrawPicButtonUp(void)
{
 if(ButtonType == btPicture)
 {
  if(ATransp)
  {
   APicUp->Bitmap->Transparent      = ATransp;
   APicUp->Bitmap->TransparentColor = ATranspColor;
  }
  else
   APicUp->Bitmap->Transparent      = false;
 }
 else
 {
  APicUp->Bitmap->Transparent      = true;
  APicUp->Bitmap->TransparentColor = clLime;
 }

 Canvas->StretchDraw(Rect(0, 0, Width, Height), APicUp->Bitmap);
 DrawText();
 DrawGlyph(0);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::SoundClick(void)
{
 PlaySound("CLICK", HInstance, SND_ASYNC | SND_RESOURCE);
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::Paint(void)
{
 if(Enabled)
 {
  if(AToggle == false)
  {
   if(!updp)
	DrawPicButtonUp();
   else
	DrawPicButtonMove();
  }
  else
   if(AStatus == true)
   {
	DrawPicButtonDown();
   }
   else
   {
	DrawPicButtonUp();
   }
  DrawText();
 }
 else
 {
  DrawPicButtonUp();
  DrawText();
  DrawKludka();
 }
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::MouseDown(TMouseButton Button,
        TShiftState Shift, int X, int Y)
{
 dp = false;
 if(!AToggle)                   
  DrawPicButtonDown();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::MouseUp(TMouseButton Button,
        TShiftState Shift, int X, int Y)
{
 if(!dp && !AToggle)
  DrawPicButtonMove();
}
//---------------------------------------------------------------------------
void __fastcall TPicbutton::Click(void)
{
 if(AToggle == true)
 {
  if(Status == true)
  {
   Status = false;
   DrawPicButtonUp();
  }
  else
  {
   Status = true;
   DrawPicButtonDown();
  }
 }
 if(ASound) SoundClick();
 TPaintBox::Click();
}
//---------------------------------------------------------------------------
__fastcall TPicbutton::~TPicbutton(void)
{
 delete APicMove, APicDown, APicUp, AGlyph, Kludka;
}
//---------------------------------------------------------------------------
namespace Picbutton
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TPicbutton)};
                 RegisterComponents("Cyfbar", classes, 0);
        }
}
//---------------------------------------------------------------------------

 