#include <iostream>
#include <limits.h>
using namespace std;
int max_cost(int a[],int n,int threshold)
{
    int rem = n%threshold,i,g_pos;
    int groups = (n/threshold) + ((rem==0)?0:1);
    int dp[groups];
    for(i=0;i<groups;i++)
    dp[i]=0;
    int j=0,k,l_min=0,g_min=INT_MIN;
    for(i=0;i<groups;i++)
    {
        if(i==groups-1&&rem!=0)
        {
            for(k=j;k<j+rem;k++)
            {
                if(a[k]>dp[i])
                dp[i] = a[k];
            }
        }
        else
        {
            for(k=j;k<j+threshold;k++)
            {
                if(a[k]>dp[i])
                dp[i] = a[k];
            }
        }
        j += threshold;
    }
    for(i=0;i<groups;i++)
    l_min += dp[i];
    if(l_min>g_min)
    g_min = l_min,g_pos=groups-1;
    int pos = n-(threshold+rem);
    if(rem!=0)
    {
        for(i=groups-2;i>=0;i--)
        {
            dp[i]=0,dp[i+1]=0;
            for(j=pos;j<pos+rem;j++)
            {
                if(a[j]>dp[i])
                dp[i] = a[j];
            }
            for(j=pos+rem;j<pos+rem+threshold;j++)
            {
                if(a[j]>dp[i+1])
                dp[i+1] = a[j];
            }
            l_min=0;
            for(k=0;k<groups;k++)
            l_min += dp[k];
            if(l_min<g_min)
            g_min = l_min,g_pos=i;
            pos -=threshold;
        }
    }    
    j=0;
    for(i=0;i<groups;i++)
    {
        int x=j;
        if(g_pos!=0||rem==0)
        {
            cout<<"( ";
            while(j<x+threshold)
            cout<<a[j++]<<" ";
            cout<<")";
        }
        else
        {
            cout<<"( ";
            while(j<x+rem)
            cout<<a[j++]<<" ";
            cout<<")";
        }
        g_pos--;
    }
    cout<<endl;
    return g_min;
}
int main()
{
    int n,i,threshold;
    cin>>n;
    int a[n];
    for(i=0;i<n;i++)
    cin>>a[i];
    cin>>threshold;
    int cost = max_cost(a,n,threshold);
    cout<<cost;
    return 0;
}