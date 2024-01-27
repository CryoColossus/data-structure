#include <iostream>
#include <math.h>
using namespace std;
struct Exnode
{
    struct Exnode *lc;
    char data;
    char bracket;
    struct Exnode *rc;
};
typedef struct Exnode *exptr;
struct estack
{
    int top;
    exptr a[50];
    int max;
};
void push(struct estack &s,exptr e)
{
    if(s.top!=s.max)
    s.a[++s.top]=e;
}
exptr pop(struct estack &s)
{
    if(s.top!=-1)
    return s.a[s.top--];
}
void express(string s,exptr &e)
{
    struct estack S;
    S.top=-1;
    S.max=50;
    int n = s.length(),i;
    for(i=0;i<n;i++)
    {
        exptr ex = new Exnode;
        ex->data = s[i];
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
            exptr erc = pop(S);
            erc->bracket = ')';
            exptr elc = pop(S);
            elc->bracket = '(';
            ex->lc = elc;
            ex->rc = erc;
            push(S,ex);
        }
        else
        push(S,ex);
    }
    e = pop(S);
}
void inorder(exptr e,char c)
{
    if(e)
    {
        if(e->bracket='('&&e->lc)
        cout<<"(";
        if(c=='*'||e->data=='^')
        inorder(e->lc,e->data);
        else
        inorder(e->lc,e->data);
        cout<<e->data;
        if(c=='*'||e->data=='^')
        inorder(e->rc,e->data);
        else
        inorder(e->rc,e->data);
        if(e->bracket=')'&&e->rc)
        cout<<")";
    }
}
int value(exptr e)
{
    if(e)
    return (e->data=='+')?value(e->lc)+value(e->rc):(e->data=='-')?value(e->lc)-value(e->rc):(e->data=='*')?value(e->lc)*value(e->rc):(e->data=='/')?value(e->lc)/value(e->rc):(e->data=='^')?pow(value(e->lc),value(e->rc)):e->data-'0';
}
int main()
{
    exptr e=nullptr;
    string s;
    cout<<"Enter your postfix expression"<<endl;
    cin>>s;
    express(s,e);
    inorder(e,'#');
    cout<<endl;
    cout<<"Value of Expression: "<<value(e)<<endl;
    return 0;
}
