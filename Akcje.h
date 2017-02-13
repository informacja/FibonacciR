#ifndef AkcjeH
#define AkcjeH

#include "Unit1.h"
//---------------------------------------------------------------------------



//	void __fastcall Zamknij1Click(TObject *Sender);


	String ScreenPNG(char CompressionQuality = 0 ,bool Clipboard = 0);

	String ScreenJPG(char CompressionQuality = 0 ,bool Clipboard = 0);

	String ScreenBMP(char CompressionQuality = 0 ,bool Clipboard = 0, String SavePath = "");

	unsigned GetQualityJPEG();

	unsigned GetQualityPNG();

	int TryToInt(AnsiString a);

	SaveScreenToClipboard();

//---------------------------------------------------------------------------

	// ProgresBar

	void ProgressBarPos(unsigned short pos);

	void ProgressBarMax();

	void ProgressBarMin();

	void ProgressBarStyle(bool Orientation_Vertical = 0, bool Style_Marquee = 0);// styl i orientacja ProgresBar1

	void ProgressAnimation();


	  //konwersja
//       int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
//{
// unsigned int num = 0;
// unsigned int size = 0;
//
// Gdiplus::GetImageEncodersSize(&num, &size);
// if(size == 0)return -1;
//
// Gdiplus::ImageCodecInfo* imageCodecInfo = new Gdiplus::ImageCodecInfo[size];
// Gdiplus::GetImageEncoders(num, size, imageCodecInfo);
//
// for(unsigned int i = 0; i < num; ++i)
// {
//  if(wcscmp(imageCodecInfo[i].MimeType, format) == 0)
//  {
//   *pClsid = imageCodecInfo[i].Clsid;
//   delete[] imageCodecInfo;
//   return i;
//  }
// }
// delete[] imageCodecInfo;
// return -1;
//}

//void __fastcall TForm1::Button1Click(TObject *Sender)
//{
// Gdiplus::Graphics graphics(this->Handle);
// String oldFile = "c:\\plik.tif";
// String newFile = "c:\\nowy.png";
// Gdiplus::Image imageFile(WideString(oldFile).c_bstr(), false);
//
// CLSID pngClsid;
// GetEncoderClsid(L"image/png", &pngClsid);
// imageFile.Save(WideString(newFile).c_bstr(), &pngClsid, NULL);
//}

#endif
