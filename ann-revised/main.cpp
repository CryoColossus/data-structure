#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <chrono>
#include <random>
using namespace std;
struct CryoNeuron
{
    double a;
    double error;
};
struct CryoNetwork
{
    vector<vector<CryoNeuron>> Nodes;
    vector<vector<vector<double>>> network;
    vector<vector<vector<double>>> gradient;
    double alpha;
};
double Sigmoid(double Z)
{
    return (double)(1/(1+exp(-Z)));
}
double ReLU(double Z)
{
    return max(0.0,Z);
}
double TanH(double Z)
{
    return tanh(Z);
}
double forward_pass(CryoNetwork &model,vector<double> x,int layer,int col)
{
    double Z=0.0,A=0.0;
    if(layer==-1)
    {
        model.Nodes[0][col].a = x[col];
        return x[col];
    }
    if(model.Nodes[layer+1][col].a!=0.0)
        return model.Nodes[layer+1][col].a;
    vector<double> temp = model.network[layer][col];
    for(int j=0;j<temp.size();j++)
    {
        if(temp[j]!=0)
        {
            A = (double)(temp[j]*forward_pass(model,x,layer-1,j));
            Z += A;
        }    
    }
    model.Nodes[layer+1][col].a = ((Z!=0.0)?Sigmoid(Z):1.0);
    return ((Z!=0.0)?Sigmoid(Z):1.0);        
}
vector<double> generate(CryoNetwork &model,vector<double> x,int layer)
{
    vector<vector<double>> temp = model.network[layer];
    vector<double> ans;
    double Z,A;
    for(int i=0;i<temp.size();i++)
    {
        Z=0.0,A=0.0;
        for(int j=0;j<temp[i].size();j++)
        {
            if(temp[i][j]!=0)
            {
                A = (double)(temp[i][j]*forward_pass(model,x,layer-1,j));
                Z += A;
            }    
        }    
        model.Nodes[layer+1][i].a = ((Z!=0)?Sigmoid(Z):1.0);
        ans.push_back(((Z!=0.0)?Sigmoid(Z):1.0));
    }
    return ans;
}
void initialize_neural_network(CryoNetwork &model,double alpha)
{
    int i,j,k;
    model.alpha = alpha;
    model.network.push_back({{0.0,0.0,0.0},{1.0,1.0,1.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{1.0,1.0,1.0}});
    model.network.push_back({{0.0,0.0,0.0,0.0,0.0},{1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0}});
    model.network.push_back({{1.0,1.0,1.0,1.0,1.0}});
    model.Nodes.push_back(vector<CryoNeuron>(model.network[0][0].size()));
    for(i=0;i<model.network.size();i++)
        model.Nodes.push_back(vector<CryoNeuron>(model.network[i].size()));
    model.gradient = model.network;
    for(i=0;i<model.gradient.size();i++)
        for(j=0;j<model.gradient[i].size();j++)
            for(k=0;k<model.gradient[i][j].size();k++)
                model.gradient[i][j][k]=0.0;
}
void clear_a(auto &Nodes)
{
    for(int i=0;i<Nodes.size();i++)
        for(int j=0;j<Nodes[i].size();j++)
            Nodes[i][j].a=0.0,Nodes[i][j].error=0.0;
}
double RMS_Error(CryoNetwork model)
{
    double e=0.0,n=0.0,i;
    fstream t_sets;
    t_sets.open("testdata.txt",ios::in);
    if(t_sets.is_open())
    {
        string s;
        vector<double> v,w;
        int x;
        while(getline(t_sets,s))
        {
            v.clear(),w.clear();
            v.push_back(1.0);
            string word="";
            x = model.Nodes[0].size()-1;
            for(auto x:s) 
                if(x==' '&&x!=0)
                    v.push_back(stod(word)),word="",x--;
                else if(x==' '&&x==0)
                    w.push_back(stod(word)),word="";
                else
                    word=word+x;
            w.push_back(stod(word));        
            vector<double> temp = generate(model,v,model.network.size()-1);
            clear_a(model.Nodes);
            vector<double> mult = {20};
            for(i=0;i<temp.size();i++)
                e += pow(w[i]-(mult[i]*temp[i]),2);
            n++;
        }
    }
    t_sets.close();
    return (double) e/n;
}
void print(CryoNetwork model)
{
    // for(int i=0;i<model.Nodes.size();i++)
    // {
    //     for(int j=0;j<model.Nodes[i].size();j++)
    //     {
    //         cout<<model.Nodes[i][j].a<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"-------------------------------------"<<endl;
    // for(int i=0;i<model.Nodes.size();i++)
    // {
    //     for(int j=0;j<model.Nodes[i].size();j++)
    //     {
    //         cout<<model.Nodes[i][j].error<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"-------------------------------------"<<endl;
    // for(int i=0;i<model.gradient.size();i++)
    // {
    //     for(int j=0;j<model.gradient[i].size();j++)
    //     {
    //         for(int k=0;k<model.gradient[i][j].size();k++)
    //         {
    //             cout<<model.gradient[i][j][k]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<"-------------------------------------"<<endl;
    // }
    cout<<"-------------------------------------"<<endl;
    for(int i=0;i<model.network.size();i++)
    {
        for(int j=0;j<model.network[i].size();j++)
        {
            for(int k=0;k<model.network[i][j].size();k++)
            {
                cout<<model.network[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<"-------------------------------------"<<endl;
    }
}
vector<double> WeightVec(CryoNetwork model,int layer,int col)
{
    vector<double> v;
    vector<vector<double>> temp = model.network[layer];
    for(int i=0;i<model.network[layer].size();i++)
            v.push_back(temp[i][col]);
    return v;
}
vector<double> ErrorVec(CryoNetwork model,int layer,int col)
{
    vector<double> v;
    vector<CryoNeuron> temp = model.Nodes[layer+1];
    for(int i=0;i<temp.size();i++)
        v.push_back(temp[i].error);
    return v;
}
double dot(vector<double> a,vector<double> b)
{
    double ans=0.0;
    for(int i=0;i<a.size();i++)
        ans += (a[i]*b[i]);
    return ans;    
}
void ErrorPropagation(CryoNetwork &model,int layer,vector<double> ans,vector<double> sol)
{
    int i;
    if(layer==model.Nodes.size()-1)
    {
        for(i=0;i<model.Nodes[layer].size();i++)
            model.Nodes[layer][i].error = ans[i]-(double)(sol[i]/20);
        return;    
    }
    for(i=0;i<model.Nodes[layer+1].size();i++)
        ErrorPropagation(model,layer+1,ans,sol);
    for(i=0;i<model.Nodes[layer].size();i++)
    {
        model.Nodes[layer][i].error = (dot(WeightVec(model,layer,i),ErrorVec(model,layer,i))
                                      *(model.Nodes[layer][i].a*(1-model.Nodes[layer][i].a)));
    }
}
void Gradient_calc(CryoNetwork &model)
{
    int i,j,k;
    for(i=0;i<model.gradient.size();i++)
        for(j=0;j<model.gradient[i].size();j++)
            for(k=0;k<model.gradient[i][j].size();k++)
                model.gradient[i][j][k] = model.Nodes[i][k].a*model.Nodes[i+1][j].error;
}
void Grad_Desc(CryoNetwork &model)
{
    int i,j,k;
    for(i=0;i<model.network.size();i++)
        for(j=0;j<model.network[i].size();j++)
            for(k=0;k<model.network[i][j].size();k++)
                model.network[i][j][k] = model.network[i][j][k]-(model.alpha*model.gradient[i][j][k]);
}
void display_network(auto Network)
{
    ofstream writer;
    writer.open("trained_network.txt");
    for(int i=0;i<Network.size();i++)
    {
        writer<<"{";
        for(int j=0;j<Network[i].size();j++)
        {
            if(j!=0)
                writer<<",";
            writer<<"{";
            for(int k=0;k<Network[i][j].size();k++)
            {
                if(k!=0)
                    writer<<",";
                writer<<Network[i][j][k];    
            }
            writer<<"}";
        }
        if(i!=Network.size()-1)
            writer<<"},"<<endl;
        else
            writer<<'}'<<endl;
    }
    writer.close();
}
void train_neural_network(CryoNetwork &model)
{
    double error = DBL_MAX;
    for(int i=0;i<10000;i++,model.alpha *= 1.0)
    {
        fstream t_sets;
        t_sets.open("testdata.txt",ios::in);
        if(t_sets.is_open())
        {
            string s;
            vector<double> v;
            while(getline(t_sets,s))
            {
                v.clear();
                v.push_back(1.0);
                string word="";
                for(auto x:s) 
                    if(x==' ')
                        v.push_back(stoi(word)),word="";
                    else
                        word=word+x;
                vector<double> ans = generate(model,v,model.network.size()-1);
                ErrorPropagation(model,0,ans,{stod(word)});
                Gradient_calc(model);
                Grad_Desc(model);
                clear_a(model.Nodes);
            }
        }
        t_sets.close();
        //print(model);
        
        double temp = RMS_Error(model);
        //if(temp<=error)
            error = temp;
        //else
        //    break;
        cout<<"Cost Value is: "<<error<<"     ("<<i<<")"<<endl;
        // for(int i=0;i<ans.size();i++)
        //     cout<<20*ans[i]<<" ";
        // cout<<endl;
    }
    display_network(model.network);
}
void read_neural_network(CryoNetwork &model)
{
    ifstream reader("trained_network.txt");
    if(reader.is_open())
    {
        char temp;
        int state=0,i=0,j=0,k=0;
        string s="";
        while(reader)
        {
            temp = reader.get();
            if(temp == ',')
            {
                if(s!="")
                {
                    model.network[i][j][k] = stod(s);
                    s = "";
                }    
                if(state==2)
                    k++;
                else if(state==1)
                    j++,k=0;
                else if(state==0)
                    i++,j=0,k=0;
            }
            else if(temp == '{')
                state++;
            else if(temp == '}')
                state--;
            else
                s = s+temp;
        }
        model.network[i][j][k] = stod(s);
    }
}
unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); 
default_random_engine e (seed);
double noise()
{
    normal_distribution<double> d(0,0.25);
    while(1)
    {
        double particle = d(e);
        if(particle>=-0.5&&particle<=0.5)
            return particle;
    }        
}
vector<double> convolution(vector<double> inp)
{
    vector<vector<double>> filter = {{0.35,0.15,-0.25},{0.3,0.25,-0.15}};
    vector<double> out;
    for(int i=0;i<filter.size();i++)
        out.push_back(5*Sigmoid(dot(inp,filter[i])));
    return out;    
}
void deconvolution(int arg)
{
    srand(time(NULL));
    double a=0,b=0,c=0,i;
    for(i=0;i<arg;i++)
    {
        while(1)
        {
            int temp = rand()%3;
            if(temp==0)
            {
                a++;
                break;
            }    
            else if(temp==1&&b!=50)
            {
                b++;
                break;
            }    
            else if(temp==2&&c!=50)
            {
                c++;
                break;
            }
        }
    }
    cout<<"1st output is: "<<round(a)<<endl;
    cout<<"2nd output is: "<<round((double)(b*0.06))<<endl;
    cout<<"3rd output is: "<<round((double)c/10)<<endl;
}
int main()
{
    double temp,i,n;
    CryoNetwork model;
    initialize_neural_network(model,0.1125);
    cout<<"Do you want to train a model (Type 0) or use the pre-existing model (Type 1)?"<<endl;
    cin>>n;
    if(n==0)
        train_neural_network(model);
    else
        read_neural_network(model);
    while(1)
    {
        vector<double> input,ans,inp;
        input.push_back(1.0);
        cout<<"---------------------------------------------------"<<endl;
        cout<<"Enter Input Set for which output will be predicted: ";
        for(i=0;i<3;i++)
        {
            cin>>temp;
            inp.push_back(temp);
        }
        inp = convolution(inp);
        for(i=0;i<inp.size();i++)
            input.push_back(((inp[i]-2.5)*2)+noise());
        ans = generate(model,input,model.network.size()-1);
        clear_a(model.Nodes);
        cout<<"The Predicted Output is: "<<round(150*ans[0])<<endl;
        for(i=0;i<ans.size();i++)
            deconvolution(round(150*ans[i]));
        cout<<endl;
        cout<<"---------------------------------------------------"<<endl;
    }    
    return 0;
}