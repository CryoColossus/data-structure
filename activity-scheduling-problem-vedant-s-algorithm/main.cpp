#include <iostream>
#include <vector>
using namespace std;
void swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
int maxval(int a[],int n)
{
    int ans=a[0];
    for(int i=0;i<n;i++)
        if(ans<a[i])
            ans=a[i];
    return ans; 
}
bool validate(int x,int y,int cal[],int s)
{
    for(int i=x;i<=y;i++)
        if(cal[i-s]==1)
            return false;
    return true;        
}
void bubble_sort(vector<int> &v,vector<int> &l)
{
    for(int i=0;i<l.size()-1;i++)     
        for(int j=0;j<l.size()-i-1;j++) 
            if(l[j]>l[j+1]) 
                swap(l[j],l[j+1]),swap(v[j],v[j+1]); 
}
bool clash(int w,int x,int y,int z)
{
    if(x<y||z<w)
        return false;
    return true;    
}
int main()
{
    int jobs,s,e,i,j,ans=0;
    vector<int> v;
    cout<<"Enter Number of Jobs"<<endl;
    cin>>jobs;
    cout<<"Enter Start and End dates"<<endl;
    cin>>s>>e;
    int data[jobs][2],clashes[jobs]={};
    cout<<"Enter Start and End day for every job"<<endl;
    for(i=0;i<jobs;i++)
        for(j=0;j<2;j++)
            cin>>data[i][j];
    for(i=0;i<jobs;i++)
        for(j=0;j<jobs;j++)
            if(i!=j&&clash(data[i][0],data[i][1],data[j][0],data[j][1]))
                clashes[i]++;
    for(i=0;i<jobs;i++)
        cout<<clashes[i]<<" ";
    cout<<endl;    
    int cal[e-s+1]={0};
    int m = maxval(clashes,jobs);
    for(i=0;i<=m;i++)
    {
        v.clear();
        for(j=0;j<jobs;j++)
            if(clashes[j]==i&&validate(data[j][0],data[j][1],cal,s))
                v.push_back(j);
        vector<int> l;        
        for(j=0;j<v.size();j++)
            l.push_back(data[v[j]][1]-data[v[j]][0]+1);
        if(!v.empty())    
            bubble_sort(v,l);
        for(j=0;j<v.size();j++)
        {
            if(validate(data[v[j]][0],data[v[j]][1],cal,s))
            {
                ans++;
                for(int k=data[v[j]][0];k<=data[v[j]][1];k++)
                    cal[k-s]=1;
            }
        }
    }
    cout<<"Maximum Jobs possible are: "<<ans<<endl;
    return 0;    
}