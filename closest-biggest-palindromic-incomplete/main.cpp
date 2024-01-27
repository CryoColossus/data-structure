#include <iostream>
using namespace std;
void improvise(string &str,int n)
{
    while(str[n]=='9'&&n>=0)
    str[n--]='0';
    if(n<0)
    {
        str = "1"+str;
    }    
    else
    str[n]++;
}
void inc(string &str,int n)
{
    if(str[n]!='9')
    str[n]++;
    else
    str[n]='0';
}
int main()
{
	int t,iter;
    string str;
    cin>>t;
    for(iter=0;iter<t;iter++)
    {
	    cin>>str;
	    int n = str.length(),i,j,flag=0,check=0,flag2=0;
	    for(i=0;i<n;i++)
	    {
	        if(str[i]!='9')
	        {
	            check=1;
	            break;
	        }
	    }
	    if(check==0)
	    {
	        for(i=0;i<=n;i++)
	        {
	            if(i==0||i==n)
	            cout<<"1";
	            else
	            cout<<"0";
	        }
	    }
	    else
	    {
    	    improvise(str,n-1);
    	    if(n%2==0)
    	    {
    	        n-=1;
    	        for(i=n/2,j=(n/2)+1;i>=0;i--,j++)
    	        {
    	            if(str[i]==str[j])
    	            {
    	                flag2=1;
    	                continue;
    	            }     
    	            else
    	            {
    	                if(str[i]>str[j])
    	                str[j]=str[i];
    	                else if(flag==0&&flag2==0)
    	                {
    	                    str[j]=++str[i];
    	                }     
    	                else if(flag2==1)
    	                {
    	                    str[j]=str[i];
    	                    inc(str,(n/2)+1);
    	                }
    	                else
    	                {
    	                    str[j]=str[i];
    	                }     
    	                flag=1;
    	            }
    	        }
    	    }
    	    else
    	    {
    	        n-=1;
    	        for(i=(n/2)-1,j=(n/2)+1;i>=0;i--,j++)
    	        {
    	            if(str[i]>str[j])
    	            str[j]=str[i];
    	            else if(flag==0)
    	            {
    	                if(str[n/2]!='9')
    	                str[n/2]++;
    	                else
    	                improvise(str,n/2);
    	                str[j]=str[i];
    	            }
    	            else
    	            str[j]=str[i];
    	            flag=1;
    	        }
    	    }
    	    for(i=0;i<=n;i++)
        	cout<<str[i];
        	cout<<endl;
	    }	
    }    
    return 0;
}

