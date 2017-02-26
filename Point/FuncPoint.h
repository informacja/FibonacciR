//---------------------------------------------------------------------------

#ifndef FuncPointH
#define FuncPointH

#include <iostream>

using namespace std;

#define MIN(a,b) (((a)<(b)) ? a : b)

//---------------------------------------------------------------------------


class Punkt
{
public:
    double X;
    double Y;

	Punkt( );
	Punkt( int , int );
	Punkt( double , double );

};

//void Show ( TPoint position );
double Minus( double X, double Y );         // zawsze odejmuje wiêkszy parametr od mniejszego
double Length( Punkt a, Punkt b );

//---------------------------------------------------------------------------

class Linear_Func
{
public:
	double A, B, X, Y, Anormal, Bnormal;
	Punkt S, srodek;
    /// do wzoru Y = A*X + B;
    void check_errors( );

public:
    void ShowFuncModel();
    void ShowNormalFuncModel();

    double CalcFor( double x );
	double CalcFor( Punkt to_get_Y_position );      // przeci¹¿enie ta funkcja sama pobierze wartoœæ x z obiektu Point
    double CalcForNormal( double x );
    double CalcForNormal( Punkt to_get_Y_position );      // przeci¹¿enie ta funkcja sama pobierze wartoœæ x z obiektu Point


    Linear_Func( Punkt a, Punkt b );
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
