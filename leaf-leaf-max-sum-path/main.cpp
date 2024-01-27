#include <iostream>
#include <limits.h>
using namespace std;
struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
};
int max(int x,int y,int z)
{
    return (x>=y&&x>=z)?x:((y>=z)?y:z);
}
int max(int x,int y)
{
    return (x>y)?x:y;
}
int length(Node *X)
{
    if(X)
    {
        if(X->left==NULL&&X->right!=NULL)
        return (length(X->right)+X->data);
        else if(X->left!=NULL&&X->right==NULL)
        return (length(X->left)+X->data);
    }    
    return (X)?(max(length(X->left),length(X->right))+X->data):0;
}
int maxPathSum(Node* root)
{ 
    if(root)
    {
        if(root->left==NULL||root->right==NULL)
        return INT_MIN;
    }
    return (root)?max(length(root->left)+length(root->right)+root->data,maxPathSum(root->left),maxPathSum(root->right)):0;   
}
void insert(struct Node* &T,int n)
{
    if(!T)
    {
        T = new(Node);
        T->data = n;
        T->left = NULL;
        T->right = NULL;
    }
    cin>>n;
    if(n!=0)
    insert(T->left,n);
    cin>>n;
    if(n!=0)
    insert(T->right,n);
}
int main()
{
    struct Node *T = nullptr;
    int n;
    cin>>n;
    insert(T,n);
    cout<<maxPathSum(T)<<endl;
    return 0;
}
