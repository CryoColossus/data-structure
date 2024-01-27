#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    int n;
    cout<<"Enter Number of Dice Rolls"<<endl;
    cin>>n;
    cout<<"The Required Probability is:"<<endl;
    cout<<(float)pow(6,(n%2==0)?n/2:((n+1)/2))/(float)pow(6,n)<<endl;
    return 0;
}