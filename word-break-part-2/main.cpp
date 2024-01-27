#include <vector>
#include <iostream>
using namespace std;
struct trie
{
    struct trie *child[26];
    bool eow;
    trie()
    {
        for(int i=0;i<26;i++)
            this->child[i] = nullptr;
        this->eow = false;
    }
};
typedef struct trie *triptr;
void trie_insert(triptr &T,string s)
{
    if(!T)
        T = new trie();
    if(s=="")
    {
        T->eow = true;
        return;
    }    
    trie_insert(T->child[s[0]-'a'],s.substr(1));
}
void recurseFill(triptr S,triptr T,string s,vector<string> &ans,string curr="")
{
    if(!T)
        return;
    if(s=="")
    {
        ans.push_back(curr);
        return;
    }
    recurseFill(S,T->child[s[0]-'a'],s.substr(1),ans,curr+s[0]);
    if(T->eow)
        recurseFill(S,S,s,ans,curr+" ");
}
void print(triptr T,string s="")
{
    if(T->eow)
        cout<<s<<endl;
    for(int i=0;i<26;i++)
        if(T->child[i])
            print(T->child[i],s+char('a'+i));
}
vector<string> wordBreak(int n, vector<string>& dict, string s)
{
    triptr T = nullptr;
    for(int i=0;i<dict.size();i++)
        trie_insert(T,dict[i]);
    //print(T);    
    vector<string> ans;
    recurseFill(T,T,s,ans);
    return ans;
}
int main()
{
    string s = "catsanddog";
    vector<string> v = {"cats","cat","and","sand","dog"};
    vector<string> ans = wordBreak(5,v,s);
    int temp = 99;
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<endl;
    return 0;
}
