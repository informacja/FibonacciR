
#include "pomoc.h"

String nowaf() {
	
	return "Działa";
}
void __fastcall TFibonacciR::FormCreate(TObject *Sender) {

	TCHAR  *buffer = new TCHAR[MAX_PATH];

	SHGetSpecialFolderPath(NULL, buffer, CSIDL_DESKTOPDIRECTORY , 0);

	EditSciezkaszukana->Text = buffer;

	delete [] buffer;
}