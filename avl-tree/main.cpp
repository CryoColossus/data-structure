#include <iostream>
#include <stack>
#include <queue>
using namespace std;
struct bstnode
{
    struct bstnode *lc;
    int data;
    struct bstnode *rc;
};
typedef struct bstnode *bstptr;
void left_rotation(bstptr c,bstptr p)
{
    if(p->rc==c)
    {
        bstptr T1=p->lc,T2=c->lc,T3=c->rc;
        int temp = p->data;
        p->data = c->data;
        c->data = temp;
        p->rc = T3;
        p->lc = c;
        c->lc = T1;
        c->rc = T2;
    }
    else
        cout<<"Invalid input to left_rotation"<<endl;
}
void right_rotation(bstptr c,bstptr p)
{
    if(p->lc==c)
    {
        bstptr T1=c->lc,T2=c->rc,T3=p->rc;
        int temp = p->data;
        p->data = c->data;
        c->data = temp;
        p->lc = T1;
        p->rc = c;
        c->lc = T2;
        c->rc = T3;
    }
    else
        cout<<"Invalid input to right_rotation"<<endl;
}
int max(int x,int y)
{return x>y?x:y;}
int height(bstptr root)
{
    if(!root)
        return 0;
    return (1+max(height(root->lc),height(root->rc)));    
}
void insert(bstptr &root,int x,stack<bstptr> s)
{
    if(!root)
    {
        root = new bstnode;
        root->lc = root->rc = nullptr;
        root->data = x;
        s.push(root);
    }
    if(root->data>x)
    {
        s.push(root);
        insert(root->lc,x,s);
    }    
    else if(root->data<x)
    {
        s.push(root);
        insert(root->rc,x,s);
    }    
    if(s.size()>=3)
    {
        bstptr p,c,gc;
        gc = s.top();
        s.pop();
        c = s.top();
        s.pop();
        p = s.top();
        int a = height(p->lc),b = height(p->rc);
        int diff = a-b;
        if((diff)>1||(diff)<-1)
        {
            if(p->lc==c&&c->lc==gc)
            {
                right_rotation(c,p);
            }
            else if(p->lc==c&&c->rc==gc)
            {
                left_rotation(gc,c);
                right_rotation(c,p);
            }
            else if(p->rc==c&&c->lc==gc)
            {
                right_rotation(gc,c);
                left_rotation(c,p);
            }
            else if(p->rc==c&&c->rc==gc)
            {
                left_rotation(c,p);
            }
        }    
    }    
}   
void levelorder_print(bstptr root)
{
    queue<bstptr> q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty())
    {
        bstptr temp = q.front();
        q.pop();
        if(temp)
        {
            cout<<temp->data<<" ";
            if(temp->lc)
                q.push(temp->lc);
            if(temp->rc)
                q.push(temp->rc);
        }
        else
        {
            if(!q.empty())
            q.push(nullptr);
            cout<<endl;
        }    
    }
}
int main()
{
    int n;
    bstptr root = nullptr;
    stack<bstptr> s;
    cout<<"Enter integers to insert inside tree (Type -1 to end input)"<<endl;
    cin>>n;
    while(n!=-1)
    {
        insert(root,n,s);
        cin>>n;
    }
    cout<<"The Balanced Search Tree (AVL Tree) Printed Level-Order is as follows:"<<endl;
    levelorder_print(root);
    return 0;
}