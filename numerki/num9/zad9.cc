#include <bits/stdc++.h>
#include <cmath>

using namespace std;

const double A = M_PI / 2, eps = 10e-6, ans = 0.37900902069;

ofstream out;

double f(double x)
{
    return sin(x) - 0.37;
}

double g(double x)
{
    double a = f(x);
    return a * a;
}

double df(double x)
{
    return cos(x);
}

double dg(double x)
{
    return 2 * cos(x) * (sin(x) - 0.37);
}

double d2g(double x)
{
    return 2 * cos(x) * cos(x) - 2 * (sin(x) - 0.37) * sin(x);
}

double u(double x)
{
    return g(x) / dg(x);
}

double hyh(double x)
{
    return g(x) * dg(x) / (dg(x) * dg(x) - g(x) * d2g(x));
}

void newton(double a1)
{
    double a2 = a1;
    double h1 = f(a1) / df(a1);
    double h2 = f(a2) / df(a2);
    int k = 0;
    out.open("Newton_f.txt");
    while(fabs(h1) >= eps + 0.001)
    {
        k++;
        h1 = f(a1) / df(a1);
        a1 = a1 - h1;
        out << k << "   " << fabs(ans - a1) << endl;
    }
    out.close();
    k = 0;
    out.open("Newton_g.txt");
    while(fabs(h2) >= eps)
    {
        k++;
        h2 = g(a2) / dg(a2);
        a2 = a2 - h2;
        out << k << "   " << fabs(ans - a2) << endl;
    }
    out.close();
}

void newtonMod(double a2)
{
    int k = 0;
    out.open("Newton_g_Mod.txt");
    while(fabs(hyh(a2)) >= eps)
    {
        k++;
        a2 = a2 - hyh(a2);
        out << k << "   " << fabs(ans - a2) << endl;
        if(k>100) break;
    }
    out.close();
}

void bisection(double a, double b)
{
    double c = a;
    int k = 0;
    out.open("Bisection.txt");
    while((b - a) >= eps)
    {
        k++;
        c = (a + b) / 2;

        out << k << "   " << fabs(ans - c) << endl;

        if(f(c) == 0) break;
        else if(f(c) * f(a) < 0) b = c;
        else a = c;
    }
    out.close();
}

void falsi(double a, double b)
{
    double c = a;
    int k = 0;
    out.open("Falsi.txt");
    while((b - a) >= eps)
    {
        k++;
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));

        out << k << "   " << fabs(ans - c) << endl;

        if(fabs(f(c)) < eps) break;
        else if(f(c) * f(a) < 0) b = c;
        else a = c;
    }
    out.close();
}

void secant(double a1, double b1)
{
    double c1 = a1, a2 = a1, c2 = a2, b2 = b1;
    double xm1, xm2, x1, x2;
    int k = 0;
    out.open("Secant_f.txt");
    do
    {
        k++;
        x1 = (a1 * f(b1) - b1 * f(a1)) / (f(b1) - f(a1));

        out << k << "   " << fabs(ans - x1) << endl;

        c1 = f(a1) * f(x1);

        a1 = b1;
        b1 = x1;

        if(c1 == 0) break;
        
        xm1 = (a1 * f(b1) - b1 * f(a1)) / (f(b1) - f(a1));
    }
    while(fabs(xm1 - x1) >= eps);
    out.close();
    k=0;
    out.open("Secant_g.txt");
    do
    {
        k++;
        x2 = (a2 * g(b2) - b2 * g(a2)) / (g(b2) - g(a2));

        out << k << "   " << fabs(ans - x2) << endl;

        c2 = g(a2) * g(x2);

        a2 = b2;
        b2 = x2;

        if(c2 == 0) break;
        
        xm2 = (a2 * g(b2) - b2 * g(a2)) / (g(b2) - g(a2));
    }
    while(fabs(xm2 - x2) >= eps-0.000008);
    out.close();
}

void secantMod(double x0)
{
    int k = 0;
    double x1 = x0 - 0.1;
    double hih = u(x1) * (x0 - x1) / (u(x0) - u(x1));
    out.open("Secant_g_Mod.txt");
    while(fabs(hih) >= eps)
    {
        k++;
        hih = u(x1) * (x0 - x1) / (u(x0) - u(x1));
        x0 = x1;
        x1 = x1 - hih;
        out << k << "   " << fabs(ans - x0) << endl;
    }
    out.close();
}

int main()
{
    newton(1.2);
    newtonMod(1);
    bisection(0, A);
    falsi(0, A);
    secant(-1, 1);
    secantMod(1);
}