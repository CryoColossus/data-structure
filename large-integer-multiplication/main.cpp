#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
void Adder(int a[],int b[],int n)
{
    int i,carry=0;
    for(i=n-1;i>=0;i--)
    {
        a[i] = a[i]+b[i]+carry;
        carry = a[i]/10;        
        if(a[i]>9)
        a[i]%=10;
    }
}
void printer(int a[],int n,int neg)
{
    int m=0;
    while(a[m]==0&&m<n)
    m++;
    cout<<"Multiplied Number: "<<endl;
    if(m==n)
    cout<<0;
    else
    {
        if(neg)
        cout<<"-";
        for(int i=m;i<n;i++)
        cout<<a[i];
    }    
    cout<<endl;
}
void multiply(string s1,string s2,int m,int n,bool negative)
{
    int a[m],b[n],i,temp[m+n],ans[m+n],j,mul,iter=m+n-1,digit,carry;
    for(i=0;i<m;i++)
    a[i] = (s1.at(i)-48);
    for(i=0;i<n;i++)
    b[i] = (s2.at(i)-48);
    for(i=0;i<m+n;i++)
    ans[i]=0;
    for(i=n-1;i>=0;i--)
    {
        carry=0;
        iter = m+n-1-((n-1)-i);
        for(j=0;j<m+n;j++)
        temp[j]=0;
        for(j=m-1;j>=0;j--)
        {
            mul = b[i]*a[j]+carry;
            digit = mul%10;
            temp[iter] = digit;
            carry = mul/10;
            iter--;
        }
        while(carry!=0)
        {
            temp[iter] = carry;
            carry/=10;
            iter--;
        }    
        Adder(ans,temp,m+n);
    }
    printer(ans,m+n,negative);
}
int main()
{
    clock_t start,end;
    start = clock();
    string s1,s2;
    bool negative=false;
    cout<<"Enter First Number"<<endl;
    cin>>s1;
    cout<<"Enter Second Number"<<endl;
    cin>>s2;
    if((s1.at(0)=='-'||s2.at(0)=='-')&&(s1.at(0)!='-'||s2.at(0)!='-'))
    negative=true;
    if(s1.at(0)=='-')
    s1 = s1.substr(1);
    if(s2.at(0)=='-')
    s2 = s2.substr(1);
    int m = s1.length();
    int n = s2.length();
    multiply(s1,s2,m,n,negative);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution Time is : " << fixed << time_taken << setprecision(10);
    cout << " sec " << endl;
    return 0;
}

