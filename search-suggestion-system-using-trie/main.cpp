#include<iostream>
#include <vector>
using namespace std;
struct trie
{
    struct trie *child[26];
    bool eow;
    trie()
    {
        for(int i=0;i<26;i++)
            child[i] = nullptr;
        eow = false;
    }
};    
typedef struct trie *triptr;
void insert(triptr &root, string s)
{
    if(!root)
        root = new trie();
    if(s=="")
    {
        root->eow = true;
        return;
    }
    insert(root->child[s[0]-'a'],s.substr(1));
}
void trie_print(triptr root,string load,vector<vector<string>> &ans,vector<string> &payload)
{
    if(root&&root->eow&&payload.size()<3)
        payload.push_back(load);
    if(payload.size()==3)
    {
        ans.push_back(payload);
        return;
    }    
    for(int i=0;i<26;i++)
        if(root&&root->child[i]&&payload.size()<3)
            trie_print(root->child[i],load+char(i+'a'),ans,payload);
}
void populate(triptr root,vector<vector<string>> &ans,string SearchWord,string temp)
{
    if(root)
    {
        vector<string> payload;
        trie_print(root,temp,ans,payload);
        if(payload.size()<3)
            ans.push_back(payload);
        if(SearchWord=="")
           return;
        populate(root->child[SearchWord[0]-'a'],ans,SearchWord.substr(1),temp+SearchWord[0]);
    } 
    else
    {
        for(int i=0;i<SearchWord.length();i++)
            ans.push_back({});
    }
}
vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) 
{
    triptr root=nullptr;
    vector<vector<string>> ans;
    for(int i=0;i<products.size();i++)
        insert(root,products[i]);
    populate(root->child[searchWord[0]-'a'],ans,searchWord.substr(1),searchWord.substr(0,1));
    for(int i=0;i<ans.size();i++)
    {
        for(int j=0;j<ans[i].size();j++)
            cout<<ans[i].at(j)<<" ";
        cout<<endl;    
    }
    return ans;
}
int main()
{
    vector<string> products = {"havana"};
    string search = "bags";
    vector<vector<string>> a = suggestedProducts(products,search);
    return 0;
}