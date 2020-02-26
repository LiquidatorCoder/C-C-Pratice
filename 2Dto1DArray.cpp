#include <iostream>
using namespace std;

int main()
{
    int n,m;
    cout<<"Enter n and m of the matrix of order (n*m) : "<<endl;
    cin>>n>>m;
    int tda[n][m];
    int oda[n*m];

    cout<<endl;
    cout<<"Enter 2D array values"<<endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>tda[i][j];
        }
    }

    cout<<endl;
    cout<<"The 2D Array you entered : "<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"[ ";
        for(int j=0; j<m; j++)
        {
            cout<<tda[i][j]<<" ";
        }
        cout<<"]"<<endl;
    }

    cout<<endl;
    cout<<"Final 1D Array for Row-Major mapped 2D array: "<<endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            int temp=0;
            temp=tda[i][j];
            oda[j+(i*m)]=temp;
        }
    }
    for(int i=0; i<n*m; i++)
    {
        cout<<oda[i]<<" ";
    }

    cout<<endl;
    cout<<endl;

    cout<<"Final 1D Array for Column-Major mapped 2D array: "<<endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            int temp=0;
            temp=tda[i][j];
            oda[i+(j*n)]=temp;
        }
    }
    for(int i=0; i<n*m; i++)
    {
        cout<<oda[i]<<" ";
    }
    cout<<endl;
}
