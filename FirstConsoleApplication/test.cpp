#include<iostream>
#include<math.h>
using namespace std;

int main()

{

    double abs_err, rel_err, p_rel_err, t_val, a_val;
    cout<<"\n INPUT TRUE VALUE:";
    cin>>t_val;

    cout<<"\n INPUT APPROXIMATE VALUE:";
    cin>>a_val;

abs_err=fabs(t_val-a_val);
rel_err=abs_err/t_val;
p_rel_err=rel_err*100;
cout<<"\nABSOLUTE ERROR= "<<abs_err;

cout<<"\nRELATIVE ERROR= "<<rel_err;
cout<<"\nPERCENTAGE RELATIVE ERROR= "<<p_rel_err;

return 0;
}
