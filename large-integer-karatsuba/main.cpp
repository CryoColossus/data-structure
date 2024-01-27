#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
void Adder(int a[],int b[],int length,int ans[])
{
    int i,carry=0;
    for(i=length-1;i>=0;i--)
    {
        ans[i+1] = ans[i+1]+a[i]+carry;
        carry = ans[i+1]/10;        
        if(ans[i+1]>9)
        ans[i+1]%=10;
    }
    carry=0;
    for(i=length-1;i>=0;i--)
    {
        ans[i+1] = ans[i+1]+b[i]+carry;
        carry = ans[i+1]/10;        
        if(ans[i+1]>9)
        ans[i+1]%=10;
    }
    if(carry!=0)
    {
        ans[0]+=carry;
        carry=0;
    }
}
void Subtract(int a[],int b[],int n,int m)
{
    int i,j,ch;
    for(i=n-1,j=m-1;i>=0;i--,j--)
    {
        if(a[j]<b[i])
        {
            ch=j-1;
            a[j]+=10;
            while(a[ch]==0)
            {
                a[ch]=9;
                ch--;
            }
            a[ch]--;
        }
        a[j]-=b[i];
    }
}
void karatsuba(int a[],int b[],int length,int ans[])
{
    int p=0,i,reducer=0,ans_length = 2*length,temp = length;
    for(i=0;i<ans_length;i++)
    ans[i]=0;
    for(i=0;i<length;i++)
    {
        if(a[i]!=0||b[i]!=0)
        break;
        else
        {
            reducer++;
            temp--;
        }
    }
    length = temp;
    if(length==0)
    return;
    int m[length],n[length],d = length/2,maxl;
    for(i=0;i<length;i++)
    {
        m[i] = a[i+reducer];
        n[i] = b[i+reducer];
    }
    if(length==1)
    {
        int num = m[0]*n[0];
        int dig = num%10;
        num/=10;
        ans[ans_length-1] = dig;
        ans[ans_length-2] = num;
        return;
    }
    int xh[length-d],xl[length-d],yh[length-d],yl[length-d];
    maxl = length-d;
    xh[0]=0;
    yh[0]=0;
    for(i=0;i<((length%2==0)?maxl:d);i++)
    {
        xh[i+(length%2)] = m[i];
        yh[i+(length%2)] = n[i];
    }
    for(i=0;i<maxl;i++)
    {
        xl[i] = m[d+i];
        yl[i] = n[d+i];
    }
    int a1[2*maxl],b1[2*maxl],s[2*(maxl+1)],carry=0;
    karatsuba(xh,yh,maxl,a1);
    karatsuba(xl,yl,maxl,b1);
    int t1[maxl+1],t2[maxl+1];
    for(i=0;i<maxl+1;i++)
    t1[i]=0,t2[i]=0;
    Adder(xh,xl,maxl,t1);
    Adder(yh,yl,maxl,t2);
    karatsuba(t1,t2,maxl+1,s);
    Subtract(s,a1,2*maxl,2*(maxl+1));
    Subtract(s,b1,2*maxl,2*(maxl+1));
    int sp = (length%2==0)?length:length+1,siter=2*maxl-1;
    for(i=ans_length-1;i>=0;i--)
    {
        if(siter<0)
        break;
        if(sp>0)
        {
            sp--;
            continue;
        }
        else
        {
            ans[i]+=a1[siter]+carry;
            carry=ans[i]/10;
            if(ans[i]>9)
            ans[i]%=10;
            siter--;
        }
    }
    if(carry!=0&&i>=0)
    ans[i]+=carry;
    sp = (length%2==0)?length/2:(length/2)+1,siter=(2*(maxl+1))-1,carry=0;
    for(i=ans_length-1;i>=0;i--)
    {
        if(siter<0)
        break;
        if(sp>0)
        {
            sp--;
            continue;
        }
        else
        {
            ans[i]+=s[siter]+carry;
            carry=ans[i]/10;
            if(ans[i]>9)
            ans[i]%=10;
            siter--;
        }
    }
    if(carry!=0&&i>=0)
    ans[i]+=carry;
    sp=0;
    siter=2*maxl-1;
    carry=0;
    for(i=ans_length-1;i>=0;i--)
    {
        if(siter<0)
        break;
        ans[i]+=b1[siter]+carry;
        carry=ans[i]/10;
        if(ans[i]>9)
        ans[i]%=10;
        siter--;
    }
    if(carry!=0&&i>=0)
    ans[i]+=carry;
}
void printer(int a[],int length,bool neg)
{
    int i=0;
    cout<<"Multiplied Number:"<<endl;
    while(a[i]==0&&i<length)
    i++;
    if(i==length)
    cout<<'0';
    else
    {
        if(neg)
        cout<<"-";
        while(i!=length)
        cout<<a[i++];
    }    
    cout<<endl;
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
    while(m<n)
    {
        s1 = '0'+s1;
        m++;
    }
    while(n<m)
    {
        s2 = '0'+s2;
        n++;
    }
    int a[m],b[n],ans[m+n],i;
    for(i=0;i<m;i++)
    a[i]=s1.at(i)-'0';
    for(i=0;i<n;i++)
    b[i]=s2.at(i)-'0';
    karatsuba(a,b,n,ans);
    printer(ans,m+n,negative);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}