#include <iostream>
using namespace std;
void power(int m, int n)
{
    int a=1,c=n;
    while (n != 0) {
        a *= m;
        n=n-1;
    }
    cout << m << "^" << c << " = ";
    cout << a;
}

void power(double m, int n)
{
    double a=1.00;
    int c=n;
    while (n != 0) {
        a *= m;
        n=n-1;
    }
    cout << m << "^" << c << " = ";
    cout << a;
}


int main()
{
    int e,y;
    float b;
    cout << "Enter base and exponent respectively : ";
    cin >> b >> e;
    y=b*10;
    if(y%10==0)
    {
        //b is int.
        b=(int)b;
        power(b,e);
    }
    else
    {
        power(b,e);
    }
    return 0;
}
