// ---------------------------------------------------------------------------

#ifndef floatingH
#define floatingH

#include "Unit1.h"

// ---------------------------------------------------------------------------

 class TFloatFI {

	double wy[7], historia[2]; 						// zmienne_pomocnicze, historia_undo(nie okodowane)

	void calc( double raw_value );           		// oblicza wzglêdem wy[0] (parametr)

	void show( );                            		// wypisuje zmienne do TEditów w Fibonaccim (Zawansowane)
	void showRound( ); 								// jak wy¿ej dodatkowo zaokr¹gla, u¿ywane przez publiczn¹ metodê Show();

	void tag_switch ( TComponent* );                // po nr Tag rozpoznaje obiekt i ustawia wy[0] do obliczeñ

	double GetValue_TEdit( TEdit* );
	double GetValue_TCSpinButton( TCSpinButton* );

 public:

//	double *w_in;

	bool round;										// zaokr¹glanie przy wyœwietlaniu

	// deklareacja wskaŸników na funkcje ( zamys³: zwiêkszenie wydajnoœci )

	typedef void( TFloatFI::*fcn_ptr  ) ( ); 		// obliczanie

//	typedef void( TFloatFI::*view_ptr ) ( ); 		// wypisywanie

	void calculate( );                              // oblicza wzglêdem FibonacciR->wej

	void Show( );                                  	// publiczna metoda uruchamia wyœwietlanie wzglêdem flagi Round

	void Key_Down( TEdit* );						// przy wciœniêciu klawisza
	void Key_Up( TEdit* );							// przy zwolnieniu klawisza ( Show() )

	void incerment( TEdit* );       				// przez nr Tag (param) obiektu inkrementuje wartoœæ i resztê
	void decerment( TEdit* );

	void incerment( TCSpinButton*  );       		// przez nr Tag (param) inkrementuje wartoœæ i resztê
	void decerment( TCSpinButton*  );

	void save( );

	TFloatFI( );

 };

// ---------------------------------------------------------------------------
#endif
