//---------------------------------------------------------------------------

#ifndef ValidationH
#define ValidationH

#include <Classes.hpp>
#include <Registry.hpp>

//---------------------------------------------------------------------------

 int Check_License( );                 	// Funkcja wywo�ywana z zewn�trz automatycznie sprz�ta po w�tku

//---------------------------------------------------------------------------

 class License_validate : public TThread
 {
	 int Zmienna_testowa; 				// Przyk�adowa zmienna

	 String s_md5_license[3];          	// [0] bios, [1] drive, [2] monitor
//     string tmp1;
   public:
	 int bios();                        // data biosu
	 int drive();						// numer seryjny dysku
	 int monitor();                     // numer seryjny monitora

	 bool save_license_to_Reg();
	 bool get_license_from_Reg();

	 void __fastcall Execute();				// G��wna procedura dzia�ania w�tku

 public:

//	 void sth();
	 __fastcall License_validate(bool CreateSuspended); // Tworzenie w�tku
	 __fastcall ~License_validate();                     	// Niszczenie w�tku
 };

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#endif
