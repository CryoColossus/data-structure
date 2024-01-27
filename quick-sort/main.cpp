#include <iostream>
#include <time.h>
using namespace std;
int swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
int partition(int a[],int first,int last)
{
    int x=first,y=last;
    int piv = a[y];
    while(x!=y)
    {
        while(a[x]<piv&&x!=y)
        x++;
        while(a[y]>=piv&&y!=x)
        y--;
        if(x<y)
        swap(a[x],a[y]);
    }    
    if(x==y)
    swap(a[last],a[x]);
    return x;
}
void quicksort(int a[],int x,int y)
{
    if(x<y)
    {
        int s = partition(a,x,y);
        quicksort(a,x,s-1);
        quicksort(a,s+1,y);
    }    
}
int populate(int a[],int n)
{
    srand(time(0));
    for(int i=0;i<n;i++)
    a[i] = (rand()%1000)+1;
}
int main()
{
    int n;
    cin>>n;
    int a[n],i;
    populate(a,n);
    cout<<"Randomly Generated Array:"<<endl;
    for(i=0;i<n;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    quicksort(a,0,n-1);
    cout<<"Quick Sorted Array:"<<endl;
    for(i=0;i<n;i++)
    cout<<a[i]<<" ";
    return 0;
}