#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <time.h>
using namespace std;
vector<double> mult = {150};
double alpha = 0.0001;
double decay_rate = 0.9999;
int epochs = 5000;
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
double crandom()
{
    while(1)
    {
        double x = (double)rand()/RAND_MAX;
        double y = rand()/2;
        if(x!=0)
            return ((y==0)?-3*x:3*x);
    }    
}
void initialize_neural_network(CryoNetwork &model,double alpha)
{
    int i,j,k;
    model.alpha = alpha;
    model.network.push_back({{0,0,0,0},{20.67192,0.960824,0.0726475,0.535317},{1.99649,2.97065,2.4282,1.22803}});
    model.network.push_back({{0,0,0},{0.992603,0.224352,2.44337},{-0.300883,-2.08505,-2.90599}});
    model.network.push_back({{-0.168687,-0.443712,2.49159}});
    //model.network.push_back({{0,0,0,0},{-1.40718,0.378556,0.201716,-1.63392},{-1.40718,0.378556,0.201716,-1.63392},{-1.40718,0.378556,0.201716,-1.63392},{-1.40718,0.378556,0.201716,-1.63392}});
    //model.network.push_back({{0,0,0,0,0},{-2.03796,1.21262,1.21262,1.21262,1.21262},{-2.03796,1.21262,1.21262,1.21262,1.21262},{-2.03796,1.21262,1.21262,1.21262,1.21262}});
    //model.network.push_back({{-2.56050,2.05775,2.05775,2.05775},{-3.43775,2.51136,2.51136,2.51136},{-3.27554,1.88192,1.88192,1.88192}});
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
double RMS_Error(CryoNetwork model,double &ratio)
{
    double e=0.0,n=0.0,i,val=0.0;
    int correct=0,total=0;
    fstream t_sets;
    t_sets.open("testdata.txt",ios::in);
    if(t_sets.is_open())
    {
        string s;
        vector<double> v,w;
        int num;
        while(getline(t_sets,s))
        {
            v.clear(),w.clear();
            v.push_back(1.0);
            string word="";
            num = model.Nodes[0].size()-1;
            for(auto x:s) 
                if(x==' '&&num!=0)
                    v.push_back(stod(word)),word="",num--;
                else if(x==' '&&num==0)
                    w.push_back(stod(word)),word="";
                else
                    word=word+x;
            w.push_back(stod(word));        
            vector<double> temp = generate(model,v,model.network.size()-1);
            clear_a(model.Nodes);
            for(i=0;i<temp.size();i++)
                e += pow(w[i]-(mult[i]*temp[i]),2);
            if(val==e)
                correct++;
            total++;    
            n++;
        }
    }
    t_sets.close();
    ratio = (double)correct/total;
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
            model.Nodes[layer][i].error += ans[i]-(double)(sol[i]/mult[i]);
        return;    
    }
    for(i=0;i<model.Nodes[layer+1].size();i++)
        ErrorPropagation(model,layer+1,ans,sol);
    for(i=0;i<model.Nodes[layer].size();i++)
    {
        model.Nodes[layer][i].error += (dot(WeightVec(model,layer,i),ErrorVec(model,layer,i))
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
    vector<vector<double>> input;
    vector<double> slide;
    fstream t_sets;
    char dummy;
    t_sets.open("testdata.txt",ios::in);
    string s,temp;
    int a1=0,a2=0,i,j;
    while(getline(t_sets,s))
    {
        temp="";
        slide.clear();
        for(i=0;i<s.length();i++)
        {
            if(s[i]!=' ')
                temp = temp+s[i];
            else
                slide.push_back(stod(temp)),temp="";
        }
        slide.push_back(stod(temp));
        input.push_back(slide);
    }
    for(int i=0;i<epochs;i++,model.alpha *= decay_rate)
    {
        if(i%5000==0)
            cin>>dummy;
        int num,batchsize=5;
        vector<double> v,w;
        while(batchsize--)
        {
            v.clear();
	        w.clear();
	        num = model.Nodes[0].size()-1;
            v.push_back(1.0);
            string word="";
            int x = rand()%input.size();
            for(int j=0;j<input[x].size();j++) 
                if(num!=0)
                    v.push_back(input[x][j]),num--;
	            else if(num==0)
	                w.push_back(input[x][j]);
            vector<double> ans = generate(model,v,model.network.size()-1);
            ErrorPropagation(model,0,ans,w);
        }
        Gradient_calc(model);
        Grad_Desc(model);
        clear_a(model.Nodes);
        double ratio;
        double tempo = RMS_Error(model,ratio);
        //if(temp<=error)
            error = tempo;
        //else
        //    break;
        cout<<"Cost Value is: "<<error<<"     ("<<i<<")      "<<"Accuracy: "<<100*ratio<<"%"<<endl;
        // for(int i=0;i<ans.size();i++)
        //     cout<<20*ans[i]<<" ";
        // cout<<endl;
        //if(error<10.0)
        //    break;
        display_network(model.network);
    }
    t_sets.close();
    //print(model);
}
void read_neural_network(CryoNetwork &model)
{
    ifstream reader("trained_network.txt");
    double ratio;
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
    cout<<"Cost Value is: "<<RMS_Error(model,ratio)<<endl;
}
int main()
{
    srand(time(0));
    double temp,i,n;
    cout.precision(17);
    CryoNetwork model;
    initialize_neural_network(model,alpha);
    cout<<"Do you want to train a model (Type 0) or use the pre-existing model (Type 1)?"<<endl;
    cin>>n;
    if(n==0)
        train_neural_network(model);
    else
        read_neural_network(model);
    while(1)
    {
        vector<double> input,ans;
        input.push_back(1.0);
        cout<<"---------------------------------------------------"<<endl;
        cout<<"Enter Input Set for which output will be predicted: ";
        for(i=0;i<model.Nodes[0].size()-1;i++)
        {
            cin>>temp;
            input.push_back(temp);
        }
        ans = generate(model,input,model.network.size()-1);
        clear_a(model.Nodes);
        cout<<"The Predicted Output is: "<<endl;
        for(i=0;i<ans.size();i++)
            cout<<round(mult[i]*ans[i])<<" ";
        cout<<endl;
        cout<<"---------------------------------------------------"<<endl;
    }    
    return 0;
}