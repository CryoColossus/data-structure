#include <iostream>
#include <limits.h>
using namespace std;
int max(int a,int b){return (a>b)?a:b;}
int Cutter(int sp[],int n)
{
    int mprof[n+1],i,j;
    mprof[0]=0;
    for(i=1;i<=n;i++)
    {
        int x = INT_MIN;
        for(j=0;j<i;j++)
        x = max(x,sp[j]+mprof[i-j-1]);
        mprof[i] = x;
    }
    return mprof[n];
}
int main()
{
    int n,i;
    cout<<"Length of Rod"<<endl;
    cin>>n;
    int sp[n];
    cout<<"Enter prices for rod lengths from 1 to "<<n<<" :"<<endl;
    for(i=0;i<n;i++)
    cin>>sp[i];
    cout<<"Maximum Money obtainable is: "<<Cutter(sp,n)<<endl;
    return 0;
}
