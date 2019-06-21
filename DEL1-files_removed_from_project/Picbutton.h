//---------------------------------------------------------------------------

#ifndef PicbuttonH
#define PicbuttonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <mmsystem.h>
//---------------------------------------------------------------------------
enum TPicType {btOrange, btSilver, btBlue, btBlack, btPicture};
//enum TPicSound {psNone, psResource, psFile, psAuto};
class PACKAGE TPicbutton : public TPaintBox
{
private:
          TPicture *APicMove;
          void __fastcall SetAPicMove(TPicture *pic);
          TPicture *APicDown;
          void __fastcall SetAPicDown(TPicture *pic);
          TPicture *APicUp;
		  void __fastcall SetAPicUp(TPicture *pic);
		  TPicture *AGlyph;
		  void __fastcall SetAGlyph(TPicture *glyph);

		  TPicType ABtype;
		  void __fastcall SetABtype(TPicType FType);

          TColor ATranspColor;
          void __fastcall SetATranspColor(TColor tc);
          bool ATransp;
		  void __fastcall SetATransp(bool at);

		  bool AGlyphATC;
		  void __fastcall SetAGlyphATC(bool atc);

          AnsiString ACaption;
          void __fastcall SetACaption(String c);

          bool AToggle;
          void __fastcall SetAToggle(bool togle);
		  bool AStatus;
		  void __fastcall SetAStatus(bool aStat);

		  bool ASound;
		  void __fastcall SetASound(bool aSound);

          virtual void __fastcall Paint(void);
          DYNAMIC void __fastcall Click(void);
          DYNAMIC void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
          DYNAMIC void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
         // DYNAMIC void __fastcall MouseMove(TShiftState Shift, int X, int Y);

          TWndMethod OldPicBtn;
          void __fastcall NewPicBtn(TMessage &Msg);

		  void __fastcall DrawText(void);
		  void __fastcall DrawGlyph(__int8 c);
		  void __fastcall DrawKludka(void);
		  void __fastcall SoundClick(void);

		  bool dp, updp;
		  TColor tmpColor;
		  Graphics::TBitmap *Kludka;

protected:

public:
        __fastcall TPicbutton(TComponent* Owner);
        __fastcall ~TPicbutton(void);
        void __fastcall DrawPicButtonMove(void);
        void __fastcall DrawPicButtonDown(void);
		void __fastcall DrawPicButtonUp(void);

__published:
        __property TPicture *PicMove = {read = APicMove, write = SetAPicMove};
        __property TPicture *PicDown = {read = APicDown, write = SetAPicDown};
        __property TPicture *PicUp   = {read = APicUp, write = SetAPicUp};
        __property TColor TransparentColorValue = {read = ATranspColor, write = SetATranspColor};
        __property bool TransparentColor = {read = ATransp, write = SetATransp, default = 1};
        __property AnsiString Caption = {read = ACaption, write = SetACaption};
        __property bool Toggle = {read = AToggle, write = SetAToggle};
		__property bool Status = {read = AStatus, write = SetAStatus};
		__property TPicture *Glyph = {read = AGlyph, write = SetAGlyph};
		__property TPicType ButtonType = {read = ABtype, write = SetABtype};
		__property bool GlyphAutoTransColor = {read = AGlyphATC, write = SetAGlyphATC};
		__property bool Sound = {read = ASound, write = SetASound};

};
//---------------------------------------------------------------------------
#endif
