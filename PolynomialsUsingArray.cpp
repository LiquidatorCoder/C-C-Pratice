#include <iostream>
using namespace std;

void cout_poly(int p[], int n)
{
    cout<<endl;
    for(int i=0;i<=n;i++)
    {
       cout << p[i];
       if (i != 0)
        cout << "x^" << i ;
       if (i != n)
       cout << " + ";
    }
}

void cin_poly(int p[], int n)
{
    cout<<"\nEnter the coefficients : "<<endl;
    for(int i=0;i<=n;i++)
    {
        cin>>p[i];
    }
}

void add_poly(int p1[], int m, int p2[], int n)
{
    int l=max(m,n);
    int c[l];
    for(int i=0;i<=l;i++)
    {
        c[i]=0;
    }
    for(int i=0;i<=m;i++)
    {
        c[i]=p1[i];
    }
    for(int i=0;i<=n;i++)
    {
        c[i]=c[i]+p2[i];
    }
    cout<<"\nAddition of both the polynomials : "<<endl;
    cout_poly(c,l);
}

void sub_poly(int p1[], int m, int p2[], int n)
{
    int l=max(m,n);
    int c[l];
    for(int i=0;i<=l;i++)
    {
        c[i]=0;
    }
    for(int i=0;i<=m;i++)
    {
        c[i]=p1[i];
    }
    for(int i=0;i<=n;i++)
    {
        c[i]=c[i]-p2[i];
    }
    cout<<"\nSubtraction of both the polynomials : "<<endl;
    cout_poly(c,l);
}

void mul_poly(int p1[], int m, int p2[], int n)
{
    int *c = new int[m+n-1];
    for(int i=0;i<=(m+n-1);i++)
    {
        c[i]=0;
    }
    for (int i=0; i<=m; i++)
   {
     for (int j=0; j<=n; j++)
     {
         c[i+j] += p1[i]*p2[j];
     }
   }
    cout<<"\nMultiplication of both the polynomials : "<<endl;
    cout_poly(c,m+n-1);
}

int main()
{
    int m,n;
    cout<<"\nEnter first polynomial degree : "<<endl;
    cin>>m;
    int a[m];
    cin_poly(a,m);
    cout_poly(a,m);
    cout<<"\nEnter second polynomial degree : "<<endl;
    cin>>n;
    int b[n];
    cin_poly(b,n);
    cout_poly(b,n);
    add_poly(a,m,b,n);
    sub_poly(a,m,b,n);
    mul_poly(a,m,b,n);
}
