#include <iostream>
using namespace std;
void palindrome(char c[],int n,int &s,int &e)
{
    int i,x,y;
    for(i=1;i<n-1;i++)
    {
        x=i;
        y=i;
        while(c[x]==c[y]&&x>=0&&y<n)
        {
            if(e-s<y-x)
            {
                e=y;
                s=x;
            }
            x--;
            y++;
        }
    }
    for(i=0;i<n-1;i++)
    {
        if(c[i]==c[i+1])
        {
            x=i;
            y=i+1;
            while(c[x]==c[y]&&x>=0&&y<n)
            {
                if(e-s<y-x)
                e=y,s=x;
                x--;
                y++;
            }
        }
    }
}
int main()
{
    int n,i,j,s=1,e=1;
    cout<<"Enter Array Size: "<<endl;
    cin>>n;
    if(n>0)
    {
        char c[n];
        cout<<"Enter Array Elements: "<<endl;
        for(i=0;i<n;i++)
        cin>>c[i];
        cout<<"Longest Palindromic Substring: "<<endl;
        palindrome(c,n,s,e);
        for(i=s;i<=e;i++)
        cout<<c[i];
        cout<<endl;
    }    
    return 0;
}
