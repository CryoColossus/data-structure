#include <iostream>
using namespace std;
int multer(int a[],int b[],int l)
{
    int sum=0,i;
    for(i=0;i<l;i++)
        sum += a[i]*b[i];
    return sum;    
}
int main()
{
    int a,b,c,i,j;
    cout<<"Enter No. of Rows of 1st Matrix"<<endl;
    cin>>a;
    cout<<"Enter No. of columns of 1st matrix i.e No. of rows of 2nd matrix"<<endl;
    cin>>b;
    cout<<"Enter No. of columns of 2nd matrix"<<endl;
    cin>>c;
    int m1[a][b],m2[c][b],mult[a][c];
    cout<<"Enter 1st matrix elements"<<endl;
    for(i=0;i<a;i++)
        for(j=0;j<b;j++)
            cin>>m1[i][j];
    cout<<"Enter 2nd matrix elements"<<endl;        
    for(i=0;i<b;i++)
        for(j=0;j<c;j++)
            cin>>m2[j][i];        
    for(i=0;i<a;i++)
        for(j=0;j<c;j++)
            mult[i][j]=multer(m1[i],m2[j],b);
    cout<<"The Multiplied Matrix is:"<<endl;        
    for(i=0;i<a;i++)
    {
        for(j=0;j<c;j++)
            cout<<mult[i][j]<<" ";    
        cout<<endl;    
    }        
    return 0;
}