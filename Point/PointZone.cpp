
#include "PointZone.h"

// ------------------------------------------------------

Point::Point( )
{
    X = 0;
    Y = 0;
};

Point::Point( double a, double b)
{
    X = a;
    Y = b;
};

Point::Point( int a, int b)
{
    X = a;
    Y = b;
};

// ------------------------------------------------------

void Show ( Point a )
{
    cout << "\nX = "; yellow(a.X); cout << "\tY = "; yellow(a.Y); //cout << endl;
}

// ------------------------------------------------------

double Minus( double a, double b )
{
    if ( a < b )
        return b - a;
    else
        return a - b;
}

// ------------------------------------------------------

double Length( Point p1, Point p2 )
{
    double a, b = 0;

    a = Minus( p1.X, p2.X );
    b = Minus( p1.Y, p2.Y );

    if ( a == b || b == 0 )
    {
        cout << "Błąd funkcji Length() dla:";
        Show(p1); Show(p2);
    }

    return sqrt( a*a + b*b );

}

