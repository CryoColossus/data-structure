#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;
struct TreeNode
{
    struct TreeNode *left;
    int data;
    struct TreeNode *right;
};
typedef struct TreeNode *treeptr;
void create(treeptr &T,char n)
{
    if(!T)
    {
        T = new TreeNode;
        T->left = nullptr;
        T->right = nullptr;
        T->data = n-'0';
    }
    cin>>n;
    if(n!='.')
    create(T->left,n);
    cin>>n;
    if(n!='.')
    create(T->right,n);
}
void print(treeptr L,int detector)
{
    if(L)
    {
        cout<<"->"<<L->data;
        print(L->right,1);
    }
    else if(detector==0)
    {
        cout<<"EMPTY LINKED LIST!"<<endl;
    }
}
void make_ll(treeptr &ll,int x)
{
    if(!ll)
    {
        ll = new TreeNode;
        ll->left = nullptr;
        ll->right = nullptr;
        ll->data = x;
    }
    else
    make_ll(ll->right,x);
}
treeptr linkify(treeptr T,int x,int y)
{
    if(!T)
    return T;
    treeptr divider = new TreeNode;
    divider->data = INT_MAX;
    treeptr ll = nullptr;
    queue<treeptr> q;
    q.push(T);
    q.push(divider);
    int level=1;
    while(q.size()!=1)
    {
        treeptr temp = q.front();
        q.pop();
        if(temp->data==INT_MAX)
        {
            q.push(divider);
            level++;
        }
        else
        {
            if(temp->left)
            q.push(temp->left);
            if(temp->right)
            q.push(temp->right);
            if(level>=x&&level<=y)
            make_ll(ll,temp->data);
        }
    }
    return ll;
}
int main()
{
    treeptr T = nullptr;
    int x,y;
    char n;
    cin>>n;
    if(n!='.')
    {
        create(T,n);
        cout<<"Enter Bounds:"<<endl;
        cin>>x>>y;
        treeptr L = linkify(T,x,y);
        cout<<"The Linked List is: "<<endl;
        print(L,0);
    }
    else
    cout<<"Empty Tree!"<<endl;
    return 0;
}