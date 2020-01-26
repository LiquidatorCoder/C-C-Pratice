#include <iostream>
using namespace std;

void swapv(int x, int y)
{
    int s;
    s=x;
    x=y;
    y=s;
    cout<<"Swapped by value a="<<x<<"\n";
    cout<<"Swapped by value b="<<y<<"\n";
}

void swapr(int &p, int &q)
{
    int t;
    t=p;
    p=q;
    q=t;
}

int main()
{
    int a,b;
    cout<<"Hello, Enter two numbers to be swapped :";
    cin>>a>>b;
    swapv(a,b);
    cout<<"a="<<a<<"\n";
    cout<<"b="<<b<<"\n";
    swapr(a,b);
    cout<<"Swapped by reference a="<<a<<"\n";
    cout<<"Swapped by reference b="<<b<<"\n";
    cout<<"a="<<a<<"\n";
    cout<<"b="<<b<<"\n";
    return 0;
}
