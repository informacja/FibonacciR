//---------------------------------------------------------------------------

#pragma hdrstop

#include "Times.h"

//---------------------------------------------------------------------------

Times::Times() { 																// constructors
	reset();
	new_ofstream();
}

Times::Times(TObject* toShowResult) {
	reset(toShowResult);
	new_ofstream();
}

//---------------------------------------------------------------------------

Times::~Times() {                                                               // destructor

	if ( obj != NULL ) Show( obj );
	#ifdef _FSTREAM_H_
	delete ofs;
	#endif
} // if you can define default object, on destruct result time will be showed on he's variable (Text, Caption)

//---------------------------------------------------------------------------

void Times::reset(TObject* toShowResult) {

	first = 0;
	second = 0;
	f = 0;
	s = 0;
	p = 0;
	c = 0;
	hint = 0;
	result = 0;
	precisionhint = 3;
	obj = toShowResult;
}
// --------------------------------------------------------------------------
 void Times::resetFlags() {
	first = 0;
	second = 0;
	f = 0;
	s = 0;
	p = 0;
	c = 0;
	hint = 0;
	result = 0;
 }

//---------------------------------------------------------------------------

inline void Times::new_ofstream() {                                            	// na potrzeby konstruktorów (redundancja)
	#ifdef _FSTREAM_H_
	ofs = new ofstream;
	#endif
	return;
}

// ---------------------------------------------------------------------------
void Times::Calculate(){                                                        // b³¹d jest tu

//   f = 0; s = 0;

	result = second - first;

	unique_ptr<String>mils(new String(result));

	unsigned sec = (int)( result / 1000);

	if ( result < 1001 ) {

	 while (QueryPerformanceFrequency(&lpFrequency) == 0) {
			QueryPerformanceFrequency(&lpFrequency) == 0;
	 }

		double Frequency= lpFrequency.QuadPart;
		double End 	  	= lpEnd.QuadPart;
		double Start  	= lpStart.QuadPart;

		Frequency = (End - Start) / Frequency;                                  //////TO DO

		// Frequency przechowuje wynik bo nie jest ju¿ potrzebne
//		if (Frequency == 0) {

//			ShowMessage(lpEnd.QuadPart+lpStart.QuadPart+lpFrequency.QuadPart);
//		}

//		seconds = Frequency;         //bug

		if ( p & c)  Frequency = starttopaused + seconds;                      	// jeœli wywo³ano funkcje Pause i Continue
		seconds = Frequency;
		Frequency = Frequency * 1000;                                           // z sekund na milisekundy

		*mils = FloatToStrF(Frequency, ffFixed, 18, 18);                       	// dok³adnoœæ do sekund do -18 potêgi (attosecond)
//		ShowMessage((String)seconds + "\n" + (*mils).ToDouble()/1000 ) ;
//		seconds = (*mils).ToDouble()/1000;


		FormatMilisec(mils.get());
//			*mils= (*mils)/1000;
	}  else {                                                                   // jeœli d³u¿ej ni¿ sekundê

		(*mils).Delete(1, (*mils).Length() - 3);                                // obcinanie tak aby zosta³y tylko milisekundy
		seconds = result / 1000;
	}

	formated = FormatFloat("00", sec / 3600) + ":" + // godziny (iloœæ nie ograniczona, maksymalna jednostka)
			FormatFloat("00", (sec /60/60 >= 1 ) ? sec /60 %60 : sec /60 )+ ":" + 	// minuty
			FormatFloat("00", (sec /60 >= 1) ? sec % 60 : sec ) + "." + 			// sekundy
			*mils.get();                                   							// milisekundy

}
// ---------------------------------------------------------------------------

 void Times::FormatMilisec(String* __inout f, bool __in hint) {

	unique_ptr<unsigned char>pos(new unsigned char((*f).LastDelimiter(",")));

	if (!*pos) *f = "No comma in method FormatMilisec()";

	while (*pos < 4) { // e.g. "000,0"

		(*f).Insert("0", 1);
		*pos = (*f).LastDelimiter(",");
	}

	for (int i = 7; i < 0; i--) {

		(*f).Insert(" ", i*3);
	}

	for (int i = 0; i < 3; i++) {                                               // usuwanie ostatnich 3 zer jeœli s¹

		if ( (*f).operator []( (*f).Length() ) == '0')
		(*f).Delete( (*f).Length(), 1);
	}
 }

// ---------------------------------------------------------------------------

 void Times::Show( ) {

   if ( !s )	Stop();

   if ( obj != NULL ) {

	try {                                                                       // dla odpowiedniego componentu wykona siê tylko jeden z poni¿szych

		(reinterpret_cast< TControl *>	(obj))->ShowHint = true;

		if ( (*obj).ToString() == "TStatusBar" )

			(reinterpret_cast< TStatusBar *>(obj))->Panels->Items[1]->Text = Result();  // tu mo¿na zmieniæ panel wyœwietlania

		else if ( (*obj).ToString() == "TLabel" )

			(reinterpret_cast< TLabel *>	(obj))->Caption 	= Result();

		else if ( (*obj).ToString() == "TEdit" )

			(reinterpret_cast< TEdit *>		(obj))->Text 	= Result();

		else if ( (*obj).ToString() == "TButton" )

			(reinterpret_cast< TButton*>	(obj))->Caption 	= Result();

//		(reinterpret_cast< TControl *>	(obj))->Hint = ResultHinted();		// dla wszystkich podpowiedŸ

	}
	catch (Exception &exception) {

		ShowMessage("Wyj¹tek metody Times::Show(TObject *Sender) " + exception.ToString() );
	}
	catch (...) {	ShowMessage("B³¹d metody Times::Show(TObject *Sender)"); }
   }
   else	ShowMessage("void Times::Show( ) error: \nNie zdefiniowano objektu przy inicjalizacji lub jego adres jest niepoprawny");
 }

// ---------------------------------------------------------------------------

void Times::Show(TObject *Sender) {

	if ( !s )	Stop();                                                         // jeœlin nie wywo³ano funkcji Stop()
//                    ShowMessage(second);
   if ( Sender != NULL ) {

	try {                                                                       // dla odpowiedniego componentu wykona siê tylko jeden z poni¿szych

		(reinterpret_cast< TControl *>	(Sender))->ShowHint = true;

		if ( (*Sender).ToString() == "TStatusBar" )

			(reinterpret_cast< TStatusBar *>(Sender))->Panels->Items[1]->Text = Result();  // tu mo¿na zmieniæ panel wyœwietlania

		else if ( (*Sender).ToString() == "TLabel" )

			(reinterpret_cast< TLabel *>	(Sender))->Caption 	= Result();

		else if ( (*Sender).ToString() == "TEdit" )

			(reinterpret_cast< TEdit *>		(Sender))->Text 	= Result();

		else if ( (*Sender).ToString() == "TButton" )

			(reinterpret_cast< TButton*>	(Sender))->Caption 	= Result();

		(reinterpret_cast< TControl *>	(Sender))->Hint = ResultHinted();		// dla wszystkich podpowiedŸ

	}
	catch (Exception &exception) {

		ShowMessage("Wyj¹tek metody Times::Show(TObject *Sender) " + exception.ToString() );
	}
	catch (...) {	ShowMessage("B³¹d metody Times::Show(TObject *Sender)"); }
   }
   else	ShowMessage("void Times::Show(TObject *Sender) error: \nNie zdefiniowano objektu przy inicjalizacji lub jego adres jest niepoprawny"); // OLD // ta funkcja jest wywo³ywana w destruktorze dlatego j¹ komentujê, by nie wywo³ywaæ nie potrzebnego komunikatu
}

// ---------------------------------------------------------------------------
 void Times::Show( String *s, String *h ) {

	if ( !s )	Stop();                                                         // jeœlin nie wywo³ano funkcji Stop()

	if (s) *s = Result();                                                       // przypisanie wartoœci wskaŸnikom
	if (h) *h = ResultHinted();

 }

// ---------------------------------------------------------------------------
 void Times::Start() {

	resetFlags();
	 first = timeGetTime();
	 f = 1;
	 if (QueryPerformanceFrequency(&lpFrequency) != 0)
		 QueryPerformanceCounter(&lpStart);
 }

// ---------------------------------------------------------------------------
 void Times::Pause() {
	 lpPause();
	 stoped = timeGetTime();
 }

// ---------------------------------------------------------------------------
 void Times::Continue() {
	 first += timeGetTime() - stoped;
	 lpContinue();
 }

// ---------------------------------------------------------------------------
 void Times::Stop() {
	 QueryPerformanceCounter(&lpEnd);
	 second = timeGetTime();
	 s = 1;
 } // Calculate()  musi byc po s = 1;


// ---------------------------------------------------------------------------
 void __fastcall Times::lpPause() {

	 if (p == true)	ShowMessage("Pause method already use");

	QueryPerformanceCounter(&lpFrequency);
	QueryPerformanceCounter(&lpEnd);
	QueryPerformanceCounter(&lpEnd);
	p = 1;

	unique_ptr<double> Frequency(new double(lpFrequency.QuadPart));
	unique_ptr<double> Start(new double(lpStart.QuadPart));
	unique_ptr<double> End(new double(lpEnd.QuadPart));

//	if (*Frequency != 0)
	starttopaused = (*End - *Start) / *Frequency;
//	else throw Exception("class Times::lpPause() Frequency = 0 ");

 }
// ---------------------------------------------------------------------------
 void __fastcall Times::lpContinue() {

	if ( p == 0 ) ShowMessage("You forgot use Pause() method");
	if ( c == 1 ) ShowMessage("Continue method already use");

	c = 1;
	QueryPerformanceCounter(&lpStart);

   }
 // ---------------------------------------------------------------------------
 void Times::checkuse() {

	if ( f && s ) Calculate();                                                   // jeœli obydwa warunki spe³nione

	if ( !f ) formated = "You forgot use Start() method";
	if ( !s ) formated = "You forgot use Stop() method";
	if ( p && !c )  formated = ("You forgot use Continue method");
	if ( !p && c )  formated = ("You forgot use Pause method");

//	if ( p && !c )  ShowMessage("You forgot use Continue method");
//	if ( !p && c )  ShowMessage("You forgot use Pause method");
 }

// ---------------------------------------------------------------------------
 String Times::Result() {

	 checkuse();

	 return formated;
 }
// ---------------------------------------------------------------------------
 void erasezeros(String &toclean) {

	if (toclean.SubString1(toclean.Length(),1) == "0")	toclean.Delete( toclean.Length(), 1);
	if (toclean.SubString1(toclean.Length(),1) == "0")	toclean.Delete( toclean.Length(), 1);
	if (toclean.SubString1(toclean.Length(),1) == "0")	toclean.Delete( toclean.Length(), 1);
	if (toclean.SubString1(toclean.Length(),1) == ",")	toclean.Delete( toclean.Length(), 1);
 }

// ---------------------------------------------------------------------------

 void Times::AddDelim(String &result, unsigned char & count) {

  if (count >= 0)
	if (count <= 3) {

			result.Insert(",", 4 - count);
			result.Delete(result.Pos(",") + precisionhint + 1, 18);
			erasezeros(result);
			result.Insert(" milisec", result.Length() + 1);
		}
		else if (count < 6) {

			result.Insert(",", 7 - count);
			result.Delete(result.Pos(",") + precisionhint + 1, 18);
			erasezeros(result);
			result.Insert("mikrosec", result.Length() + 1);
		}
		else if (count < 9) {

			result.Insert(",", 10 - count);
			result.Delete(result.Pos(",") + precisionhint + 1, 18);
			erasezeros(result);
			result.Insert(" nanosec", result.Length() + 1);
		}

}

// ---------------------------------------------------------------------------
  String Times::ResultHinted() {

//	TDateTime Dt;
//		Dt = FileDateToDateTime(seconds);
//
//   ShowMessage(Dt.Val);

	checkuse();

	unique_ptr<unsigned char> count(new unsigned char(0));
	unique_ptr<String> buff(new String(formated));
	unique_ptr<String> result(new String(""));

	if (seconds >= 1) {

	*result = (*buff).SubString(1, (*buff).Pos(":")-1 ) + "h ";                 // godziny
	(*buff).Delete(1,(*buff).Pos(":"));                                                        // usuwa dwukropek

	*result += (*buff).SubString(1, (*buff).Pos(":")-1 )  + "m ";               // minuty
	(*buff).Delete(1,(*buff).Pos(":"));

	*result += (*buff).SubString(1, (*buff).Pos(".")-1 ) + "s ";                // sekundy
	(*buff).Delete(1,(*buff).Pos("."));

	(*buff).Delete( 4,255 ) ;
	if ( (*buff).operator [](1) == '0' ) (*buff).Delete(1,1);                   // usuwanie zer od przodu (milisekundy)
	if ( (*buff).operator [](1) == '0' ) (*buff).Delete(1,1);
	if ( (*buff).operator [](1) == '0' ) (*buff).Delete(1,1);
	
	*result += *buff + "mils ";             									// milisekundy

	if ((*result).SubString(1,3) == "00h") (*result).Delete(1,3);
	if ((*result).SubString(1,1) == " ") (*result).Delete(1,1);
	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);                 // usuwanie zer przed minutami
	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);
	if ((*result).SubString(1,1) == "m") (*result).Delete(1,1);
	if ((*result).SubString(1,1) == " ") (*result).Delete(1,1);
	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);                 // usuwanie zer pred sekundami
	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);
	if ((*result).SubString(1,1) == "s") (*result).Delete(1,1);
//	if ((*result).SubString(1,1) == " ") (*result).Delete(1,1);                 // teoretycznie nie potrzebne
//	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);
//	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);
//	if ((*result).SubString(1,1) == "0") (*result).Delete(1,1);

	  return *result;

	} else {                                                                    // poni¿ej 1 sekundy

		*buff = FloatToStrF(seconds, ffFixed, 18, 18);

		(*buff).Delete(1, 2);                                                   // usuwa "0,"

		while( (*buff).operator [](1) == '0') {                                 // a¿ usunie wszystkie zera (na pocz¹tku)  // String result[0]

			(*buff).Delete(1, 1);
			(*count)++;
			if (*count > 15) break;                                             // zabezpieczenie przed pêtl¹ inf

		}

		AddDelim(*buff, *count);
	}

   return *buff;
 }
// ---------------------------------------------------------------------------
 String Times::ResultInSeconds() {

	checkuse();
	// jeœli start lub koniec
	if ( !f || !s ) return formated;                                          	// jeœli jeden warunek niespe³niony

   return seconds;
 }

// ---------------------------------------------------------------------------
 String ResultFloatToStrF( TFloatFormat Format,	int Precision, int Digits, const TFormatSettings & AFormatSettings) {

 }
// ---------------------------------------------------------------------------
 #ifdef _FSTREAM_H_
 void Times::ResultToFile(String Name) {

	 checkuse();

	 seconds = ResultInSeconds().ToDouble();
	 // ShowMessage(seconds);
	 (*ofs).open((Name + ".txt").c_str(), ios::out | ios::app);

	 *ofs << // setprecision(27)  <<
		 ((AnsiString)FloatToStrF(seconds, ffFixed, 18, 18)).c_str() << endl;

	 (*ofs).close();

 }
#endif
 // ---------------------------------------------------------------------------

#pragma package(smart_init)
