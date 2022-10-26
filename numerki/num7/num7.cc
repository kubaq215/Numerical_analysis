#include <bits/stdc++.h>

using namespace std;

double f(double x)
{
    return 1 /(1 + 25 * x * x);
}

void cholesky(double *ksi, int n, double *fn, double h)
{
    double l1[n], l2[n], y[n], c[n];
    for(int i=0; i<n; i++)
    {
        l1[i] = 4;
        l2[i] = 1;
        y[i] = 6 / (h * h) * (fn[i] - 2 * fn[i+1] + fn[i+2]);
    }
    
    // faktoryzacja
    l1[0] = 2;
    for(int i=1; i<n; i++) 
    {
        l2[i-1] = l2[i-1] / l1[i-1];
        l1[i] = sqrt(l1[i] - l2[i-1] * l2[i-1]);
    }
    // fsub
    c[0] = y[0] / l1[0];
    for(int i=1; i<n; i++)
    {
        c[i] = (y[i] - l2[i-1] * c[i-1]) / l1[i];
    }
    // bsub
    ksi[n] = c[n-1] / l1[n-1];
    for(int i=n-1; i>0; i--)
    {
        ksi[i] = (c[i-1] - l2[i-1] * ksi[i+1]) / l1[i-1];
    }
}

struct dane
{
    int n;
    double *fn, *ksi, *xn, y[201];
    double h;

    void wczytaj(int N, string name1, string name2)
    {
        n = N;
        xn = new double [N+1];
        fn = new double [N+1];
        ksi = new double [N+1];
        ksi[0] = ksi[N] = 0;
        double x = -1;
        h = (double) 2 / N;
        for(int i=0; i<N+1; i++)
        {
            xn[i] = x;
            fn[i] = f(x);
            x += h; 
        }
        cholesky(ksi, n-1, fn, h);
        policz(name1, name2);
    }

    void policz(string name1, string name2)
    {
        ofstream out;
        double x = -1;
        double A, B, C, D, s[n+1];
        int k = 0;
        out.open(name1);
        for(int i=0; i<n; i++)
        {
            double xh = xn[i+1] - xn[i];
            for(int j=0; j<200 / n; j++)
            {
                A = (xn[i+1] - x) / xh;
                B = (x - xn[i]) / xh;
                C = (double) 1/6 * (pow(A, 3) - A) * pow(xh, 2);
                D = (double) 1/6 * (pow(B, 3) - B) * pow(xh, 2);
                y[k] = A * fn[i] + B * fn[i+1] + C * ksi[i] + D * ksi[i+1];
                out << x << "   " << y[k] << endl;
                k++;
                x+=0.01;
            }
            s[0] = y[0];
            s[i+1] = y[k-1];
        }
        out.close();
        out.open(name2);
        for(int i=0; i<n+1; i++)
        {
            out << i << "   " << fabs(fn[i] - s[i]) << endl;
        }
    }
};



int main()
{
   dane d;
   d.wczytaj(4, "d_4.txt", "odl_4.txt");
   d.wczytaj(8, "d_8.txt", "odl_8.txt");
   d.wczytaj(20, "d_20.txt", "odl_20.txt");
}