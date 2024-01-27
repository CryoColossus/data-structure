#include <iostream>
using namespace std;
void spiral_print(int **a,int x,int y)
{
    if(x>y)
        return;
    int i;
    for(i=x;i<y;i++)
        cout<<a[x][i]<<" ";
    for(i=x+1;i<y;i++)
        cout<<a[i][y-1]<<" ";
    for(i=y-2;i>=x;i--)
        cout<<a[y-1][i]<<" ";
    for(i=y-2;i>x;i--)
        cout<<a[i][x]<<" ";
    spiral_print(a,x+1,y-1);
}
int main()
{
    int n,i,j;
    cout<<"Enter size of Matrix"<<endl;
    cin>>n;
    int **a = new int*[n];
    for(i=0;i<n;i++)
        a[i] = new int[n];
    cout<<"Enter Matrix Elements"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            cin>>a[i][j];
    }
    cout<<"Result Matrix is:"<<endl;
    spiral_print(a,0,n);
    return 0;
}