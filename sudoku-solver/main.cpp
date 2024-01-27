#include <iostream>
using namespace std;
void print(int **board)
{
    cout<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;    
    }
    cout<<endl;
}
bool valid(int **board)
{
    int a[9],i,j,k,t,x,y;
    for(i=0;i<9;i++)
    {
        for(k=0;k<9;k++)
            a[k]=k+1;
        for(j=0;j<9;j++)
        {
            t = board[i][j];
            if(a[t-1]==t)
                a[t-1]=0;
            else if(t==0)
                continue;
            else
                return false;
        }
    }
    for(i=0;i<9;i++)
    {
        for(k=0;k<9;k++)
            a[k]=k+1;
        for(j=0;j<9;j++)
        {
            t = board[j][i];
            if(a[t-1]==t)
                a[t-1]=0;
            else if(t==0)
                continue;
            else
                return false;
        }
    }
    for(i=0;i<9;i+=3)
    {
        for(j=0;j<9;j+=3)
        {
            for(k=0;k<9;k++)
                a[k]=k+1;
            for(x=i;x<i+3;x++)
            {
                for(y=j;y<j+3;y++)
                {
                    t = board[x][y];
                    if(a[t-1]==t)
                        a[t-1]=0;
                    else if(t==-2)
                        continue;
                    else
                        return false;
                }
            }
        }
    }
    return true;
}
void solve(int **board,int x,int y)
{
    if(x>8||y>8)
        return;
    if(board[x][y]!=0)
    {
        y=(y+1)%9;
        x=((y==0)?x+1:x);
        solve(board,x,y);
    }
    else
    {
        for(int i=1;i<10;i++)
        {
            board[x][y]=i;
            if(valid(board))
            {
                if(x>=8&&y>=8)
                {
                    print(board);
                    return;
                }    
                else
                {
                    int x1=((y==8)?x+1:x);
                    int y1=(y+1)%9;
                    solve(board,x1,y1);
                }    
            }
            board[x][y]=0;
        }
    }
}
int main()
{
    int i,j;
    int **board = new int*[9];
    for(i=0;i<9;i++)
        board[i] = new int[9]();
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            cin>>board[i][j];
    solve(board,0,0); 
    cout<<"Normal Exit"<<endl;
    return 0;
}