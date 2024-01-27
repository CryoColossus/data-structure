#include <iostream>
#include <time.h>
using namespace std;
bool check_sudoku(char c[9][9])
{
    int a[9],i,j,k,t,x,y;
    for(i=0;i<9;i++)
    {
        for(k=0;k<9;k++)
        a[k]=k+1;
        for(j=0;j<9;j++)
        {
            t = c[i][j]-'0';
            if(a[t-1]==t)
            a[t-1]=0;
            else if(t==-2)
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
            t = c[j][i]-'0';
            if(a[t-1]==t)
            a[t-1]=0;
            else if(t==-2)
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
                    t = c[x][y]-'0';
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
void populate(char a[9][9])
{
    int i,j,d,n;
    srand(time(0));
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            d = rand()%10;
            if(d>=1)
            a[i][j]='.';
            else
            {
                n = (rand()%9)+1;
                a[i][j]=n+'0';
            }    
        }
    }
}
int main()
{
    int n,i,t,j;
    char a[9][9];
    populate(a);
    cout<<"Generated Array: "<<endl;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    bool s = check_sudoku(a);
    if(s)
    cout<<"Valid!"<<endl;
    else
    cout<<"Invalid!"<<endl;
    return 0;
}