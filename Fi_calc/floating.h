// ---------------------------------------------------------------------------

#ifndef floatingH
#define floatingH

#include "Unit1.h"

// ---------------------------------------------------------------------------

 class TFloatFI {

	double wy[7], historia[2]; 						// zmienne_pomocnicze, historia_undo(nie okodowane)

	void calc( double raw_value );           		// oblicza wzgl�dem wy[0] (parametr)

	void show( );                            		// wypisuje zmienne do TEdit�w w Fibonaccim (Zawansowane)
	void showRound( ); 								// jak wy�ej dodatkowo zaokr�gla, u�ywane przez publiczn� metod� Show();

	void tag_switch ( TComponent* );                // po nr Tag rozpoznaje obiekt i ustawia wy[0] do oblicze�

	double GetValue_TEdit( TEdit* );
	double GetValue_TCSpinButton( TCSpinButton* );

 public:

//	double *w_in;

	bool round;										// zaokr�glanie przy wy�wietlaniu

	// deklareacja wska�nik�w na funkcje ( zamys�: zwi�kszenie wydajno�ci )

	typedef void( TFloatFI::*fcn_ptr  ) ( ); 		// obliczanie

//	typedef void( TFloatFI::*view_ptr ) ( ); 		// wypisywanie

	void calculate( );                              // oblicza wzgl�dem FibonacciR->wej

	void Show( );                                  	// publiczna metoda uruchamia wy�wietlanie wzgl�dem flagi Round

	void Key_Down( TEdit* );						// przy wci�ni�ciu klawisza
	void Key_Up( TEdit* );							// przy zwolnieniu klawisza ( Show() )

	void incerment( TEdit* );       				// przez nr Tag (param) obiektu inkrementuje warto�� i reszt�
	void decerment( TEdit* );

	void incerment( TCSpinButton*  );       		// przez nr Tag (param) inkrementuje warto�� i reszt�
	void decerment( TCSpinButton*  );

	void save( );

	TFloatFI( );

 };

// ---------------------------------------------------------------------------
#endif
