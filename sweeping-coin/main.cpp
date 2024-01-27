#include <iostream>
using namespace std;
int max(int w,int x,int y,int z)
{
    if(w>=x&&w>=y&&w>=z)
    return w;
    if(x>=y&&x>=z)
    return x;
    if(y>=z)
    return y;
    else
    return z;
}
int pipe(int **M,int x,int y,int r,int c,int **T)
{
    int t1=0,t2=0,t3=0,t4=0;
    if(x!=0&&T[x-1][y]!=0)
    t1 = T[x-1][y];
    else if(x!=0&&M[x-1][y]>M[x][y])
    t1 = M[x][y]+pipe(M,x-1,y,r,c,T);
    if(x!=r-1&&T[x+1][y]!=0)
    t2 = T[x+1][y];
    else if(x!=r-1&&M[x+1][y]>M[x][y])
    t2 = M[x][y]+pipe(M,x+1,y,r,c,T);
    if(y!=0&&T[x][y-1]!=0)
    t3 = T[x][y-1];
    else if(y!=0&&M[x][y-1]>M[x][y])
    t3 = M[x][y]+pipe(M,x,y-1,r,c,T);
    if(y!=c-1&&T[x][y+1]!=0)
    t4 = T[x][y+1];
    else if(y!=c-1&&M[x][y+1]>M[x][y])
    t4 = M[x][y]+pipe(M,x,y+1,r,c,T);
    if(t1==0&&t2==0&&t3==0&&t4==0)
    return M[x][y];
    return max(t1,t2,t3,t4);
}
int max_path(int **M,int r,int c,int **T)
{
    int max=0,temp;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(i!=0&&T[i-1][j]!=0)
            temp = T[i-1][j];
            else if(i!=0&&M[i-1][j]>M[i][j])
            temp = M[i][j]+pipe(M,i-1,j,r,c,T);
            if(temp>max)
            max=temp;
            if(i!=r-1&&T[i+1][j]!=0)
            temp = T[i+1][j];
            else if(i!=r-1&&M[i+1][j]>M[i][j])
            temp = M[i][j]+pipe(M,i+1,j,r,c,T);
            if(temp>max)
            max=temp;
            if(j!=0&&T[i][j-1]!=0)
            temp = T[i][j-1];
            else if(j!=0&&M[i][j-1]>M[i][j])
            temp = M[i][j]+pipe(M,i,j-1,r,c,T);
            if(temp>max)
            max=temp;
            if(j!=c-1&&T[i][j+1]!=0)
            temp = T[i][j+1];
            else if(j!=c-1&&M[i][j+1]>M[i][j])
            temp = M[i][j]+pipe(M,i,j+1,r,c,T);
            if(temp>max)
            max=temp;
        }
    }
    return max;
}
int main()
{
    int r,c,i,j;
    cin>>r>>c;
    int **M = new int*[r];
    int **T = new int*[r];
    for(i=0;i<r;i++)
    {
        M[i] = new int[c];
        T[i] = new int[c];
    }   
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        M[i][j]==0;
    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        cin>>M[i][j];
    }
    int x = max_path(M,r,c,T);
    cout<<x<<endl;
    return 0;
}
