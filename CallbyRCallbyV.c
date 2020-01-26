#include <stdio.h>
void swapv(int x, int y)
{
    int s;
    s=x;
    x=y;
    y=s;
    printf("Swapped by value a=%d\n",x);
    printf("Swapped by value b=%d\n",y);
}

void swapr(int *p, int *q)
{
    int t;
    t=*p;
    *p=*q;
    *q=t;
}

int main()
{
    int a,b;
    printf("Hello, Enter two numbers to be swapped :");
    scanf("%d %d",&a,&b);
    swapv(a,b);
    printf("a=%d\n",a);
    printf("b=%d\n",b);
    swapr(&a,&b);
    printf("Swapped by reference a=%d\n",a);
    printf("Swapped by reference b=%d\n",b);
    printf("a=%d\n",a);
    printf("b=%d\n",b);
    return 0;
}
