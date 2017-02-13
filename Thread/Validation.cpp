//---------------------------------------------------------------------------

#pragma hdrstop

#include "Validation.h"
#include "Singleton.h"
#include "md5.h"

//class Singleton;
//extern Singleton::License;

//---------------------------------------------------------------------------

int Check_License( )
{
	if( Singleton::License == NULL )		// Jeœli w¹tku nie ma, to go stwórz
	{
		S::License  = new License_validate( true );	// Tutaj tworzymy w¹tek, stworzony w¹tek jest uœpiony

		if ( 	S::License == NULL ) 		// Sprawdzamy, czy w¹tek uda³o siê stworzyæ poprawnie
		{          //Beep();
			ShowError( "Nie mo¿na stworzyæ w¹tku licencji!" );
		}
		else
		{
			S::License->Start();		// Startujemy w¹tek do dzia³ania
			S::License->drive();
		}
	}
	// start
//
//	License->sth();

	// przeniesione do sekcji Execute
//		if( License != NULL )			// Jeœli w¹tek istnieje, to go zamykamy (kolejne operacje)
//	{
//		License->Terminate(); 		// Wymuszamy zamkniêcie w¹tku
//		License->WaitFor();     	// Czekamy, a¿ w¹tek siê zamknie (uruchomi wszystkie destruktory, itp.)
//
//		delete License; 			// Kasujemy pamiêæ obiektu
//		License = NULL;         	// Zerujemy wskaŸnik (¿eby nastepnym razem móc znów w³¹czyæ ten w¹tek, bo po NULL sprawdzamy, czy w¹tej jest, czy go nie ma)
//	}

	return 0;
}

//---------------------------------------------------------------------------

__fastcall License_validate::License_validate( bool CreateSuspended ) : TThread( CreateSuspended ) {

	for ( int i = 0; i < sizeof(s_md5_license)/4; i++ ) s_md5_license[i];

};	// Tworzenie w¹tku

//---------------------------------------------------------------------------

__fastcall License_validate::~License_validate() {	};

//---------------------------------------------------------------------------

void __fastcall License_validate::Execute() {

	 Sleep(500);
		 Beep();

}

 //---------------------------------------------------------------------------

 int License_validate::bios()
 {
	  std::string tmp = 0;

//if (!tmp.empty())
//{
//	TBytes buf;
//	buf.Length = tmp.length();
//	memcpy(&buf[0], tmp.c_str(), buf.Length);
//	std::auto_ptr<TEncoding> enc(TEncoding::GetEncoding(DesiredCodepageHere));
//	// or: std::auto_ptr<TEncoding> enc(TEncoding::GetEncoding("DesiredCharsetHere"));
//	S = enc->GetString(buf);
//}

//	  wchar_t zakodowane = md5( 0 );
//	  s_md5_license[0] = zakodowane;
//	s_md5_license[0] = md5( 0 );

 }




   struct RawSMBIOSData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
	DWORD    Length;
    BYTE    SMBIOSTableData[];
};

 //---------------------------------------------------------------------------

 int License_validate::drive()
 {
	DWORD	FirmwareTableProviderSignature;
	DWORD	FirmwareTableID;
	RawSMBIOSData	pFirmwareTableBuffer;
	DWORD	BufferSize = sizeof(pFirmwareTableBuffer);


	GetSystemFirmwareTable(
		'ACPI', 'PCAF',
		&pFirmwareTableBuffer,
		BufferSize
	);

//	ShowMessage( pFirmwareTableBuffer.SMBIOSTableData[ 11 ]);
 }


//---------------------------------------------------------------------------

 int License_validate::monitor()
 {

 }

//---------------------------------------------------------------------------

bool License_validate::save_license_to_Reg()
{
	unique_ptr<TRegistry> Reg (new TRegistry);
										 //Hera			    //FibonacciR
	if ( Reg->OpenKey("Software\\" +  S::FirmName +"\\"+ S::ProductName + "\\" + "License", true) )
	{
		Reg->WriteString( "BIOS"	, s_md5_license[0] );
		Reg->WriteString( "DRIVE"	, s_md5_license[1] );
		Reg->WriteString( "MONITOR"	, s_md5_license[2] );
		return 1;
	}
	return 0;
}

//---------------------------------------------------------------------------

bool License_validate::get_license_from_Reg()
{
	unique_ptr<TRegistry> Reg (new TRegistry);
										 //Hera    		   //FibonacciR
	if ( Reg->OpenKey("Software\\" +  S::FirmName +"\\"+ S::ProductName + "\\" + "License", false) )
   {
	  if (Reg->ValueExists("BIOS"))		s_md5_license[0] = Reg->ReadInteger("BIOS");
	  if (Reg->ValueExists("DRIVE"))   	s_md5_license[1] = Reg->ReadInteger("DRIVE");
	  if (Reg->ValueExists("MONITOR")) 	s_md5_license[2] = Reg->ReadInteger("MONITOR");
	  return 1;
   }
   return 0;
}


//---------------------------------------------------------------------------

#pragma package(smart_init)
