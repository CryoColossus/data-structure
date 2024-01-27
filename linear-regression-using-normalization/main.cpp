#include <iostream>
using namespace std;

//LINEAR REGRESSION Model

    //Dot Product Function
double dot_product(double a[],double b[],int n)
{
    double product=0;
    for(int i=0;i<n;i++)
        product += a[i]*b[i];
    return product;    
}    

    //Performs Xt transformation on the output vector
void output_transformer(double **input_transpose,double output[],double p1[],int train,int features)
{
    int i,j;
    for(i=0;i<features;i++)
    {
        p1[i]=0;
        for(j=0;j<train;j++)
            p1[i] += input_transpose[i][j]*output[j];
    }    
        
}

    //Combines X and Xt into a single transformation 
void full_transformer(double **input_transpose,double **input,double **final_transformer,int train,int features)
{
    int i,j,k;
    for(i=0;i<features;i++)
    {
        for(j=0;j<features;j++)
        {
            final_transformer[i][j]=0;
            for(k=0;k<train;k++)
                final_transformer[i][j] += input_transpose[i][k]*input[k][j];
        }
    }
}

    //Calculates the final parametric vector
void parametric_transformer(double **final_transformer,double p1[],double optimized_parameters[],int features)
{
    int i,j;
    for(i=0;i<features;i++)
    {
        optimized_parameters[i]=0;
        for(j=0;j<features;j++)
            optimized_parameters[i] += final_transformer[i][j]*p1[j];
    }
}

    //Finding CoFactor for a given element
void getCofactor(double **final_transformer, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = final_transformer[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}    

    //Calculation of the Determinant of a Matrix
int determinant(double **final_transformer, int n)
{
    int i,j;
    double D = 0;
    if (n == 1)
        return final_transformer[0][0];
    double **temp = new double*[n];
    for(i=0;i<n;i++)
        temp[i] = new double[n];
    int sign = 1;
    for (int f = 0; f < n; f++)
    {
        getCofactor(final_transformer, temp, 0, f, n);
        D += sign * final_transformer[0][f] * determinant(temp, n - 1);
        sign *= -1;
    }
    return D;
}

    //Adjoint for the required Matrix
void adjoint(double **A,double **adj,int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    double **temp = new double*[N];
    for(int k=0;k<N;k++)
        temp[k] = new double[N];
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            getCofactor(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}    

    //Inverse of the combined transformation
void inverse(double **final_transformer,int features)
{
    int i,j;
    double det = determinant(final_transformer,features);
    double **adj = new double*[features];
    for(i=0;i<features;i++)
        adj[i] = new double[features];
    adjoint(final_transformer,adj,features);
    for(i=0;i<features;i++)
    {
        for(j=0;j<features;j++)
        {
            final_transformer[i][j] = adj[i][j];
            final_transformer[i][j]/=det;
        }    
    }
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

//Main Function

int main()
{
    int f,t,i,j;
    
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
        
    /*Model Definition - Linear Regression using Normalization
    Only 1 iteration algorithm*/
    
    double **input_transpose = new double*[f+1];
    for(i=0;i<f+1;i++)
        input_transpose[i] = new double[t];
        
    for(i=0;i<t;i++)
    {
        for(j=0;j<f+1;j++)
            input_transpose[j][i] = input[i][j];
    }
    double p1[f+1];
    
    output_transformer(input_transpose,output,p1,t,f+1);
    
    double **final_transformer = new double*[f+1];
    for(i=0;i<f+1;i++)
        final_transformer[i] = new double[f+1];
        
    full_transformer(input_transpose,input,final_transformer,t,f+1);
    
    inverse(final_transformer,f+1);
    
    double optimized_parameters[f+1];
    
    parametric_transformer(final_transformer,p1,optimized_parameters,f+1);
    
    // Training is complete finally!
    
    cout<<"Training of Model is complete!"<<endl;
    cout<<"Learned Parameter Values are: "<<endl;
    
    double local_cost;
    costify(local_cost,optimized_parameters,input,output,t,f+1);
    
    for(i=0;i<f+1;i++)
        cout<<optimized_parameters[i]<<" ";
    cout<<endl;    
    cout<<"Cost is: "<<local_cost<<endl;
    
    // Ask the new features whose target is to be known
    
    double x[f+1];
    cout<<"Enter the input features for which the new target is to be known. (Press Ctrl+C to exit.)"<<endl;
    while(1)
    {
        x[0]=1;
        for(i=1;i<f+1;i++)
            cin>>x[i];
    
    //Calculate the new target
    
        double solution = dot_product(x,optimized_parameters,f+1);
        cout<<"The predicted target by the model is: "<<solution<<endl;
    }
    return 0;
}



