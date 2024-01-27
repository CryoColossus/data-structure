#include <iostream>
using namespace std;
void str_add(string &s,string x,string y)
{
    s="";
    while(x.length()<y.length())
        x = '0'+x;
    while(y.length()<x.length())
        y = '0'+y;
    int carry=0;    
    for(int i=x.length()-1;i>=0;i--)
    {
        int t = (x[i]-'0')+(y[i]-'0')+carry;
        carry = t/10;
        t=t%10;
        s = (char)(t+'0')+s;
    }
    if(carry!=0)
        s = (char)(carry+'0')+s;
}
string paths(int m,int n)
{
    int i,j;
    string result;
    string *dp = new string[n];
    dp[0]={"1"};
    for(i=0;i<m;i++)
        for(j=1;j<n;j++)
            str_add(dp[j],dp[j],dp[j-1]);
    result=dp[n-1];
    delete[] dp;
    return result;        
}    
int main()
{
    int m,n;
    cin>>m>>n;
    cout<<"Total Possible Paths: "<<paths(m,n)<<endl;
    return 0;
}
