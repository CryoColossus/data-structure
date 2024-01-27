#include <iostream>
#include <time.h>
using namespace std;
bool search(int **a,int m,int n,int target)
{
    int l = (m-1)/2,c=0;
    if(a[m-1][0]<=target)
    {
        l = m-1;
        c=1;
    }
    int x=0,y=m-1;
    while(c==0)
    {
        if(a[l][0]>target)
        y = l-1;
        else if(l==m-1)
        break;
        else if(a[l][0]<=target&&a[l+1][0]>target)
        break;
        else if(a[l][0]<target&&a[l+1][0]<=target)
        x = l+1;
        else if(a[l][0]<target)
        x = l;
        else if(a[l][0]==target)
        break;
        if(x==y)
        l = x;
        l = (x+y)/2;
    }
    cout<<l<<endl;
}
void populate(int **a,int m,int n)
{
    int i,j,ran=0;
    srand(time(0));
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            ran+=(rand()%10)+1;
            a[i][j] = ran;
        }
    }
}
int main()
{
    int m,n,i,j,target;
    cout<<"Enter Number of Rows and Columns: "<<endl;
    cin>>m>>n;
    int** a = new int*[m];
    for(i=0;i<m;i++)
    a[i] = new int[n];
    populate(a,m,n);
    cout<<"Generated Array: "<<endl;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    cout<<"Enter Target Value: "<<endl;
    cin>>target;
    cout<<endl;
    search(a,m,n,target);
}

