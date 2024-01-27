#include <iostream>
#include <stack>
using namespace std;
int max(int a,int b,int c)
{return (a>=b&&a>=c)?a:((b>=c)?b:c);}
void dynamic_fill(int ***a,string s1,string s2,string s3,int m,int n,int o)
{
    for(int i=0;i<m+1;i++)
        for(int j=0;j<n+1;j++)
            for(int k=0;k<o+1;k++)
                if(i==0||j==0||k==0)
                    a[i][j][k]=0;
                else if(s1[i-1]==s2[j-1]&&s1[i-1]==s3[k-1])
                    a[i][j][k]=a[i-1][j-1][k-1]+1;
                else
                    a[i][j][k] = max(a[i-1][j][k],a[i][j-1][k],a[i][j][k-1]);
}
void subsequence(int ***a,int x,int y,int z,string s1,string s2,string s3,stack<char> &s)
{
    int i=x,j=y,k=z;
    while(i!=0&&j!=0&&k!=0)
    {
        if(s1[i-1]==s2[j-1]&&s1[i-1]==s3[k-1])
        {
            s.push(s1[i-1]);
            i--,j--,k--;
        }    
        else if(a[i][j][k]==a[i-1][j][k])
            i--;
        else if(a[i][j][k]==a[i][j-1][k])
            j--;
        else if(a[i][j][k]==a[i][j][k-1])
            k--;    
    }
}
int lcs(string s1,string s2,string s3,int m,int n,int o,stack<char> &s)
{
    int i,j,k;
    int ***a = new int**[m+1];
    for(i=0;i<m+1;i++)
        a[i] = new int*[n+1];
    for(i=0;i<m+1;i++)
        for(j=0;j<n+1;j++)
            a[i][j] = new int[o+1];
    dynamic_fill(a,s1,s2,s3,m,n,o);
    subsequence(a,m,n,o,s1,s2,s3,s);
    return a[m][n][o];
}
void printer(stack<char> s)
{
    while(!s.empty())
    {
        cout<<s.top();
        s.pop();
    }    
}
int main()
{
    stack<char> s;
    string str1,str2,str3;
    cout<<"Enter First String"<<endl;
    cin>>str1;
    cout<<"Enter Second String"<<endl;
    cin>>str2;
    cout<<"Enter Third String"<<endl;
    cin>>str3;
    int x = lcs(str1,str2,str3,str1.length(),str2.length(),str3.length(),s);
    cout<<"Length of LCS is: "<<x<<endl;
    cout<<"The LCS is: ";
    printer(s);
    cout<<endl;
    return 0;
}
