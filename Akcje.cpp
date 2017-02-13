#pragma hdrstop

#include "Unit1.h"

// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Action1Execute(TObject *Sender) {
	FibonacciR->Close();
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Zamknij1Click(TObject *Sender) {

	Action1Execute(this);   // FibonacciR->Close();
}
// ---------------------------------------------------------------------------
void __fastcall TFibonacciR::Zamknij2Click(TObject *Sender) {

	Action1Execute(this);   // FibonacciR->Close();
}
// ---------------------------------------------------------------------------
 String ScreenPNG(char Quality, bool clip) {



	unique_ptr<TPngImage> PNG(new TPngImage());
	unique_ptr<TImage>  Image1(new TImage(NULL));
	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);

	(*PulpitCanvas).Handle = GetDC(0);

	Image1->Height = Screen->Height;
	Image1->Width = Screen->Width;
	Image1->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height),
		PulpitCanvas.get(), Rect(0, 0, Screen->Width, Screen->Height));

	ReleaseDC(0, (*PulpitCanvas).Handle);

	PNG->Assign(Image1->Picture->Bitmap);

	if (0 <= Quality <10 ) PNG->CompressionLevel = Quality; else throw "Niepoprawna wartoœæ Quality";

	if (clip) {                                                                 // schowek

		PNG->Draw(	Image1->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		unique_ptr<TClipboard>pCB(new TClipboard);
		pCB->Assign(Image1->Picture);

		return ("Screen skopiowany do schowka (-PNG) " + CurrToStr(100 - PNG->CompressionLevel *10) + "%");
	}

	PNG->SaveToFile( S::NAMEscreen + ".png" );                     // plik

	 return "Screen " + S::NAMEscreen + ".png zapisany "+ CurrToStr(100 - PNG->CompressionLevel *10) + "%";
 }
// ---------------------------------------------------------------------------

 String ScreenJPG(char Quality, bool clip) {

	unique_ptr<TJPEGImage> Jpeg(new TJPEGImage());
	unique_ptr<TImage>  Image1(new TImage(NULL));
	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);

	(*PulpitCanvas).Handle = GetDC(0);

	Image1->Height = Screen->Height;
	Image1->Width = Screen->Width;
	Image1->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height), PulpitCanvas.get(),  Rect(0, 0, Screen->Width, Screen->Height));

	ReleaseDC(0, (*PulpitCanvas).Handle);

	Jpeg->Assign(Image1->Picture->Bitmap);

	  if (Quality) {

		 if ( 0 > Quality || Quality > 100) throw "Niepoprawna wartoœæ Quality";;

		Jpeg->CompressionQuality = Quality;
		Jpeg->Compress();

	  }
		if (clip) {                                                             // schowek

		unique_ptr<TClipboard>pCB(new TClipboard);

		Image1->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height),
			 Jpeg->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		pCB->Assign(Image1->Picture);

		return ("Screen skopiowany do schowka (JPEG) " + CurrToStr(Jpeg->CompressionQuality ) + "%");
		}

	  Jpeg->SaveToFile( S::NAMEscreen + ".jpg" );


	 return "Screen " + S::NAMEscreen + ".jpg zapisany " + CurrToStr(Jpeg->CompressionQuality ) + "%";
 }
// ---------------------------------------------------------------------------

 String ScreenBMP(char Quality, bool clip, String where) {

	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);
	unique_ptr<Graphics::TBitmap >  Bmp(new Graphics::TBitmap );

	(*PulpitCanvas).Handle = GetDC(0);
	Bmp->Width = Screen->Width;
	Bmp->Height = Screen->Height;
	Bmp->Canvas->CopyRect(Rect(0, 0, Bmp->Width, Bmp->Height), PulpitCanvas.get(),
		Rect(0, 0, Bmp->Width, Bmp->Height));
	ReleaseDC(0, (*PulpitCanvas).Handle);

	if (clip) {

		unique_ptr<TClipboard>pCB(new TClipboard);
		unsigned short MyFormat;
		unsigned int AData;
		HPALETTE APalette;

		Bmp->SaveToClipboardFormat(MyFormat, AData, APalette);
		pCB->SetAsHandle(MyFormat, AData);

		return "Screen skopiowany do schowka (BMP) ";
	}


	if (where != 0 || "") {

		if (where.LastChar() != "\\") where += "\\";

		Bmp->SaveToFile( where + S::NAMEscreen + ".bmp");
	}
	else 	Bmp->SaveToFile( S::NAMEscreen + ".bmp");

		return "Screen " + S::NAMEscreen + ".bmp" + " zapisany";

 }
// ---------------------------------------------------------------------------
unsigned GetQualityJPEG() {

	 unique_ptr<AnsiString>Qua(new AnsiString(Form2->ComboBoxQuality->Text));

	 try {

		 unique_ptr<unsigned char>i(new unsigned char(100));    				// przypadek gdy pierwszy znak jest cyfr¹

		 *i = (*Qua).SubString(1, 1).ToInt();

		 return 100 - (*i) * 10;

	 }
	 catch (...) {

		 while (TryToInt((*Qua).SubString(1, 1)) == ' ') {                      // jeœli znajdzie cyfrê czyli ró¿ne od ' ' (spacja)

			 (*Qua).Delete(1, 1);

			 if ((*Qua) == "")	 return 100;
		 }
		 try {
			 return 100 - (*Qua).SubString(1, 1).ToInt() *10;

		 }
		 catch (...) {
			 return 100;
		 }
	 }
 }
// ---------------------------------------------------------------------------
unsigned GetQualityPNG() {

   unique_ptr<AnsiString>Qua(new AnsiString(Form2->ComboBoxQuality->Text));

   while (TryToInt((*Qua).SubString(1, 1)) == ' ') {                      // jeœli znajdzie cyfrê czyli ró¿ne od ' ' (spacja)

			 (*Qua).Delete(1, 1);

			 if ((*Qua) == "")	 return 0;
		 }
		 try {
			 return (*Qua).SubString(1, 1).ToInt() ;

		 }
		 catch (...) {
			 return 0;                                                          // Lossless
		 }
 }
// ---------------------------------------------------------------------------
int TryToInt(AnsiString a) {

	try {

	return a.SubString(1,1).ToInt();  nothrow;                                  // try to INT

	} catch (...) {

		return ' ';                                                             // niepowodzenie zwraca spacje

	}
}
////////////////////////////////////////////////////////////////////////////////
//  ProgresBar  // ProgresBar  // ProgresBar  // ProgresBar  // ProgresBar  ////
////////////////////////////////////////////////////////////////////////////////

void ProgressBarPos(unsigned short pos){

	FibonacciR->ProgressBar1->Position = pos;
}

void ProgressBarMax() {

	FibonacciR->ProgressBar1->Position = 100;
}

void ProgressBarMin(){

	FibonacciR->ProgressBar1->Position = 0;
}

void ProgressBarStyle(bool ver, bool mar ) {

	FibonacciR->ProgressBar1->Orientation = (ver) ? pbVertical : pbHorizontal;

	FibonacciR->ProgressBar1->Style = (mar) ? pbstMarquee : pbstNormal;
}

void func() {ProgressBarMin();}

void ProgressAnimation() {



	unique_ptr<TTimer> t(new TTimer(0));

	TNotifyEvent a;
//	a = reintepreter_cast <TNotifyEvent> (func());

	ProgressBarMin();
	ProgressBarStyle(1,1);
	(*t).Interval = 1000;
	(*t).Enabled = true;
	(*t).OnTimer =  a;
//	 (*t).OnTimer {
//	 ProgressBarMax;
//	 }

}

// (*t).OnTimer();
void __fastcall tTimer(TObject *Sender)
{
ProgressBarMax();
}

#pragma package(smart_init)
