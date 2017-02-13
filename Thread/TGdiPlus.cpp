//---------------------------------------------------------------------------

#include <System.hpp>
#include "TGdiPlus.h"
#pragma hdrstop
#pragma package(smart_init)

//---------------------------------------------------------------------------

#define JPG  L"image/jpg"
#define PNG  L"image/png"
#define BMP  L"image/bmp"
#define GIF  L"image/gif"
#define TIFF L"image/tiff"
#define WEBP L"image/webp"

#define Ok 0

//---------------------------------------------------------------------------
// unsing namespace gd;
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Gdiplus::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TGdiplus::TGdiplus(bool CreateSuspended)	: TThread(CreateSuspended)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup( &m_gdiplusToken, &gdiplusStartupInput, NULL);

	grphx_hwnd = NULL;
	jpg__image = NULL;
	Image_path = new String("");
	guid = Gdiplus::ImageFormatJPEG;
//	guid = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };

}

//---------------------------------------------------------------------------

__fastcall TGdiplus::~TGdiplus()
{
	Gdiplus::GdiplusShutdown( m_gdiplusToken );
	delete Image_path;
}

//---------------------------------------------------------------------------
void __fastcall TGdiplus::Execute()
{
	NameThreadForDebugging(System::String(L"GdiplusThread"));
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------

bool TGdiplus::Load_Image( TImage* hImg, String * path )
{
	if( FileExists( *path ) )
	{
//		if( hImg->Picture->Bitmap->Width == 0 )
//			hImg->Picture->Assign( NULL );

		jpg__image = jpg__image->FromFile( (*path).w_str(), false );
		grphx_hwnd = grphx_hwnd->FromHDC( hImg->Canvas->Handle );

		grphx_hwnd->DrawImage( jpg__image, 0, 0, hImg->Width, hImg->Height );

		hImg->Repaint();

		*Image_path = *path;                                                      // ustawia œcie¿kê dla pracy w¹tka

		return true;
	}
	else
	{
     	*Image_path = "";
		return false;
	}

}

//---------------------------------------------------------------------------

bool TGdiplus::Convert_Save( String * out_path )
{

	CLSID pngClsid = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };

	guid = pngClsid;
//	SetClipboardData()

//	GetEncoderClsid( (wchar_t*)Image_path, &pngClsid);


	jpg__image = jpg__image->FromFile( (*Image_path).w_str(), false );

	jpg__image->Save( (*out_path).c_str(), &guid, NULL);

    return 1;
}

//---------------------------------------------------------------------------
	  #include "Func.h"
bool TGdiplus::Convert( String* in, String* out )
{
		String a     = "C:\\Users\\WorkSpace\\Desktop\\DSCN7470.JPG";

		String b	= "C:\\Users\\WorkSpace\\Desktop\\test.png"  ;

		in = &a;
		out = &b;

CLSID pngClsid;
GetEncoderClsid(L"image/png", &pngClsid);

  IStream* pIStream    = NULL;
if(CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) != S_OK)
{
	ShowError("Failed to create stream on global memory!");
//	return;
}
//Image image( a.w_str() );
	   // Setup encoder parameters
Gdiplus::EncoderParameters encoderParameters;
encoderParameters.Count = 1;
encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
encoderParameters.Parameter[0].NumberOfValues = 1;

// setup compression level
ULONG quality = 50;
encoderParameters.Parameter[0].Value = &quality;


//if(SaveStatus != Ok)
//{
//	// this should free global memory used by the stream
//	// according to MSDN
//	pIStream->Release();
//	AfxMessageBox(_T("Failed to save to stream!"));
//	return;
//}
	CLSID encoderClsid;
	Gdiplus::Status stat;
	Gdiplus::Image* image = new Gdiplus::Image( (*in).w_str() );
	// Get the CLSID of the PNG encoder.
	GetEncoderClsid( JPG, &encoderClsid);
			   LogSave( (String)encoderClsid.Data1 + "\n" ) ;
				GetEncoderClsid( PNG, &encoderClsid);
			   LogSave( (String)encoderClsid.Data1 + "\n" ) ;
			   	GetEncoderClsid( WEBP, &encoderClsid);
			   LogSave( (String)encoderClsid.Data1 + "\n" ) ;
	GetEncoderClsid( JPG, &encoderClsid);
	   Gdiplus::Status SaveStatus = image->Save(pIStream, &pngClsid, &encoderParameters);

	stat = image->Save( (*out).w_str(), &encoderClsid, NULL);
//		stat = image->Save( pIStream, &pngClsid, &encoderParameters);
	if (stat == Ok )
		printf("Bird.png was saved successfully \n " );
	else   {
		printf( " Failure : stat = % d \n ", stat);                             // stat = 2 ?????
		MessageBeep(4556);

		   ShowError( stat );
	}
	delete image;

}

// ---------------------------------------------------------------------------

String TGdiplus::GetImageDir()
{
	return ExtractFilePath( *Image_path );
}
