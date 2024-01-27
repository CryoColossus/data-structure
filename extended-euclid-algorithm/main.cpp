#include <iostream>
using namespace std;
void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
int main()
{
    int a,b,t,q,r,data[2][3] = {{1,0,1},{0,1,-1}},n1,n2;
    cout<<"Enter the two numbers to calculate the GCD of: "<<endl;
    cin>>a>>b;
    if(b>a)
        swap(a,b);
    n1 = a;
    n2 = b;
    q = a/b;
    r = a%b;    
    data[0][2] = data[0][0] - q*data[0][1];
    data[1][2] = data[1][0] - q*data[1][1];
    if(a<0)
        cout<<"The GCD value is: "<<b<<endl;
    else if(b<0)
        cout<<"The GCD value is: "<<a<<endl;
    else
    {
        while(b!=0)
        {
            if(r!=0)
                q = b/r;
            data[0][0] = data[0][1];
            data[1][0] = data[1][1];
            data[0][1] = data[0][2];
            data[1][1] = data[1][2];
            data[0][2] = data[0][0] - q*data[0][1];
            data[1][2] = data[1][0] - q*data[1][1];
            t = a%b;
            a = b;
            b = t;
            if(b!=0)
                r = a%b;
        }
        cout<<"The GCD value is: "<<a<<endl;
        cout<<"The variables a and b are "<<data[0][2]<<" and "<<data[1][2]<<endl; 
        cout<<"Such that "<<n1<<"*"<<data[0][2]<<"+"<<n2<<"*"<<data[1][2]<<" = "<<a<<endl;
    }
    return 0;
}