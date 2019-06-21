/** \file
\brief Przyrz�d do pomiar�w czasu i wydajno�ci
\author Adam Sawicki - sawickiap@poczta.onet.pl - http://regedit.gamedev.pl/ \n

Cz�� biblioteki CommonLib \n
Kodowanie Windows-1250, koniec wiersza CR+LF, test: Za��� g�l� ja�� \n
Licencja: GNU GPL. \n
Dokumentacja: \ref Module_Profiler \n
Elementy modu�u: \ref code_profiler
*/
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#ifndef COMMON_PROFILER_H_
#define COMMON_PROFILER_H_

#include <stack> // :(

namespace common
{

/** \addtogroup code_profiler Modu� Profiler
Dokumentacja: \ref Module_Profiler \n
Nag��wek: Profiler.hpp */
//@{

class Profiler;

/// Pozycja danych profilera
class ProfilerItem
{
private:
	// Sumaryczny czas wykonania [s]
	double m_Time;
	// Liczba przebieg�w
	double m_Count;
	// Czas rozpocz�cia bie��cego przebiegu [s]
	double m_StartTime;
	tstring m_strName; // Nazwa elementu
	std::vector<ProfilerItem> m_ItemVector; // Podelementy

	friend class Profiler;
		ProfilerItem* Begin(const tstring &Name);
		void Start();
		void Stop();
public:
	ProfilerItem(const tstring &Name);

	const tstring &GetName() { return m_strName; }
	bool Empty() { return (around(m_Count, 0.1)); }
	double GetCount() { return m_Count; }
	double GetAvgTime() { return ( Empty() ? 0.0 : m_Time / m_Count ); }
	size_t GetItemCount() { return m_ItemVector.size(); }
	ProfilerItem* GetItem(size_t index) { return &m_ItemVector[index]; }
	void FormatString(tstring *S, unsigned dwLevel);
};

/// Profiler
class Profiler
{
private:
	std::stack<ProfilerItem*> m_ItemStack;
	ProfilerItem m_DefaultItem;

public:
	Profiler();
	Profiler(const tstring &Name);
	void Begin(const tstring &Name);
	void End();
	ProfilerItem* GetRootItem() { return &m_DefaultItem; }
	/// Zapisuje ca�e drzewo profilu do �a�cucha - ka�da pozycja w osobnym wierszu
	/** Wci�cia to dwie spacje <tt>"  "</tt>
	Ko�ce wiersza to <tt>\\n</tt>
	Jednostka to milisekundy. */
	void FormatString(tstring *S);
};

/// Klasa, kt�rej obiekt mo�esz dla wygody utworzy� zamiast wywo�ywa� Begin i End profilera.
/** Tworzenie tego obiektu wywo�uje Profiler::Begin, a usuwanie - Profiler::End.
Obiekt automatyczny utworzony na stosie sam si� usunie przy wyj�ciu
z funkcji. Dlatego warto tworzy� obiekt tej klasy jako zmienn� lokaln� o byle
jakiej nazwie i nieu�ywan� nigdzie dalej na pocz�tku ka�dej profilowanej
funkcji. */
class Profile
{
private:
	Profiler &m_Profiler;
public:
	/// U�ywa g_Profiler
	Profile(const tstring &Name);
	/// U�ywa podanego, w�asnego profilera
	Profile(const tstring &Name, Profiler &Profiler_);
	~Profile();
};

/// G��wny profiler globalny dla w�tku g��wnego
extern Profiler g_Profiler;

//@}
// code_profiler

} // namespace common

/** \addtogroup code_profiler */
//@{
/** Dla jeszcze wi�szej wygody, zamiast tworzy� obiekt klasy Profile wystarczy
na pocz�tku guardowanej do profilowania funkcji czy dowolnego bloku { }
postawi� to makro. */
#define PROFILE_GUARD(Name) common::Profile __profile_guard_object(Name);
//@}

#endif

