FILE *F;
  char MyData[2047];
  long BytesRead;

  F = fopen("../about.txt", "r");   // path relative to Debug
									// use a file larger than 2048 bytes to make it interesting.
  if (F)
  {
	struct stat statbuf;
	fstat(fileno(F), &statbuf);
	ProgressBar1->Max = statbuf.st_size;
	if (ProgressBar1->Max > 10)
	{
	  ProgressBar1->Step = (ProgressBar1->Max)/10;
//	  ProgressBar1->Step = Min(ProgressBar1->Step, 2047);
	}
	else
	  ProgressBar1->Step = ProgressBar1->Max;
	std::auto_ptr<char> DataBuffer(new char[ProgressBar1->Step]);
	for (ProgressBar1->Position = 0;
		 ProgressBar1->Position < ProgressBar1->Max;
		 ProgressBar1->StepIt())  // move the ProgressBar Position using StepIt
	{
	  fread(DataBuffer.get(), ProgressBar1->Step, 1, F);
	  // Do this or the read will wrap and start over!
//      ProgressBar1->Step =
//		Min(ProgressBar1->Step, ProgressBar1->Max - ProgressBar1->Position);
	}
	fclose(F);
  }

//// From MSDN

//private:
//   void CopyWithProgress( array<String^>^filenames )
//   {
//	  // Display the ProgressBar control.
//	  pBar1->Visible = true;
//
//	  // Set Minimum to 1 to represent the first file being copied.
//	  pBar1->Minimum = 1;
//
//	  // Set Maximum to the total number of files to copy.
//	  pBar1->Maximum = filenames->Length;
//
//	  // Set the initial value of the ProgressBar.
//	  pBar1->Value = 1;
//
//	  // Set the Step property to a value of 1 to represent each file being copied.
//	  pBar1->Step = 1;
//
//	  // Loop through all files to copy.
//	  for ( int x = 1; x <= filenames->Length; x++ )
//	  {
//		 // Copy the file and increment the ProgressBar if successful.
//		 if ( CopyFile( filenames[ x - 1 ] ) == true )
//		 {
//			// Perform the increment on the ProgressBar.
//			pBar1->PerformStep();
//		 }
//	  }
//   }

//zapisywanie ustawień w jednej zmiennej
kodowanie() {

	 short int *wsk = new short int;
	 *wsk = 0;

	 if (Form2->RadioButton6->Checked) {
	 pow10(3);
//		 *wsk = pow(2, 1);
	 }
	 else if (Form2->RadioButton5->Checked) {
//		 *wsk = pow(2, 2);
	 }

	 if (Form2->RadioButton8->Checked) {
//		 *wsk += pow(2, 3);
	 }

	 if (Form2->CheckBoxULOG->Checked) {

		 if (Form2->RadioButton10->Checked) {
//			 *wsk += pow(2, 5);
		 }
		 else {
//			 *wsk += pow(2, 4);
		 }
	 }

	 U::pr = *wsk; //przypisanie wartości
	 delete wsk;
//	 ShowMessage(Ustawienia::pr);
 }
 
if (U::pr) {

		int *buff = new int;
		short int *pot = new short int;
		*pot = 5 ;

		do {



			*buff = U::pr - pow(2, (*pot));

//			if (pref==1) {
//					   Edit1->Text = Edit1->Text+" 1";
//			}

			if (*buff >= 0) {                //dla watości identycznej z potęgą

				U::pr = *buff;

				switch (*pot) {

				case 0: {               //nie powinno mieć miejsca
						Edit1->Text = Edit1->Text+" 0";
					} break;

				case 1: {
						Edit1->Text = Edit1->Text+" 1";
					} break;

				case 2: {    Edit1->Text = Edit1->Text+" 2";
					} break;

				case 3: {     Edit1->Text = Edit1->Text+" 3";
					} break;

				case 4: {     Edit1->Text = Edit1->Text+" 4";
					} break;

				case 5: {     Edit1->Text = Edit1->Text+" 5";
					} break;

				default: Edit1->Text = Edit1->Text+" default";
				}

			}


			 // dlaczego nie działa *pot--;

			 *pot -= 1;

		} while (*pot >= 0);

		delete buff, pot;
	}