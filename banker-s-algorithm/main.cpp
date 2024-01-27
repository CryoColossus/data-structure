#include <iostream>
#include <queue>
using namespace std;
bool done(bool a[],int n)
{
    for(int i=0;i<n;i++)
        if(!a[i])
            return false;
    return true;        
}
bool sufficient(int **need,int avai[],int row,int columns)
{
    for(int i=0;i<columns;i++)
        if(need[row][i]>avai[i])
            return false;
    return true;        
}
bool banker(int **need,int **allo,int avai[],int p,int r,queue<int> &q)
{
    bool check[p]={false},update=true;
    while(!done(check,p)&&update)
    {
        update=false;
        for(int i=0;i<p;i++)
        {
            if(sufficient(need,avai,i,r)&&!check[i])
            {
                q.push(i+1);
                check[i]=true;
                for(int j=0;j<r;j++)
                    avai[j]+=allo[i][j];
                update=true;    
            }
        }
    }
    return (done(check,p))?true:false;
}
void success_print(queue<int> q)
{
    cout<<"There exists a Safe Sequence!"<<endl;
    cout<<"The sequence is:"<<endl;
    while(!q.empty())
    {
        cout<<"P"<<q.front();
        q.pop();
        if(!q.empty())
            cout<<"->";
    }
}
void failure_print()
{
    cout<<"The system will go into unsafe state eventually"<<endl;
    cout<<"That may result in a deadlock situation"<<endl;
}
void fill(int **a,int r,int c)
{
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            cin>>a[i][j];
}
int main()
{
    int p,r,i,j;
    cout<<"Enter Number of Processes"<<endl;
    cin>>p;
    cout<<"Enter Number of Resources"<<endl;
    cin>>r;
    int **allo = new int*[p];
    for(i=0;i<p;i++)
        allo[i] = new int[r];
    int **max = new int*[p];
    for(i=0;i<p;i++)
        max[i] = new int[r];
    int **need = new int*[p];
    for(i=0;i<p;i++)
        need[i] = new int[r];    
    int avai[r];
    cout<<"Enter Allocated Matrix ("<<p<<"x"<<r<<" Matrix)"<<endl;
    fill(allo,p,r);
    cout<<"Enter Max Requirement Matrix ("<<p<<"x"<<r<<" Matrix)"<<endl;
    fill(max,p,r);
    cout<<"Enter Available Resources ("<<r<<"x1 Matrix)"<<endl;
    for(i=0;i<r;i++)
        cin>>avai[i];
    for(i=0;i<p;i++)
        for(j=0;j<r;j++)
            need[i][j]=max[i][j]-allo[i][j];
    queue<int> q;
    bool safety = banker(need,allo,avai,p,r,q);   
    (safety)?success_print(q):failure_print();
    return 0;
}
