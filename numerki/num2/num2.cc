#include <bits/stdc++.h>
#include <math.h>

using namespace std;


void LU(double mat[5][5], double l[5][5], double u[5][5])
{
    int i, j, k;
    for(i=0; i<5; i++)
    {
        for(j=i; j<5; j++)
        {
            double sum = 0;
            for(k=0; k<i; k++)
                sum += l[i][k] * u[k][j];
            
            u[i][j] = mat[i][j] - sum;
        }

        for(j=i; j<5; j++)
        {
            if(i==j)
                l[i][i] = 1;
            else
            {
                double sum = 0;
                for(k=0; k<i; k++)
                    sum += l[j][k] * u[k][i];

                l[j][i] = (mat[j][i] - sum) / u[i][i]; 
            }
        }
    }
}

void fsub(double l[5][5], double b[5], double y[5])
{
    int i, j;
    
    for(i=0; i<5; i++)
    {
        double sum = 0;
        for(j=0; j<i; j++)
            sum += l[i][j] * y[j];
        
        y[i] = b[i] - sum;
    }
}

void bsub(double u[5][5], double y[5], double x[5])
{
    int i, j;

    for(i=4; i>=0; i--)
    {
        double sum = 0;
        for(j=i+1; j<5; j++)
            sum += u[i][j] * x[j];
        
        x[i] = (y[i] - sum) / u[i][i];
    }
}
int main()
{
    double A1[5][5], A2[5][5], b[5], bp[5], l[5][5], u[5][5];
    ifstream in1("A1.txt"), in2("A2.txt"), in3("b.txt");

    int i, j;

    for(i=0; i<5; i++)
    {
        in3 >> b[i];

        if(i==0) bp[i] = b[i] + 10e-5;
        else bp[i] = b[i];

        for(j=0; j<5; j++)
        {    
            in1 >> A1[i][j];
            in2 >> A2[i][j];
        }
    }

    memset(l, 0, sizeof(l));
    memset(u, 0, sizeof(u));

    double y[5], x1[5], x2[5];

    LU(A1, l, u);
    fsub(l, b, y);
    bsub(u, y, x1);
    
    cout << "\nA1y1 = b" << "\n\n";
    for(i=0; i<5; i++)
        cout << "y" << i+1 << " = " << x1[i] << endl;

//-------------------------------------------------------
    LU(A1, l, u);
    fsub(l, bp, y);
    bsub(u, y, x2);

    cout << "\nA1y'1 = b'" << "\n\n";
    for(i=0; i<5; i++)
        cout << "y" << i+1 << " = " << x2[i] << endl; 

//-------------------------------------------------------    
    double sum1, sum2;
    for(i=0; i<5; i++)
    {
        sum1 += x1[i]*x1[i];
        sum2 += x2[i]*x2[i];
    }    
    double del1 = abs(sqrt(sum1) - sqrt(sum2));

    cout << "\nDelta1 = " << del1 << endl;

//-------------------------------------------------------
    LU(A2, l, u);
    fsub(l, b, y);
    bsub(u, y, x1);

    cout << "\nA2y2 = b" << "\n\n";
    for(i=0; i<5; i++)
        cout << "y" << i+1 << " = " << x1[i] << endl; 
    
//-------------------------------------------------------
    LU(A2, l, u);
    fsub(l, bp, y);
    bsub(u, y, x2); 

    cout << "\nA2y'2 = b'" << "\n\n";
    for(i=0; i<5; i++)
        cout << "y" << i+1 << " = " << x2[i] << endl;  

//-------------------------------------------------------
    sum1 = 0;
    sum2 = 0;
    for(i=0; i<5; i++)
    {
        sum1 += x1[i]*x1[i];
        sum2 += x2[i]*x2[i];
    }    
    double del2 = abs(sqrt(sum1) - sqrt(sum2)); 

    cout << "\nDelta2 = " << del2 << endl;
            
    return 0;
}