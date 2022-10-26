#include <bits/stdc++.h>
#include <functional>
#include <gsl/gsl_linalg.h>

using namespace std;

ofstream out1, out2;

double f1(double x)
{
    return 1 / (1 + 25 * x * x);
}

double f2(double x)
{
    return 1 / (1 + x * x);
}

double xi1(double n, int i)
{
    return -1 + 2 * (i / (n + 1));
}

double xi2(double n, int i)
{
    return cos((2 * i + 1) / (2 * (n + 1)) * M_PI);
}

struct dane
{
    int n;
    double *A1, *A2, *y1, *y2, *x1, *x2;

    void wczytaj(int N, function<double (double)> f)
    {
        N++;
        n = N;
        A1 = new double [N*N];
        A2 = new double [N*N];
        y1 = new double [N];
        y2 = new double [N];
        x1 = new double [N];
        x2 = new double [N];
        int k = 0;
        for(int i=0; i<N; i++)
        {
            x1[i] = xi1(N-2, i);
            x2[i] = xi2(N-1, i);
            y1[i] = f(x1[i]);
            y2[i] = f(x2[i]);
            for(int j=0; j<N; j++)
            {
                A1[k] = pow(x1[i], N-1-j);
                A2[k] = pow(x2[i], N-1-j);
                k++;
            }
        }
    }
};

double func(gsl_vector *g, double x)
{
    double y = 0;
    for(int i=0; i<g->size; i++)
    {
        y += gsl_vector_get(g, i) * pow(x, g->size-1-i);
    }
    return y;
}

void interpol(dane d, string name1, string name2)
{
    gsl_matrix_view a = gsl_matrix_view_array(d.A1, d.n, d.n);
    gsl_matrix_view b = gsl_matrix_view_array(d.A2, d.n, d.n);
    gsl_vector_view ya = gsl_vector_view_array(d.y1, d.n);
    gsl_vector_view yb = gsl_vector_view_array(d.y2, d.n);
    gsl_vector *ana = gsl_vector_alloc(d.n);
    gsl_vector *anb = gsl_vector_alloc(d.n);
    gsl_permutation *perma = gsl_permutation_alloc(d.n);
    gsl_permutation *permb = gsl_permutation_alloc(d.n);
    int signuma, signumb;
    gsl_linalg_LU_decomp(&a.matrix, perma, &signuma);
    gsl_linalg_LU_decomp(&b.matrix, permb, &signumb);
    gsl_linalg_LU_solve(&a.matrix, perma, &ya.vector, ana);
    gsl_linalg_LU_solve(&b.matrix, permb, &yb.vector, anb);

    double xa = -1, xb = -1;
    out1.open(name1);
    out2.open(name2);
    for(int i=0; i<=200; i++)
    {
        out1 << xa << "      " << func(ana, xa) << endl;
        out2 << xb << "      " << func(anb, xb) << endl;
        xa += 0.01;
        xb += 0.01;
    }
    out1.close();
    out2.close();
}

int main()
{
    dane d1_3, d1_7, d1_11, d1_40;
    dane d2_3, d2_7, d2_11, d2_40;
    d1_3.wczytaj(3, f1);
    d1_7.wczytaj(7, f1);
    d1_11.wczytaj(11, f1);
    d1_40.wczytaj(40, f1);
    d2_3.wczytaj(3, f2);
    d2_7.wczytaj(7, f2);
    d2_11.wczytaj(11, f2);
    d2_40.wczytaj(40, f2);
    interpol(d1_3, "d1a_3.txt", "d1b_3.txt");
    interpol(d1_7, "d1a_7.txt", "d1b_7.txt");
    interpol(d1_11, "d1a_11.txt", "d1b_11.txt");
    interpol(d1_40, "d1a_40.txt", "d1b_40.txt");
    interpol(d2_3, "d2a_3.txt", "d2b_3.txt");
    interpol(d2_7, "d2a_7.txt", "d2b_7.txt");
    interpol(d2_11, "d2a_11.txt", "d2b_11.txt");
    interpol(d2_40, "d2a_40.txt", "d2b_40.txt");

}