#include<iostream>
using namespace std;
class integer
{
    int m,n;
public:
    integer(void);
    void output()
    {
        cout<<"m = "<<m<<endl;
        cout<<"n = "<<n<<endl;
    }
};
integer::integer(void)
{
    m=1,n=1;
}

class interger2
{
    int m,n;
public:
    interger2(int x);
    void output()
    {
        cout<<"m = "<<m<<endl;
        cout<<"n = "<<n<<endl;
    }
};
interger2::interger2(int x)
{
    m=x,n=100;
}


class interger3
{
    int m,n;
public:
    interger3(int x,int y);
    void output()
    {
        cout<<"m = "<<m<<endl;
        cout<<"n = "<<n<<endl;
    }
};
interger3::interger3(int x,int y)
{
    m=x,n=y;
}


int main()
{
    integer int1;
    int1.output();

    interger2 int2=interger2(100);
    int2.output();

    interger3 int3=interger3(0,100);
    int3.output();
}
