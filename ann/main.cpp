#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
struct cryo_neuron
{
    vector<int> predecessors;
    vector<double> weights;
    double bias;
    int act_func_no;
    int number;
    cryo_neuron(vector<int> v,vector<double> d,double b,int a,int num)
    {
        predecessors = v;
        weights = d;
        bias = b;
        act_func_no = a;
        number = num;
    }
};
typedef struct cryo_neuron *cryoptr;
double activation(double arg,int num)
{
    switch(num)
    {
        case 0:
            return (1/(1+exp(-arg)));
            break;
        case -1:
            cout<<"Error: Called Activation on Input Layer"<<endl;
            break;
        default: 
            cout<<"Error: Unrecognized Activation Function Code Passed"<<endl;  
    }
    return 0;
}
double forward_pass(vector<vector<cryoptr>> network,int layer,vector<double> x,int col)
{
    if(layer==0)
        return x[col];
    else
    {
        double Z=0.0;
        cryoptr temp = network[layer][col];
        for(int i=0;i<temp->predecessors.size();i++)
        {
            double val = (double)(temp->weights[i]*forward_pass(network,layer-1,x,i));
            //cout<<"For i value of "<<i<<" and layer "<<layer<<" the value is "<<val<<" in neuron "<<temp->number<<endl;
            Z += val;
        }
        return(activation(Z+temp->bias,temp->act_func_no));
    }
}
vector<double> generate(vector<vector<cryoptr>> network,vector<double> x,int layer)
{
    vector<double> v;
    double Z;
    for(int i=0;i<network[layer].size();i++)
    {
        cryoptr temp = network[layer][i];
        Z = 0.0;
        for(int j=0;j<temp->predecessors.size();j++)
        {
            double val = (double)(temp->weights[j]*forward_pass(network,layer-1,x,j));
            //cout<<"For j value of "<<j<<" and layer "<<layer<<" the value is "<<val<<" in neuron "<<temp->number<<endl;
            Z += val;
        }    
        v.push_back(activation(Z+temp->bias,temp->act_func_no));    
    }
    return v;
}
void initialize_neural_network(vector<vector<cryoptr>> &network)
{
    vector<int> i;
    vector<double> d;
    vector<cryoptr> v;
    cryoptr temp = new cryo_neuron(i,d,0.0,-1,0);
    v.push_back(temp);
    temp = new cryo_neuron(i,d,0.0,-1,1);
    v.push_back(temp);
    network.push_back(v);
    v.clear();
    temp = new cryo_neuron({0,1},{1.0,1.0},0.0,0,2);
    v.push_back(temp);
    temp = new cryo_neuron({0},{1.0},0.0,0,3);
    v.push_back(temp);
    temp = new cryo_neuron({1},{1.0},0.0,0,4);
    v.push_back(temp);
    network.push_back(v);
    v.clear();
    temp = new cryo_neuron({0,1,2},{1.0,1.0,1.0},0.0,0,5);
    v.push_back(temp);
    network.push_back(v);
}
double Error(vector<vector<cryoptr>> network)
{
    double e=0.0,n=0.0;
    fstream t_sets;
    t_sets.open("testdata.txt",ios::in);
    if(t_sets.is_open())
    {
        string s;
        vector<double> v;
        while(getline(t_sets,s))
        {
            v.clear();
            string word="";
            for(auto x:s) 
            {
                if(x==' ')
                {
                    v.push_back(stoi(word));
                    word="";
                }
                else
                    word=word+x;
            }
            vector<double> temp = generate(network,v,network.size()-1);
            e += pow(stoi(word)-(20*temp[0]),2);
            n++;
        }
    }
    t_sets.close();
    return (double) e/n;
}
int main()
{
    vector<vector<cryoptr>> network;
    initialize_neural_network(network);
    cout<<"Cost Value is: "<<Error(network)<<endl;
    vector<double> ans = generate(network,{5.0,5.0},network.size()-1);
    cout<<endl;
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<endl;
    return 0;
}