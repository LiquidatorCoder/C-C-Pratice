#include <iostream>
#define MAX 9999
using namespace std;

class upper_tri_matrix
{
    int *input_matrix_pointer;
    int *output_matrix_pointer;
    int size;
public:
    upper_tri_matrix(){input_matrix_pointer = new int[0];output_matrix_pointer = new int[0];size = 0;}
    upper_tri_matrix(int n){input_matrix_pointer = new int[n*n];output_matrix_pointer = new int[(n*(n-1)/2)];size = n
;}
    void cin_matrix();
    void cout_matrix();
    upper_tri_matrix operator + (upper_tri_matrix B);
    upper_tri_matrix operator - (upper_tri_matrix B);
};
void upper_tri_matrix::cin_matrix()
{
    cout<<"Enter the 2D Matrix : "<<endl;
    for(int i = 0; i<size*size; i++)
    {
        int temp;
        cin>>temp;
        input_matrix_pointer[i] = temp;
    }
    //cout<<"Enter the 2D Matrix : "<<endl;
    //for(int i = 0; i<size; i++)
    //{
        //for(int j = 0; j<size; j++)
        //{
            //int temp;
            //cin>>temp;
            //output_matrix_pointer[(j-i+1)+(i-1)*size-((i-1)*(i-2))/2] = temp;
        //}
    //}
}

void upper_tri_matrix::cout_matrix()
{
    cout<<"2D Matrix : "<<endl;
    for(int i = 0; i<size; i++)
    {
        cout<<"[";
        for(int j = 0; j<size; j++)
        {
           cout<<input_matrix_pointer[i*(size)+j]<<" ";
        }
        cout<<"]\n";
    }

    //cout<<"2D Matrix : "<<endl;
    //for(int i = 0; i<size; i++)
    //{
        //cout<<"[";
        //for(int j = 0; j<size; j++)
        //{
           //cout<<output_matrix_pointer[i*(size)+j]<<" ";
        //}
        //cout<<"]\n";
        //size = size - 1;
    //}
}
upper_tri_matrix upper_tri_matrix::operator + (upper_tri_matrix B)
{
    upper_tri_matrix C(size);
    for(int i = 0; i<size*size; i++)
    {
        C.input_matrix_pointer[i] = input_matrix_pointer[i] + B.input_matrix_pointer[i];
    }
    return C;
}

upper_tri_matrix upper_tri_matrix::operator - (upper_tri_matrix B)
{
    upper_tri_matrix C(size);
    for(int i = 0; i<size*size; i++)
    {
        C.input_matrix_pointer[i] = input_matrix_pointer[i] - B.input_matrix_pointer[i];
    }
    return C;
}

int main()
{
    int n = 0;
    cout<<"Enter the size of the matrix (N) :"<<endl;
    cin>>n;
    upper_tri_matrix A(n);
    A.cin_matrix();
    A.cout_matrix();
    upper_tri_matrix B(n);
    B.cin_matrix();
    B.cout_matrix();
    upper_tri_matrix C(n);
    C = A + B;
    C.cout_matrix();
    C = A - B;
    C.cout_matrix();
    return 0;
}
