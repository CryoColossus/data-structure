#include <iostream>
#include <limits.h>
#include <stack>
using namespace std;
int Area(int a[],int n)
{
    stack<int> s;
    int curr,max=INT_MIN,i;
    for(i=0;i<n;i++)
    {
        if(s.empty()||a[s.top()]<=a[i])
        s.push(i);
        else
        {
            while(!s.empty()&&a[s.top()]>a[i])
            {
                int temp = s.top();
                s.pop();
                curr = a[temp]*((s.empty())?i:i-s.top()-1);
                if(curr>max)
                max = curr;
            }
            s.push(i);
        }
    }
    while(!s.empty())
    {
        int temp = s.top();
        s.pop();
        curr = a[temp]*((s.empty())?i:i-s.top()-1);
        if(curr>max)
        max = curr;
    }
    return max;
}
int main()
{
    int n,i;
    cout<<"Enter number of Bars"<<endl;
    cin>>n;
    int a[n];
    for(i=0;i<n;i++)
        cin>>a[i];
    cout<<"The Largest Rectangular Area under the Histogram is:"<<endl;
    cout<<Area(a,n)<<endl;
}