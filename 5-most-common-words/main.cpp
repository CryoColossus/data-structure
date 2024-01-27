#include <iostream>
using namespace std;
struct Node
{
    struct Node *lc;
    string data;
    int freq;
    struct Node *rc;
};
typedef struct Node *bstptr;
void insert(bstptr &T,string s)
{
    if(!T)
    {
        T = new Node;
        T->lc = nullptr;
        T->rc = nullptr;
        T->data = s;
        T->freq = 1;
    }
    else
    {
        if(T->data>s)
        insert(T->lc,s);
        else if(T->data<s)
        insert(T->rc,s);
        else
        T->freq++;
    }
}
void populate(bstptr T,bstptr b[],int &i)
{
    if(T)
    {
        populate(T->lc,b,i);
        b[i++]=T;
        populate(T->rc,b,i);
    }
}
void swap(bstptr &a,bstptr &b)
{
    bstptr temp = a;
    a = b;
    b = temp;
}
int partition(bstptr a[],int first,int last)
{
    int x=first,y=last;
    int piv = a[y]->freq;
    while(x!=y)
    {
        while(a[x]->freq<piv&&x!=y)
        x++;
        while(a[y]->freq>=piv&&y!=x)
        y--;
        if(x<y)
        swap(a[x],a[y]);
    }    
    if(x==y)
    swap(a[last],a[x]);
    return x;
}
void quicksort(bstptr a[],int x,int y)
{
    if(x<y)
    {
        int s = partition(a,x,y);
        if(x!=s-1)
        quicksort(a,x,s-1);
        if(s+1!=y)
        quicksort(a,s+1,y);
    }    
}
int min(int a,int b)
{return (a<b)?a:b;}
int NumberNodes(bstptr T)
{return (T)?NumberNodes(T->lc)+NumberNodes(T->rc)+1:0;}
int main()
{
    int n,i,l,num=1;
    bstptr T = nullptr;
    string s;
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
        insert(T,s);
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
    int size = NumberNodes(T);
    bstptr b[size];
    i=0;
    populate(T,b,i);
    quicksort(b,0,size-1);
    cout<<"The "<<min(5,size)<<" most frequent words are:"<<endl;
    for(i=1;i<6;i++)
    cout<<b[size-i]->data<<" "<<b[size-i]->freq<<endl;
    return 0;
}
