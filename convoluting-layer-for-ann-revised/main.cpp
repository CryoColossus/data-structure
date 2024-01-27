#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <chrono>
#include <random>
using namespace std;
unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); 
default_random_engine e (seed);
double noise()
{
    normal_distribution<double> d(0,0.25);
    while(1)
    {
        double particle = d(e);
        if(particle>=-1.0&&particle<=1.0)
            return particle;
    }        
}
double sigmoid(double Z)
{
    return 1/(1+exp(-Z));
}
double dot(vector<double> a,vector<double> b)
{
    double ans=0.0;
    for(int i=0;i<a.size();i++)
        ans += a[i]*b[i];
    return (5*sigmoid(ans));    
}
vector<double> convolution(vector<double> inp)
{
    vector<vector<double>> filter = {{0.35,0.15,-0.25},{0.3,0.25,-0.15}};
    vector<double> out;
    for(int i=0;i<filter.size();i++)
        out.push_back(dot(inp,filter[i]));
    return out;    
}
int main()
{
    double a,b,c;
    srand(time(NULL));
    while(1)
    {
        cout<<"Enter Input: ";
        cin>>a>>b>>c;
        vector<double> inp;
        inp.push_back(a);
        inp.push_back(b);
        inp.push_back(c);
        inp = convolution(inp);
        cout<<"Convoluted Output is: "<<endl;
        for(int i=0;i<inp.size();i++)
            cout<<((inp[i]-2.5)*2)+noise()<<" ";
        cout<<endl;    
    }    
    return 0;
}
