#include <stdio.h>
void fibo(int n, int i, int f0, int f1, int next)
{
    if(i>n)
    {
        return;
    }
    else
    {
        printf("%d ",f0);
        f0=f1;
        f1=next;
        next=f0+f1;
        fibo(n,i+1,f0,f1,next);
    }
}

int main()
{
    int n;
    printf("Enter the number till where you want the Fibonacci series  : ");
    scanf("%d",&n);
    if(n<0)
    {
     printf("Fibonacci series does not exist for negative integers.");
    }
    else
    {
     fibo(n,1,0,1,1);
    }
    return 0;
}
