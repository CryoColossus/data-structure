#include <iostream>
using namespace std;
int main()
{
    long long int n;
    cout<<"Enter your Number to start the series: ";
    cin>>n;
    cout<<"The Generated Series is: "<<endl;
    cout<<n<<" ";
    do
    {
        n = (n%2==0)?n/2:3*n+1;
        cout<<n<<" ";
    }while(n!=1);
    return 0;
}
