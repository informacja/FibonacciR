#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
void TIntFI::oblicz()
 {
	unique_ptr<float> w(new float((float)FibonacciR->wej1->Value));             // get value

//	lpobrana = *w;

	wy[1] = *w * FI;
	wy[0] = *(w) - wy[1];
	wy[2] = *w + wy[1];
	wy[3] = ((int)*w << 1) + wy[1];

	wy[4] = ((int)*w << 1) * FI;	   											// funkcja dla worda
	wy[5] = wy[4] - *w;

 }

//---------------------------------------------------------------------------

void TIntFI::toint()
 {
   for (int i = 0; i <= 5; i++) {

  if(wy[i] - static_cast<int>(wy[i]) >= 0.5)

		wy[i] = static_cast<int>(wy[i]) + 1;

  else	wy[i] = static_cast<int>(wy[i]);

   }
 }
//---------------------------------------------------------------------------
 int TIntFI::toint(float nm)
 {
  if(nm - static_cast<int>(nm)>=0.5) {

	nm=static_cast<int>(nm)+1;
	return nm;
	}

  else  {
	nm=static_cast<int>(nm);
	return nm;
	}
 }

//---------------------------------------------------------------------------

 void TIntFI::zapisz() {

 if (FibonacciR->wej1->Value == 0) return;

	oblicz();

	 try {

		unique_ptr<ofstream> wyniki(new ofstream);
		unique_ptr<unsigned char> l(new unsigned char(S::Fr.Length() + Form2->SpinEditFill->Value));

		 (*wyniki).open( (S::NAMEcalc + ".txt").c_str(), ios::out | ios::app);

		 *wyniki << "Dla " << setw( 9 ) << FibonacciR->wej1->Value <<
			" wyliczono :  " << internal;
if (Form2->CheckBoxZ1->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[0] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ2->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[1] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ3->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[2] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ4->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[3] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ5->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[4] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ6->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[5] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";

		 *wyniki << endl;

		 (*wyniki).close();

	 }
	 catch (...) {

			ShowError("/Przechwycono\\ Błąd metody TIntFI::zapisz()");

		 }
	 }

//---------------------------------------------------------------------------

 void TIntFI::wypisz() {
   FibonacciR->wyj1->Value=wy[0];
   FibonacciR->wyj2->Value=wy[1];
   FibonacciR->wyj3->Value=wy[2];
   FibonacciR->wyj4->Value=wy[3];
   FibonacciR->wyj5->Value=wy[4];
   FibonacciR->wyj6->Value=wy[5];
 }

 //---------------------------------------------------------------------------

 void U::SavePref() {                                                           // zapisuje ustawienia

	   if (Form2->SpeedButtonNamePre->Down) {

		   namepref = STR_BEGINING;
		   dopisek = Form2->EditNameADS->Text;

	   }   else if (Form2->SpeedButtonNamePost->Down) {

		   namepref = STR_POSTFIX;

	   }   else if (Form2->SpeedButtonNameNew->Down)  {

		   namepref = stream_name_tag::STR_NEW_NAME;
		   dopisek = Form2->EditNameADS->Text;

	   }   else    namepref = SRT_SAME;

// =	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=

	   if (Form2->RadioButton9->Checked) {

		   pathpref = PATH_USER;
		   zpath = Form2->Edit1->Text;
	   }
	   else   pathpref = PATH_CURR;

	   if (Form2->CheckBoxULOG->Checked) {

		   if (Form2->RadioButton10->Checked)   logpref = LOG_DESKTOP;

		   else if(Form2->RadioButton11->Checked){

			  logpref = LOG_HERE;
			  logpath = ExtractFilePath(ParamStr(0));
		   }
		   else  {

		   logpref = LOG_OTHER;
		   logpath = Form2->SaveTextFileDialog1->FileName;
		   }
	   }
 }
//---------------------------------------------------------------------------

 String U::ApplyPref1(String name) {

	switch (namepref) {

//	case SRT_SAME:; break;         nothing to do

	case STR_BEGINING: name = dopisek + name; break;

	case STR_POSTFIX:  name = AddBeforDot(name, dopisek); break;

	case STR_NEW_NAME: name = dopisek; break;

	default: ;

	}

	return name;
 }
//---------------------------------------------------------------------------

 String U::ApplyPref2(String path) {

  switch (pathpref) {

	case PATH_CURR:  {

		unique_ptr<TCHAR> buffer(new TCHAR[512]);

			if (!GetCurrentDirectoryW( 512, buffer.get()))

				ShowError("Nie udało się pobrać aktualnej ścieżki\n\nBłąd U::ApplyPref2(PATH_CURR)");

			else 	path = TrimRight(buffer.get());

	} break;

	case PATH_USER: {

		path = zpath;

		if (!DirectoryExists(path)) {
			 FibonacciR->StatusInfo("Lokalizacja \"" + path + "\" nie istnieje\n jeśli to możliwe zostanie utworzona");
		}

	} break;

	default: ;
  }

	if (!DirectoryExists(path) && !FileExists(path)) {

	   ShowError("Ścieżka \"" +path+ "\" nie istnieje\n\nBłąd kontrolny U::ApplyPref2();                              ( zignoruj to )");
	}

  return path;
 }

//---------------------------------------------------------------------------

 void U::SaveLog(AnsiString path, AnsiString name, AnsiString from) {

  switch (logpref)                                                              // gdzie zapisać loga
  {
	case LOG_DESKTOP:
	{
		unique_ptr<TCHAR> buffer(new TCHAR[512]);

		SHGetSpecialFolderPath(NULL, buffer.get(), CSIDL_DESKTOPDIRECTORY , 0);
		logpath = buffer.get();

	} break;

	case LOG_HERE:  logpath = Getpath(ParamStr(0)); break;

	case LOG_OTHER: logpath = Form2->SaveTextFileDialog1->FileName; break;

	default: ;

  }

	logpath = Getpath(logpath) + S::NAMElog + ".log";   // ścieżka zapisu loga

	unique_ptr<ofstream> log(new ofstream);

	try {

		 (*log).open(logpath.c_str(), ios::out | ios::app);

		 if (!first_open) {

			 *log << "[  " << GetDataTime().c_str() << "  ]" << endl;
		 }

		 *log << "From:   " << left << setw(50) << from.c_str() <<

		 " To:   " << setw(40) << path.c_str() << ":" << right << setw(25)<<name.c_str() <<

		 "	  LastError: " << GetLastError() <<

		 endl;

		 (*log).close();

	 }
	 catch (...) {

			 ShowError("Błąd metody U::SaveLog()");
	}

	first_open++;
 }

// ---------------------------------------------------------------------------

 U::U() {

//	logpref = stream_name_tag::SRT_SAME; //zmiennym statycznym nie przypisuje się mają domyślnie 0

  }

stream_name_tag U::namepref   = SRT_SAME;

stream_path_tag U::pathpref   = PATH_CURR;

stream_logfile_tag U::logpref = LOG_DESKTOP;

short U::first_open = 0;

String U::dopisek = "";
String U::zpath   = "C:\\";
String U::logpath = "C:\\";

//---------------------------------------------------------------------------



#pragma package(smart_init)
