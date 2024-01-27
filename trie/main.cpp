#include <iostream>
#include <string>
using namespace std;
struct trie
{
    struct trie *c[26];
    bool end_of_word;
};
typedef struct trie *triptr;
struct iqueue
{
    int s;
    int e;
    char a[50];
    int max;
};
void enqueue(struct iqueue &q,char n)
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
char dequeue(struct iqueue &q)
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
void insert(triptr &T,string s,int x=0)
{
    if(!T)
    {
        T = new trie;
        for(int i=0;i<26;i++)
        T->c[i] = nullptr;
        T->end_of_word = false;
    }
    if(x<s.length())
    insert(T->c[s[x]-'a'],s,x+1);
    else
    T->end_of_word=true;
}
void print(triptr T,iqueue q)
{
    if(T)
    {
        if(T->end_of_word)
        {
            enqueue(q,'0');
            while(!is_Empty(q))
            {
                char c = dequeue(q);
                if(c=='0')
                break;
                cout<<c;
                enqueue(q,c);
            }    
            cout<<endl;
        }    
        for(int i=0;i<26;i++)
        {
            if(T->c[i])
            {
                char c = i+'a';
                enqueue(q,c);
                print(T->c[i],q);
                dequeue(q);
            }    
        }
    }
}
int main()
{
    triptr T = nullptr;
    string s;
    iqueue q;
    q.max=50;
    q.s=-1;
    q.e=-1;
    cout<<"Enter All The Words"<<endl;
    cin>>s;
    while(s!="/0")
    {
        insert(T,s);
        cin>>s;
    }
    cout<<"The Words are: "<<endl;
    print(T,q);
}
