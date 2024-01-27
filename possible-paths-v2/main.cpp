#include <iostream>
#include <vector>
using namespace std;
int FindWays(int n, int m, vector<vector<int>>blocked_cells)
	{
	    int a[n+1][m+1],i,j,mod=(int)1e9+7;
	    for(i=0;i<n+1;i++)
	        for(j=0;j<m+1;j++)
	            a[i][j]=-1;
	    for(i=0;i<blocked_cells.size();i++)
	        a[blocked_cells[i][0]-1][blocked_cells[i][1]-1] = 0;
	    for(i=0;i<=n+1;i++)
	        a[i][m]=0;
	    for(i=0;i<=m+1;i++)
	        a[n][i]=0;
        if(a[n-1][m-1]==-1)
            a[n-1][m-1]=1;
        for(i=n-1;i>=0;i--)
        {
            for(j=m-1;j>=0;j--)
            {
                if(a[i][j]==-1)
                    a[i][j] = (a[i+1][j] + a[i][j+1])%mod;
                else if(a[i][j]==0)
                    continue;
                else if(i!=n-1&&j!=m-1)
                    cout<<"CRITICAL ERROR!!!"<<endl;
            }   
        } 
        // for(i=0;i<n+1;i++)
        // {
	       // for(j=0;j<m+1;j++)
	       //     cout<<a[i][j]<<" ";
	       // cout<<endl; 
        // }         
        return a[0][0];
	}
int main()
{
    int n,m,b,i;
    cout<<"Enter Row and Column Size of Array"<<endl;
    cin>>n>>m;
    cout<<"Enter Number of Blockades"<<endl;
    cin>>b;
    vector<vector<int>> v(b,vector<int>(2));
    for(i=0;i<b;i++)
        cin>>v[i][0]>>v[i][1];
    cout<<FindWays(n,m,v)<<endl;                        
    return 0;
}