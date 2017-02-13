/** \file
\brief Modu� podstawowy
\author Adam Sawicki - sawickiap@poczta.onet.pl - http://regedit.gamedev.pl/ \n

Cz�� biblioteki CommonLib \n
Kodowanie Windows-1250, koniec wiersza CR+LF, test: Za��� g�l� ja�� \n
Licencja: GNU GPL. \n
Dokumentacja: \ref Module_Base \n
Elementy modu�u: \ref code_base
*/
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#ifndef COMMON_BASE_H_
#define COMMON_BASE_H_

/** \addtogroup code_base Modu� Base
Dokumentacja: \ref Module_Base \n
Nag��wek: Base.hpp */
//@{

// G��wne includy
#include <cassert>
#include <string>
#include <vector>

// Niechciane includy :(
#include <limits>
#include <cmath>

#ifdef WIN32
	/// To jest na wypadek w��czania gdzie� ni�ej przez u�ytkownika <windows.h>
	#define NOMINMAX
#endif

// String chc� mie� jak typ wbudowany
using std::string;
using std::wstring;

// Niezale�nie od systemu, sygnatura bie��cej funkcji b�dzie w makrze __FUNCSIG__ - konwersja z konwencji GCC na Visual C++.
/* Makro __FUNCTION__ z sam� nazw� funkcji jest takie samo w Visual C++ jak i w GCC, wi�c go nie ruszam. */
#ifndef WIN32
	#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

// Sprawy zwi�zane z Unicode
#ifdef WIN32
	#include <tchar.h>
	#include <wchar.h>
	/// Typ znakowy, zale�nie od makra _UNICODE zdefiniowany jako char lub wchar_t.
	typedef TCHAR tchar;
#else
	#define _T(x) (x)
	typedef char tchar;
#endif

#ifdef _UNICODE
	/// Typ �a�cuchowy, zale�nie od makra _UNICODE zdefiniowany jako std::string lub std::wstring.
	typedef std::wstring tstring;
	/// Konwertuje znak na liczb� naturaln�.
	#define TCHAR_TO_INT(c) ( (int)(c) )
	/// Konwertuje liczb� 0..255 na znak.
	#define INT_TO_TCHAR(i) ( (wchar_t)(i) )
#else
	typedef std::string tstring;
	#define TCHAR_TO_INT(c) ( (int)(uint1)(c) )
	#define INT_TO_TCHAR(i) ( (char)(uint1)(i) )
#endif

/// Nazwa bie��cego pliku �r�d�owego jako �a�cuch, zale�nie od makra _UNICODE jest w Unikodzie
#define __TFILE__ _T(__FILE__)
/// Pe�na sygnatura bie��cej funkcji w kodzie, zale�nie od makra _UNICODE jest w Unikodzie
#define __TFUNCSIG__ _T(__FUNCSIG__)
/// Sama nazwa bie��cej funkcji w kodzie, zale�nie od makra _UNICODE jest w Unikodzie
#define __TFUNCTION__ _T(__FUNCTION__)

// Wy��cz g�upie warningi Visual C++
#ifdef WIN32
	// ' var ' : conversion from 'size_t' to ' type ', possible loss of data
	#pragma warning(disable: 4267)
	// 'function': was declared deprecated
	#pragma warning(disable: 4996)
#endif

/** \addtogroup base_main_types Postawowe typy danych */
//@{
#ifdef WIN32
	/// Liczba 32-bitowa bez znaku
	typedef unsigned __int32 uint;
	/// Liczba 8-bitowa ze znakiem
	typedef __int8 int1;
	/// Liczba 8-bitowa bez znaku
	typedef unsigned __int8 uint1;
	/// Liczba 16-bitowa ze znakiem
	typedef __int16 int2;
	/// Liczba 16-bitowa bez znaku
	typedef unsigned __int16 uint2;
	/// Liczba 32-bitowa ze znakiem
	typedef __int32 int4;
	/// Liczba 32-bitowa bez znaku
	typedef unsigned __int32 uint4;
	/// Liczba 64-bitowa ze znakiem
	typedef __int64 int8;
	/// Liczba 64-bitowa bez znaku
	typedef unsigned __int64 uint8;
#else
	typedef unsigned int uint;
	typedef char int1;
	typedef unsigned char uint1;
	typedef short int2;
	typedef unsigned short uint2;
	typedef int int4;
	typedef unsigned int uint4;
	typedef long long int8;
	typedef unsigned long long uint8;
#endif
//@}

/// Wektor �a�cuch�w
typedef std::vector<tstring> STRING_VECTOR;

/// Je�li wska�nik niezerowy, zwalnia go i zeruje
#define SAFE_DELETE(x) { delete (x); (x) = 0; }
/// Je�li wska�nik niezerowy, zwalnia go jako tablic� i zeruje
#define SAFE_DELARR(x) { delete [] (x); (x) = 0; }
/// Je�li wska�nik niezerowy, wywo�uje mu Release() i zeruje
#define SAFE_RELEASE(x) { if (x) { (x)->Release(); (x) = 0; } }

#ifdef WIN32
	/// Asercja, kt�ra ZAWSZE przerywa program kiedy jest niespe�niona (w debuggerze - robi breakpoint, bez debuggera - wywala program).
	#define	ASSERT_INT3(x) if ((x) == 0) { __asm { int 3 } }
	/// Asercja, kt�ra w kompilacji Debug przerywa program kiedy jest niespe�niona (w debuggerze - robi breakpoint, bez debuggera - wywala program).
	#ifdef _DEBUG
		#define	ASSERT_INT3_DEBUG(x) if ((x) == 0) { __asm { int 3 } }
	#else
		#define ASSERT_INT3_DEBUG(x) { }
	#endif
#endif

/// Do robienia alignacji co do jednego bajtu dla struktur, czyli bez wype�niaczy
/** Autor: agent_J. */
#ifdef _MSC_VER
	#define PACKED __declspec(align(1))
#else
	#define PACKED __attribute__((packed))
#endif

/// Makro do umieszczania w klasach, �eby klasa nie mia�a konstruktora kopiuj�cego ani operatora przypisania.
/* U�ywa� na pocz�tku definicji klasy.
Na podstawie biblioteki wxWidgets. */
#define DECLARE_NO_COPY_CLASS(ClassName)        \
	private:                                    \
		ClassName(const ClassName&);            \
		ClassName& operator=(const ClassName&);

/// Asercja w czasie kompilacji
#define STATIC_ASSERT(x) { const char temp[ (((x) == 0) ? 0 : 1) ] = {'\0'}; }

/// Uniwersalny, brakuj�cy w C++ operator dos�ownego rzutowania (reintepretacji bitowej)
template <typename destT, typename srcT>
destT &absolute_cast(srcT &v)
{
	return reinterpret_cast<destT&>(v);
}
template <typename destT, typename srcT>
const destT &absolute_cast(const srcT &v)
{
	return reinterpret_cast<const destT&>(v);
}

//@}
// code_base

/// G��wna przestrze� nazw biblioteki CommonLib
namespace common
{

/** \addtogroup code_base Modu� Base */
//@{

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_general Og�lne */
//@{

#ifndef _countof
	/// \internal
	template <typename _CountofType, size_t _SizeOfArray>
	char (*__countof_helper(_CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
	/// Makro do pobierania w czasie kompilacji liczby element�w statycznej tablicy.
	/** Skopiowane z stdlib.h z Visual C++. */
	#define _countof(_Array) sizeof(*__countof_helper(_Array))
#endif

/// Orientacja, czyli u�o�enie - pionowa lub pozioma
enum ORIENTATION
{
	O_NONE,
	O_VERT,
	O_HORIZ,
};

/// Alokuje now� tablic� dynamiczn� 2D
template <typename T>
T **new_2d(size_t cx, size_t cy)
{
	T **a = new T*[cx];
	for (size_t x = 0; x < cx; x++)
		a[x] = new T[cy];
	return a;
}

/// Zwalnia tablic� dynamiczn� 2D
template <typename T>
void delete_2d(T **a, size_t cx)
{
	for (size_t x = 0; x < cx; x++)
		delete[] a[x];
	delete[] a;
}

/// Kopiuje string do char* ��cznie ze znakami '\\0' (czego nie zapewnia strcpy)
/**
- Na ko�cu do��cza '\\0'.
- Oczywi�cie dest musi by� dostatecznie pojemne. */
inline void strcpy0(tchar* dest, const tstring &src)
{
	for (size_t i = 0; i < src.length(); i++)
		dest[i] = src[i];
	dest[src.length()] = '\0';
}

/// Wzorzec projektowy Singleton - klasa bazowa
/**
Spos�b u�ycia:
\code
class MyClass : public common::Singleton<MyClass>
{
public:
  void Foo();
};

...
MyClass::GetInstance().Foo();
\endcode
*/
template <typename T>
class Singleton
{
public:
	/// Pobiera jedyn� instancj� tej klasy. Tworzy j� przy pierwszym pobraniu.
	static T & GetInstance()
	{
		static T Instance;
		return Instance;
	}
};

/// Zeruje pami��
void ZeroMem(void *Data, size_t NumBytes);
/// Kopuje pami��
void CopyMem(void *Out, const void *In, size_t NumBytes);
/// Zwraca true, je�li pami�� jest identyczna
bool CompareMem(const void *Data1, const void *Data2, size_t NumBytes);
/// Wype�nia pami�� podanym bajtem
void FillMem(void *Data, size_t NumBytes, uint1 Byte);

/// Algorytm jak te z STL - sortowanie przez wstawianie.
template<class Iterator>
void InsertionSort(Iterator b, Iterator e)
{
	if (b == e) return;
	for (Iterator j = b + 1; j < e; j++)
	{
		typename std::iterator_traits<Iterator>::value_type key;
		key = *j;
		Iterator i = j;
		while (i > b && key < *(i-1))
		{
			*i = *(i-1);
			i--;
		} 
		*i = key;
	}
}

/// Algorytm jak te z STL - sortowanie przez wstawianie, z w�asnym komparatorem.
template<class Iterator, typename Compare>
void InsertionSort(Iterator b, Iterator e, Compare Comp)
{
	if (b == e) return;
	for (Iterator j = b + 1; j < e; j++)
	{
		typename std::iterator_traits<Iterator>::value_type key;
		key = *j;
		Iterator i = j;
		while (i > b && Comp(key, *(i-1)))
		{
			*i = *(i-1);
			i--;
		} 
		*i = key;
	}
}
//@}

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_smartptr Inteligentne wska�niki */
//@{

/// Polityka zwalaniania inteligentnych wska�nik�w, kt�ra robi: <tt>delete p;</tt>
class DeletePolicy
{
public:
	template <typename T>
	static void Destroy(T *p)
	{
		// Sztuczka inspirowana Boost (checked_delete.hpp)
		typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
		(void) sizeof(type_must_be_complete);
		delete p;
	}
};
/// Polityka zwalaniania inteligentnych wska�nik�w, kt�ra robi: <tt>delete [] p;</tt>
class DeleteArrayPolicy
{
public:
	template <typename T>
	static void Destroy(T *p)
	{
		// Sztuczka inspirowana Boost (checked_delete.hpp)
		typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
		(void) sizeof(type_must_be_complete);
		delete [] p;
	}
};
/// Polityka zwalaniania inteligentnych wska�nik�w, kt�ra robi: <tt>p->Release();</tt>
class ReleasePolicy
{
public:
	template <typename T>
	static void Destroy(T *p)
	{
		if (p) p->Release();
	}
};

/// Inteligentny wska�nik z wy��cznym prawem w�asno�ci.
/**
- Niekopiowalny.
- W destruktorze zwalnia. */
template <typename T, typename PolicyT = DeletePolicy>
class scoped_ptr
{
    template<typename Y, typename PolicyY> friend class scoped_ptr;

private:
	T *m_Ptr;

	scoped_ptr(const scoped_ptr &);
	scoped_ptr & operator = (const scoped_ptr &);

public:
	typedef T value_type;
	typedef T *ptr_type;

	explicit scoped_ptr(T *p = NULL) : m_Ptr(p) { }
	~scoped_ptr() { PolicyT::template Destroy<T>(m_Ptr); }
	
	T & operator * () const { assert(m_Ptr != NULL); return *m_Ptr; }
	T * operator -> () const { assert(m_Ptr != NULL); return m_Ptr; }
	T & operator [] (uint i) const { return m_Ptr[i]; }

	inline friend bool operator == (const scoped_ptr &lhs, const T *rhs) { return lhs.m_Ptr == rhs; }
	inline friend bool operator == (const T *lhs, const scoped_ptr &rhs) { return lhs == rhs.m_Ptr; }
	inline friend bool operator != (const scoped_ptr &lhs, const T *rhs) { return lhs.m_Ptr != rhs; }
	inline friend bool operator != (const T *lhs, const scoped_ptr &rhs) { return lhs != rhs.m_Ptr; }

	T * get() const { return m_Ptr; }
	void swap(scoped_ptr<T, PolicyT> &b) { T *tmp = b.m_Ptr; b.m_Ptr = m_Ptr; m_Ptr = tmp; }
	void reset(T *p = NULL) { assert(p == NULL || p != m_Ptr); scoped_ptr<T, PolicyT>(p).swap(*this); }
};

/// Inteligentny wska�nik ze zliczaniem referencji
/**
- Kopiowalny.
- Zwalnia, kiedy zwolniony zostanie ostatni wskazuj�cy na obiekt common::shared_ptr. */
template <typename T, typename PolicyT = DeletePolicy>
class shared_ptr
{
    template<typename Y, typename PolicyY> friend class shared_ptr;

private:
	T *m_Ptr;
	unsigned *m_Counter;

public:
	typedef T value_type;
	typedef T *ptr_type;

	explicit shared_ptr(T *p = NULL) : m_Ptr(p), m_Counter(new unsigned(1)) { }
	~shared_ptr() { if (--(*m_Counter) == 0) { delete m_Counter; PolicyT::template Destroy<T>(m_Ptr); } }
	
	shared_ptr(const shared_ptr &p) : m_Ptr(p.m_Ptr), m_Counter(p.m_Counter) { (*m_Counter)++; }
	shared_ptr & operator = (const shared_ptr &p) { reset<T>(p); return *this; }
	template <typename U, typename PolicyU> explicit shared_ptr(const shared_ptr<U, PolicyU> &p) : m_Ptr(p.m_Ptr), m_Counter(p.m_Counter) { (*m_Counter)++; }
	template <typename U, typename PolicyU> shared_ptr & operator = (const shared_ptr<U, PolicyU> &p) { reset<U, PolicyU>(p); return *this; }

	T & operator * () const { assert(m_Ptr != NULL); return *m_Ptr; }
	T * operator -> () const { assert(m_Ptr != NULL); return m_Ptr; }
	T & operator [] (uint i) const { return m_Ptr[i]; }

	inline friend bool operator == (const shared_ptr &lhs, const T *rhs) { return lhs.m_Ptr == rhs; }
	inline friend bool operator == (const T *lhs, const shared_ptr &rhs) { return lhs == rhs.m_Ptr; }
	inline friend bool operator != (const shared_ptr &lhs, const T *rhs) { return lhs.m_Ptr != rhs; }
	inline friend bool operator != (const T *lhs, const shared_ptr &rhs) { return lhs != rhs.m_Ptr; }
	template <typename U, typename PolicyU> bool operator == (const shared_ptr<U, PolicyU> &rhs) const { return m_Ptr == rhs.m_Ptr; }
	template <typename U, typename PolicyU> bool operator != (const shared_ptr<U, PolicyU> &rhs) const { return m_Ptr != rhs.m_Ptr; }

	T * get() const { return m_Ptr; }
	void swap(shared_ptr<T, PolicyT> &b) { T *tmp = b.m_Ptr; b.m_Ptr = m_Ptr; m_Ptr = tmp; unsigned *tmpc = b.m_Counter; b.m_Counter = m_Counter; m_Counter = tmpc; }
	void reset(T *p = NULL) { if (p == m_Ptr) return; shared_ptr<T, PolicyT>(p).swap(*this); }
	template <typename U, typename PolicyU> void reset(const shared_ptr<U, PolicyU> &p) { shared_ptr<U, PolicyU>(p).swap(*this); }
	bool unique() const { return *m_Counter == 1; }
};

#ifdef WIN32
	/// Polityka zwalniania uchwytu - robi: <tt>CloseHandle(p);</tt>
	class CloseHandlePolicy  { public: template <typename T> static void Destroy(T p) { if (p != NULL) CloseHandle(p); } };
	/// Polityka zwalniania uchwytu - robi: <tt>DeleteObject(p);</tt>
	class DeleteObjectPolicy { public: template <typename T> static void Destroy(T p) { if (p != NULL) DeleteObject(p); } };
#endif

/// Inteligentny uchwyt - wy��czna w�asno��
template <typename T, typename PolicyT>
class scoped_handle
{
    template<typename Y, typename PolicyY> friend class scoped_handle;

private:
	T m_Ptr;

	scoped_handle(const scoped_handle &);
	scoped_handle & operator = (const scoped_handle &);

public:
	typedef T value_type;

	explicit scoped_handle(T p) : m_Ptr(p) { }
	~scoped_handle() { PolicyT::template Destroy<T>(m_Ptr); }
	
	inline friend bool operator == (const scoped_handle &lhs, const T &rhs) { return lhs.m_Ptr == rhs; }
	inline friend bool operator == (const T &lhs, const scoped_handle &rhs) { return lhs == rhs.m_Ptr; }
	inline friend bool operator != (const scoped_handle &lhs, const T &rhs) { return lhs.m_Ptr != rhs; }
	inline friend bool operator != (const T &lhs, const scoped_handle &rhs) { return lhs != rhs.m_Ptr; }

	const T & get() const { return m_Ptr; }
	void swap(scoped_handle<T, PolicyT> &b) { T tmp = b.m_Ptr; b.m_Ptr = m_Ptr; m_Ptr = tmp; }
	void reset(T p) { scoped_handle<T, PolicyT>(p).swap(*this); }
};

/// Inteligentny uchwyt ze zliczaniem referencji
template <typename T, typename PolicyT>
class shared_handle
{
    template<typename Y, typename PolicyY> friend class shared_handle;

private:
	T m_Ptr;
	unsigned *m_Counter;

public:
	typedef T value_type;

	explicit shared_handle(T p) : m_Ptr(p), m_Counter(new unsigned(1)) { }
	~shared_handle() { if (--(*m_Counter) == 0) { delete m_Counter; PolicyT::template Destroy<T>(m_Ptr); } }
	
	shared_handle(const shared_handle &p) : m_Ptr(p.m_Ptr), m_Counter(p.m_Counter) { (*m_Counter)++; }
	shared_handle & operator = (const shared_handle &p) { reset<T>(p); return *this; }
	template <typename U, typename PolicyU> explicit shared_handle(const shared_handle<U, PolicyU> &p) : m_Ptr(p.m_Ptr), m_Counter(p.m_Counter) { (*m_Counter)++; }
	template <typename U, typename PolicyU> shared_handle & operator = (const shared_handle<U, PolicyU> &p) { reset<U, PolicyU>(p); return *this; }

	inline friend bool operator == (const shared_handle &lhs, const T &rhs) { return lhs.m_Ptr == rhs; }
	inline friend bool operator == (const T &lhs, const shared_handle &rhs) { return lhs == rhs.m_Ptr; }
	inline friend bool operator != (const shared_handle &lhs, const T &rhs) { return lhs.m_Ptr != rhs; }
	inline friend bool operator != (const T &lhs, const shared_handle &rhs) { return lhs != rhs.m_Ptr; }
	template <typename U, typename PolicyU> bool operator == (const shared_handle<U, PolicyU> &rhs) const { return m_Ptr == rhs.m_Ptr; }
	template <typename U, typename PolicyU> bool operator != (const shared_handle<U, PolicyU> &rhs) const { return m_Ptr != rhs.m_Ptr; }

	const T & get() const { return m_Ptr; }
	void swap(shared_handle<T, PolicyT> &b) { T tmp = b.m_Ptr; b.m_Ptr = m_Ptr; m_Ptr = tmp; unsigned *tmpc = b.m_Counter; b.m_Counter = m_Counter; m_Counter = tmpc; }
	void reset(T p) { if (p == m_Ptr) return; shared_handle<T, PolicyT>(p).swap(*this); }
	template <typename U, typename PolicyU> void reset(const shared_handle<U, PolicyU> &p) { shared_handle<U, PolicyU>(p).swap(*this); }
	bool unique() const { return *m_Counter == 1; }
};

template <typename T, typename PolicyT> void swap(scoped_ptr<T, PolicyT> &a, scoped_ptr<T, PolicyT> &b) { a.swap(b); }
template <typename T, typename PolicyT> void swap(shared_ptr<T, PolicyT> &a, shared_ptr<T, PolicyT> &b) { a.swap(b); }
template <typename T, typename PolicyT> void swap(scoped_handle<T, PolicyT> &a, scoped_handle<T, PolicyT> &b) { a.swap(b); }
template <typename T, typename PolicyT> void swap(shared_handle<T, PolicyT> &a, shared_handle<T, PolicyT> &b) { a.swap(b); }

//@}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_math Podstawowa matematyka
Sztuczki z bitami opracowane na podstawie:
Bit Twiddling Hacks, Sean Eron Anderson, http://www-graphics.stanford.edu/~seander/bithacks.html
*/
//@{

/** \addtogroup base_minmax Maksymalne i minimalne warto�ci
Maksymalne i minimalne warto�ci liczb r�nych typ�w. */
//@{
const int1 MININT1 = std::numeric_limits<int1>::min();
const int1 MAXINT1 = std::numeric_limits<int1>::max();
const int2 MININT2 = std::numeric_limits<int2>::min();
const int2 MAXINT2 = std::numeric_limits<int2>::max();
const int4 MININT4 = std::numeric_limits<int4>::min();
const int4 MAXINT4 = std::numeric_limits<int4>::max();
const int8 MININT8 = std::numeric_limits<int8>::min();
const int8 MAXINT8 = std::numeric_limits<int8>::max();
const uint1 MAXUINT1 = std::numeric_limits<uint1>::max();
const uint2 MAXUINT2 = std::numeric_limits<uint2>::max();
const uint4 MAXUINT4 = std::numeric_limits<uint4>::max();
const uint8 MAXUINT8 = std::numeric_limits<uint8>::max();
const float MINFLOAT = std::numeric_limits<float>::min();
const float MAXFLOAT = std::numeric_limits<float>::max();
//@}

/// Liczba zmiennoprzecinkowa bliska zeru
/** O dziwo to makro zamienione na funkcj� inline dzia�a wolniej - nigdy nie ufaj
optymalizacji kompilatora! */
#define FLOAT_ALMOST_ZERO(F) ((absolute_cast<uint4>(F) & 0x7f800000L) == 0)

/** \addtogroup base_math_consts Sta�e matematyczne
Bo sta�e z cmath/math.h nie chc� dzia�a� mimo zdefiniowania wcze�niej USE_MATH_CONSTANTS :P */
//@{
const float E         = 2.71828182845904523536f;  ///< e
const float LOG2E     = 1.44269504088896340736f;  ///< log2(e)
const float LOG10E    = 0.434294481903251827651f; ///< log10(e)
const float LN2       = 0.693147180559945309417f; ///< ln(2)
const float LN10      = 2.30258509299404568402f;  ///< ln(10)
const float PI        = 3.14159265358979323846264338327950288419716939937510582f;  ///< pi
const float PI_2      = 1.57079632679489661923f;  ///< pi/2
const float PI_4      = 0.785398163397448309616f; ///< pi/4
const float PI_X_2    = 6.28318530717958647692f;  ///< 2*pi
const float _1_PI     = 0.318309886183790671538f; ///< 1/pi
const float _2_PI     = 0.636619772367581343076f; ///< 2/pi
const float _2_SQRTPI = 1.12837916709551257390f;  ///< 2/sqrt(pi)
const float SQRT2     = 1.41421356237309504880f;  ///< sqrt(2)
const float SQRT3     = 1.7320508075688772935274463415059f; ///< sqrt(3)
const float SQRT1_2   = 0.707106781186547524401f; ///< 1/sqrt(2)
//@}

// Windows - potrzebuje float.h
#ifdef WIN32
	/// Zwraca true, je�li liczba jest niezwyczajna (INF lub NaN)
	bool is_finite(float x);
	/// Zwraca true, je�li liczba jest niezwyczajna (INF lub NaN)
	bool is_finite(double x);
	/// Zwraca true, je�li liczba jest NaN
	bool is_nan(float x);
	/// Zwraca true, je�li liczba jest NaN
	bool is_nan(double x);
// Linux - potrzebuje math.h
#else
	inline bool is_finite(float x)  { return (finitef(x) != 0); }
	inline bool is_finite(double x) { return (finite(x)  != 0); }
	inline bool is_nan(float x)  { return (isnanf(x) != 0); }
	inline bool is_nan(double x) { return (isnan(x)  != 0); }
#endif

/// Dodaje dwie liczby z ograniczeniem zakresu zamiast zawini�cia przy przepe�nieniu
/** Jako T u�ywa� uint1, uint2, uint4, uint8
(Autor: Tarlandil) */
template <typename T>
T safe_add(T a, T b)
{
	T R = a + b;
	if (R < std::max(a, b)) return std::numeric_limits<T>::max();
	else return R;
}

/// Odejmuje dwie liczby z ograniczeniem zakresu zamiast zawini�cia przy przepe�nieniu
/** Jako T u�ywa� uint1, uint2, uint4, uint8
(Autor: Tarlandil) */
template <typename T>
T safe_sub(T a, T b)
{
	if (b > a) return T();
	else return a - b;
}

/// Mno�y dwie liczby z ograniczeniem zakresu zamiast zawini�cia przy przepe�nieniu
/** Jako T u�ywa� uint1, uint2, uint4, uint8
(Autor: Tarlandil) */
template <typename T>
T safe_mul(T a, T b)
{
	if (b == T()) return T();
	T R = a * b;
	if (R / b != a) return std::numeric_limits<T>::max();
	else return R;
}

/// Bezpieczny arcus cosinus, ogranicza zakres wej�ciowy do -1...+1 zwracaj�c w razie przekrocznia skrajne warto�ci wyniku.
inline float safe_acos(float x)
{
	if (x <= -1.0f) return PI;
	if (x >= 1.0f) return 0.0f;
	return acosf(x);
}

/// Zaokr�gla liczb�, zamiast j� obcina�
/** Tak matematycznie, czyli do g�ry lub w d� zale�nie od cz�ci u�amkowej. */
inline int round(float x)
{
	return static_cast<int>(floorf(x+0.5f));
}
inline int round(double x)
{
	return static_cast<int>(floor(x+0.5));
}

/// Dzieli 2 liczby ca�kowite zaokr�glaj�c wynik w g�r�
/** Jako typ stosowa� int, uint itp.
Dzia�a tylko dla liczb dodatnich.
Uwa�a� na przekroczenie zakresu liczby (x+y).
(Author: Tarlandil) */
template <typename T>
inline T ceil_div(T x, T y)
{
	return (x+y-1) / y;
}

/// Zwraca true, je�li liczba le�y w epsilonowym otoczeniu zera
inline bool around(float x, float epsilon)
{
	return (fabsf(x) <= epsilon);
}
inline bool around(double x, double epsilon)
{
	return (fabs(x) <= epsilon);
}

/// Zwraca true, je�li liczba le�y w epsilonowym otoczeniu drugiej liczby
inline bool around(float x, float y, float epsilon)
{
	return (fabsf(x-y) <= epsilon);
}
inline bool around(double x, double y, double epsilon)
{
	return (fabs(x-y) <= epsilon);
}

/// Zwraca true, je�li dwie liczby zmiennoprzecinkowe s� praktycznie r�wne
/** Te funkcje s� fajne bo nie trzeba zna� epsilona, ale za to jest wi�cej liczenia.
(Autor: Tarlandil) */
inline bool float_equal(float x, float y)
{
	float epsilon = (fabsf(x)+fabsf(y)) * 1e-4f;
	//return around(x, y, epsilon);
	return (fabsf(x-y) <= epsilon);
}
inline bool double_equal(double x, double y)
{
	double epsilon = (fabs(x)+fabs(y)) * 1e-13;
	//return around(x, y, epsilon);
	return (fabs(x-y) <= epsilon);
}

/// Zwraca znak podanej liczby ca�kowitej, czyli -1 0 lub 1
/** Stosowa� dla typ�w ca�kowitych ze znakiem, czyli int1, int2, int4, int8. */
template <typename T> inline T sign(T v) { return (v > 0) - (v < 0); }

/// ��czy bity dw�ch liczb wg maski, tzn. wybiera z A te bity, kt�re w masce maj� 0 i z B te bity, kt�re w masce maj� 1.
template <typename T> inline T MergeBits(T a, T b, T Mask) { return a ^ ((a ^ b) & Mask); }

/// Zwraca liczb� bit�w, kt�re s� jedynk�
template <typename T> inline uint CountBitsSet(T v) { uint c; for (c = 0; v; c++) v &= v - 1; return c; }

/// Oblicza parzysto�� liczby
inline uint CalcParity(uint v) {
	v ^= v >> 1; v ^= v >> 2; v = (v & 0x11111111U) * 0x11111111U; return (v >> 28) & 1;
}
/// Oblicza parzysto�� liczby
inline uint8 CalcParity(uint8 v) {
	v ^= v >> 1; v ^= v >> 2; v = (v & 0x1111111111111111ULL) * 0x1111111111111111ULL; return (v >> 60) & 1;
}

/// Zamienia miejscami ci�g bit�w w liczbie
template <typename T> inline T SwapBitSequences(T v, uint SrcBit, uint DstBit, uint NumBits)
{
	int x = ((v >> SrcBit) ^ (v >> DstBit)) & ((1 << NumBits) - 1);
	return v ^ ((x << SrcBit) | (x << DstBit));
}

/// Zwraca true, je�li podana liczba jest pot�g� dw�jki.
/** T musi by� liczb� ca�kowit� bez znaku - uint1, uint2, uint4, uint8, albo liczb� ze znakiem ale na pewno dodatni�.
Dla 0 zwraca true. */
template <typename T> inline bool IsPow2(T x) { return (x & (x-1)) == 0; }

/// Zwraca mask� bitow� z ustawionymi na jedynk� n najm�odszymi bitami.
/** n musi by� z z zakresu 0..32. */
uint4 GetBitMask(uint4 n);

/// Zwraca logarytm dw�jkowy z podanej liczby ca�kowitej bez znaku, tzn numer najstarszego niezerowego bitu.
/** Innymi s�owy, o ile bit�w przesun�� w lewo jedynk� �eby otrzyma� najstarsz�
jedynk� podanej liczby. Warto�� 0 zwraca dla liczb 0 i 1. */
uint log2u(uint v);
/// Zwraca logarytm dziesi�tny z podanej liczby ca�kowitej bez znaku, tzn numer najstarszej cyfry dziesi�tnej.
/** Dla zera niezdefiniowany. */
uint log10u(uint v);

/// Zwraca najmniejsz� pot�g� dw�jki wi�ksz� lub r�wn� podanej liczbie
/** Dla v == 0 zwraca 0.
Dla v > 0x80000000 wynik jest niezdefiniowany. */
inline uint next_pow2(uint v) {
	v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v;
}

/// Przeplata m�odsze 16 bit�w a (do parzystych) i m�odsze 16 bit�w b (do nieparzystych) do liczby wynikowej
uint InterleaveBits(uint a, uint b);

/// Liczy pot�ge o ca�kowitym wyk�adniku (bardzo szybko!)
/** T mo�e by� dowoln� liczb� - int, uint4, float itp.
(Autor: Tarlandil) */
template <typename T>
T powi(T a, uint4 b)
{
	T r = (T)1;
	T p = a;
	while (b)
	{
		if (b & 1)
			r *= p;
		p *= p;
		b >>= 1;
	}
	return r;
}

/// Zwraca najwi�ksz� z podanych 3 liczb
template <typename T>
inline T max3(const T &a, const T &b, const T &c)
{
	return std::max(a, std::max(b, c));
}

/// Zwraca najmniejsz� z podanych 3 liczb
template <typename T>
inline T min3(const T &a, const T &b, const T &c)
{
	return std::min(a, std::min(b, c));
}

/// Zwraca liczb� x ograniczon� do podanego zakresu od a do b
template <typename T>
inline T minmax(const T &a, const T &x, const T &b)
{
	if (x < a) return a; else if (x > b) return b; else return x;
	//return std::min(b, std::max(a, x));
}

/// Zwraca cz�� ca�kowit� liczby wraz ze znakiem
/** (Autor: Tarlandil) */
inline float trunc(float x)
{
	return (x < 0.0f) ? ceilf(x) : floorf(x);
}
inline double trunc(double x)
{
	return (x < 0.0) ? ceil(x) : floor(x);
}

/// Zwraca cz�� u�amkow� liczby wraz ze znakiem
/** (Autor: Tarlandil) */
inline float frac(float x)
{
	return x - trunc(x);
}
inline double frac(double x)
{
	return x - trunc(x);
}

/// Oblicza sinus i cosinus za jednym zamachem. Mo�e by� szybsze, ni� liczenie osobno.
void sincos(float angle, float *sine, float *cosine);

/// Interpolacja liniowa 1D (t = 0..1)
inline float Lerp(float x, float y, float t)
{
	return x + t*(y-x);
}
/// Interpolacja liniowa 1D (t jest ograniczane do 0..1)
inline float SafeLerp(float x, float y, float t)
{
	return Lerp(x, y, minmax(0.0f, t, 1.0f));
}

/// Interpolacja liniowa 2D
/** tx tyczy si� pierwszego indeksu, ty drugiego. */
inline float Lerp2D(float x11, float x21, float x12, float x22, float tx, float ty)
{
	return Lerp(Lerp(x11, x21, tx), Lerp(x12, x22, tx), ty);
}

/// Normalizuje k�t do przedzia�u < 0..2PI )
inline float NormalizeAngle(float angle)
{
	angle /= PI_X_2;
	angle = frac(angle);
	if (angle < 0.0f)
		angle += 1.0f;
	else if (angle >= 1.0f)
		angle -= 1.0f;
	return angle * PI_X_2;
}

/// Normalizuje k�t do przedzia�u -PI..+PI
inline float NormalizeAngle2(float Angle)
{
	Angle += PI;
	Angle -= floorf(Angle * (1.0f/PI_X_2)) * PI_X_2;
	Angle -= PI;
	return Angle;
}

/// Przelicza k�t ze stopni na radiany
inline float DegToRad(float Angle)
{
	// Angle * PI / 180
	return Angle * 0.017453292519943295769222222222222f;
}
/// Przelicza k�t z radian�w na stopnie
inline float RadToDeg(float Angle)
{
	// Angle * 180 / PI
	return Angle * 57.295779513082320876846364344191f;
}

/// Oblicza r�nic� k�t�w A-B, gdzie A, B nale�� do: 0..2*PI
/** Uwzgl�dnia przekr�canie si� k�t�w, znajduje wi�c najkr�tsz� drog� mi�dzy nimi. */
inline float AngleDiff(float A, float B)
{
	float R1 = B - A;
	float R2 = B - PI_X_2 - A;
	float R3 = B + PI_X_2 - A;

	float R1a = fabsf(R1);
	float R2a = fabsf(R2);
	float R3a = fabsf(R3);

	if (R1a < R2a && R1a < R3a)
		return R1;
	else if (R2a < R3a)
		return R2;
	else
		return R3;
}

/// Krzywa wyg�adzona 0..1 -> 0..1: e(x) = 3*x^2 - 2*x^3
inline float EaseCurve(float x)
{
	return x * x * (3.0f - 2.0f * x);
}
// Krzywa wyg�adzona 0..1 -> 0..1: e(x) = 6*t^5 - 15*t^4 + 10*t^3
/** Lepsza od EaseCurve, bo ma zerow� drug� pochodn� dla x=0 i x=1. */
inline float EaseCurve2(float x)
{
	return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
}

/// Zwraca warto�� 0..1 zmieniaj�c� si� p�ynnie, jak x zmienia si� od min do max.
/** Funkcja wzorowana na funkcji smoothstep z j�zyka HLSL.
Zwraca wyg�adzon� interpolacj� Hermite'a.
Dla x < min zwraca 0.
Dla x > max zwraca 1.
Dla x mi�dzy min i max zwraca liczb� 0..1, kt�ra zmienia si� p�ynnie (nieliniowo). */
inline float smoothstep(float min, float max, float x)
{
	if(x < min) return 0.0f;
	if(x > max) return 1.0f;
	x = (x - min) / (max - min);
	return x * x * (3.0f - 2.0f * x);
}

/// Funkcja wyg�adzaj�ca - Critically Damped Smoothing
/** To jest wyliczane wg r�wnania r�niczkowego na jak��tam spr�yn�, dok�adnie
analitycznie, wi�c TimeDelta mo�e by� dowolnie du�e.
\param[in,out] InOutPos  Pozycja przed i po przeliczeniu tego kroku
\param[in,out] InOutVel  Pr�dko�� przed i po przeliczeniu tego kroku
\param Dest              Pozycja docelowa
\param SmoothTime        Wsp�czynnik "bezw�adno�ci" w jednostkach czasu
\param TimeDelta         Czas kroku (np. czas od poprzedniej klatki)
\param MaxSpeed          Maksymalna dopuszczalna pr�dko�� (maksymalna odleg�o�� na jak� pozycja mo�e nie nad��a�?) */
void SmoothCD(float *InOutPos, float Dest, float *InOutVel, float SmoothTime, float TimeDelta);
void SmoothCD(float *InOutPos, float Dest, float *InOutVel, float SmoothTime, float TimeDelta, float MaxSpeed);

/// Zwraca liczb� z przedzia�u 0..1, zale�nie od warto�ci x wzgl�dem brzeg�w trapezu a, b, c, d.
/**
\verbatim
    x < a => 0
a < x < b => 0..1
b < x < c => 1
c < x < d => 1..0
d < x     => 0
\endverbatim
*/
inline float Trapezoidal(float x, float a, float b, float c, float d)
{
	if (x < a)
		return 0.f;
	else if (x < b)
		return (x-a)/(b-a);
	else if (x < c)
		return 1.f;
	else if (x < d)
		return 1.f - (x-c)/(d-c);
	else
		return 0.f;
}
/// Jak Trapezoidal(), ale zamiast 0..1 zwraca liczb� z przedzia�u min..max.
inline float Trapezoidal(float x, float a, float b, float c, float d, float min, float max)
{
	return Trapezoidal(x, a, b, c, d) * (max-min) + min;
}

/// R�wnanie kwadratowe a*x^2 + b*x + c = 0
/** Musi by�: a != 0.
- Brak pierwiastk�w - zwraca 0, x1 i x2 niezdefiniowane.
- Jeden pierwiastek - zwraca 1, x1 = x2 = jedyne rozwi�zanie.
- Dwa pierwistki - zwraca 2, x1 to pierwszy pierwiastek, x2 to drugi */
int QuadraticEquation(float a, float b, float c, float *Out_x1, float *Out_x2);

/// Oblicza �redni� i opcjonalnie wariancj� ze zbioru liczb typu float.
/** sqrt(Variance) to ochylenie standardowe.
\param Variance Mo�na poda� NULL, je�li nas nie interesuje. */
void CalcMeanAndVariance(const float Numbers[], size_t NumberCount, float *OutMean, float *OutVariance = NULL, bool VarianceBiased = true);
void CalcMeanAndVariance(const void *NumberData, size_t NumberCount, int NumberStride, float *OutMean, float *OutVariance = NULL, bool VarianceBiased = true);

/** \addtogroup base_perlin_noise Szum Perlina
Deterministyczne, pseudolosowe funkcje 1, 2, 3 zmiennych generuj�ce szum perlina
oraz cz�sto mylony z nim Fractional Brownian Motion (fBm). Szum perlina to
ci�g�a funkcja pseudolosowa o amplitudzie -1..1 i cz�stotliwo�ci 1.
W funkcjach BrownianNoise:
- i - liczba oktaw
- Persistence - utrzymanie amplitudy w kolejnych oktawach; zalecane 0..1*/
//@{
float PerlinNoise1(float x);
float PerlinNoise2(float x, float y);
float PerlinNoise3(float x, float y, float z);
float BrownianNoise1(float x,                   uint i, float Persistence);
float BrownianNoise2(float x, float y,          uint i, float Persistence);
float BrownianNoise3(float x, float y, float z, uint i, float Persistence);
//@}

//@}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_strings �a�cuchy */
//@{

/// Rodzaje znak�w ko�ca wiersza
enum EOLMODE
{
	EOL_NONE, ///< Podczas konwersji pozostawienie bez zmian
	EOL_CRLF, ///< 13 i 10 (Windows)
	EOL_LF,   ///< 10      (Unix)
	EOL_CR	  ///< 13      (Mac)
};

/// �a�cuch pusty - do wykorzystania aby mo�na by�o pobiera� do niego referencje itp.
extern const tstring EMPTY_STRING;
/// Standardowy �a�cuch ko�ca wiersza zale�ny od systemu
extern const tchar * const EOL;

/// Strona kodowa polskich znakow
enum CHARSET
{
	CHARSET_NONE = 0, ///< Brak polskich liter
	CHARSET_WINDOWS,  ///< Strona kodowa Windows-1250 (u�ywana w GUI Windows)
	CHARSET_ISO,      ///< Strona kodowa ISO-8859-2 (Latin-2) (u�ywana w Linuksie)
	CHARSET_IBM,      ///< Strona kodowa IBM (CP852) (u�ywana na konsoli Windows)
	CHARSET_UTF8,     ///< Strona kodowa UTF-8
};

/// Zwraca true, jesli znak jest alfanumeryczny (litera lub cyfra) wg ustawie� systemu
bool CharIsAlphaNumeric(tchar ch);
/// Zwraca true, jesli znak jest litera
bool CharIsAlpha(tchar ch);
/// Zwraca true, jesli znak jest cyfr� dziesietn�
inline bool CharIsDigit(tchar ch) { return (ch >= _T('0') && ch <= _T('9')); }
/// Zwraca true, je�li znak jest cyfr� szesnastkow�
/** - Akceptuje ma�e i du�e litery. */
inline bool CharIsHexDigit(tchar ch) { return (ch >= _T('0') && ch <= _T('9')) || (ch >= _T('A') && ch <= _T('F')) || (ch >= _T('a') && ch <= _T('f')); }
/// Zwraca true, jesli znak jest mala litera
bool CharIsLower(tchar ch);
/// Zwraca true, jesli znak jest duza litera
bool CharIsUpper(tchar ch);
/// Zwraca true, jesli podany znak jest odstepem, czyli bialym znakiem wg systemu
/** Dwie wersje tej funkcji - ANSI i Unicode - s� potrzebne dla Stream - HexDecoder. */
bool CharIsWhitespace(char ch);
#ifdef WIN32
bool CharIsWhitespace(wchar_t ch);
#endif
/// Zwraca true, jesli podany znak jest odstepem, czyli bialym znakiem
/** Czyli jednym ze znakow:
- <tt>0x09 (9)  "\\t"</tt> - tabulacja
- <tt>0x0A (10) "\\n"</tt> - znak konca wiersza
- <tt>0x0D (13) "\\r"</tt> - znak konca wiersza
- <tt>          "\\v"</tt> - tabulacja pionowa
- <tt>0x20 (32) " "</tt>  - spacja */
inline bool CharIsWhitespace_f(tchar ch)
{
	return (ch == _T(' ') || ch == _T('\n') || ch == _T('\r') || ch == _T('\t') || ch == _T('\v'));
}

/// Odwraca �a�cuch w miejscu
void ReverseString(tstring *s);
/// Obcina bia�e znaki z pocz�tku i ko�ca �a�cucha w miejscu
void Trim(tstring *s);
/// Obcina bia�e znaki z pocz�tku i ko�ca �a�cucha
void Trim(tstring *Out, const tstring &s);

// UWAGA! Z nieznanych przyczyn UpperCase i LowerCase �le konwertuje w stronie
// kodowej IBM. Lepiej najpierw zmieni� wielko�� liter w innej stronie a potem
// przekonwertowa� na IBM - wtedy dzia�a. Kiedy� mo�e naprawi� ten b�ad :/

/// Je�li to litera, konwertuje na ma��
/** - Nie obs�uguje wielobajtowych stron kodowych (UTF-8). */
tchar CharToLower(tchar ch);
/// Je�li to litera, konwertuje na du��
/** - Nie obs�uguje wielobajtowych stron kodowych (UTF-8). */
tchar CharToUpper(tchar ch);
/// Konwertuje �a�cuch na ma�e litery
/** - Nie obs�uguje wielobajtowych stron kodowych (UTF-8). */
void LowerCase(tstring *s);
inline void LowerCase(tstring *Out, const tstring &s) { *Out = s; LowerCase(Out); }
/// Konwertuje �a�cuch na du�e
/** - Nie obs�uguje wielobajtowych stron kodowych (UTF-8). */
void UpperCase(tstring *s);
inline void UpperCase(tstring *Out, const tstring &s) { *Out = s; UpperCase(Out); }

/// Zmienia znak specjalny kodowania Windows-1250 na odpowiednik normalny.
/** Jesli podany znak jest jednym ze znakow specjalnych Windows-1250,
zwraca przez a_s jego normalny odpowiednik (mo�na poda� wska�nik 0) i zwraca true.
Je�li to nie jest taki znak, zwraca false. */
bool Charset_WindowsSpecialChar(char a_c, string *a_s);
/// Zmienia znak z jednej strony kodowej na druga lub pozostawia bez zmian.
/** Nie obsluguje stron kodowych wielobajtowych, tzn. UTF-8
(wynik jest wtedy niezdefiniowany). */
char Charset_Convert_Char(char a_c, CHARSET a_Charset1, CHARSET a_Charset2);
/// Konwertuje lancuch na podana strone kodowa
/** \param[out] out nie moze byc tym samym lancuchem, co s. */
void Charset_Convert(string *out, const string &s, CHARSET Charset1, CHARSET Charset2);

/// Szyforowanie/deszyfrowanie algorytmem ROT13
void Rot13(tstring *InOut);
inline void Rot13(tstring *Out, const tstring &In) { *Out = In; Rot13(Out); }

/// Rodzaj znaku ko�ca wiersza na odpowiadaj�cy mu znak (lub znaki)
void EolModeToStr(tstring *Out, EOLMODE EolMode);

/// Zamienia w �a�cuchu wszystkie wyst�pienia jedego pod�a�cucha na drugi
/** Result musi by� oczywi�cie, jak w ka�dej takiej funkcji, innym �a�cuchem ni� s. */
void Replace(tstring *result, const tstring &s, const tstring &s1, const tstring &s2);
/// Zmienia w �a�cuchu wszystkie wyst�pienia znaku Ch1 na Ch2
void Replace(tstring *Out, const tstring &s, tchar Ch1, tchar Ch2);
/// Zmienia w �a�cuchu wszystkie wyst�pienia znaku Ch1 na Ch2 w miejscu
void Replace(tstring *InOut, tchar Ch1, tchar Ch2);

/// Zmienia wszelkiego rodzaju znaki ko�ca wiersza w poddanym tek�cie na takie same - wg podanego trybu
void ReplaceEOL(tstring *result, const tstring &s, EOLMODE EOLMode);

/// Zamienia wszystkie odst�py na pojedyncze spacje
void NormalizeWhitespace(tstring *result, const tstring &s);

/// Zwraca �a�cuch powt�rzony podan� liczb� razy
void DupeString(tstring *Out, const tstring &s, size_t count);

/// Zwraca pod�a�cuch z prawej strony
void RightStr(tstring *Out, const tstring &s, size_t Length);

/// Zwraca liczb� wyst�pie� pod�a�cucha
size_t SubstringCount(const tstring &str, const tstring &substr);

/// Zwraca true, je�li podane �a�cuchy s� r�wne bez rozr�niania wielko�ci liter
bool StrEqualI(const tstring &s1, const tstring &s2);
/// Zwraca true, je�li podfragmenty podanych �a�cuch�w s� identyczne
bool SubStrEqual(const tstring &s1, size_t off1, const tstring &s2, size_t off2, size_t length);
/// Zwraca true, je�li podfragmenty podanych �a�cuch�w s� identyczne nie rozr�niaj�c wielko�ci liter
bool SubStrEqualI(const tstring &s1, size_t off1, const tstring &s2, size_t off2, size_t length);

/// Czy �a�cuch zawiera znaki ko�ca wiersza?
bool ContainsEOL(const tstring &s);

/// Zwraca true, jesli podany lancuch zaczyna sie od podanego podlancucha
bool StrBegins(const tstring &s, const tstring &sub, size_t Begin = 0);
/// Zwraca true, je�li podany �a�cuch ko�czy si� podanym pod�a�cuchem
bool StrEnds(const tstring &s, const tstring &Sub);

/// Kolejne wywo�ania rozdzielaj� �a�cuch na kolejne elementy oddzielone w jego tre�ci okre�lonym pod�a�cuchem
/** \param[out] out
\param[in,out] index */
bool Split(const tstring &s, const tstring &delimiter, tstring *out, size_t *index);
/// Dzia�a jak Split(), ale �a�cuchem rozdzielaj�cym jest ka�dy dowolny znak z delimiters
bool SplitFirstOf(const tstring &s, const tstring &delimiters, tstring *out, size_t *index);
/// Dzieli �a�cuch na cz�ci i zwraca je jako wektor
void Split(STRING_VECTOR *Out, const tstring &s, const tstring &Delimiter);
/// Kolejne wywo�ania rozdzielaj� �a�cuch na kolejne elementy oddzielone w jego tre�ci kt�r�� z sekwencji uznawan� za koniec wiersza (czyli na kolejne wiersze)
bool SplitEOL(const tstring &s, tstring *out, size_t *index);
/// Kolejne wywo�ania rozdzielaj� �a�cuch na elementy oddzielone odst�pami uwzgl�dniaj�c ci�gi obi�te w cudzys�owy <tt>""</tt> jako ca�o��
bool SplitQuery(const tstring &s, tstring *out, size_t *index);
/// Sprawdza, czy podany �ancuch jest zgodny z podan� mask� mog�c� zawiera� znaki wieloznaczne
/** '?' zast�puje dowolny jeden znak, '*' zast�puje dowoln� liczb� (tak�e 0) dowolnych znak�w. */
bool ValidateWildcard(const tstring &Mask, const tstring &S, bool CaseSensitive = true, size_t MaskOff = 0, size_t SOff = 0);
/// Zwraca zmiennoprzecinkow� trafno�� wyszukiwania stringa SubStr w stringu Str
/** Zaawansowany algorytm, wymy�lony przeze mnie dawno temu. Bierze pod uwag�
rzeczy takie jak:
-# ile razy pod�a�cuch wyst�puje
-# czy pasuje wielko�� liter
-# d�ugo�� �a�cucha i pod�a�cucha
-# czy to ca�e s�owo
-# czy to ca�y �a�cuch. */
float FineSearch(const tstring &SubStr, const tstring &Str);
/// Odleg�o�� edycyjna mi�dzy dwoma �a�cuchami.
/** Z�o�ono��: O( s1.length * s2.length ).
Im mniejsza, tym �a�cuchy bardziej podobne. Je�li identyczne, zwraca 0. */
size_t LevenshteinDistance(const tstring &s1, const tstring &s2);
/// Odleg�o�� edycyjna mi�dzy dwoma �a�cuchami bez uwzgl�dniania wielko�ci liter.
/** Z�o�ono��: O( s1.length * s2.length ).
Im mniejsza, tym �a�cuchy bardziej podobne. Je�li identyczne, zwraca 0. */
size_t LevenshteinDistanceI(const tstring &s1, const tstring &s2);

/** \addtogroup base_natural_sort Sortowanie naturalne
Sortowanie naturalne, czyli takie, w kt�rym np. "abc2" jest przed "abc120". */
//@{

/// Klasa do por�wnywania w porz�dku naturalnym.
class StringNaturalCompare
{
private:
	bool m_CaseInsensitive;

	int CompareNumbers(const tstring &s1, size_t i1, const tstring &s2, size_t i2);

public:
	StringNaturalCompare(bool CaseInsensitive) : m_CaseInsensitive(CaseInsensitive) { }
	int Compare(const tstring &s1, const tstring &s2);
};

/// Predykat do sortowania �a�cuch�w w porz�dku naturalnym
/** Przyk�ad u�ycia:
\code
std::vector<string> v;
std::sort(v.begin(), v.end(), common::StringNaturalLess());
\endcode
*/
class StringNaturalLess : public StringNaturalCompare
{
public:
	StringNaturalLess(bool CaseInsensitive = true) : StringNaturalCompare(CaseInsensitive) { }
	bool operator () (const tstring &s1, const tstring &s2) { return (Compare(s1, s2) < 0); }
};

/// Predykat do sortowania �a�cuch�w w porz�dku naturalnym
class StringNaturalGreater : public StringNaturalCompare
{
public:
	StringNaturalGreater(bool CaseInsensitive = true) : StringNaturalCompare(CaseInsensitive) { }
	bool operator () (const tstring &s1, const tstring &s2) { return (Compare(s1, s2) > 0); }
};

//@}

/// Predykat do por�wnywania �a�cuch�w bez rozr�niania wielko�ci liter.
class StrLessCi
{
public:
	bool operator () (const tstring &s1, const tstring &s2)
	{
		tstring u1 = s1, u2 = s2;
		UpperCase(&u1);
		UpperCase(&u2);
		return u1 < u2;
	}
};
/// Predykat do por�wnywania �a�cuch�w bez rozr�niania wielko�ci liter.
class StrGreaterCi
{
public:
	bool operator () (const tstring &s1, const tstring &s2)
	{
		tstring u1 = s1, u2 = s2;
		UpperCase(&u1);
		UpperCase(&u2);
		return u1 > u2;
	}
};

/** \addtogroup base_unicode Obs�uga Unicode
Dost�pne tylko w Windows. */
//@{

#ifdef WIN32

/** \addtogroup base_unicode_convs Konwersje �a�cuch�w Unicode

Konwersje mi�dzy �a�cuchem Unicode (UTF-16) a �a�cuchem w innym kodowaniu - Single Byte lub Multi Byte.

CodePage to kodowanie znak�w typu char. Przyk�adowe warto�ci:
  - Sta�e: CP_UTF8 (UTF-8), CP_ACP (natywna, 1-bajtowa strona kodowa systemu).
  - Numery takie jak 1250 dla kodowania Windows-1250 (p. MSDN > "Code Page Identifiers").

Funkcje zwracaj� false w przypadku niepowodzenia konwersji. W�wczas Out jest pusty.
*/
//@{

bool ConvertUnicodeToChars(string *Out, const wstring &S, unsigned CodePage);
bool ConvertUnicodeToChars(string *Out, const wchar_t *S, unsigned NumChars, unsigned CodePage);

bool ConvertCharsToUnicode(wstring *Out, const string &S, unsigned CodePage);
bool ConvertCharsToUnicode(wstring *Out, const char *S, unsigned NumChars, unsigned CodePage);	

//@}

/** \addtogroup base_unicode_headers Nag��wki Unicode
�a�cuchy zako�czone zerem - nag��wki poszczeg�lnych format�w Unicode.
(Standardowo u�ywany w Windows jest UTF-16 Little Endian.) */
//@{
extern const char * const BOM_UTF8;
extern const char * const BOM_UTF16_LE;
extern const char * const BOM_UTF16_BE;
//@}

#endif

/** \addtogroup base_unicode_conv_functions Konwersje mi�dzy tstring, string, wstring
W przypadku niepowodzenia zwracaj� false i Out jest wtedy pusty. */
//@{
#ifdef _UNICODE
	bool TstringToString(string *Out, const tstring &S);
	bool StringToTstring(tstring *Out, const string &S);
	inline bool TstringToWstring(wstring *Out, const tstring &S) { *Out = S; return true; }
	inline bool WstringToTstring(tstring *Out, const wstring &S) { *Out = S; return true; }

	inline string TstringToStringR(const tstring &S) { string R;  if (!TstringToString(&R, S)) return string();  return R; }
	inline tstring StringToTstringR(const string &S) { tstring R; if (!StringToTstring(&R, S)) return tstring(); return R; }
	inline wstring TstringToWstring(const tstring &S) { return S; }
	inline tstring WstringToTstring(const wstring &S) { return S; }
#else
	inline bool TstringToString(string *Out, const tstring &S) { *Out = S; return true; }
	inline bool StringToTstring(tstring *Out, const string &S) { *Out = S; return true; }
	inline string TstringToStringR(const tstring &S) { return S; }
	inline tstring StringToTstringR(const string &S) { return S; }
	#ifdef WIN32
		bool TstringToWstring(wstring *Out, const tstring &S);
		bool WstringToTstring(tstring *Out, const wstring &S);
		inline wstring TstringToWstringR(const tstring &S) { wstring R; if (!TstringToWstring(&R, S)) return wstring(); return R; }
		inline tstring WstringToTstringR(const wstring &S) { tstring R; if (!WstringToTstring(&R, S)) return tstring(); return R; }
	#endif
#endif
//@}
// Konwersje mi�dzy tstring, string, wstring

//@}
// Obs�uga Unicode

//@}
// �a�cuchy

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_paths �cie�ki do plik�w */
//@{

#ifdef WIN32
	/// Separator katalog�w w �cie�ce, zale�ny od platformy.
	const tchar DIR_SEP = _T('\\');
#else
	const tchar DIR_SEP = _T('/');
#endif

/// Zwraca true, je�li �cie�ka jest bezwzgl�dna
bool PathIsAbsolute(const tstring &s);
/// Dodaje do sciezki konczacy '/' lub '\', jesli go nie ma - na miejscu
void IncludeTrailingPathDelimiter(tstring *InOutPath);
/// Dodaje do sciezki konczacy '/' lub '\', jesli go nie ma - do nowego stringa
void IncludeTrailingPathDelimiter(tstring *OutPath, const tstring &InPath);
/// Pozbawia sciezke konczacego '/' lub '\', jesli go ma - na miejscu
void ExcludeTrailingPathDelimiter(tstring *InOutPath);
/// Pozbawia sciezke konczacego '/' lub '\', jesli go ma - do nowego stringa
void ExcludeTrailingPathDelimiter(tstring *OutPath, const tstring &InPath);
/// Zwraca pocz�tek �cie�ki, w postaci takiej jak "C:\", "\\komputer\udzia�\" czy "/" albo "\"
/** Je�li �cie�ka jest wzgl�dna, zwraca �a�cuch pusty. */
void ExtractPathPrefix(tstring *OutPrefix, const tstring &s);
/// Zwraca �cie�k� do pliku bez nazwy pliku
void ExtractFilePath(tstring *OutPath, const tstring &s);
/// Zwraca sam� nazw� pliku bez �cie�ki
void ExtractFileName(tstring *OutFileName, const tstring &s);
/// Zwraca rozszerzenie pliku wraz z kropk�
void ExtractFileExt(tstring *OutExt, const tstring &s);
/// Zmienia w nazwie pliku rozszerzenie na nowe
/** Jesli Ext = "", usuwa rozszerzenie.
Nowe rozszerzenie musi zawiera� rozpoczynaj�c� kropk� (tzn. nie musi, ale wypada�oby :) */
void ChangeFileExt(tstring *Out, const tstring &FileName, const tstring &Ext);
/// Pozbawia sciezke artefaktow typu ".\\" czy "..\\"
/** Odpowiednio ja oczywiscie przetwarza tak, ze wyjscie jest logicznie rownowazne wejsciu. */
void NormalizePath(tstring *OutPath, const tstring &s);
/// Przetwarza sciezke wzgledna na bezwzgledna wzgledem okreslonej sciezki
/** Na przyk�ad Base="C:\\Kat", Path="PodKat\\Plik.txt", Wynik="C:\\Kat\\PodKat\\Plik.txt". */
void RelativeToAbsolutePath(tstring *Out, const tstring &Base, const tstring &Path);
/// Przetwarza sciezke bezwzgledna na wzgledna wzgledem okreslonej sciezki
/** Je�li si� nie da, wychodzi r�wnie� bezwzgl�dna, r�wna Target.
Na przyk�ad Base="C:\\Kat", Tareget="C:\\Kat\\Podkat\\Plik.txt", Wynik="PodKat\\Plik.txt". */
void AbsoluteToRelativePath(tstring *Out, const tstring &Base, const tstring &Target);

//@}
// �cie�ki do plik�w


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_conversions Konwersje mi�dzy �a�cuchem a r�nymi typami */
/**
Stara�em si� zagwarantowa� w Windows (w Linux jeszcze nie - mo�e kiedy�...),
�eby konwersje zawsze dzia�a�y tak samo niezale�nie od locale ustawionego w
bibliotece standardowej C (funkcja setlocale), C++ (klasa locale) czy WinAPI
(funkcja SetThreadLocale). Szczeg�lnie konwersje mi�dzy liczb�
zmiennoprzecinkow� a �a�cuchem zawsze u�ywaj� kropki, a nie przecinka.
*/
//@{

/** \internal */
extern const tchar _DIGITS_L[];
/** \internal */
extern const tchar _DIGITS_U[];

/// Zwraca liczbowy odpowiednik cyfry szesnastkowej.
/** Je�li b��d, zwraca 0xFF.
Akceptuje zar�wno ma�e, jak i du�e litery.
(Dwie wersje tej funkcji - osobno dla ANSI i Unicode - s� potrzebne w Stream - HexDecoder.) */
inline int HexDigitToNumber(char Ch)
{
	if      (Ch >= '0' && Ch <= '9') return (int)(uint1)(Ch -  '0');
	else if (Ch >= 'A' && Ch <= 'F') return (int)(uint1)(Ch - ('A' - 10));
	else if (Ch >= 'a' && Ch <= 'f') return (int)(uint1)(Ch - ('a' - 10));
	else return 0xFF;
}
#ifdef WIN32
inline int HexDigitToNumber(wchar_t Ch)
{
	if      (Ch >= L'0' && Ch <= L'9') return (int)(Ch -  L'0');
	else if (Ch >= L'A' && Ch <= L'F') return (int)(Ch - (L'A' - 10));
	else if (Ch >= L'a' && Ch <= L'f') return (int)(Ch - (L'a' - 10));
	else return 0xFF;
}
#endif

/// Konwersja liczby ca�kowitej na �a�cuch
/** \param Base musi by� z zakresu 2..36 */
template <typename T>
void UintToStr(tstring *Out, T x, uint4 Base = 10, bool UpperCase = true)
{
	if (x == 0)
	{
		Out->assign(_T("0"));
		return;
	}

	Out->clear();
	Out->reserve(8);

	// Podstawa to pot�ga dw�jki - b�dzie pro�ciej, bo przesuwanie bitowe zamiast dzielenia
	if (IsPow2<uint4>(Base))
	{
		// O ile bit�w przesuwa�?
		uint4 Bits = log2u(Base);
		// Maska bitowa do &-owania
		uint4 BitMask = GetBitMask(Bits);
		// Jazda!
		if (UpperCase)
		{
			while (x != 0)
			{
				*Out += _DIGITS_U[x & BitMask];
				x = x >> Bits;
			}
		}
		else
		{
			while (x != 0)
			{
				*Out += _DIGITS_L[x & BitMask];
				x = x >> Bits;
			}
		}
	}
	// Podstawa to nie pot�ga dw�jki
	else
	{
		if (UpperCase)
		{
			while (x != 0)
			{
				*Out += _DIGITS_U[x % Base];
				x /= Base;
			}
		}
		else
		{
			while (x != 0)
			{
				*Out += _DIGITS_L[x % Base];
				x /= Base;
			}
		}
	}

	ReverseString(Out);
}

template <typename T>
void IntToStr(tstring *Out, T x, uint4 Base = 10, bool UpperCase = true)
{
	if (x == 0)
	{
		Out->assign(_T("0"));
		return;
	}

	Out->clear();
	Out->reserve(8);

	// Liczba dodatnia - identycznie jak w UintToStr
	if (x > 0)
	{
		// Podstawa to pot�ga dw�jki - b�dzie pro�ciej, bo przesuwanie bitowe zamiast dzielenia
		if (IsPow2<uint4>(Base))
		{
			// O ile bit�w przesuwa�?
			uint4 Bits = log2u(Base);
			// Maska bitowa do &-owania
			uint4 BitMask = GetBitMask(Bits);
			// Jazda!
			if (UpperCase)
			{
				while (x != 0)
				{
					*Out += _DIGITS_U[x & BitMask];
					x = x >> Bits;
				}
			}
			else
			{
				while (x != 0)
				{
					*Out += _DIGITS_L[x & BitMask];
					x = x >> Bits;
				}
			}
		}
		// Podstawa to nie pot�ga dw�jki
		else
		{
			if (UpperCase)
			{
				while (x != 0)
				{
					*Out += _DIGITS_U[x % Base];
					x /= Base;
				}
			}
			else
			{
				while (x != 0)
				{
					*Out += _DIGITS_L[x % Base];
					x /= Base;
				}
			}
		}
	}
	// Liczba ujemna - tu b�dzie musia�o by� inaczej
	// Modulo jest UB, wi�c u�yjemy obej�cia.
	else
	{
		T x_div_base;
		if (UpperCase)
		{
			while (x != 0)
			{
				x_div_base = x/(T)Base;
				*Out += _DIGITS_U[- (x - x_div_base*(T)Base)];
				x = x_div_base;
			}
		}
		else
		{
			while (x != 0)
			{
				x_div_base = x/(T)Base;
				*Out += _DIGITS_L[- (x - x_div_base*(T)Base)];
				x = x_div_base;
			}
		}
		*Out += '-';
	}

	ReverseString(Out);
}

/// Konwertuje znak cyfry w dowolknym systemie ('0'..'9', 'A'..'Z', 'a'..'z') na liczb�, zwraca false je�li b��d.
/** \internal */
template <typename T>
bool _CharToDigit(T *Digit, tchar ch)
{
	if (ch >= _T('0') && ch <= _T('9'))
		*Digit = static_cast<T>(ch-_T('0'));
	else if (ch >= _T('A') && ch <= _T('Z'))
		*Digit = static_cast<T>(ch-_T('A')+10);
	else if (ch >= _T('a') && ch <= _T('z'))
		*Digit = static_cast<T>(ch-_T('a')+10);
	else
		return false;
	return true;
}

/// Konwersja �a�cucha na liczb� ca�kowit�
/** \return Zwraca:
-  0 - sukces
- -1 - b��d sk�adni �a�cucha
- -2 - przekroczenie zakresu */
template <typename T>
int StrToUint(T *Number, const tstring &str, unsigned Base = 10)
{
	T BaseT = static_cast<T>(Base);
	if (str.empty()) return -1;
	*Number = 0;
	T Digit, LastNumber = 0, Limit = std::numeric_limits<T>::max()/BaseT;
	for (size_t i = 0; i < str.length(); ++i) {
		if (!_CharToDigit(&Digit, str[i])) return -1;
		if (Digit >= BaseT)  return -1;
		if (*Number > Limit) return -2;
		*Number = *Number * BaseT + Digit;
		if (*Number < LastNumber) return -2;
		LastNumber = *Number;
	}
	return 0;
}

template <typename T>
int StrToInt(T *Number, const tstring &str, unsigned Base = 10)
{
	T BaseT = static_cast<T>(Base);
	if (str.empty()) return -1;
	*Number = 0;
	size_t i = 0;
	int Sign = +1;
	if (str[0] == '+') i = 1;
	else if (str[0] == '-') { Sign = -1; i = 1; }
	T Digit, LastNumber = 0, Limit;
	if (Sign > 0) Limit = std::numeric_limits<T>::max()/BaseT;
	else          Limit = std::numeric_limits<T>::min()/BaseT;
	for (; i < str.length(); ++i) {
		if (!_CharToDigit(&Digit, str[i])) return -1;
		if (Digit >= BaseT) return -1;
		if (Sign > 0) { if (*Number > Limit) return -2; }
		else          { if (*Number < Limit) return -2; }
		*Number = *Number * BaseT + Digit * Sign;
		if (Sign > 0) { if (*Number < LastNumber) return -2; }
		else          { if (*Number > LastNumber) return -2; }
		LastNumber = *Number;
	}
	return 0;
}

template <typename T> inline tstring IntToStrR (T x, int base = 10, bool UpperCase = true) { tstring r; IntToStr<T> (&r, x, base, UpperCase); return r; }
template <typename T> inline tstring UintToStrR(T x, int base = 10, bool UpperCase = true) { tstring r; UintToStr<T>(&r, x, base, UpperCase); return r; }

inline void Size_tToStr(tstring *Out, size_t x, size_t Base = 10, bool UpperCase = true) { UintToStr(Out, (uint4)x, Base, UpperCase); }
inline tstring Size_tToStrR(size_t x, size_t Base = 10, bool UpperCase = true) { tstring R; Size_tToStr(&R, x, Base, UpperCase); return R; }

/// Konwersja liczby na �a�cuch o minimalnej podanej d�ugo�ci.
/** Zostanie do tej d�ugo�ci uzupe�niony zerami. */
template <typename T>
void UintToStr2(tstring *Out, T x, unsigned Length, int base = 10)
{
	tstring Tmp;
	UintToStr(&Tmp, x, base);
	if (Tmp.length() >= Length)
		*Out = Tmp;
	else
	{
		Out->clear();
		Out->reserve(std::max(Tmp.length(), Length));
		for (size_t Left = Length - Tmp.length(); Left > 0; Left--)
			*Out += _T('0');
		*Out += Tmp;
	}
}
template <typename T>
void IntToStr2(tstring *Out, T x, unsigned Length, int base = 10)
{
	tstring Tmp;
	IntToStr<T>(&Tmp, x, base);
	if (Tmp.length() >= Length)
		*Out = Tmp;
	else
	{
		Out->clear();
		Out->reserve(std::max(Tmp.length(), Length));
		assert(!Tmp.empty());
		if (Tmp[0] == _T('-'))
		{
			*Out += _T('-');
			for (size_t Left = Length - Tmp.length(); Left > 0; Left--)
				*Out += _T('0');
			Out->append(Tmp.begin()+1, Tmp.end());
		}
		else
		{
			for (size_t Left = Length - Tmp.length(); Left > 0; Left--)
				*Out += _T('0');
			*Out += Tmp;
		}
	}
}

template <typename T> tstring UintToStr2R(T x, unsigned Length, int Base = 10) { tstring R; UintToStr2<T>(&R, x, Length, Base); return R; }
template <typename T> tstring IntToStr2R (T x, unsigned Length, int Base = 10) { tstring R; IntToStr2<T> (&R, x, Length, Base); return R; }

/// Konwertuje znak na �a�cuch, jako �e automatycznie to si� niestety nie odbywa
inline void CharToStr(tstring *Out, tchar ch) { Out->clear(); *Out += ch; }
inline tstring CharToStrR(tchar ch) { tstring s; s += ch; return s; }

/// Konwersja liczb zmiennoprzecinkowych na �a�cuch
/** \param Mode:
- 'e' : -0.12345e-001
- 'E' : -0.12345E-001
- 'f' : -0.12345
- 'g' : optimum ('e', 'f')
- 'G' : optimum ('E', 'f')
\param Precision 0..20 */
void DoubleToStr(tstring *Out, double x, char Mode = 'g', int Precision = 6);
void FloatToStr(tstring *Out, float x, char Mode = 'g', int Precision = 6);

inline tstring DoubleToStrR(double x, char Mode = 'g', int Precision = 6) { tstring R; DoubleToStr(&R, x, Mode, Precision); return R; }
inline tstring FloatToStrR (float x, char Mode = 'g', int Precision = 6) { tstring R;  FloatToStr (&R, x, Mode, Precision); return R; }

/// Konwersja �a�cucha na liczb� zmiennoprzecinkow�.
/**
- W przypadku b��du sk�adni zwracaj� warto�� != 0.
- B��dy zakresu nie s� sprawdzane - wynik niezdefiniowany. */
int StrToDouble(double *out, const tstring &s);
int StrToFloat (float *out,  const tstring &s);

/// Konwertuje warto�� logiczn� na �a�cuch
/** \param mode:
- '0' : 0 / 1
- 'f' : false / true
- 'F' : False / True
- 'U' : FALSE / TRUE
- 'g' : f / t
- 'G' : F / T */
void BoolToStr(tstring *Out, bool x, char mode = 'f');
inline tstring BoolToStrR(bool x, char mode = 'f') { tstring R; BoolToStr(&R, x, mode); return R; }
/// Konwertuje �a�cuch na warto�� logiczn�
/**
- Dozwolone wszelkie warto�ci jak w BoolToStr.
- B��d: zwraca false. */
bool StrToBool(bool *result, const tstring &s);

/// Konwertuje wska�nik na �a�cuch 8 znak�w zapisany szesnastkowo
void PtrToStr(tstring *Out, const void* p);
inline tstring PtrToStrR(const void *p) { tstring R; PtrToStr(&R, p); return R; }

/// Liczba bajt�w na �a�cuch z rozmiarem np. "1 B", "10.5 kB"
/** Jako T uzywac uint1, uint2, uint4, uint8 lub int ale na pewno warto�ci dodaniej.
\param Space czy mi�dzy liczb� a jednostk� dawa� spacj�
\param Precision ilo�� cyfr po przecinku (mo�e by� te� 0) */
template <typename T>
void SizeToStr(tstring *str, T size, bool Space, int Precision)
{
	double size2 = (double)size;
	if (size2 >= 1024.0*1024.0*1024.0*1024.0)
	{
		DoubleToStr( str, size2/(1024.0*1024.0*1024.0*1024.0), 'f', Precision );
		str->append(Space ? _T(" TB") : _T("TB"));
	}
	else if (size2 >= 1024.0*1024.0*1024.0)
	{
		DoubleToStr( str, size2/(1024.0*1024.0*1024.0), 'f', Precision );
		str->append(Space ? _T(" GB") : _T("GB"));
	}
	else if (size2 >= 1024.0*1024.0)
	{
		DoubleToStr( str, size2/(1024.0*1024.0), 'f', Precision );
		str->append(Space ? _T(" MB") : _T("MB"));
	}
	else if (size2 >= 1024.0)
	{
		DoubleToStr( str, size2/1024.0, 'f', Precision );
		str->append(Space ? _T(" KB") : _T("KB"));
	}
	else
	{
		UintToStr( str, size );
		str->append(Space ? _T(" B") : _T("B"));
	}
}
template <typename T> tstring SizeToStrR(T Size, bool Space, int Precision) { tstring r; SizeToStr<T>(&r, Size, Space, Precision); return r; }

//@}
// Konwersje mi�dzy �a�cuchem a r�nymi typami


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_time Czas */
//@{

/// Klasa do precyzyjnego mierzenie czasu
class TimeMeasurer
{
private:
	#ifdef WIN32
		bool m_QPF_Using;
		int8 m_QPF_TicksPerSec;
		int8 m_QPF_Start;
		uint4 m_Start;
	#else
		// w mikrosekundach
		int8 m_Start;
	#endif

public:
	TimeMeasurer();

	/// Zwraca czas od uruchomienia aplikacji, w sekundach
	double GetTimeD();
	/// Zwraca czas od uruchomienia aplikacji, w sekundach
	float  GetTimeF();
};

/// G��wny miernik czasu dla w�tku g��wnego
extern TimeMeasurer g_Timer;

/// Zatrzymuje bie��cy w�tek na podan� liczb� milisekund
/** Dzia�a z jak��tam dok�adno�ci� - mo�e nie super, ale na pewno wi�ksz� ni�
ca�a sekunda. */
void Wait(uint4 Miliseconds);

//@}
// Czas


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_periodic_funcs Funkcje okresowe */
//@{

/*
Funkcje zwracaj�ce r�nego rodzaju przebiegi okresowe.
Domy�lne (bez ustawianych w�asnych parametr�w) maj� zakres wyj�ciowy 0..1,
cz�stotliwo�� 1 i faz� 0.
- Base      - dolne ograniczenie
- Amplitude - pe�na wysoko��
*/

/// Standard sine wave which smoothly changes from low to high and back again.
inline float WaveformSine(float x, float Base, float Amplitude, float Frequency, float Phase)
{
	return Base + (sinf((x + Phase) * Frequency * PI_X_2)+1.0f)*0.5f * Amplitude;
}
inline float WaveformSine(float x)
{
	return (sinf(x * PI_X_2)+1.0f)*0.5f;
}

/// An angular wave with a constant increase / decrease speed with pointed peaks.
inline float WaveformTriangle(float x, float Base, float Amplitude, float Frequency, float Phase)
{
	float Input = frac((x + Phase) * Frequency);
	float Output;
	if (Input < 0.25f)
		Output = Input * 4.0f;
	else if (Input < 0.75f)
		Output = 1.0f - ((Input - 0.25f) * 4.0f);
	else
		Output = ((Input - 0.75f) * 4.0f) - 1.0f;
	return Base + (Output+1.0f)*0.5f * Amplitude;
}
inline float WaveformTriangle(float x)
{
	float Input = frac(x);
	float Output;
	if (Input < 0.25f)
		Output = Input * 4.0f;
	else if (Input < 0.75f)
		Output = 1.0f - ((Input - 0.25f) * 4.0f);
	else
		Output = ((Input - 0.75f) * 4.0f) - 1.0f;
	return (Output+1.0f)*0.5f;
}

/// Half of the time is spent at the min, half at the max with instant transition between.
inline float WaveformSquare(float x, float Base, float Amplitude, float Frequency, float Phase)
{
	return Base + (frac((x + Phase) * Frequency) <= 0.5f ? 1.0f : 0.0f) * Amplitude;
}
inline float WaveformSquare(float x)
{
	return frac(x) <= 0.5f ? 1.0f : 0.0f;
}

/// Gradual steady increase from min to max over the period with an instant return to min at the end.
inline float WaveformSawtooth(float x, float Base, float Amplitude, float Frequency, float Phase)
{
	return Base + frac((x + Phase) * Frequency) * Amplitude;
}
inline float WaveformSawtooth(float x)
{
	return frac(x);
}

/// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
inline float WaveformInvSawtooth(float x, float Base, float Amplitude, float Frequency, float Phase)
{
	return Base + (1.0f - frac((x + Phase) * Frequency)) * Amplitude;
}
inline float WaveformInvSawtooth(float x)
{
	return 1.0f - frac(x);
}

/// Pulse Width Modulation.
/** Works like square, except the high to low transition is controlled by duty
cycle. With a duty cycle of 50% (0.5) will give the same output as square. */
inline float WaveformPWM(float x, float DutyCycle, float Base, float Amplitude, float Frequency, float Phase)
{
	return Base + (frac((x + Phase) * Frequency) <= DutyCycle ? 1.0f : 0.0f) * Amplitude;
}
inline float WaveformPWM(float x, float DutyCycle)
{
	return (frac(x) <= DutyCycle ? 1.0f : 0.0f);
}

//@}
// Funkcje okresowe


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup base_random_gen Generator liczb pseudolosowych
*/
//@{

/// Generator liczb pseudolosowych
/** Jest przede wszystkim szybki. Nie jest bardzo dobrze losowy. Mo�na go u�ywa�
jako deterministycznego tworz�c w�asne obiekty tej klasy i r�cznie je
naziarniaj�c. */
class RandomGenerator
{
private:
	// Current seed
	uint4 m_Seed;
	float m_NextNormalNumber; bool m_NextNormalNumberIs;

public:
	/// Constructor - seed from the clock
	RandomGenerator();
	/// Constructor - seed with given seed
	RandomGenerator(uint4 seed) : m_Seed(seed), m_NextNormalNumberIs(false) { }

	/// Wpisuje nowe ziarno.
	void Seed(uint4 a_Seed)
	{
		m_Seed = a_Seed;
	}

	/// Generuje liczb� losow� ca�kowit� bez znaku, pe�ny zakres
	/** Na podstawie ksi��ki "Pere�ki programowania gier", tom III, Dante Treglia
	Uwaga! M�odsze bity s� s�abo losowe, powtarzaj� si� w bardzo kr�tkim okresie. */
	uint4 RandUint_Fast()
	{
		return ( m_Seed = (m_Seed * 196314165 + 907633515) );
	}
	/// Generuje liczb� losow�, w kt�rej wszystkie bity s� do�� losowe
	uint4 RandUint()
	{
		return
			(RandUint_Fast() & 0xFF000000)       |
			(RandUint_Fast() & 0xFF000000) >>  8 |
			(RandUint_Fast() & 0xFF000000) >> 16 |
			(RandUint_Fast() & 0xFF000000) >> 24;
	}
	/// Generuje liczb� losow� w zakresie 0 .. max-1
	uint4 RandUint(uint4 max)
	{
		return RandUint() % max;
	}
	/// Generuje liczb� losow� w zakresie min .. max-1
	uint4 RandUint(uint4 min, uint4 max)
	{
		return RandUint() % (max-min) + min;
	}

	/// Generuje losowy bajt
	uint1 RandByte()
	{
		return (RandUint_Fast() & 0xFF000000) >> 24;
	}

	/// Generuje liczb� losow� rzeczywist� z przedzia�u 0.0..1.0
	/** Autor tego genialnego algorytmu: Mikael */
	float RandFloat()
	{
		return absolute_cast<float>(RandUint() & 0x007FFFFF | 0x3F800000) - 1.0f;
	}
	/// Generuje liczb� losow� rzeczywist� z przedzia�u 0.0..max
	float RandFloat(float max)
	{
		return RandFloat() * max;
	}
	/// Generuje liczb� losow� rzeczywist� z przedzia�u min..max
	float RandFloat(float min, float max)
	{
		return RandFloat() * (max - min) + min;
	}

	/// Generuje losowy stan logiczny
	bool RandBool()
	{
		return (RandUint() >= 0x7FFFFFFF);
	}

	/// Generuje liczb� losow� ca�kowit� ze znakiem z zakresu Min .. Max-1
	int RandInt(int Min, int Max)
	{
		if (Max > Min)
			return static_cast<int>(RandUint(Max-Min)) + Min;
		else
			return static_cast<int>(RandUint(Min-Max)) + Max;
	}

	/// Wype�nia podany bufor losowymi danymi binarnymi
	/** \param DataLength w bajtach. */
	void RandData(void *OutData, size_t DataLength);

	/// Generuje liczb� losow� o rozk�adzie normalnym (Gaussa)
	/** Zgodnie z definicj�, wylosowana liczba le�y w zakresie z prawdopodobie�stwem:
	- -1 * sigma .. +1 * sigma : 68%
	- -2 * sigma .. +2 * sigma : 95%
	- -3 * sigma .. +3 * sigma : 99.73% */
	float RandNormal(float sigma);
};

/// Domy�lny generator liczb losowych do u�ywania w w�tku g��wnym i kiedy nie musi by� deterministyczny
extern RandomGenerator g_Rand;

/// Wolniejszy w inicjalizacji, generowaniu i wi�kszy, ale za to tu�o lepszy generator liczb pseudolosowych.
/** �r�d�o:
Mersenne Twister Home Page,
http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
*/
class MersenneTwister
{
public:
	/// Inicjalizuje bie��cym czasem systemowym
	MersenneTwister();
	/// Inicjalizuje podanym ziarnem
	MersenneTwister(uint Seed);
	/// Inicjalizuje ziarnem w postaci podanej tablicy
	MersenneTwister(uint InitKeys[], int KeyCount);

	/// Generuje liczb� uint [0,0xffffffff]
	uint NextUint();
	/// Generuje liczb� int [0,0x7fffffff]
	int NextInt31();
	/// Generuje liczb� double [0,1]
	double NextReal1();
	/// Generuje liczb� double [0,1)
	double NextReal2();
	/// Generuje liczb� double (0,1)
	double NextReal3();
	/// Generuje liczb� double [0,1) z rozdzielczo�ci� 53 bit�w
	double NextReal_Res53();

private:
	uint m_State[624];
	int m_Left;
	uint *m_Next;

	void Init(uint Seed);
	void NextState();
};

/// Generator unikatowych identyfikator�w
class UniqueGenerator
{
private:
	uint4 m_Next;

public:
	/// Pierwszy b�dzie mia� nr 1.
	UniqueGenerator();
	/// Pierwszy b�dzie mia� podany tutaj numer
	UniqueGenerator(uint4 First);

	/// Zwraca unikatow� liczb�
	uint4 GetUint() { return m_Next++; }
	/// Zwraca unikatowy �a�cuch w formacie "########", gdzie ######## to liczba szesnastkowa.
	void GetString(tstring *Out);
	tstring GetString() { tstring R; GetString(&R); return R; }
	/// Zwraca unikatowy �a�cuch w formacie "<prefix>########", gdzie ######## to liczba szesnastkowa.
	void GetString(tstring *Out, const tstring &Prefix);
	/// \copydoc GetString(tstring*,const tstring&)
	tstring GetString(const tstring &Prefix) { tstring R; GetString(&R, Prefix); return R; }
};

/// Generator domy�lny do u�ytku w w�tku g��wnym.
extern UniqueGenerator g_Unique;

//@}


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Parser wiersza polece�

/// \internal
class CmdLineParser_pimpl;

/// Parser wiersza polece�
class CmdLineParser
{
private:
	scoped_ptr<CmdLineParser_pimpl> pimpl;

public:
	/// Rodzaj pobranej informacji
	enum RESULT
	{
		RESULT_OPT,       ///< Opcja
		RESULT_PARAMETER, ///< Go�y parametr bez opcji
		RESULT_END,       ///< Koniec parametr�w
		RESULT_ERROR,     ///< B��d sk�adni
	};

	/// Wersja dla main(int argc, char **argv)
	CmdLineParser(int argc, tchar **argv);
	/// Wersja dla WinMain(HINSTANCE Instance, HINSTANCE, char *CmdLine, int CmdShow)
	CmdLineParser(const tchar *CmdLine);

	~CmdLineParser();

	/// Rejestruje opcj� jednoznakow�.
	/** \param Id podawa� liczby wi�ksze od 0. */
	void RegisterOpt(uint Id, tchar Opt, bool Parameter);
	/// Rejestruje opcj� wieloznakow�.
	/** \param Id podawa� liczby wi�ksze od 0. */
	void RegisterOpt(uint Id, const tstring &Opt, bool Parameter);

	/// Wczytuje nast�pn� informacj�, zwraca jej rodzaj
	RESULT ReadNext();

	/// Zwraca dane na temat ostatnio wczytanej informacji - identyfikator opcji.
	/** Je�li nie zosta�a wczytana opcja, zwraca 0. */
	uint GetOptId();
	/// Zwraca dane na temat ostatnio wczytanej informacji - tre�� parametru.
	/** Je�li nie ma, �a�cuch pusty. */
	const tstring & GetParameter();
};

//@}
// code_base

} // namespace common


//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
/** \addtogroup code_sthtostr Uniwersalne konwersje
Uniwersalny i rozszerzalny mechanizm konwersji na i z �a�cucha */
//@{

template <typename T>
struct SthToStr_obj
{
	void operator () (tstring *Str, const T &Sth)
	{
		// Runtime error
		assert(0 && "SthToStr: Unsupported type.");
		// Compilation error
		// Dzia�a tylko w Visual C++, g++ pokazuje b��d kompilacji nawet kiedy nieu�yte
#ifdef WIN32
		int y = UnsupportedTypeInSthToStr;
#endif
	}
	static inline bool IsSupported() { return false; }
};

template <typename T>
inline void SthToStr(tstring *Str, const T &Sth)
{
	SthToStr_obj<T>()(Str, Sth);
}

template <typename T>
struct StrToSth_obj
{
	bool operator () (const tstring &Str, T *Sth)
	{
		// Runtime error
		assert(0 && "StrToSth: Unsupported type.");
		// Compilation error
		// Dzia�a tylko w Visual C++, g++ pokazuje b��d kompilacji nawet kiedy nieu�yte
#ifdef WIN32
		int y = UnsupportedTypeInSthToStr;
#endif
		return false;
	}
	static inline bool IsSupported() { return false; }
};

template <typename T>
inline bool StrToSth(T *Sth, const tstring &Str)
{
	return StrToSth_obj<T>()(Sth, Str);
}

//@}

namespace common
{

/** \addtogroup code_sthtostr */
//@{

/// \internal
class Format_pimpl
{
	friend class Format;

private:
	tstring m_String;
	char m_Sep;
	size_t m_Index;

	Format_pimpl(const tstring &Fmt, char Sep) : m_String(Fmt), m_Sep(Sep), m_Index(0) { }
};

/// Klasa do wygodnego sk�adania string�w z r�nych informacji
/**
Przyk�ad u�ycia:
\code
int i = 10; float f = 3.14f; tstring s = _T("A");
string MyString = Format("i=#, f=#, s=#") % i % f % s;
\endcode
*/
class Format
{
private:
	shared_ptr<Format_pimpl> pimpl;

public:
	Format(const tstring &Fmt, char Sep = '#') : pimpl(new Format_pimpl(Fmt, Sep)) { }
	/// Dodaje kolejn� informacj� do formatowanego �a�cucha
	/** \internal
	- To taki jakby dziwny konstuktor kopiuj�cy.
	- U�ywam za ka�dym razem tworzenia osobnego obiektu, bo nie mo�na w g++
	modyfikowa� obiektu tymczasowego i nie da�oby si� tego tak wygodnie
	u�ywa�.
	- Do u�ytku wewn�trznego - nie u�ywa�! */
	Format(const Format &f, const tstring &Element);
	/// \internal
	Format(const Format &f, const tchar *Element);

	operator tstring () const { return pimpl->m_String; }
	/// Zwraca finalny string - stosowa� tam, gdzie nie zadzia�a automatyczne rzutowanie na string.
	tstring str() const { return pimpl->m_String; }
};

template <typename T>
const Format operator % (const Format &fmt, const T &x)
{
	tstring s;
	SthToStr<T>(&s, x);
	return Format(fmt, s);
}

inline const Format operator % (const Format &fmt, const tchar *x)
{
	return Format(fmt, x);
}

//@}

} // namespace common


/** \addtogroup code_sthtostr */
//@{

//------------------------------------------------------------------------------
// SthToStr

template <>
struct SthToStr_obj<bool>
{
	void operator () (tstring *Str, const bool &Sth)
	{
		common::BoolToStr(Str, Sth, 'f');
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<tchar>
{
	void operator () (tstring *Str, const tchar &Sth)
	{
		common::CharToStr(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<int2>
{
	void operator () (tstring *Str, const int2 &Sth)
	{
		common::IntToStr<int2>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<int4>
{
	void operator () (tstring *Str, const int4 &Sth)
	{
		common::IntToStr<int4>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};
template <>
struct SthToStr_obj<long>
{
	void operator () (tstring *Str, const long &Sth)
	{
		common::IntToStr<int4>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<int8>
{
	void operator () (tstring *Str, const int8 &Sth)
	{
		common::IntToStr<int8>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<uint1>
{
	void operator () (tstring *Str, const uint1 &Sth)
	{
		common::UintToStr<uint1>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<uint2>
{
	void operator () (tstring *Str, const uint2 &Sth)
	{
		common::UintToStr<uint2>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<uint4>
{
	void operator () (tstring *Str, const uint4 &Sth)
	{
		common::UintToStr<uint4>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};
template <>
struct SthToStr_obj<unsigned long>
{
	void operator () (tstring *Str, const unsigned long &Sth)
	{
		common::UintToStr<uint4>(Str, (uint4)Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<uint8>
{
	void operator () (tstring *Str, const uint8 &Sth)
	{
		common::UintToStr<uint8>(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<float>
{
	void operator () (tstring *Str, const float &Sth)
	{
		common::FloatToStr(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<double>
{
	void operator () (tstring *Str, const double &Sth)
	{
		common::DoubleToStr(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<tstring>
{
	void operator () (tstring *Str, const tstring &Sth)
	{
		*Str = Sth;
	}
	static inline bool IsSupported() { return true; }
};

template <typename T>
struct SthToStr_obj< std::vector<T> >
{
	void operator () (tstring *Str, const std::vector<T> &Sth)
	{
		Str->clear();
		tstring Element;
		for (typename std::vector<T>::const_iterator it = Sth.begin(); it != Sth.end(); ++it)
		{
			if (!Str->empty())
				*Str += ',';
			SthToStr<T>(&Element, *it);
			*Str += Element;
		}
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<char *>
{
	void operator () (tstring *Str, tchar *Sth)
	{
		*Str = Sth;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<const tchar *>
{
	void operator () (tstring *Str, const tchar *Sth)
	{
		*Str = Sth;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<void *>
{
	void operator () (tstring *Str, void *Sth)
	{
		common::PtrToStr(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct SthToStr_obj<const void *>
{
	void operator () (tstring *Str, const void *Sth)
	{
		common::PtrToStr(Str, Sth);
	}
	static inline bool IsSupported() { return true; }
};

//------------------------------------------------------------------------------
// SthToStr

template <>
struct StrToSth_obj<bool>
{
	bool operator () (bool *Sth, const tstring &Str)
	{
		return common::StrToBool(Sth, Str);
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<tchar>
{
	bool operator () (tchar *Sth, const tstring &Str)
	{
		if (Str.length() != 1) return false;
		*Sth = Str[0];
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<int2>
{
	bool operator () (int2 *Sth, const tstring &Str)
	{
		return common::StrToInt<int2>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<int4>
{
	bool operator () (int4 *Sth, const tstring &Str)
	{
		return common::StrToInt<int4>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};
template <>
struct StrToSth_obj<long>
{
	bool operator () (long *Sth, const tstring &Str)
	{
		return common::StrToInt<int4>((int4*)Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<int8>
{
	bool operator () (int8 *Sth, const tstring &Str)
	{
		return common::StrToInt<int8>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<uint1>
{
	bool operator () (uint1 *Sth, const tstring &Str)
	{
		return common::StrToUint<uint1>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<uint2>
{
	bool operator () (uint2 *Sth, const tstring &Str)
	{
		return common::StrToUint<uint2>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<uint4>
{
	bool operator () (uint4 *Sth, const tstring &Str)
	{
		return common::StrToUint<uint4>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};
template <>
struct StrToSth_obj<unsigned long>
{
	bool operator () (unsigned long *Sth, const tstring &Str)
	{
		return common::StrToUint<uint4>((uint4*)Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<uint8>
{
	bool operator () (uint8 *Sth, const tstring &Str)
	{
		return common::StrToUint<uint8>(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<float>
{
	bool operator () (float *Sth, const tstring &Str)
	{
		return common::StrToFloat(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<double>
{
	bool operator () (double *Sth, const tstring &Str)
	{
		return common::StrToDouble(Sth, Str) == 0;
	}
	static inline bool IsSupported() { return true; }
};

template <>
struct StrToSth_obj<tstring>
{
	bool operator () (tstring *Sth, const tstring &Str)
	{
		*Sth = Str;
		return true;
	}
	static inline bool IsSupported() { return true; }
};

template <typename T>
struct StrToSth_obj< std::vector<T> >
{
	bool operator () (std::vector<T> *Sth, const tstring &Str)
	{
		Sth->clear();
		uint4 Index = 0;
		tstring Element;
		T Val;
		while (common::Split(Str, _T(","), &Element, &Index))
		{
			if (!StrToSth<T>(&Val, Element)) return false;
			Sth->push_back(Val);
		}
		return true;
	}
	static inline bool IsSupported() { return true; }
};

//@}
// code_sthtostr

#endif
