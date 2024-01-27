#include <iostream>
using namespace std;
int main()
{
    double I=0.00,P=0.00,A=0.00,Y=0.00;
    string s;
    cin>>s;
    if(s=="StartOfTransactions")
    {
        double val,total=0.00;
        string splits;
        int n;
        cin>>n;
        cout<<"Enter Transactions"<<endl;
        while(n--)
        {
            cin>>val>>splits;
            total += val;
            for(int i=0;i<splits.length();i++)
            {
                if(splits[i]=='I')
                {
                    I -= val/splits.length();
                }
                else if(splits[i]=='P')
                {
                    P -= val/splits.length();
                }
                else if(splits[i]=='A')
                {
                    A -= val/splits.length();
                }
                else if(splits[i]=='Y')
                {
                    Y -= val/splits.length();
                }
            }
        }
        cout<<"Enter Payments"<<endl;
        while(total > 0.0001)
        {
            cin>>val>>splits;
            if(splits[0]=='I')
            {
                I += val;
            }
            else if(splits[0]=='P')
            {
                P += val;
            }
            else if(splits[0]=='A')
            {
                A += val;
            }
            else if(splits[0]=='Y')
            {
                Y += val;
            }
            total -= val;
        }
        cout<<"The Net Balances after the calculations are as follows:"<<endl;
        cout<<"Ishan Net Balance: "<<I<<endl;
        cout<<"Prathamesh Net Balance: "<<P<<endl;
        cout<<"Aashay Net Balance: "<<A<<endl;
        cout<<"Yash Net Balance: "<<Y<<endl;
    }    
    else
    {
        cout<<"Invalid Format Input"<<endl;
    }
    return 0;
}