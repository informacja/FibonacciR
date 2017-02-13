//---------------------------------------------------------------------------

#ifndef WprogramieH
#define WprogramieH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TImage *Image1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Infooprogramie1;
	TMenuItem *FullInfo1;
	TMenuItem *N1;
	TGroupBox *GroupBox1;
	TLabel *Label6;
	TLabel *Label5;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Lopis1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TMenuItem *arciki1;
	TMenuItem *N2;
	TLabel *Labelarcik;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TLabel *Label18;
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Infooprogramie1Click(TObject *Sender);
	void __fastcall FullInfo1Click(TObject *Sender);
	void __fastcall arciki1Click(TObject *Sender);
	void __fastcall LabelarcikClick(TObject *Sender);
//	void Pobierz();
private:

		 void infomemory();

		 void infobios();

		 void infoproc();

//		 void infomemory();
public:	 	// User declarations
unsigned short KOD;
//const char k;
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
