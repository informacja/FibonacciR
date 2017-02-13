//---------------------------------------------------------------------------

#ifndef TimesH
#define TimesH

//---------------------------------------------------------------------------
											// If  <fstream.h> not include, func based on file read\write
#include <fstream.h>   	   	// ofstream     // like ResultToFile() will be not compile
#include <Windows.h>        // DWORD
#include <Vcl.Dialogs.hpp>  // ShowMessage
#include <memory>      		// unique_ptr
#include <System.hpp>		// String
	/* OR */
//#include <Vcl.Samples.Spin.hpp>	// String // if  <System.hpp> not available
//#include <clipbrd.hpp>         	// String
//#include <SysInit.hpp>         	// String

//---------------------------------------------------------------------------

  class Times {

	TObject* obj;                                                               // object on whose will be displayed
	String formated;                                                            // result formated
	unsigned char precisionhint;                                                // wartoœæ w podpowiedzi po przecinku
	DWORD first, second, stoped, result;                                        // for low precision 0.000
	double seconds, starttopaused;                                              // var allways in seconds
	bool f, s, p, c, hint;                                                      // flags, witch can be use method result()
	// first, second, pause, contiue, usehint
	LARGE_INTEGER lpFrequency, lpStart, lpEnd, lpStoped;
	#ifdef _FSTREAM_H_
	ofstream *ofs;
	#endif

	inline void new_ofstream();
	void Calculate();
	void FormatMilisec(String* __inout attoseconds, bool __in hint_0 = 0);
	void __fastcall lpPause();                                                  // For LARGE_INTEGER
	void __fastcall lpContinue();
	void AddDelim(String &result, unsigned char & count);
	void checkuse();                                                            // check whith programist use Start() method and Stop() or Show()

   public:

	Times();
	Times( TObject* toShowResult );

	~Times(); // if you can define default object, on destruct result time will be showed there

	void reset(TObject* toShowResult = NULL);                                   // asign difrent object to display result time
	void resetFlags();

	void Start();
	void Pause();
	void Continue();
	void Stop();

	// you can use methods below without Stop() method, it works automaticly    // show results on
	void Show( TObject* to_set_text_and_hint);                                  // defined object
	void Show( String* raw_text, String *hinted_text_0 = 0);                    // paste default formated time, with hint text                                      		// mo¿na u¿ywaæ zastepczo dla stop
	void Show( ); 																// if object defined in constructor displayed on it

//	double Result();
	String Result();
	String ResultHinted();
	String ResultInSeconds();
	String ResultFloatToStrF( TFloatFormat Format,
		int Precision, int Digits, const TFormatSettings & AFormatSettings);
	#ifdef _FSTREAM_H_
	void ResultToFile(String FileName);
//	void // Œrednia z pliku
	#endif

   };

//---------------------------------------------------------------------------

#endif

/*

Tips:

	You shouldn't use Pause & Continue method,
	if measure code work time's shorter than 1 second.

	If measure must be sensisitve, use Stop() method instead of Show()

///////////////////////		  Code Examples        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Times T;
String work_time;

T.Start();

T.Pause();

Sleep(1000);        	// waint second

T.Continue();

T.Stop(); 				// You can use Stop method, but T.Show() doing it automaticly

work_time = T.Result();
ShowMessage(work_time);

T.Show(Memo1);         	// wyœwietla na zmiennej Text obiektu Memo oraz zmienia wartoœæ Hint
T.Show(StatusBar1);    	// wyœwietla na PANELU o numerze 1 (mo¿liwoœæ edycji w kodzie Ÿród³owym)

////////////////////////////////////////////////////////////////////////////////


// testowano dla komponentów : TMemo, TStatusBar, TEdit, TLabel

*/

