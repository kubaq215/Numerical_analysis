#include <bits/stdc++.h>
#include <math.h>

using namespace std;

ofstream out1, out2;

double f(double x)
{
    double a = cos(x);
    return a;
}

double fp(double x)
{
    return -sin(x);
}

double derative1(double x, double h)
{
    double q = h+x;
    return (f(q)-f(x))/h;
}

double derative2(double x, double h)
{
    double q = h+x, r = x-h;
    return (f(q)-f(r))/(2*h);
}

double E1(double x, double h)
{
    return fabs(derative1(x, h) - fp(x));
}

double E2(double x, double h)
{
    return fabs(derative2(x, h) - fp(x));
}

int main()
{
    double x, h = 1e-1;
    cout << "podaj wartosc x: ";
    cin >> x;

    out1.open("data1.dat");
    out2.open("data2.dat");

    for(int i=0; i<1655; i++)
    {
        out1 << h << "   " << E1(x, h) << endl;
        out2 << h << "   " << E2(x, h) << endl;
        h = h * 0.98;
    }

    out1.close();
    out2.close();

    return 0;
}