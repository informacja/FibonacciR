#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include "PointZone.h"


class Linear_Func
{
public:
    double A, B, X, Y, Anormal, Bnormal = 0; // pomocnicze
    Point S, srodek;
    /// do wzoru Y = A*X + B;
    void check_errors( );

public:
    void ShowFuncModel();
    void ShowNormalFuncModel();

    double CalcFor( double x );
    double CalcFor( Point to_get_Y_position );      // przeci¹¿enie ta funkcja sama pobierze wartoœæ x z obiektu Point
    double CalcForNormal( double x );
    double CalcForNormal( Point to_get_Y_position );      // przeci¹¿enie ta funkcja sama pobierze wartoœæ x z obiektu Point


    Linear_Func( Point a, Point b );
};


#endif // FUNC_H_INCLUDED
