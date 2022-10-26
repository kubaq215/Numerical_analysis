#include <bits/stdc++.h>

using namespace std;

void bsub(double a[2][50], double y[50], double u[50])
{
    y[49] = u[49] / a[0][49];
    for(int i=48; i>=0; i--)
    {
        y[i] = (u[i] - a[1][i] * y[i+1]) / a[0][i];
    }
}

int main()
{
    double a[2][50], u[50], b[50];
    double z[50], y[50], x[50];

    for(int i=0; i<50; i++)
    {
        a[0][i] = 9;
        a[1][i] = 7;
        u[i] = 1;
        b[i] = 5;
    }

    bsub(a, y, u);
    bsub(a, z, b);

    double sum1 = 0, sum2 = 0;
    for(int i=0; i<50; i++)
    {
        sum1 += y[i];
        sum2 += z[i];
    }
    double k = sum2 / (1 + sum1);
    for(int i=0; i<50; i++)
    {
        y[i] = k * y[i];
        x[i] = z[i] - y[i];
    }
    for(int i=0; i<50; i++)
        cout << "x" << i+1 << " = " << x[i] << endl;
    cout << endl;
}