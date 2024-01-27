#include <iostream>
using namespace std;
long long closest_divisible(long long m,long long n)
{
    long long x = n%m;
    long long y = m-x;
    return ((y>x)?(n-x):(n+y));
}
int main()
{
    long long m,n;
    cin>>m>>n;
    cout<<endl;
    cout<<closest_divisible(m,n)<<endl;
    return 0;
}