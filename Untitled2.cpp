//Program to demonstrate the use of STL (Standard Template Library)
#include<iostream>
#include<vector>
using namespace std;
//Driver code
int main()
{
	//create a vector to store int
	vector<int> vec;
	int i;
	//display the original size of vec
	cout<<"Vector size = "<<vec.size()<<endl;
	//push 5 values into the vector
	for(i = 0 ; i < 5 ; i++)
	{
		vec.push_back(i);
	}
	//display extended size of vec
	cout<<"Extended vector size = "<<vec.size()<<endl;
	//access 5 value from the vector
	for(i = 0 ; i < 5 ; i++)
	{
		cout<<"Value of vec["<<i<<"] = "<<vec[i]<<endl;
	}
	//use iterator to access the values
	vector<int> :: iterator v = vec.begin();
	while(v != vec.end())
	{
		cout<<"Value of v = "<<*v<<endl;
		v++;
	}
	return 0;
}
