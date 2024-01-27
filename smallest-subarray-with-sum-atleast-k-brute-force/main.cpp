#include <iostream>
using namespace std;
int diff(int coins[],int x,int y)
{
    int sum=0;
    if(x<y)
    return 0;
    for(int i=y;i<=x;i++)
    sum += coins[i];
    return sum;
}
int min_house(int coins[],int n,int target)
{
    if(n<=0)
    return -1;
    int dp[n][n],i,j,k;
    for(i=0;i<n;i++)
    dp[i][i] = coins[i];
    for(i=1;i<n;i++)
    {
        for(j=0,k=i;k<n;j++,k++)
        dp[j][k] = dp[j][k-1]+dp[j+1][k]-diff(coins,k-1,j+1);
    }
    for(i=1;i<n;i++)
    {
        for(j=0,k=i;k<n;j++,k++)
        {
            if(dp[j][k]>=target)
            return i+1;
        }
    }
    return -1;
}
int main()
{
    int n,target,ans=0;
    cin>>n;
    int coins[n];
    for(int i=0;i<n;i++)
    cin>>coins[i];
    cin>>target;
    ans = min_house(coins,n,target);
    cout<<ans<<endl;
    return 0;
}