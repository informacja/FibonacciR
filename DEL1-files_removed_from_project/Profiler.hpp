/** \file
\brief Przyrz¹d do pomiarów czasu i wydajnoœci
\author Adam Sawicki - sawickiap@poczta.onet.pl - http://regedit.gamedev.pl/ \n

Czêœæ biblioteki CommonLib \n
Kodowanie Windows-1250, koniec wiersza CR+LF, test: Za¿ó³æ gêœl¹ jaŸñ \n
Licencja: GNU GPL. \n
Dokumentacja: \ref Module_Profiler \n
Elementy modu³u: \ref code_profiler
*/
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#ifndef COMMON_PROFILER_H_
#define COMMON_PROFILER_H_

#include <stack> // :(

namespace common
{

/** \addtogroup code_profiler Modu³ Profiler
Dokumentacja: \ref Module_Profiler \n
Nag³ówek: Profiler.hpp */
//@{

class Profiler;

/// Pozycja danych profilera
class ProfilerItem
{
private:
	// Sumaryczny czas wykonania [s]
	double m_Time;
	// Liczba przebiegów
	double m_Count;
	// Czas rozpoczêcia bie¿¹cego przebiegu [s]
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
	/// Zapisuje ca³e drzewo profilu do ³añcucha - ka¿da pozycja w osobnym wierszu
	/** Wciêcia to dwie spacje <tt>"  "</tt>
	Koñce wiersza to <tt>\\n</tt>
	Jednostka to milisekundy. */
	void FormatString(tstring *S);
};

/// Klasa, której obiekt mo¿esz dla wygody utworzyæ zamiast wywo³ywaæ Begin i End profilera.
/** Tworzenie tego obiektu wywo³uje Profiler::Begin, a usuwanie - Profiler::End.
Obiekt automatyczny utworzony na stosie sam siê usunie przy wyjœciu
z funkcji. Dlatego warto tworzyæ obiekt tej klasy jako zmienn¹ lokaln¹ o byle
jakiej nazwie i nieu¿ywan¹ nigdzie dalej na pocz¹tku ka¿dej profilowanej
funkcji. */
class Profile
{
private:
	Profiler &m_Profiler;
public:
	/// U¿ywa g_Profiler
	Profile(const tstring &Name);
	/// U¿ywa podanego, w³asnego profilera
	Profile(const tstring &Name, Profiler &Profiler_);
	~Profile();
};

/// G³ówny profiler globalny dla w¹tku g³ównego
extern Profiler g_Profiler;

//@}
// code_profiler

} // namespace common

/** \addtogroup code_profiler */
//@{
/** Dla jeszcze wiêszej wygody, zamiast tworzyæ obiekt klasy Profile wystarczy
na pocz¹tku guardowanej do profilowania funkcji czy dowolnego bloku { }
postawiæ to makro. */
#define PROFILE_GUARD(Name) common::Profile __profile_guard_object(Name);
//@}

#endif

