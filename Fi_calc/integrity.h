#ifndef integrityH
#define integrityH

#include "Enum.h"

//---------------------------------------------------------------------------

 class TIntFI {


		float wy[6];                           // lpobrana, bufor_do_oblicze�

//		int rodzaj_formatowania_eksportu, historia;      //

	public:

		typedef void (TIntFI::*fcn_ptr)();

		void oblicz();        // oblicz i wpisuje do zmiennych wy1...

		void zapisz(); 		  // zapisuje do pliku

		int toint(float);     // og�lne dla wszystkich zmiennych float zwraca int

		void toint(); 	   	  // zamiania float na int(dla zak�adki Liczby Calkowite)

		void wypisz();        // wype�nia wszystkie pola wynikami z wy[]

		friend void SaveToFile();

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


		static void SavePref();         										// przepisuje ustawienia do powy�szych

		static String ApplyPref1( String file_name = "" );   							// nazwa

		static String ApplyPref2( String file_path = "" );   							// �cie�ka zapisu

		static void SaveLog( AnsiString path_save = zpath,

		AnsiString name_save = "NoName", AnsiString CopyFromPath = "Not Defined");    	//plik log

 };

//---------------------------------------------------------------------------

#endif
