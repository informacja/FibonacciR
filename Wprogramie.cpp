#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Label1Click(TObject *Sender) {

	KOD = random(9000) + 999;
	Label1->Hint = KOD;
	Form2->MaskEditKod->Visible = true;
	Form2->EditKod->Visible = true;
 }
//---------------------------------------------------------------------------
void __fastcall TForm3::Image1Click(TObject *Sender) {
Form3->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Infooprogramie1Click(TObject *Sender)
{
 typedef BOOL (_stdcall *PGetProcessMemoryInfo)(HANDLE, void*, DWORD);

 PGetProcessMemoryInfo Memproc;
 HMODULE hMod;
 PROCESS_MEMORY_COUNTERS ProcMem;

 memset(&ProcMem, 0, sizeof(ProcMem));
 ProcMem.cb = sizeof(ProcMem);

 hMod = ::LoadLibraryA("psapi.dll");
 AnsiString a;

 if(!hMod) return;
 Memproc = (PGetProcessMemoryInfo)::GetProcAddress(hMod, "GetProcessMemoryInfo");
 if(!Memproc) return;
 if((*Memproc)(GetCurrentProcess(), &ProcMem, sizeof(ProcMem)))
  a= ProcMem.WorkingSetSize /1024/1024 ;
  ShowMessage("Program wykorzystuje: " + a + " MB pamiêci.");

 FreeLibrary(hMod);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FullInfo1Click(TObject *Sender)
{
	if (FullInfo1->Checked) {

	  FullInfo1->Checked=false;
	  Image1->Visible=true;
	  GroupBox1->Visible=false;
	  GroupBox2->Visible=false;
	  GroupBox3->Visible=false;
	}

	else {

	FullInfo1->Checked=true;
	Labelarcik->Visible=false;
	  Image1->Visible=false;
	   GroupBox1->Visible=true;
	   GroupBox2->Visible=true;
	   GroupBox3->Visible=true;

		infomemory();
		infobios();
		infoproc();

	}

  GroupBox1->Refresh();
}
//---------------------------------------------------------------------------
void TForm3::infomemory() {
//		 TMemoryStatus *MS = new TMemoryStatus;

		 unique_ptr<TMemoryStatus> MS(new TMemoryStatus);

		 MS->dwLength = sizeof(MEMORYSTATUS); // tego mo¿na nie stosowaæ.
		 GlobalMemoryStatus(MS.get());
		 Label10->Caption = FormatFloat("#,### MB", MS->dwAvailPageFile / 1024 /1024 );
		 Label11->Caption = FormatFloat("#,### MB", MS->dwAvailPhys    / 1024 /1024 );
		 Label12->Caption = FormatFloat("#,### MB", MS->dwAvailVirtual     / 1024 /1024 );
		 Label13->Caption = FormatFloat("#,### %", MS->dwMemoryLoad    );
		 Label14->Caption = FormatFloat("#,### MB", MS->dwTotalPageFile    / 1024 /1024 );
		 Label15->Caption = FormatFloat("#,### MB", MS->dwTotalPhys / 1024 /1024 );
		 Label16->Caption = FormatFloat("#,### MB", MS->dwTotalVirtual / 1024 /1024 );
//		 Label17->Caption = FormatFloat("#,### MB", MS->dwAvailPageFile / 1024 /1024 );

//		 delete MS;
}
//---------------------------------------------------------------------------
void TForm3::infobios() {

// HKEY hKey;
// LONG Res1,Res2;
// DWORD cData = 255;
// TCHAR SystemBiosVersion[255] = {'\0'};
// Res1 = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", NULL, KEY_QUERY_VALUE, &hKey);
//
// if(Res1 == ERROR_SUCCESS)
// {
//  Res2 = RegQueryValueExA(hKey, "SystemBiosVersion", NULL, NULL, (LPBYTE)SystemBiosVersion, &cData);
//  if(Res2==ERROR_SUCCESS)
//  {
//   int i = 0;
//   while(i < cData)
//   {
//	if(SystemBiosVersion[i] == '\0') SystemBiosVersion[i] = ' ';
//	i++;
//   }
//   Edit1->SetTextBuf(SystemBiosVersion);
//  }
//  else
//  {
////   Application->MessageBox("RegQueryValueEx: SystemBiosVersion", "ERROR", MB_OK | MB_ICONSTOP);
//  }
// }
// else
// {
////  Application->MessageBox("RegQueryValueEx: SystemBiosVersion", "ERROR", MB_OK | MB_ICONSTOP);
// }
//
// RegCloseKey(hKey);

}
//---------------------------------------------------------------------------
void TForm3::infoproc() {

		 HKEY hKey;
		 LONG Res1, Res2;
		 DWORD cData = 255;
		 char *ProcessorNameString = "";
		 Res1 = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
			 "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", NULL,
			 KEY_QUERY_VALUE, &hKey);

		 if (Res1 == ERROR_SUCCESS) {
			 Res2 = RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL,
				 ProcessorNameString, &cData);
			 if (Res2 == ERROR_SUCCESS) {
				 Label18->Caption = ((String)ProcessorNameString).Trim();
			 }
		 }
		 RegCloseKey(hKey);
	 }
//---------------------------------------------------------------------------

void Pobierz() {

}
//---------------------------------------------------------------------------

void __fastcall TForm3::arciki1Click(TObject *Sender)
{
	  FullInfo1->Checked=false;
	  Image1->Visible=false;
	  GroupBox1->Visible=false;
	  GroupBox2->Visible=false;
	  GroupBox3->Visible=false;

	  Labelarcik->Visible=true;

	  LabelarcikClick(Sender);

}
//---------------------------------------------------------------------------
#define B  "ID_MSG"

void __fastcall TForm3::LabelarcikClick(TObject *Sender)
{
	int i = random(5);
//		   ShowMessage(B);
	String a = "ID_MSG" + i;   // nie bangla
	String b = "ID_MSG1";
	  switch (i) {

//	  case 0 :  Labelarcik->Caption = AnsiString::LoadStr(1000);    break;

	  case 1 :  Labelarcik->Caption = "Co maj¹ wspólnego informatyk i blondynka?\n- Oboje ¿yj¹ dziêki sztucznej inteligencji.";  break;

	  case 2 :  Labelarcik->Caption = "- Nauczyciel sprawdza³ dzisiaj zeszyt i pyta³ czemu mam tylko co trzeci¹ lekcjê \n- to mu powiedzia³em ¿e to wersja demo a za pe³n¹ musi zap³aciæ.";   break;

	  case 3 :	Labelarcik->Caption = "Przychodzi informatyk do apteki i mówi:\n- Poproszê witaminê C++."; break;

	  case 4 :	Labelarcik->Caption = "- Panie, zainstalowa³em Windows...\n- Tak?\n- No i teraz mam problem...\n- No, to ju¿ mi pan powiedzia³.";

	  default:
		  ;
	  }
}
//---------------------------------------------------------------------------
//void __fastcall TForm1::Button1Click(TObject *Sender)
//{
// TMemoryStream *memory = NULL;
// String FileName = ExtractFilePath(ParamStr(0)) + "test.exe"; // plik z zasobami
// if(!FileExists(FileName))
// {
//  ShowMessage("B£¥D! NIe odnaleziono pliku");
//  return;
// }
//
// HANDLE hfile = BeginUpdateResource(FileName.c_str(), false);
// if(hfile == NULL ) return;
//
// memory = new TMemoryStream();
// memory->LoadFromFile(ExtractFilePath(ParamStr(0)) + "music1.wav");
//
// if(UpdateResource(hfile, "WAVE", "ID_SONG1",
//				   MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
//				   memory->Memory, memory->Size))
// {
//  EndUpdateResource(hfile, false);
// }
// if(memory != NULL) delete memory;
//}
void __fastcall TForm3::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_ESCAPE) this->Close();
}
//---------------------------------------------------------------------------

