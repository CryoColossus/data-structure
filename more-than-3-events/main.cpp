#include <iostream>
using namespace std;
int min(int a[][2],int n)
{
    int m = a[0][0];
    for(int i=0;i<n;i++)
    {
        if(m>a[i][0])
        m = a[i][0];
    }
    return m;
}
int max(int a[][2],int n)
{
    int m = a[0][1];
    for(int i=0;i<n;i++)
    {
        if(m<a[i][1])
        m = a[i][1];
    }
    return m;
}
void mark(int a[][2],int n,int check[],int l,int offset)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=a[i][0];j<=a[i][1];j++)
        check[j-1]++;
    }
}
int main()
{
    int n,i,j,low,high,l;
    cout<<"Enter Number of Upcoming Events: "<<endl;
    cin>>n;
    if(n>=3)
    {
        int a[n][2];
        for(i=0;i<n;i++)
        cin>>a[i][0]>>a[i][1];
        low = min(a,n);
        high = max(a,n);
        l = high-low+1;
        int check[l];
        for(i=0;i<l;i++)
        check[i]=0;
        mark(a,n,check,l,low);
        cout<<"Days with 3 or more than 3 activities are:"<<endl;
        for(i=0;i<l;i++)
        {
            if(check[i]>2)
            cout<<"Day: "<<i+1<<endl;
        }
    } 
    else
    cout<<"Number of Events less than 3!"<<endl;
    return 0;
}