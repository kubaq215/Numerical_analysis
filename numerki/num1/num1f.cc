#include <bits/stdc++.h>
#include <math.h>

using namespace std;

ofstream out1, out2;

float f(float x)
{
    float a = cos(x);
    return a;
}

float fp(float x)
{
    return -sin(x);
}

float derative1(float x, float h)
{
    float q = h+x;
    return (f(q)-f(x))/h;
}

float derative2(float x, float h)
{
    float q = h+x, r = x-h;
    return (f(q)-f(r))/(2*h);
}

float E1(float x, float h)
{
    return fabs(derative1(x, h) - fp(x));
}

float E2(float x, float h)
{
    return fabs(derative2(x, h) - fp(x));
}


int main()
{
    float x, h = 1e-1;
    cout << "podaj wartosc x: ";
    cin >> x; 
    
    out1.open("data1f.dat");
    out2.open("data2f.dat");

    for(int i=0; i<1565; i++)
    {
        out1 << h << "   " << E1(x, h) << endl;
        out2 << h << "   " << E2(x, h) << endl;
        h = h * 0.99;
    }

    out1.close();
    out2.close();

    return 0;
}