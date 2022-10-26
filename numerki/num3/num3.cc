#include <bits/stdc++.h>

using namespace std;

void LU(double a[4][100], double lu[4][100])
{
    lu[1][0] = a[1][0];
    lu[2][0] = a[2][0];
    lu[3][0] = a[3][0];
    lu[0][0] = a[0][0] / lu[1][0];
    for(int i=1; i<100; i++)
    {
        lu[1][i] = a[1][i] - lu[0][i-1] * lu[2][i-1];
        lu[2][i] = a[2][i] - lu[0][i-1] * lu[3][i-1];
        lu[3][i] = a[3][i];
        lu[0][i] =  a[0][i] / lu[1][i];   
    }
}

void fsub(double lu[4][100], double x[100], double b[100])
{
    b[0] = x[0];
    for(int i=1; i<100; i++)
    {   
        b[i] = x[i] - lu[0][i-1] * b[i-1];
    }
}

void bsub(double lu[4][100], double b[100], double y[100])
{
    y[99] = b[99] / lu[1][99];
    y[98] = (b[98] - lu[2][98] * y[99]) / lu[1][98];
    for(int i=97; i>=0; i--)
    {   
        y[i] = (b[i] - lu[2][i] * y[i+1] - lu[3][i] * y[i+2]) / lu[1][i];
    }
}


int main()
{
    double a[4][100], lu[4][100], x[100], b[100], y[100];

    for(int i=0; i<4; i++)
        for(int j=0; j<100; j++)
        {
            if(i == 0)
            {    
                a[i][j] = 0.2;
                x[j] = j+1;
            }
            else if(i == 1)
                a[i][j] = 1.2;
            else if(i == 2)
                a[i][j] = 0.1 / (j+1);
            else if(i == 3)
                a[i][j] = 0.4 / ((j+1)*(j+1));
        }

    LU(a, lu);
    fsub(lu, x, b);
    bsub(lu, b, y);
    double s = 1;
    for(int i=0; i<100; i++)
    {
        s *= lu[1][i];
        cout << "y" << i+1 << " = " << y[i] << endl;
    }
    cout << "wyznacznik - " << s << endl;

    return 0;
}