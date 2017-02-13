//---------------------------------------------------------------------------

#ifndef SingletonH
#define SingletonH
#include "Func.h"
#include "Times.h"
#include <vector>
//#include "Point_Form.h"

class Times;
class License_validate;
class TWPoint;
struct pos;
#define S Singleton                                                             // makro

// ---------------------------------------------------------------------------

class Singleton
{
private:
	Singleton();
	Singleton( const Singleton & );
public:
	static Singleton & getSingleton()
	{
		static Singleton singleton;
        return singleton;
	}

	static TStatusBar *ptr;
	static TImageList *iconlist_small;
	static TImageList *iconlist_large;



	static unsigned ICO_DATA;
	static unsigned ICO_ZONE_ID;
	static Times T;
	static String Fr;						// Format zapisu do pliku
	static double increment_value; 			// wartoœæ inkrementacji

//	static unsigned ICO_EMPTY;

	static bool ProVersion;
	static bool Activated;
	static bool SaveToReg;

	static String WinDir;			// Œcie¿ka do domyœlnie C:\Windows
	static String NAMEcalc;			// nazwa pliku z wynikami z ( dwie pierwsze zak³adki )
	static String NAMElog;  		// nazwa pliku log
	static String NAMEscreen;		// nazwa pliku screena ekranu
	static String FirmName;         // Hera
	static String ProductName;		// FibonacciR

	static unsigned BREAK_SEARCH;  	// liczba plików po której zapyta czy szukaæ nadal
	static unsigned char MAX_DEPTH;	// na ile podfolderów przeszukiwaæ
	static String FiltrSearch;     	// przy wyszukiwaniu ADS i plików

	static bool sDirectionSort;			// sterowanie list¹, kierunek sortowania
public:
	static License_validate *License;			// globalny wskaŸnik na w¹tek



//	static int *ImgIndexSync;
	static String test;     	// przy wyszukiwaniu ADS i plików
	static bool Del_only_one_sign;



	static void Status( String TextInfo, unsigned PanelIndex_0 = 0, bool Hint_0 = 0);
	static AnsiString BreakQuest();

	static void ProgressBarStyle(bool ver, bool mar);

	static bool canData();
	static bool canZID();
	static bool canHide();

	static void Save( bool save );




	void metoda1();
	void metoda2( int argument );
	int metoda3( int argument );
	int met(int);
};

// ---------------------------------------------------------------------------

String GetWinDir( String s) {

	unique_ptr<wchar_t> buffer(new wchar_t[30]);
	GetSystemWindowsDirectory(buffer.get(), 30);                                // pobieranie œcie¿ki do %windir%
	s = buffer.get();
	return s;
}

// ---------------------------------------------------------------------------

#endif
