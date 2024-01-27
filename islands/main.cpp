#include <iostream>
#include <time.h>
using namespace std;
struct ipair
{
    int x;
    int y;
};
struct Stack
{
    int top;
    struct ipair a[500];
    int max;
};
void push(struct Stack &q,ipair p)
{
    if(q.top!=q.max)
    q.a[++q.top]=p;
    else
    cout<<"Overflow!"<<endl;
}
ipair pop(struct Stack &q)
{
    if(q.top!=-1)
    return q.a[q.top--];
}
bool isEmpty(struct Stack q)
{return (q.top==-1)?true:false;}
void tracker(int **a,int n,struct Stack &q)
{
    while(!isEmpty(q))
    {
        ipair p = pop(q);
        int i = p.x;
        int j = p.y;
        if(j!=0)
        {
            p.x = i;
            p.y=j-1;
            if(a[i][j-1]==1)
            {
                push(q,p);
                a[i][j-1]=0;
            }    
        }
        if(j!=n-1)
        {
            p.x = i;
            p.y = j+1;
            if(a[i][j+1]==1)
            {
                push(q,p);
                a[i][j+1]=0;
            }    
        }
        if(i!=n-1)
        {
            p.x = i+1;
            p.y = j;
            if(a[i+1][j]==1)
            {
                push(q,p);
                a[i+1][j]=0;
            }    
        }
        if(i!=0)
        {
            p.x = i-1;
            p.y = j;
            if(a[i-1][j]==1)
            {
                push(q,p);
                a[i-1][j]=0;
            }    
        }
    }
}
int search_islands(int **a,int n)
{
    int i,j,no_of_islands=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]==1)
            {
                struct ipair p;
                struct Stack q;
                q.top=-1;
                q.max=500;
                p.x = i;
                p.y = j;
                push(q,p);
                tracker(a,n,q);
                no_of_islands++;
            }
        }
    }
    return no_of_islands;
}
void populate(int **a,int n)
{
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        a[i][j]=rand()%2;
    }    
}
int main()
{
    int n,i,j,islands;
    cout<<"Enter size of Map"<<endl;
    cin>>n;
    int **a = new int*[n];
    for(i=0;i<n;i++)
    a[i] = new int[n];
    populate(a,n);
    cout<<"Generated Map is:"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]==0)
            cout<<"  ";
            else
            cout<<"1 ";
        }
        cout<<endl;
    }
    islands = search_islands(a,n);
    cout<<endl;
    cout<<"Number of Islands are: "<<islands<<endl;
    return 0;
}
