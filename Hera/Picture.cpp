//---------------------------------------------------------------------------

#pragma hdrstop

#include "Picture.h"
#include "Func.h"
//---------------------------------------------------------------------------

// konstruktory
 Picture::Picture() {

	image = new TImage(0);
	Clipboard = false;
	FileName = "FiboScreen";
	MinQuality = 30;
//	imgd = new TDBImage;

 } // unique new

 Picture::Picture(TImage *image) {

	image = new TImage(image);
	Clipboard = false;
	FileName = "FiboScreen";
	MinQuality = 30;
 }

// destruktor
 Picture::~Picture() {
// image->~TImage();
//	image->FreeOnRelease();
//delete image;               // not work
 }

//---------------------------------------------------------------------------

 String Picture::ScreenBMP(String where, String name) {

	ValidateImputs( &name);

	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);
	unique_ptr<Graphics::TBitmap >  Bmp(new Graphics::TBitmap );

	(*PulpitCanvas).Handle = GetDC(0);
	Bmp->Width = Screen->Width;
	Bmp->Height = Screen->Height;
	Bmp->Canvas->CopyRect(Rect(0, 0, Bmp->Width, Bmp->Height), PulpitCanvas.get(),
		Rect(0, 0, Bmp->Width, Bmp->Height));
	ReleaseDC(0, (*PulpitCanvas).Handle);

	if (Clipboard) {

		unique_ptr<TClipboard>pCB(new TClipboard);
		unsigned short MyFormat;
		unsigned int AData;
		HPALETTE APalette;

		Bmp->SaveToClipboardFormat(MyFormat, AData, APalette);
		pCB->SetAsHandle(MyFormat, AData);

		return "Screen skopiowany do schowka (BMP)";
	}

	if (where != "" && 0 ) {                                                     		// jeœli œcie¿ka nie jest pusta

		if (where.LastChar() != "\\") where += "\\";                            // czy œcie¿ka koñczy siê backslashem

		Bmp->SaveToFile( where + name + ".bmp");                                // zapis przez œcie¿kê

		return "Screen " + where + name + ".bmp" + " zapisany";
	}
	else 	Bmp->SaveToFile( name + ".bmp"); 									// do aktualnego folderu

	return "Screen " + name + ".bmp" + " zapisany";

}

// ---------------------------------------------------------------------------

 String Picture::ScreenPNG(String where, char Quality, String name) {

	ValidateImputs( &name);

	unique_ptr<TPngImage> PNG(new TPngImage());
	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);

	(*PulpitCanvas).Handle = GetDC(0);

	image->Height = Screen->Height;
	image->Width = Screen->Width;
	image->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height),
				PulpitCanvas.get(), Rect(0, 0, Screen->Width, Screen->Height));

	ReleaseDC(0, (*PulpitCanvas).Handle);

	PNG->Assign(image->Picture->Bitmap);

	if ( Quality < MinQuality)  Quality  = MinQuality;

	PNG->CompressionLevel = GetQualityPNG(Quality);

	if (Clipboard) {                                                                 // schowek

		PNG->Draw(	image->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		unique_ptr<TClipboard>pCB(new TClipboard);
		pCB->Assign(image->Picture);

		return ("Screen skopiowany do schowka (PNG) " + CurrToStr(100 - PNG->CompressionLevel *10) + "%");
	}

	if (where != "" && 0 ) {

		if (where.LastChar() != "\\") where += "\\";

		PNG->SaveToFile( where + name + ".png");

		return "Screen " + where + name + ".png" + " zapisany";
	}
	else	PNG->SaveToFile( name + ".png" );

	return "Screen " + where + name + ".png zapisany "+ CurrToStr(100 - PNG->CompressionLevel *10) + "%";
 }

//---------------------------------------------------------------------------

 String Picture::ScreenJPG(String where, char Quality, String name) {

	ValidateImputs( &name);

	unique_ptr<TJPEGImage> Jpeg(new TJPEGImage());
	unique_ptr<TImage>  Image1(new TImage(NULL));
	unique_ptr<TCanvas>  PulpitCanvas(new TCanvas);

	(*PulpitCanvas).Handle = GetDC(0);

	Image1->Height = Screen->Height;
	Image1->Width = Screen->Width;
	Image1->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height), PulpitCanvas.get(),  Rect(0, 0, Screen->Width, Screen->Height));

	ReleaseDC(0, (*PulpitCanvas).Handle);

	Jpeg->Assign(Image1->Picture->Bitmap);

	  if ( GetQualityJPG((unsigned*)&Quality)) {

		if ( Quality < MinQuality)  Quality  = MinQuality;                      // wartoœæ minimalna

		Jpeg->CompressionQuality = Quality;
		Jpeg->Compress();

	  }
		if (Clipboard) {                                                        // schowek

		unique_ptr<TClipboard>pCB(new TClipboard);

		Image1->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height),
			 Jpeg->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		pCB->Assign(Image1->Picture);

		return ("Screen skopiowany do schowka (JPEG) " + CurrToStr(Jpeg->CompressionQuality ) + "%");
		}

	  Jpeg->SaveToFile( name + ".jpg" );

	 return "Screen " + name + ".jpg zapisany " + CurrToStr(Jpeg->CompressionQuality ) + "%";
 }

 //===========================================================================

 String Picture::ConvertToBMP(String path, String name, TImage *img ) {

	ValidateImputs(&name, img);

	unique_ptr<Graphics::TBitmap >  Bmp(new Graphics::TBitmap );

	Bmp->Width = img->Width;
	Bmp->Height = img->Height;
	Bmp->Canvas->CopyRect(Rect(0, 0, Bmp->Width, Bmp->Height), img->Canvas,
						  Rect(0, 0, Bmp->Width, Bmp->Height));

	if (Clipboard) {

		unique_ptr<TClipboard>pCB(new TClipboard);
		unsigned short MyFormat;
		unsigned int AData;
		HPALETTE APalette;

		Bmp->SaveToClipboardFormat(MyFormat, AData, APalette);
		pCB->SetAsHandle(MyFormat, AData);

		return "Obraz skopiowany do schowka (BMP)";
	}

	if (path != "") {                                                     		// jeœli œcie¿ka nie jest pusta

		if (path.LastChar() != "\\") path += "\\";                            	// czy œcie¿ka koñczy siê backslashem

		Bmp->SaveToFile( path + name + ".bmp");                                	// zapis przez œcie¿kê
	}
	else 	Bmp->SaveToFile( name + ".bmp"); 									// do aktualnego folderu

  return "Obraz " + path + name + ".bmp" + " zapisany";

 }

 //---------------------------------------------------------------------------

 String Picture::ConvertToPNG(String path, String name, char qual, TImage *img) {

	ValidateImputs(&name, img);
//								*img->Picture = *image->Picture;
	unique_ptr<TPngImage> PNG(new TPngImage());


//	image->Height = Screen->Height;
//	image->Width = Screen->Width;


//	unique_ptr<TStream> a(new TStream);
//image->Picture->Graphic->SaveToStream( a.get() );

//	PNG->LoadFromStream( a.get() );
//image->Picture->SaveToFile("C:\\test.bmp");
	PNG->Assign(img->Picture);

	if ( qual < MinQuality)  qual  = MinQuality;

	PNG->CompressionLevel = GetQualityPNG(qual);

	if (Clipboard) {                                                                 // schowek

		PNG->Draw(	image->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		unique_ptr<TClipboard>pCB(new TClipboard);
		pCB->Assign(img->Picture);

		return ("Screen skopiowany do schowka (PNG) " + CurrToStr(100 - PNG->CompressionLevel *10) + "%");
	}

	if (path != "" && 0) {                                                     		// jeœli œcie¿ka nie jest pusta&&

		if (path.LastChar() != "\\") path += "\\";                            	// czy œcie¿ka koñczy siê backslashem

		PNG->SaveToFile( path + name + ".png");                                	// zapis przez œcie¿kê

		return "Screen " + path + name + ".png zapisany "+ CurrToStr(100 - PNG->CompressionLevel *10) + "%";
	}
	else PNG->SaveToFile( name + ".png" );                     					// plik

    return "Screen " + name + ".png zapisany "+ CurrToStr(100 - PNG->CompressionLevel *10) + "%";
 }


 //---------------------------------------------------------------------------

 String Picture::ConvertToJPG(String path, String name, char qual, TImage *img) {

	ValidateImputs(&name, img);

	unique_ptr<TJPEGImage> Jpeg(new TJPEGImage());
//	unique_ptr<TImage>  Image1(new TImage(NULL));
	   unique_ptr<TDBImage> imgs(new TDBImage( img));

//	(*PulpitCanvas).Handle = GetDC(0);

//	img->Height = Screen->Height;
//	img->Width = Screen->Width;
//	img->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height), PulpitCanvas.get(),  Rect(0, 0, Screen->Width, Screen->Height));

//	ReleaseDC(0, (*PulpitCanvas).Handle);
//		  imgs->
//	Jpeg->Assign(img->Picture);

	  if ( GetQualityJPG((unsigned*)&qual)) {

		if ( qual < MinQuality)  qual  = MinQuality;                      // wartoœæ minimalna

		Jpeg->CompressionQuality = qual;
		Jpeg->Compress();

	  }
		if (Clipboard) {                                                        // schowek

		unique_ptr<TClipboard>pCB(new TClipboard);

		img->Canvas->CopyRect(Rect(0, 0, Screen->Width, Screen->Height),
			 Jpeg->Canvas, Rect(0, 0, Screen->Width, Screen->Height));

		pCB->Assign(img->Picture);

		return ("Screen skopiowany do schowka (JPEG) " + CurrToStr(Jpeg->CompressionQuality ) + "%");
		}

	  Jpeg->SaveToFile( name + ".jpg" );

	 return "Screen " + name + ".jpg zapisany " + CurrToStr(Jpeg->CompressionQuality ) + "%";
 }

//---------------------------------------------------------------------------

 void Picture::SetDefFileName(String Name) {

	Name = FileName;
 }

// ---------------------------------------------------------------------------

 unsigned Picture::GetQualityJPG(unsigned *value) {                             // scale 0-100

	*value = ( 0 < value <= 100) ? *value : 90;                                 // default value 90

	return *value;
 }
// ---------------------------------------------------------------------------

unsigned Picture::GetQualityPNG(unsigned value) {                               // scale 9-0

	if ( value <= 100) {                                                        // dla unsigned nie sparwdzam czy wiêksze od zera

	value = 10 - Toint(value/10);

	return value;

	} else return 1;                                                            		// default value

 }

// ---------------------------------------------------------------------------

 void Picture::SetMinQuality(char Min) {

	if ( 0 <= Min <= 100) MinQuality = Min;
 }

// ---------------------------------------------------------------------------

 void Picture::SaveToClipboard( bool save) {

	Clipboard = save;

 }

// ---------------------------------------------------------------------------

 void Picture::ValidateImputs(String *Name, TImage *img) {

	 if ( *Name == NULL		)	*Name = FileName;                                // jeœli równe 0
	 if ( (*Name).IsEmpty()	)	*Name = FileName;                                // lub puste

//	 if (img == NULL)
//							img = new TImage(0);

//	   img->Picture = dynamic_cast<TImage*>(image)->Picture;
//	 img->Assign(image->Picture->Bitmap);

//	 img->Canvas->CopyRect(Rect(0, 0, image->Width, image->Height), image->Canvas,
//						  Rect(0, 0, image->Width, image->Height));
//						  *img->Canvas->Draw(0,0,image->Picture->Graphic);
		 if (img == NULL)  {
		unique_ptr<Exception> e(new Exception("Nie za³adowano grafiki"));
		Application->ShowException(e.get());
		throw NULL;nothrow;
	 }
 }

// ---------------------------------------------------------------------------

#pragma package(smart_init)
