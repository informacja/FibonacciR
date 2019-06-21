#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
void Przepis_na::oblicz()
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

void Przepis_na::toint()
 {
   for (int i = 0; i <= 5; i++) {

  if(wy[i] - static_cast<int>(wy[i]) >= 0.5)

		wy[i] = static_cast<int>(wy[i]) + 1;

  else	wy[i] = static_cast<int>(wy[i]);

   }
 }
//---------------------------------------------------------------------------
 int Przepis_na::toint(float nm)
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

 void Przepis_na::zapisz() {

 if (FibonacciR->wej1->Value == 0) return;

	oblicz();

	 try {

		unique_ptr<ofstream> wyniki(new ofstream);
		unique_ptr<unsigned char> l(new unsigned char(S::Fr.Length() + Form2->SpinEditFill->Value));

		 (*wyniki).open( (S::NAMEcalc + ".txt").c_str(), ios::out | ios::app);

		 *wyniki << "Dla " << setw( 9 ) << FibonacciR->wej1->Value <<
			" wyliczono :  " << right;
if (Form2->CheckBoxZ1->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[0] )).c_str() << " " << setw(*l);
if (Form2->CheckBoxZ2->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[1] )).c_str() << " " << setw(*l) ;
if (Form2->CheckBoxZ3->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[2] )).c_str() << " " << setw(*l) ;
if (Form2->CheckBoxZ4->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[3] )).c_str() << " " << setw(*l) ;
if (Form2->CheckBoxZ5->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[4] )).c_str() << " " << setw(*l) ;
if (Form2->CheckBoxZ6->Checked) *wyniki << ((AnsiString)FormatFloat( S::Fr , wy[5] )).c_str() << " ";

		 *wyniki << endl;

		 (*wyniki).close();

	 }
	 catch (...) {

			ShowError("/Przechwycono\\ Błąd metody Przepis_na::zapisz()");

		 }
	 }

//---------------------------------------------------------------------------
 void Przepis_na::wypisz() {
   FibonacciR->wyj1->Value=wy[0];
   FibonacciR->wyj2->Value=wy[1];
   FibonacciR->wyj3->Value=wy[2];
   FibonacciR->wyj4->Value=wy[3];
   FibonacciR->wyj5->Value=wy[4];
   FibonacciR->wyj6->Value=wy[5];
 }

//###########################################################################

 void Doubcl::oblicz() {

	try {

		unique_ptr<double> w(new double( FibonacciR->wej->Text.ToDouble() ));

			wy[2]=*w*FI;
			wy[1]=*(w)-wy[2];
			wy[3]=*w+wy[2];
			wy[4]=2**w+wy[2];
																				// (int)*w << 1) nie stosować (niedokładne dla zmienno przecinkowych)
			wy[5]=2**w*FI;
			wy[6]=wy[5]-*w;

		}

	  catch (EConvertError &ConvertErr) {

		  curpos = FibonacciR->wej->SelStart;

			 if ( FibonacciR->wej->Text == "" ) {                               // jeśli nie ma co obliczyć (pusta wartość)

				FibonacciR->wej->Text = 0;
				oblicz();
				wypisz();

				FibonacciR->StatusInfo("Pole nie może być puste");

				FibonacciR->wej->Perform(EM_SETSEL, curpos, curpos+1);      	// zaznacza zero

			 } else {                                                        	// jest przekazana nietypowa zawatość

				 FibonacciR->wej->Text = DigitRewrite(FibonacciR->wej->Text, 1, 1);
				 oblicz();
				 wypisz();
				 FibonacciR->StatusInfo("Błąd konwersji: " + ConvertErr.ToString());

				FibonacciR->wej->Perform(EM_SETSEL, curpos-1, curpos-1);
			}
	   }
	  catch (...) {

		ShowError("Nieznany błąd w sekcji Doubcl::oblicz()");
	  }

 }

 //---------------------------------------------------------------------------

 void Doubcl::zapisz() {

 oblicz();

  try {

	unique_ptr<ofstream> wyniki(new ofstream);

		 (*wyniki).open("Wyniki.txt", ios::out | ios::app);

		 *wyniki << "Dla " <<
			 // wyniki.width(20)<<
			 internal <<

			 // <<setfill (' ')
			 setw(12) << NULL <<
			 // FormatFloat( '#' ,lpobrana)<<setprecision(2)<<
			 // wyniki.width(19 - lenght)<<
			 " wyliczono :  ";
		 if (Form2->CheckBoxZ1->Checked) {

			 *wyniki << wy[0] << " " << setw(7) ;
		  }
		 // internal << wyj[1] << " "<<
		 // wyniki.width(bv + 2)<<
		 // wyniki << right << wyj[2] << " "<<
		 // wyniki.width(bv + 3)<<

		 if (Form2->CheckBoxZ2->Checked) {

//			 *wyniki << CurrToStrF(wy[1], ffFixed, 4) << " " << setw(7) ;
		  }
		 if (Form2->CheckBoxZ3->Checked) {

			 *wyniki << wy[2] << " " << setw(7) ;
		  }
		 if (Form2->CheckBoxZ4->Checked) {

			 *wyniki << wy[3] << " " << setw(7) ;
		  }
		 if (Form2->CheckBoxZ5->Checked) {

			 *wyniki << wy[4] << " " << setw(7) ;
		  }
		 if (Form2->CheckBoxZ6->Checked) {

			 *wyniki << wy[5] << " ";

		  }

		 *wyniki << endl ;

		 (*wyniki).close();


  }
  catch(Exception &eError)
  {
	throw Exception("Przyczyna błędu: " + eError.Message);
  }
  catch(...) {
	  ShowError("Nieznany błąd Doubcl::zapisz");
  }
 }

 //---------------------------------------------------------------------------

 void Doubcl::wypisz() {
   FibonacciR->wy1->Text=wy[1];
   FibonacciR->wy2->Text=wy[2];
   FibonacciR->wy3->Text=wy[3];
   FibonacciR->wy4->Text=wy[4];
   FibonacciR->wy5->Text=wy[5];
   FibonacciR->wy6->Text=wy[6];
//
//   TObject a;        new
//		FindControl(g)
//			get
//   a.
//
//   Components[i]->Name, dynamic_cast<TObject *>(Components[i]))
//	  obje
//	  FibonacciR->wy[i+1]->Text = wy[i];

 }

 void Doubcl::wypiszRound() {

   FibonacciR->wy1->Text=Round(wy[1]);
   FibonacciR->wy2->Text=Round(wy[2]);
   FibonacciR->wy3->Text=Round(wy[3]);
   FibonacciR->wy4->Text=Round(wy[4]);
   FibonacciR->wy5->Text=Round(wy[5]);
   FibonacciR->wy6->Text=Round(wy[6]);
 }

 //***************************************************************************

 void U::SavePref() {                                                           // zapisuje ustawienia

	   if (Form2->RadioButton6->Checked) {

		   namepref = STR_BEGINING;
		   dopisek = Form2->Edit4->Text;

	   }   else if (Form2->RadioButton5->Checked) {

		   namepref = STR_POSTFIX;


	   }   else if (Form2->RadioButton8->Checked)  {

		   namepref = stream_name_tag::STR_NEW_NAME;
		   dopisek = Form2->Edit4->Text;

	   }   else    namepref = SRT_SAME;

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
