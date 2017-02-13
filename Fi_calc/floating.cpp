//---------------------------------------------------------------------------

#pragma hdrstop

#include "floating.h"
#include "Hera\\Singleton.h"
//---------------------------------------------------------------------------
				   
 TFloatFI::TFloatFI() {

	memset( wy, 0, sizeof(wy) );
	round = true;
	Show();
 }
// ---------------------------------------------------------------------------

 void TFloatFI::calculate( ) {

	try {

//		unique_ptr<double> w(new double( FibonacciR->wej->Text.ToDouble() ));
//		wy[0] = *w;

		unique_ptr<double> w(new double( FibonacciR->wej->Text.ToDouble() ));
		*w = wy[0];

		wy[2] = *w * FI;
		wy[1] = *(w) - wy[2];
		wy[3] = *w + wy[2];
		wy[4] = 2 * *w + wy[2];
										// (int)*w << 1) nie stosowaæ (niedok³adne dla zmienno przecinkowych)
		wy[5] = 2 * *w * FI;
		wy[6] = wy[5] - *w;

		}

	  catch (EConvertError &ConvertErr) {

		  curpos = FibonacciR->wej->SelStart;

			 if ( FibonacciR->wej->Text == "" ) {                               // jeœli nie ma co obliczyæ (pusta wartoœæ)

				FibonacciR->wej->Text = 0;
				calculate();
				Show();

				FibonacciR->StatusInfo("Pole nie mo¿e byæ puste");

				FibonacciR->wej->Perform(EM_SETSEL, curpos, curpos+1);      	// zaznacza zero

			 } else {                                                        	// jest przekazana nietypowa zawatoœæ

				 FibonacciR->wej->Text = DigitRewrite(FibonacciR->wej->Text, 1, 1);
				 calculate();
				 Show();
				 FibonacciR->StatusInfo("B³¹d konwersji: " + ConvertErr.ToString());

				FibonacciR->wej->Perform(EM_SETSEL, curpos-1, curpos-1);
			}
	   }
	  catch (...) {

		ShowError("Nieznany b³¹d w sekcji TFloatFI::oblicz()");
	  }
 }
 //---------------------------------------------------------------------------

  void TFloatFI::calc( double w ) {

//	try {

//		unique_ptr<double> w(new double( FibonacciR->wej->Text.ToDouble() ));
		wy[0] = w;

		wy[2] = w * FI;
		wy[1] = w - wy[2];
		wy[3] = w + wy[2];
		wy[4] = 2 * w + wy[2];
										// (int)*w << 1) nie stosowaæ (niedok³adne dla zmienno przecinkowych)
		wy[5] = 2 * w * FI;
		wy[6] = wy[5] - w;

		}

// ---------------------------------------------------------------------------

 void TFloatFI::Show( ) {

	if ( round ) showRound();	else	show();

 }

// ---------------------------------------------------------------------------

 void TFloatFI::show( ) {

	 FibonacciR->wej->Text = wy[0];
	 FibonacciR->wy1->Text = wy[1];
	 FibonacciR->wy2->Text = wy[2];
	 FibonacciR->wy3->Text = wy[3];
	 FibonacciR->wy4->Text = wy[4];
	 FibonacciR->wy5->Text = wy[5];
	 FibonacciR->wy6->Text = wy[6];

 }
//---------------------------------------------------------------------------

 void TFloatFI::showRound( ) {

	 FibonacciR->wej->Text = Round(wy[0]);
	 FibonacciR->wy1->Text = Round(wy[1]);
	 FibonacciR->wy2->Text = Round(wy[2]);
	 FibonacciR->wy3->Text = Round(wy[3]);
	 FibonacciR->wy4->Text = Round(wy[4]);
	 FibonacciR->wy5->Text = Round(wy[5]);
	 FibonacciR->wy6->Text = Round(wy[6]);
 }
//---------------------------------------------------------------------------
 void TFloatFI::Key_Down( TEdit* ) {

 }
//---------------------------------------------------------------------------
 
 void TFloatFI::Key_Up( TEdit* obj ) {

	if ( TryStrToFloat(obj->Text, wy[0]) ) ;                                    // do nothing
	else wy[0] = DigitRewrite( obj->Text ).ToDouble();

	tag_switch( obj );


//	calc()
//    calculate();

	Show();
 
 }
// ---------------------------------------------------------------------------

 void TFloatFI::incerment( TEdit * obj ) {
				
	if ( (*obj).ToString() != "TEdit" ) ShowError( "Wrong object from TFloatFI::incerment_TEdit( TObject* ) is " + (*obj).ToString() );

	curpos = obj->SelStart;

	wy[0] = GetValue_TEdit( obj  ); 	// konwertuje wartoœæ Text na double
 
	wy[0] += S::increment_value;         			// inkrementacja
	
	tag_switch( obj );  	// na podstawie nr_Tag obiektu, u¿ywa zmiennej wy[0] ustawionej powy¿ej

	obj->Perform(EM_SETSEL, curpos + 1, curpos + 1);

	Show();
}

// ---------------------------------------------------------------------------

 void TFloatFI::decerment( TEdit * obj ) {

	curpos = obj->SelStart;

	wy[0] = GetValue_TEdit( obj  ); 	// konwertuje wartoœæ Text na double
 
	wy[0] -= S::increment_value;         			// dekrementacja
	
	tag_switch( obj );  	// na podstawie nr_Tag obiektu, u¿ywa zmiennej wy[0] ustawionej powy¿ej

	obj->Perform(EM_SETSEL, curpos + 1, curpos + 1);

	Show();
 }

// ---------------------------------------------------------------------------

 void TFloatFI::incerment( TCSpinButton * obj ) {
			
	curpos = static_cast<TEdit*>(obj->FocusControl)->SelStart;

	wy[0] = GetValue_TCSpinButton( obj ); 		// konwertuje wartoœæ Text na double
 
	wy[0] += S::increment_value;
	
	tag_switch( obj );  	// na podstawie nr_Tag obiektu, u¿ywa zmiennej wy[0] ustawionej powy¿ej

	static_cast<TEdit*>(obj->FocusControl)->Perform(EM_SETSEL, curpos + 1, curpos + 1);

	Show();
 }
	
// ---------------------------------------------------------------------------

 void TFloatFI::decerment( TCSpinButton * obj ) {

	curpos = static_cast<TEdit*>(obj->FocusControl)->SelStart;

	wy[0] = GetValue_TCSpinButton( obj ); 		
 
	wy[0] -= S::increment_value;
	
	tag_switch( obj );  	// na podstawie nr_Tag obiektu, u¿ywa zmiennej wy[0] ustawionej powy¿ej

	static_cast<TEdit*>(obj->FocusControl)->Perform(EM_SETSEL, curpos + 1, curpos + 1);

	Show();
 }

//---------------------------------------------------------------------------

 void TFloatFI::tag_switch ( TComponent* obj) {

	 switch ( obj->Tag ) {

	 case 1:	 calc(wy[0]);		 		   	break;
	 case 2:     calc(wy[0] / FI / FI);		   	break;
	 case 3:     calc(wy[0] / FI);				break;
	 case 4:     calc(wy[0] / FI - wy[0]);	   	break;
	 case 5:     calc(wy[0] * FI * FI);        	break;
	 case 6:  	 calc(wy[0] / 2 / FI);         	break;
	 case 7:  	 calc(wy[0] / FI * 2 + wy[0]); 	break;
		 
	 default:
		 ShowError("Brak taga nr: " + obj->Tag);
	 }
 }

// ---------------------------------------------------------------------------

 double TFloatFI::GetValue_TEdit( TEdit* obj ) {

	 try {
		 return obj->Text.ToDouble();
	 }
	 catch (...) {
		 return DigitRewrite(obj->Text).ToDouble();
	 }
 }

// ---------------------------------------------------------------------------

 double TFloatFI::GetValue_TCSpinButton( TCSpinButton* obj) {

	 try {
		 return reinterpret_cast<TEdit*>(obj->FocusControl)->Text.ToDouble();
	 }
	 catch (...) {
		 return DigitRewrite(reinterpret_cast<TEdit*>(obj->FocusControl)->Text).ToDouble();
	 }
 }

// ---------------------------------------------------------------------------
 
 void TFloatFI::save( ) {

//  if (FibonacciR->wej1->Value == 0) return;

// calculate();

  try {

	unique_ptr<ofstream> wyniki(new ofstream);
	unique_ptr<unsigned char> l(new unsigned char(S::Fr.Length() + Form2->SpinEditFill->Value));

		 (*wyniki).open( (S::NAMEcalc + ".txt").c_str(), ios::out | ios::app);

		 *wyniki << "Dla " << setw( 9 ) << wy[0] << " wyliczono :  " << internal;

if (Form2->CheckBoxZ1->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[1] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ2->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[2] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ3->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[3] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ4->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[4] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ5->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[5] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";
if (Form2->CheckBoxZ6->Checked) *wyniki << setw(*l) << ((AnsiString)FormatFloat( S::Fr , wy[6] )).c_str() << " " ; else *wyniki << setw(*l + 1) << "";

		 *wyniki << endl;
//
//		 (*wyniki).open("Wyniki.txt", ios::out | ios::app);
//
//		 *wyniki << "Dla " <<
//			 // wyniki.width(20)<<
//			 internal <<
//
//			 // <<setfill (' ')
//			 setw(12) << NULL <<
//			 // FormatFloat( '#' ,lpobrana)<<setprecision(2)<<
//			 // wyniki.width(19 - lenght)<<
//			 " wyliczono :  ";
//		 if (Form2->CheckBoxZ1->Checked) {
//
//			 *wyniki << wy[0] << " " << setw(7) ;
//		  }
//		 // internal << wyj[1] << " "<<
//		 // wyniki.width(bv + 2)<<
//		 // wyniki << right << wyj[2] << " "<<
//		 // wyniki.width(bv + 3)<<
//
//		 if (Form2->CheckBoxZ2->Checked) {
//
////			 *wyniki << CurrToStrF(wy[1], ffFixed, 4) << " " << setw(7) ;
//		  }
//		 if (Form2->CheckBoxZ3->Checked) {
//
//			 *wyniki << wy[2] << " " << setw(7);
//		 }
//		 if (Form2->CheckBoxZ4->Checked) {
//
//			 *wyniki << wy[3] << " " << setw(7);
//		 }
//		 if (Form2->CheckBoxZ5->Checked) {
//
//			 *wyniki << wy[4] << " " << setw(7) ;
//		  }
//		 if (Form2->CheckBoxZ6->Checked) {
//
//			 *wyniki << wy[5] << " ";
//
//		  }
//
//		 *wyniki << endl ;

		 (*wyniki).close();


  }
  catch(Exception &eError) {
		throw Exception("Przyczyna b³êdu w TFloatFI::zapisz: " + eError.Message);
	}
	catch (...) {
		ShowError("Nieznany b³¹d TFloatFI::zapisz");
	}
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
