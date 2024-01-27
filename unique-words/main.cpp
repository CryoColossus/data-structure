#include <iostream>
using namespace std;
struct Node
{
    struct Node *lc;
    string data;
    int list;
    struct Node *rc;
};
typedef struct Node *bstptr;
void insert(bstptr &T,string s,int x)
{
    if(!T)
    {
        T = new Node;
        T->lc = nullptr;
        T->rc = nullptr;
        T->data = s;
        T->list = x;
    }
    else
    {
        if(s<T->data)
        insert(T->lc,s,x);
        else if(s>T->data)
        insert(T->rc,s,x);
        else if(T->list!=x)
        T->list = -1;
    }
}
void printer(bstptr T,bool &pri)
{
    if(T)
    {
        printer(T->lc,pri);
        if(T->list!=-1)
        {
            cout<<T->data<<endl;
            pri=true;
        }    
        printer(T->rc,pri);
    }
}
int main()
{
    int m,n,i,l,num;
    string s;
    bool pri=false;
    bstptr T=nullptr;
    for(i=1;i<=2;i++)
    {
        num=1;
        cout<<"Enter Strings of List "<<i<<" :"<<endl;
        cin>>s;
        if(s[0]>='A'&&s[0]<='Z')
        s[0]+=32;
        l = s.length();
        while(num==1)
        {
            num=0;
            if((s[l-1]>='!'&&s[l-1]<='/')||(s[l-1]>=':'&&s[l-1]<='@'))
            {
                s = s.substr(0,l-1);
                num=1;
                l--;
            }    
            if((s[0]>='!'&&s[0]<='/')||(s[0]>=':'&&s[0]<='@'))
            {
                s = s.substr(1,l-1);
                num=1;
                l--;
            }
        }
        while(s!="/0")
        {
            num=1;
            insert(T,s,i);
            cin>>s;
            if(s=="/0")
            break;
            l = s.length();
            while(num==1)
            {
                num=0;
                if((s[l-1]>='!'&&s[l-1]<='/')||(s[l-1]>=':'&&s[l-1]<='@'))
                {
                    s = s.substr(0,l-1);
                    num=1;
                    l--;
                }    
                if((s[0]>='!'&&s[0]<='/')||(s[0]>=':'&&s[0]<='@'))
                {
                    s = s.substr(1,l-1);
                    num=1;
                    l--;
                }    
            }    
            if(s[0]>='A'&&s[0]<='Z')
            s[0]+=32;
        }
    }
    cout<<endl;
    cout<<"Required List of Strings is: "<<endl;
    printer(T,pri);
    if(!pri)
    cout<<"No Strings!"<<endl;
    return 0;
}
