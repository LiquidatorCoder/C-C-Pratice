#include<iostream>
using namespace std;
void si(float a=20000.0, float b=4.0, float c=2.0)
{
    float s;
    s=(a*b*c)/100.00;
    cout<<"\nPrinciple : "<<a;
    cout<<"\nRate : "<<b;
    cout<<"\nTime : "<<c;
    cout<<"\nSimple Interest : "<<s;
    cout<<"\nTotal Amount : "<<s+a;
}
int main()
{
    float p,r,t;
    cout<<"Hello, Enter the Principal Rate and Time (0 to pass) : ";
    cin>>p;
    if(p==0)
    {
        si();
    }
    else
    {
       cin>>r;
       if(r==0)
       {
           si(p);
       }
       else
       {
           cin>>t;
           if(t==0)
           {
               si(p,r);
           }
           else
           {
               si(p,r,t);
           }
       }
    }
    return 0;
}

