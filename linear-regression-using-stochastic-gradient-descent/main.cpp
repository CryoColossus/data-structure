#include <iostream>
#include <cfloat>
using namespace std;

//Randomizer

int randomizer(int bound)
{
    srand(time(0));
    return (rand()%bound);
}

//Dot Product Function

double dot_product(double a[],double b[],int n)
{
    double product=0;
    for(int i=0;i<n;i++)
        product += a[i]*b[i];
    return product;    
}

void costify(double &local_cost,double parameter[],double **input,double output[],int train,int features)
{
    local_cost = 0;
    double temp;
    int i,j;
    for(i=0;i<train;i++)
    {
        temp=0;
        for(j=0;j<features;j++)
        {
            temp += input[i][j]*parameter[j];
        }
        local_cost += (temp-output[i])*(temp-output[i]);
    }
    local_cost /= (2*train);
}

//LINEAR REGRESSION MODEL

void linear_regression(double parameter[],double **input,double output[],int examples,int no_of_feat,double alpha)
{
    int i;
    double parameter_[no_of_feat];
    double cost,temp[no_of_feat];
    for(i=0;i<no_of_feat;i++)
    {
        int j = randomizer(examples);
        for(int k=0;k<no_of_feat;k++)
            temp[k] = input[j][k];
        cost = (output[j]-dot_product(temp,parameter,no_of_feat))*input[j][i]; // Stochastic Gradient Descent
        parameter_[i] = parameter[i]+(alpha*cost); // General Gradient Descent
    }
    for(i=0;i<no_of_feat;i++)
        parameter[i] = parameter_[i];
}

//Main Function

int main()
{
    int f,t,i,j;
    double alpha = 0.000001; // Learning Rate
    //NOTE: Value of Alpha is Hypercritical for Model's Performance. (Changes for Every Dataset)
    
    //Initializing the Inputs
    
    cout<<"Enter Number of Features for the Model"<<endl;
    cin>>f;
    cout<<"Enter Number of Training Sets for the Model"<<endl;
    cin>>t;
    double output[t];
    double **input = new double*[t];
    for(i=0;i<t;i++)
        input[i] = new double[f+1];
    cout<<"Enter training set values and the output"<<endl;
    
    //Populate the training sets with features and targets.
    
    for(i=0;i<t;i++)
    {
        input[i][0]=1;
        for(j=1;j<f+1;j++)
            cin>>input[i][j];
        cin>>output[i];    
    }
    
    //Initializing the parameter vector whose values are learned upon.
    
    double parameter[f+1];
    for(i=0;i<f+1;i++)
        parameter[i]=1;
        
    /*Model Definition - Linear Regression
    Training Model for many iterations*/
    
    double optimized_parameter[f+1];
    double optimized_cost=DBL_MAX,local_cost;
    for(i=0;i<10000000;i++)
    {
        linear_regression(parameter,input,output,t,f+1,alpha);
        if(i%1==0)
        alpha *= 0.9999999999999;      //Decaying Learning Parameter (Depending from Dataset to Dataset)
        costify(local_cost,parameter,input,output,t,f+1);
        if(local_cost<optimized_cost)
        {
            for(j=0;j<f+1;j++)
                optimized_parameter[j] = parameter[j];
            optimized_cost = local_cost;    
        }
    }    
    
    // Training is complete finally!
    
    cout<<"Training of Model is complete!"<<endl;
    cout<<"Learned Parameter Values are: "<<endl;
    for(i=0;i<f+1;i++)
        cout<<optimized_parameter[i]<<" ";
    cout<<endl;    
    cout<<"Cost is: "<<optimized_cost<<endl;
    cout<<"Learning rate is: "<<alpha<<endl;
    
    // Ask the new features whose target is to be known
    
    double x[f+1];
    cout<<"Enter the input features for which the new target is to be known. (Press Ctrl+C to exit.)"<<endl;
    while(1)
    {
        x[0]=1;
        for(i=1;i<f+1;i++)
            cin>>x[i];
    
    //Calculate the new target
    
        double solution = dot_product(x,parameter,f+1);
        cout<<"The predicted target by the model is: "<<solution<<endl;
    }
    return 0;
}

