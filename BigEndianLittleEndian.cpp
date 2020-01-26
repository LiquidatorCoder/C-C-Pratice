#include <iostream>
using namespace std;

int main()
{
    unsigned int x = 5;
    char *b = (char*)&x;
    if (*b == 5)
    {
        cout<<"Compiler is working in Little Endian"<<endl;
    }
    else
    {
        cout<<"Compiler is working in Big Endian"<<endl;
    }
}
