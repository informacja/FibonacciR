// from FibonacciR 

//---------------------------------------------------------------------------

void __fastcall TFibonacciR::ComboBox1Change(TObject *Sender) {

	char aName[255];
	char aFileSystem[255];
//	DWORD dwTemp;   0,0

	AnsiString ldysku = ExtractFileDrive(ComboBox1->Text);

	GetVolumeInformationA( (ldysku + "\\").c_str(), aName, sizeof(&aName), NULL, 0, 0,
													aFileSystem, sizeof(&aFileSystem));
	Label2->Caption = aFileSystem;

//   delete [] aName, aFileSystem;

 Label2Click(Sender); //musi być na końcu  (kolorowanie)
 }

//---------------------------------------------------------------------------
 
 void __fastcall TFibonacciR::Label2Click(TObject *Sender) {

	Label2->Font->Color = ( Label2->Caption == "NTFS" ) ? clGreen : clRed;
}


//---------------------------------------------------------------------------
 void __fastcall TFibonacciR::ComboBox1Change(TObject *Sender) {

	char aName[255];
	char aFileSystem[255];
//	DWORD dwTemp;   0,0

	AnsiString ldysku = ExtractFileDrive(ComboBox1->Text);

	GetVolumeInformationA( (ldysku + "\\").c_str(), aName, sizeof(&aName), NULL, 0, 0,
													aFileSystem, sizeof(&aFileSystem));
	Label2->Caption = aFileSystem;

//   delete [] aName, aFileSystem;

 Label2Click(Sender); //musi być na końcu  (kolorowanie)
 }

//---------------------------------------------------------------------------
void __fastcall TFibonacciR::TabSheet5Enter(TObject *Sender) {
	// ComboBox1->Clear();
	EnumDrivers(ComboBox1->Items);
	// Label2->Caption="";
}
//---------------------------------------------------------------------------