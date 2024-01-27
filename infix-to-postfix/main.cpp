#include <iostream>
using namespace std;
struct stack
{
	char data;
	int top;
	int max;
	int size[400];
};
void push(struct stack &s,char c)
{
	if(s.top==s.max)
	return;
	s.size[++s.top]=c;
}
char pop(struct stack &s)
{
	return s.size[s.top--];
}
bool is_empty(struct stack s)
{
	return (s.top==-1)?true:false;
}
int main() {
	
	int t,i,brack,length,j;
	string str;
	char c;
	cin>>t;
	for(i=0;i<t;i++)
	{
		struct stack S;
		S.top=-1;
		S.max=400;		
		cin>>str;
		brack=0;
		length=str.length();
		for(j=0;j<length;j++)
		{
			c = str[j];
			if(c=='(')
			brack++;
			else if(c==')')
			{
				brack--;
				cout<<pop(S);
			}
			else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
			{
				push(S,c);
			}
			else
			cout<<c;
		}
	}
	
	return 0;
}