#include <iostream>
using namespace std;
void swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
void merger(int a[],int x,int y,int temp[])
{
    int l = ((x+y)/2)+1,m=x,i;
    for(i=x;i<=y;i++)
        temp[i]=a[i];
        
}
void merge_sort(int a[],int x,int y,int temp[])
{
    if(x>=y)
        return;
    if(x+1==y)
    {
        if(a[x]>a[y])
            swap(a[x],a[y]);
        return;    
    }
    int mid = (x+y)/2;    
    merge_sort(a,x,mid,temp);
    merge_sort(a,mid+1,y,temp);
    merger(a,x,y,temp);
}
int main()
{
    int n,i;
    cout<<"Enter Size of Array"<<endl;
    cin>>n;
    int a[n],temp[n];
    cout<<"Enter Array Elements"<<endl;
    for(i=0;i<n;i++)
        cin>>a[i];
    merge_sort(a,0,n-1,temp); 
    for(i=0;i<n;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
