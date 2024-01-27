#include <iostream>
#include <string>
using namespace std;
struct Node
{
    struct Node *lc;
    string initials;
    int value;
    struct Node *rc;
};
typedef struct Node *bstptr;
void insert(bstptr &T,string s,int n)
{
    if(!T)
    {
        T = new Node;
        T->lc = nullptr;
        T->rc = nullptr;
        T->initials = s;
        T->value = n;
    }
    else
    {
        if(s>T->initials)
        insert(T->rc,s,n);
        else if(s<T->initials)
        insert(T->lc,s,n);
        else
        T->value += n;
    }
}
void Printer(bstptr T)
{
    if(T)
    {
        Printer(T->lc);
        cout<<T->initials<<" "<<T->value<<endl;
        Printer(T->rc);
    }
}
int main()
{
    int n;
    bstptr T = nullptr;
    cout<<"Enter Number of Entries"<<endl;
    cin>>n;
    if(n>0)
    {
        string a[n];
        cout<<"Enter Initials:"<<endl;
        int b[n],i;
        for(i=0;i<n;i++)
        cin>>a[i];
        cout<<"Enter Numbers:"<<endl;
        for(i=0;i<n;i++)
        cin>>b[i];
        for(i=0;i<n;i++)
        insert(T,a[i],b[i]);
        cout<<"Required List: "<<endl;
        Printer(T);
    }    
    return 0;
}
