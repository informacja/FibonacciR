//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PropertiesDlg.h"
#include "Unit1.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPropetisDlg *PropetisDlg;
//---------------------------------------------------------------------
//__fastcall TPropetisDlg::TPropetisDlg(TComponent* AOwner)
//	: TForm(AOwner)
//{
//}
//---------------------------------------------------------------------
 TPropetisDlg::TPropetisDlg(TComponent* AOwner, String* FilePath, bool ADS_1) : TForm(AOwner)
 {
	   Path = FilePath;
	   this->Text = "W³aœciwoœci: " + ExtractFileName(*FilePath);

	   FillWnd();
 }


//---------------------------------------------------------------------
 void TPropetisDlg::LoadImg(){

	HICON ico;
	WORD idx;
	ico = ExtractAssociatedIcon(HInstance, (*Path).c_str(), &idx);
	if (!ico) { ShowMessage("B³¹d ikony LoadImg()")  ;

	}
	ImageEXE->Picture->Icon->Handle = ico;

		 ImageOpenWith->Picture->Icon->Modified = true;

   SHFILEINFO info;
//   DWORD result = SHGetFileInfo((*Path).c_str(), 0, &info,
//								sizeof(info), SHGFI_ICON |
//								SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX);
   if ( SHGetFileInfo((*Path).c_str(), 0, &info,	sizeof(info), SHGFI_ICON |
								SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX) != 0)

	  FibonacciR->IconList->GetIcon(info.iIcon, ImageOpenWith->Picture->Icon);
   else
	  ImageOpenWith->Picture->Icon->Assign(NULL);

//                                     FibonacciR->IconList->DrawingStyle=

//	  ImageOpenWith->Picture->Icon->Assign(  );
		 ImageOpenWith->Stretch = true;


//	wchar_t Exec[255];     FindExecutableW( (*Path).c_str(), 0, Exec);
//	ico = ExtractAssociatedIcon(HInstance, Exec, &idx);
//
//	ImageOpenWith->Picture->Icon->Handle = ico;
//	ImageOpenWith->Stretch = true;
//	ImageOpenWith->Assign(ImageOpenWith->Picture);
 }
//---------------------------------------------------------------------
	void TPropetisDlg::LoadSize(){

	unique_ptr<String> size(new String( filesize( ((AnsiString)*Path ).c_str()) ));

	LabelSize->Caption = GetSize((*size).ToInt()) + " " + "(bajtów: "+ *size +")";

	}
//---------------------------------------------------------------------
	void TPropetisDlg::LoadTime(){
	}
//---------------------------------------------------------------------
 void TPropetisDlg::FillWnd() {


	GetAllFileVersionInformation( ((AnsiString)*Path).c_str(), FibonacciR->Memo1);

	EditFileName->Text = ExtractFileName(*Path);
	LabelPath->Caption = ExtractFileDir(*Path);
	LabelFileType->Caption = ExtractFileExt(*Path);


	LoadImg();
	LoadSize();
	LoadTime();
//	LabelOpenWith->Caption = Exec;
//	LabelSize->Caption = GetFileVersionInfo( ((AnsiString)*Path).c_str(), "FileVersion");

 }

//---------------------------------------------------------------------
  bool Properties(String* File_Path, bool ADS) {

//	unique_ptr<TPropetisDlg> DLG(new TPropetisDlg(0));


  }
//---------------------------------------------------------------------
String  TPropetisDlg::GetFileVersionInfo(char *ModulePath, String KeyName)
{
 LPVOID lpStr1 = NULL, lpStr2 = NULL;
 WORD* wTmp;
 DWORD dwHandlev = NULL;
 UINT dwLength;
 char sFileName[1024] = {0};
 char sTmp[1024] = {0};
 String sInfo;
 LPVOID* pVersionInfo;

 if(ModulePath == NULL) GetModuleFileNameA(NULL, sFileName, 1024);
 else strcpy(sFileName, ModulePath);

 DWORD dwInfoSize = GetFileVersionInfoSizeA((char*)(LPCTSTR)sFileName, &dwHandlev);
 if(dwInfoSize)
 {
  pVersionInfo = new LPVOID[dwInfoSize];
  if(GetFileVersionInfoA((char*)(LPCTSTR)sFileName, dwHandlev, dwInfoSize, pVersionInfo))
  {
   if(VerQueryValue(pVersionInfo, L"\\VarFileInfo\\Translation", &lpStr1, &dwLength))
   {
    wTmp = (WORD*)lpStr1;
	sprintf(sTmp, (const char*)("\\StringFileInfo\\%04x%04x\\" + KeyName).c_str(), *wTmp, *(wTmp + 1));
	if(VerQueryValueA(pVersionInfo, sTmp, &lpStr2, &dwLength)) sInfo = (LPSTR)lpStr2;
   }
  }
  delete[] pVersionInfo;
 }
 return sInfo;
}

//---------------------------------------------------------------------------

void __fastcall TPropetisDlg::FormClose(TObject *Sender, TCloseAction &Action)
{
Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPropetisDlg::OKBtnClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------


