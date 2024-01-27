#include <iostream>
using namespace std;
int zeroes(int n)
{
    int fact=5,adder=1,val=0;
    while(adder!=0)
    {
        adder=n/fact;
        val+=adder;
        fact*=5;
    }
    return val;
}
int main()
{
    int n,T;
    cin>>T;
    for(int i=0;i<T;i++)
    {
        cin>>n;
        int x = zeroes(n);
        cout<<x<<endl;
    }    
    return 0;
}
