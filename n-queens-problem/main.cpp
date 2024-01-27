#include <iostream>
using namespace std;
void Valid_Solution(int **a,int n,int &count)
{
    cout<<endl;
    cout<<"A Solution is: "<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;    
    }
    count++;
}
bool peace(int **a,int n,int x,int y)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(a[i][y]==1&&i!=x)
            return false;
        if(a[x][i]==1&&i!=y)
            return false;
    }
    int m = min(x,y);
    while(max(x-m,y-m)<n)
    {
        if(a[x-m][y-m]==1&&m!=0)
            return false;
        m--;    
    }
    m=0;
    while(x-m!=0&&y+m!=n-1)
        m++;
    while(x-m<n&&!y+m>=0)
    {
        if(a[x-m][y+m]==1&&m!=0)
            return false;
        m--;
    }
    return true;
}
void Queenify(int **a,int n,int row,int &count)
{
    if(row>=n)
        return;
    for(int i=0;i<n;i++)
    {
        a[row][i]=1;
        if(peace(a,n,row,i))
        {
            if(row!=n-1)
                Queenify(a,n,row+1,count);
            else
                Valid_Solution(a,n,count);
        }    
        a[row][i]=0;    
    }
}
int main()
{
    int n,i,j,count=0;
    cout<<"Enter size of chessboard"<<endl;
    cin>>n;
    int **a = new int*[n];
    for(i=0;i<n;i++)
        a[i] = new int[n];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            a[i][j]=0;
    }
    Queenify(a,n,0,count);
    cout<<endl;
    cout<<"Total number of Solutions: "<<count<<endl; 
    return 0;    
}
