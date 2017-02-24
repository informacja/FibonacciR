#ifndef POINTZONE_H_INCLUDED
#define POINTZONE_H_INCLUDED

#define MIN(a,b) (((a)<(b)) ? a : b)
//#define MAX(a,b) (((a)>(b)) ? a : b)

#include <iostream>
#include "color.h"
#include <math.h>

using namespace std;

// ------------------------------------------------------

/*
typedef struct position
{
    int X;
    int Y;
} Point;
*/

class Point
{
public:
    double X;
    double Y;

    Point( );
    Point( int , int );
    Point( double , double );

};

// ------------------------------------------------------

void Show ( Point position );
double Minus( double X, double Y );         /// zawsze odejmuje wiêkszy parametr od mniejszego
double Length( Point a, Point b );


#endif // POINTZONE_H_INCLUDED
