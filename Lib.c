#include <stdio.h>
struct member
{
    int id_no;
    char m_books[10][40];
    char m_name[];

};
struct book
{
    int bid_no;
    char b_avail[5];
    char b_name[];

};

int main()
{
    struct member m1[100];
    struct book b1[100];
    int c;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\t\tLIBRARY\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Welcome to Library.\n");
    printf("Choose from 1 to 7 from the menu below.\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("1. Add a Book\n");
    printf("2. Issue a Book\n");
    printf("3. Return a Book\n");
    printf("4. Add a Member\n");
    printf("5. Forfeit Membership\n");
    printf("6. List of Books\n\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Enter your choice : ");
    scanf("%d",&c);
    switch(c)
    {

    case 1:
        printf("You selected 1.\n");
        break;
    case 2:
        printf("You selected 2.\n");
        break;
    case 3:
        printf("You selected 3.\n");
        for(int i=0;m1[i].m_name!=0; i++)
        {
            printf("%s",m1[i].m_name);
        }

        break;
    case 4:
        printf("You selected 4.\n");
        break;
    case 5:
        printf("You selected 5.\n");
        break;
    case 6:
        printf("You selected 6.\n");
        break;
    }
    return 0;
}
