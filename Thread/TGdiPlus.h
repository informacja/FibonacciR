//---------------------------------------------------------------------------

#ifndef TGdiPlusH
#define TGdiPlusH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <GdiPlus.h>
#include <Vcl.ExtCtrls.hpp>		// TImage
//---------------------------------------------------------------------------
//namespace gd
//{

class TGdiplus : public TThread
{
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	Gdiplus::Image    *jpg__image; 		// WskaŸnik na obraz JPG, który wczytamy z pliku do pamiêci
	Gdiplus::Graphics *grphx_hwnd; 		// WskaŸnik na "uchwyt" komponentu, na którym bêdziemy rysowaæ

	String *Image_path;

	CLSID guid;


protected:
	void __fastcall Execute();

public:

    String GetImageDir();
	bool Load_Image( TImage* img, String * path );
	bool Convert_Save( String * out_path );
	bool Convert( String* in, String* out );

	__fastcall TGdiplus(bool CreateSuspended);
	__fastcall ~TGdiplus();
};

//}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
  unsigned int  num = 0;    // number of image encoders
  unsigned int  size = 0;   // size of the image encoder array in bytes

  Gdiplus::GetImageEncodersSize(&num, &size);
  if(size == 0)return -1;

  Gdiplus::ImageCodecInfo* imageCodecInfo = new Gdiplus::ImageCodecInfo[size];
  Gdiplus::GetImageEncoders(num, size, imageCodecInfo);

  for(unsigned int i = 0; i < num; ++i)
  {
    if( wcscmp(imageCodecInfo[i].MimeType, format) == 0 )
    {
       *pClsid = imageCodecInfo[i].Clsid;
       delete[] imageCodecInfo;
       return i;
    }
  }
  delete[] imageCodecInfo;
  return -1;
}


 #include <windows.h>
#include <gdiplus.h>
#include <stdio.h>
//using namespace Gdiplus;

int GetEncoderClsid1(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
	  return -1;  // Failure

   pImageCodecInfo = ( Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
	  return -1;  // Failure

    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
	  if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
	  {
		 *pClsid = pImageCodecInfo[j].Clsid;
		 free(pImageCodecInfo);
		 return j;  // Success
	  }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

enum Format{
bmp = 0,
jpeg
//imag/gif
//image/tiff
//image/png
};



//	image/bmp  : {557cf400-1a04-11d3-9a73-0000f81ef32e}
//	image/jpeg : {557cf401-1a04-11d3-9a73-0000f81ef32e}
//	image/gif  : {557cf402-1a04-11d3-9a73-0000f81ef32e}
//	image/tiff : {557cf405-1a04-11d3-9a73-0000f81ef32e}
//	image/png  : {557cf406-1a04-11d3-9a73-0000f81ef32e}

//---------------------------------------------------------------------------
#endif
