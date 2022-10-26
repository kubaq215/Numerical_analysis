#include <bits/stdc++.h>

using namespace std;

const double xp = 109.144393013368812717089895159;

ofstream out1, out2;

double norm(double x[100])
{
    double sum = 0;
    for(int i=0; i<100; i++)
    {
        sum += x[i] * x[i];
    }
    return sqrt(sum);
}

int Jacobi(double a[3][100], double x[100], double b[100], double eps)
{
    out1.open("Jacobi.txt");
    int n = 0;
    double x1[100];
    double k = 0;
    do
    {
        n++;
        for(int i=0; i<100; i++)
            x1[i] = x[i];

        x[0] = (b[0] - a[1][0] * x1[1] - a[2][0] * x1[2]) / a[0][0];
        x[1] = (b[1] - a[1][1] * (x1[0] + x1[2]) - a[2][2] * x1[3]) / a[0][1];
        for(int i=2; i<=97; i++)
        {
            x[i] = (b[i] - a[1][i] * (x1[i-1] + x1[i+1]) - a[2][i] * (x1[i-2] + x1[i+2])) /a[0][i];
        }
        x[98] = (b[98] - a[1][98] * (x1[97] + x1[99]) - a[2][98] * x1[96]) / a[0][98];
        x[99] = (b[99] - a[1][99] * x1[98] - a[2][99] * x1[97]) / a[0][99];

        k = norm(x);
        out1 << n << "  " << setprecision(20) << abs(xp - k) << endl;
    } while (!(k < xp + eps && k > xp - eps) && n < 100000);
    // cout << k << endl;
    out1.close();
    return n;
}

int GauSei(double a[3][100], double x[100], double b[100], double eps)
{
    out2.open("GauSei.txt");
    int n = 0;
    double k = 0;
    do
    {
        n++;
        x[0] = (b[0] - a[1][0] * x[1] - a[2][0] * x[2]) / a[0][0];
        x[1] = (b[1] - a[1][1] * (x[0] + x[2]) - a[2][2] * x[3]) / a[0][1];
        for(int i=2; i<=97; i++)
        {
            x[i] = (b[i] - a[1][i] * (x[i-1] + x[i+1]) - a[2][i] * (x[i-2] + x[i+2])) /a[0][i];
        }
        x[98] = (b[98] - a[1][98] * (x[97] + x[99]) - a[2][98] * x[96]) / a[0][98];
        x[99] = (b[99] - a[1][99] * x[98] - a[2][99] * x[97]) / a[0][99];

        k = norm(x);
        out2 << n << "  " << setprecision(20) << abs(xp - k) << endl;
    } while (!(k < xp + eps && k > xp - eps) && n < 100000);
    // cout << k << endl;
    out2.close();
    return n;
}


int main()
{
    double a[3][100], b[100], x[100], x2[100];

    for(int i=0; i<100; i++)
    {
        a[0][i] = 3;
        a[1][i] = 1;
        a[2][i] = 0.2; 
        b[i] = i+1;
        x[i] = 12345;
        x2[i] = 12345;
    }
    double eps = 1e-14;
    int Ngs = GauSei(a, x, b, eps);
    cout << "Gaus Seidl " << Ngs << endl;
    int Njc = Jacobi(a, x2, b, eps);
    cout << "Jacobi " << Njc << endl;

    for(int i=0; i<100; i++)
    {
        cout << "x" << i+1 << "= " << x[i] << endl;
    }


    return 0;
}