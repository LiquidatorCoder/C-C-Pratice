//Program to illustrate multilevel inheritance
#include<iostream>
#include<conio.h>
//Declare class Person
class Person
{
//Declare data members for class Person
char name[100], gender[10];
int age;
public:
//Get details of person
void getdata()
{
cout<<endl<<"Name: ";
cin>>name;
cout<<endl<<"Age: ";
cin>>age;
cout<<endl<<"Gender: ";
cin>>gender;
}
//Define display function to show person's  details
void display()
{
cout<<endl<<"Name: "<<name;
cout<<endl<<"Age: "<<age;
cout<<endl<<"Gender: "<<gender;
}
};
//Declare another class Employee that inherits Person's data members and makes them publicly accessible
class Employee: public Person
{
//Declare data members for class Employee
char company[100];
float salary;
public:
//Get details of employee
void getdata()
{
Person :: getdata(); //Get Person data using '::' operator
cout<<endl<<"Name of Company: ";
cin>>company;
cout<<endl<<"Salary(in Rs): ";
cin>>salary;
}
//Define display function to show employee's  details
void display()
{
Person :: display(); //Display Person data using '::' operator
cout<<endl<<"Name of Company: "<<company;
cout<<endl<<"Salary(in Rs): "<<salary;
}
};
//Declare 3rd class Programmer that inherits Employee's data members (which has already inherited from Person) and makes them publicly accessible
class Programmer: public Employee
{
//Declare data members for Programmer
int number;
public:
//Get details of programmer
void getdata()
{
Employee::getdata();//Get Employee data using '::' operator
cout<<endl<<"Number of programming languages known: ";
cin>>number;
}
//Define display function to show programmer's  details
void display()
{
Employee::display();//Display Employee data using '::' operator
cout<<endl<<"Number of programming languages known: "<<number;
}
};
//Driver code
void main()
{
clrscr();
Programmer p; //Declare Programmer object
cout<<"\tEnter data";
p.getdata(); //Call getdata() function to get all the data
cout<<endl<<"\tDisplaying data";
p.display(); //Call display() function to display all the data
getch();
}


