
#ifndef GenericH
#define GenericH

#include "Unit1.h"
// ---------------------------------------------------------------------------

template<typename T>

inline int ToInt(T liczba) {

	liczba = (liczba -static_cast<int>(liczba) >= 0.5) ?

		static_cast<int>(liczba) + 1 : static_cast<int>(liczba);

	return liczba;
}

// ---------------------------------------------------------------------------

template<typename T>
T TrimT(T* w) { 															// Trim Total (usuwa wszystkie puste pola z stringa)

	unique_ptr<unsigned short> rd(new unsigned short((*w).LastDelimiter(" ") ));

	  while ( *rd ) {

			(*w).Delete(*rd, 1);

			*rd = (*w).LastDelimiter(" ");

	  }





//	unique_ptr<unsigned short>rd(new unsigned short(*w).LastDelimiter(" "));
//
//	do {
//		(*w).Delete(*rd, 1);
//
//		*rd = (*w).LastDelimiter(" ");
//	}
//	while (*rd);

	return *w;
}

// ---------------------------------------------------------------------------

template<class T>
class Tablica {
protected:
	unsigned rozmiar;
	T *tp;

public:
	Tablica(unsigned roz = 12);

	T &operator[](unsigned indeks) {
		return *(tp + indeks);
	}

	~Tablica() {
		delete[]tp;
	}
};

// ---------------------------------------------------------------------------

template<class T>
Tablica<T>::Tablica(unsigned roz) {
	tp = new T[rozmiar = roz];
	for (int i = 0; i < rozmiar; i++)
		* (tp + i) = 0;
}
// ---------------------------------------------------------------------------


// template <typename T, typename>
template <typename T>
 int FindOut(  T a... ) {
		  //T where, T what,
	unique_ptr<unsigned char> count(new unsigned char(0));                      // liczba parametrów(what), zwraca iloœæ znaleŸonych w where
//	unique_ptr<char[]> buff(new char[sizeof(what)+1]);
	char* str = NULL; // = ((AnsiString)what).c_str();
//	T* str = &what;
	va_list vl;
//			  ShowMessage(sizeof(where));
//  char *str ;
//  str = buff[];
//  const unsigned numargs = sizeof...(Arguments);

  va_start(vl,a);

  str = (char*)12;
//  ShowMessage( a );

  do {

	 ShowMessage( (int)va_arg(vl, T ) + " \n" +(int) sizeof(a) );

//	*str = va_arg(vl, T );
	(*count)++;
//	ShowMessage(*str);
  } while (str != NULL);

  va_end(vl);

  return *count;
// String *first = &what;
//
//	va_list vl;
//
//	va_start(vl, what);
//
//	do {
//
//		ShowMessage(*(String*)vl);
//		first = va_arg(vl,String*);
//
//	}while (first != NULL);
//
//	 va_end(*vl);
//
//	 return 1;

 }

  template <typename T>
 void Show( T a) {
	 ShowMessage( a );
 }
#endif


