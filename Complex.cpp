#include<iostream>
using namespace std;
class Complex_Number
{
    int real = 1;
    int imag = 1;
public:
    void input()
    {
        cout<<"\nEnter a complex number : ";
        cin>>real>>imag;
    }
    void output()
    {
        cout<<"\n"<<real<<" + "<<imag<<"i";
    }
    void r_add(int in1)
    {
        real=real+in1;
    }
    void r_sub(int in1)
    {
        real=real-in1;
    }
    void i_add(int in2)
    {
        imag=imag+in2;
    }
    void i_sub(int in2)
    {
        imag=imag-in2;
    }
};
int main()
{
    int ui1,ui2;
    Complex_Number C1;
    C1.output();
    C1.input();
    C1.output();
    cout<<"\nEnter any real number to add and subtract :";
    cin>>ui1;
    C1.r_add(ui1);
    C1.output();
    C1.r_sub(ui1);
    C1.output();
    cout<<"\nEnter any imaginary number to add and subtract : ";
    cin>>ui2;
    C1.i_sub(ui2);
    C1.output();
    C1.i_add(ui2);
    C1.output();
    return 0;
}
