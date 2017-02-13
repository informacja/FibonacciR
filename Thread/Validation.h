//---------------------------------------------------------------------------

#ifndef ValidationH
#define ValidationH

#include <Classes.hpp>
#include <Registry.hpp>

//---------------------------------------------------------------------------

 int Check_License( );                 	// Funkcja wywo³ywana z zewn¹trz automatycznie sprz¹ta po w¹tku

//---------------------------------------------------------------------------

 class License_validate : public TThread
 {
	 int Zmienna_testowa; 				// Przyk³adowa zmienna

	 String s_md5_license[3];          	// [0] bios, [1] drive, [2] monitor
//     string tmp1;
   public:
	 int bios();                        // data biosu
	 int drive();						// numer seryjny dysku
	 int monitor();                     // numer seryjny monitora

	 bool save_license_to_Reg();
	 bool get_license_from_Reg();

	 void __fastcall Execute();				// G³ówna procedura dzia³ania w¹tku

 public:

//	 void sth();
	 __fastcall License_validate(bool CreateSuspended); // Tworzenie w¹tku
	 __fastcall ~License_validate();                     	// Niszczenie w¹tku
 };

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#endif
