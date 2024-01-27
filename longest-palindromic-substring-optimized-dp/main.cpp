#include <iostream>
using namespace std;
string check(string S,int** a,int x)
{
    int i,j,t,flag=0;
    for(i=0;i<x;i++)
    a[i][i]=1;
    for(i=0;i<x-1;i++)
    a[i][i+1] = (S[i]==S[i+1])?1:0;
    for(i=2;i<x;i++)
    {
        for(j=0;i+j<x;j++)
        a[j][j+i] = (a[j+1][j+i-1]==1&&S[j]==S[j+i])?1:0;
    }
    for(i=x-1;i>=0;i--)
    {
        for(j=0;j+i<x;j++)
        {
            if(a[j][j+i]==1)
            {
                flag=1;
                break;
            }    
        }
        if(flag==1)
        break;
    }
    string str = "";
    for(t=j;t<=j+i;t++)
    str = str + S[t];
    return str;
}
string longestPalindrome(string S)
{
    int x = S.length();
    int** a = new int*[x];
    for(int i=0;i<x;i++)
    a[i] = new int[x];
    string str = check(S,a,x);
    return str;
}
int main()
{
    string str;
    cout<<"Enter String"<<endl;
    cin>>str;
    cout<<endl;
    string ans = longestPalindrome(str);
    cout<<ans<<endl;
    return 0;
}