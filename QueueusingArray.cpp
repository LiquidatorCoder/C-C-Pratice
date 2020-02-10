#include <iostream>
using namespace std;

struct Queue {
    int front, rear, capacity;
    int* queue;
    Queue(int c)
    {
        front = rear = 0;
        capacity = c;
        queue = new int;
    }
    ~Queue() { delete[] queue; }
    void enqueue(int data)
    {
        if (capacity == rear) {
            cout<<"\nQueue is full\n";
            return;
        }
        else {
            queue[rear] = data;
            rear++;
        }
        return;
    }
    void dequeue()
    {
        if (front == rear) {
            cout<<"\nQueue is  empty\n";
            return;
        }
        else {
            for (int i = 0; i < rear - 1; i++) {
                queue[i] = queue[i + 1];
            }
            rear--;
        }
        return;
    }
    void disp()
    {
        int i;
        if (front == rear) {
            cout<<"\nQueue is Empty\n";
            return;
        }
        for (i = front; i < rear; i++) {
            cout<<queue[i]<<" ";
        }
        return;
    }
};

int main(void)
{
    int len = 0;
    cout<<"Enter length of queue : "<<endl;
    cin>>len;
    Queue q(len);
    char c;
    while(c!='q')
    {
        cout<<"\nEnter your choice : (e for enqueue, r for dequeue, d for disp, q for quit) : "<<endl;
        cin>>c;
        if(c=='e')
        {
            int val = 0;
            cout<<"Enter the value to added to queue : "<<endl;
            cin>>val;
            q.enqueue(val);
        }
        else if(c=='r')
        {
            q.dequeue();
        }
        else if(c=='d')
        {
            q.disp();
        }
    }
    return 0;
}
