//---------------------------------------------------------------------------

#pragma hdrstop

#include "FuncPoint.h"


Punkt::Punkt( )
{
    X = 0;
    Y = 0;
};

Punkt::Punkt( double a, double b)
{
    X = a;
    Y = b;
};

Punkt::Punkt( int a, int b)
{
    X = a;
    Y = b;
};

// ------------------------------------------------------

void Show ( Punkt a )
{
	cout << "\nX = "; //yellow(a.X);
	cout << "\tY = "; //yellow(a.Y); //cout << endl;
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

double Length( Punkt p1, Punkt p2 )
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

// ---------------------------------------------------------------------------


/*
double MIN( double a, double b)
{
    return (((a)<(b)) ? a : b);
}
*/
// ------------------------------------------------------

Linear_Func::Linear_Func( Punkt a, Punkt b )
{
    A = Minus( a.Y, b.Y ) / Minus( a.X, b.X );

    B = - ( (A * a.X) - a.Y );
    // środek
    S.X = (Minus( a.X, b.X ) / 2.0) + MIN( a.X, b.X );
    S.Y = (Minus( a.Y, b.Y ) / 2.0) + MIN( a.Y, b.Y );

  //  setIntensity();
 //   cout << S.X <<endl <<S.Y<<endl;

    /// wyznaczanie prostej prostopadłej
    //  (z ang.) normal = prostopadła

    // wyznaczanie współczynnika kierunkowego dla funkcji prostopadłej
    Anormal = -1 / A;
//    black(Anormal);

    // obliczanie wyrazu wolnego, funkcji prostopadłej, tak by przechodziła przez punkt S( pomiędzy punktami A i B )
    Bnormal = (Anormal * S.X) - S.Y;

    //srodek.X = ( Bnormal - B ) / ( Anormal - A );
    //srodek.Y = Anormal * srodek.X + Bnormal;

    //cout << "Środek pomiędzy punktami "; Show(srodek);

    check_errors();

    /// matematycznie       y = ax + b      // wzór funkcji liniowej
    /// programistycznie    Y = A * X + B

}
// ------------------------------------------------------

void Linear_Func::ShowFuncModel()
{
	cout << "\ny";

	cout << A;
	if ( B < 0 ) {
		cout << "x - ";  cout << B-B-B;   // wartość dodatnia np. B=-3; (-3)-(-3)-(-3) = 3;
	} else {
		cout << "x + ";  cout << B;
	}

    cout << endl;
}

void Linear_Func::ShowNormalFuncModel()
{
    cout << "\ny";

    cout << Anormal;

    if ( Bnormal < 0 ) {
		cout << "x - "; cout << Bnormal-Bnormal-Bnormal;   // wartość dodatnia np. B=-3; (-3)-(-3)-(-3) = 3;
	} else {
		cout << "x + "; cout << Bnormal;
	}
    cout << endl;
}

// ------------------------------------------------------

double Linear_Func::CalcFor( double x )
{
    return A * x + B;     /// y = ax + b;
}

double Linear_Func::CalcFor( Punkt z )
{
    return A * z.X + B;     /// y = ax - b;
}

double Linear_Func::CalcForNormal( double x )
{
    return Anormal * x + Bnormal;     /// y = ax + b;
}

double Linear_Func::CalcForNormal( Punkt z )      // przeci¹¿enie ta funkcja sama pobierze wartoœæ x z obiektu Point
{
    return Anormal * z.X - Bnormal;     /// y = ax - b;
}

// ------------------------------------------------------

void Linear_Func::check_errors( )
{
     // sprawdzamy czy s¹ b³edy np. nie poprawne dane zosta³y wprowadzone
    if ( A == 0 )
        cerr << "\nWspó³czynnik kierunkowy = 0\n";
    if ( B == 0 )
        cerr << "\nWyraz wolny B = 0\n";
    return;
}







//---------------------------------------------------------------------------
#pragma package(smart_init)
