#include <iostream>
using namespace std;
int decimalify(string s,int a)
{
    int i,x,mul=1,sum=0;
    for(i=s.length()-1;i>=0;i--)
    {
        char temp = s[i];
        if(temp<='9')
            x = temp-'0';
        else
            x = temp-'A'+10;
        sum += (x*mul);
        mul *= a;
    }
    return sum;
}
void targetify(int x,int b,string &s)
{
    s = "";
    int rem;
    char temp;
    while(x!=0)
    {
        rem = x%b;
        if(rem<10)
            temp = rem+'0';
        else
            temp = rem-10+'A';
        s = temp+s;    
        x = x/b;
    }
}
int main()
{
    string s;
    int a,b,i,j,x;
    cout<<"Enter the number"<<endl;
    cin>>s;
    cout<<"Enter the base of the string and the target base"<<endl;
    cin>>a>>b;
    if(a!=10)
        x = decimalify(s,a);
    else
        x = stoi(s);
    if(b!=10)
        targetify(x,b,s);
    cout<<"The Number in new base is: "<<s<<endl;
    return 0;
}
