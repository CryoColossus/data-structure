#include <iostream>
using namespace std;
struct Btnode
{
    struct Btnode *lc;
    int data;
    struct Btnode *rc;
};
typedef struct Btnode *btptr;
struct iqueue
{
    int s;
    int e;
    btptr a[50];
    int max;
};
void enqueue(struct iqueue &q,btptr n)
{
    if(q.s==-1||q.e==-1)
    {
        q.a[0]=n;
        q.s=0;
        q.e=0;
    }
    else if((q.e+1)%q.max==q.s)
    cout<<"Queue is Full!"<<endl;
    else
    q.a[(++q.e)%q.max]=n;
}
btptr dequeue(struct iqueue &q)
{
    if(q.s==-1||q.e==-1)
    cout<<"Queue is Empty!"<<endl;
    else if(q.s==q.e)
    {
        int n = q.s;
        q.s=-1;
        q.e=-1;
        return q.a[n];
    }
    else
    return q.a[(q.s++)%q.max];
}
bool is_Empty(struct iqueue q)
{return (q.s==-1||q.e==-1)?true:false;}
void create(btptr &b,int n)
{
    if(!b)
    {
        b = new Btnode;
        b->lc = nullptr;
        b->rc = nullptr;
        b->data=n;
    }
    cin>>n;
    if(n!=0)
    create(b->lc,n);
    cin>>n;
    if(n!=0)
    create(b->rc,n);
}
void level_printer(btptr b)
{
    iqueue q;
    q.s=-1;
    q.e=-1;
    q.max=50;
    enqueue(q,b);
    while(!is_Empty(q))
    {
        btptr temp = dequeue(q);
        if(temp->lc)
        enqueue(q,temp->lc);
        if(temp->rc)
        enqueue(q,temp->rc);
        cout<<temp->data<<" ";
    }
}
int main()
{
    btptr b=nullptr;
    int n;
    cout<<"Enter Binary Tree elements"<<endl;
    cin>>n;
    create(b,n);
    level_printer(b);
}
