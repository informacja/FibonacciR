#ifndef KlasyH
#define KlasyH

#include "Enum.h"

//---------------------------------------------------------------------------

 class Przepis_na {


		float wy[6];                           // lpobrana, bufor_do_obliczeñ

//		int rodzaj_formatowania_eksportu, historia;      //

	public:

		typedef void (Przepis_na::*fcn_ptr)();

		void oblicz();        // oblicz i wpisuje do zmiennych wy1...

		void zapisz(); 		  // zapisuje do pliku

		int toint(float);     // ogólne dla wszystkich zmiennych float zwraca int

		void toint(); 	   	  // zamiania float na int(dla zak³adki Liczby Calkowite)

		void wypisz();        // wype³nia wszystkie pola wynikami z wy[]

		friend void SaveToFile();

 };

//---------------------------------------------------------------------------

 class Doubcl {

		double wy[7], historia[2];                            // bufor_do_obliczeñ

	public:

		typedef void (Doubcl::*fcn_ptr)();                                      // obliczanie

		typedef void (Doubcl::*view_ptr)();                                     // wypisywanie

		void oblicz();

		void wypisz();

		void wypiszRound();   													// jak wy¿ej dodatkowo zaokr¹gla

		void incerment( unsigned tag_nr );
		void decerment( unsigned tag_nr );

		void zapisz();
 };

//---------------------------------------------------------------------------

 class U {                                                                      // SINGLETON

//		unsigned stream_name: 2;   //nazwa zapisywanego strumienia
	//	unsigned second:1;
	//	unsigned 3_rd:2;
	//
	//	--->bool zpfolder, zpstream;          //zapisu przez


		static String dopisek, zpath;

		static short first_open;


	public:

		U();

		static stream_name_tag 	  namepref;

		static stream_path_tag 	  pathpref;

		static stream_logfile_tag logpref;

//		static unsigned int pr;

		static String logpath;


		static void SavePref();         										// przepisuje ustawienia do powy¿szych

		static String ApplyPref1( String file_name = "" );   							// nazwa

		static String ApplyPref2( String file_path = "" );   							// œcie¿ka zapisu

		static void SaveLog( AnsiString path_save = zpath,

		AnsiString name_save = "NoName", AnsiString CopyFromPath = "Not Defined");    	//plik log

 };

//---------------------------------------------------------------------------

#endif
