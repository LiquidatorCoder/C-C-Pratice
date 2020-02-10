#include <iostream>
using namespace std;
#define max 100

class Stack {
    int top;
public:
    int a[max];
    Stack() { top = -1; }
    void push(int x);
    int disp();
    int pop();
    bool isEmpty();
};

void Stack::push(int x)
{
    if (top >= (max - 1)) {
        cout << "Stack Overflow";
    }
    else {
        a[++top] = x;
        cout << x << " is pushed into stack\n";
    }
}

int Stack::disp()
{
    if (top < 0) {
        cout << "Stack is Empty";
        return 0;
    }
    else {
        int x = a[top];
        return x;
    }
}

int Stack::pop()
{
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int x = a[top--];
        return x;
    }
}
bool Stack::isEmpty()
{
    return (top < 0);
}

int main()
{
    class Stack s;
    char c;
    while(c!='q')
    {
        cout<<"\nEnter your choice : (p for push, r for pop, d for disp, q for quit) : "<<endl;
        cin>>c;
        if(c=='p')
        {
            int val = 0;
            cout<<"Enter the value to be pushed : "<<endl;
            cin>>val;
            s.push(val);
        }
        else if(c=='r')
        {
            cout<<s.pop()<<" Popped from stack\n";
        }
        else if(c=='d')
        {
            cout<<s.disp()<<" is at the top of the stack\n";
        }
    }
    return 0;
}
