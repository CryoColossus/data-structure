#include <iostream>
#include <deque>
using namespace std;
void swap(char &x,char &y)
{
    char temp = x;
    x = y;
    y = temp;
}
void display_board(char board[8][8])
{
    cout<<endl<<endl;
    for(int i=0;i<8;i++)
    {
        cout<<"|---|---|---|---|---|---|---|---|"<<endl;
        for(int j=0;j<8;j++)
	{		
            cout<<"| ";
	        cout<<board[i][j];
	        cout<<" ";
	}
        cout<<"| "<<8-i<<endl;    
    }    
    cout<<"|---|---|---|---|---|---|---|---|"<<endl;
    cout<<"  A   B   C   D   E   F   G   H  "<<endl<<endl;
}
void initialize_board(char board[8][8],bool castle[2][3])
{
    int i,j;
    for(i=0;i<2;i++)
        for(j=0;j<3;j++)
            castle[i][j]=true;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            board[i][j]=' ';
    char piece[8]={'r','n','b','q','k','b','n','r'};
    for(i=0;i<8;i++)
        board[0][i]=piece[i],board[7][i]=piece[i]-('a'-'A');
    for(i=0;i<8;i++)
        board[1][i]='p',board[6][i]='P';
}
bool checked(char board[8][8],char color,int x,int y)
{
    int i,t[2][2]={{2,-2},{1,-1}},j;
    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            if(x+t[0][i]<8&&x+t[0][i]>=0&&y+t[1][j]<8&&y+t[1][j]>=0&&(board[x+t[0][i]][y+t[1][j]]==((color=='W')?'n':'N')))
                return true;
            else if(x+t[1][i]<8&&x+t[1][i]>=0&&y+t[0][j]<8&&y+t[0][j]>=0&&(board[x+t[1][i]][y+t[0][j]]==((color=='W')?'n':'N')))
                return true;    
    for(i=x-1;i>0;i--)//1
        if(board[i][y]!=' ')
            break;
    if(i>=0)
        if(board[i][y]==((color=='W')?'r':'R')||board[i][y]==((color=='W')?'q':'Q')||(board[i][y]==((color=='W')?'k':'K')&&x-i==1))
            return true;
    for(i=x+1;i<8;i++)//2
        if(board[i][y]!=' ')
            break;   
    if(i<8)
        if(board[i][y]==((color=='W')?'r':'R')||board[i][y]==((color=='W')?'q':'Q')||(board[i][y]==((color=='W')?'k':'K')&&i-x==1))
            return true;
    for(i=y-1;i>0;i--)//3
        if(board[x][i]!=' ')
            break;
    if(i>=0)
        if(board[x][i]==((color=='W')?'r':'R')||board[x][i]==((color=='W')?'q':'Q')||(board[x][i]==((color=='W')?'k':'K')&&y-i==1))
            return true;
    for(i=y+1;i<8;i++)//4
        if(board[x][i]!=' ')
            break;   
    if(i<8)
        if(board[x][i]==((color=='W')?'r':'R')||board[x][i]==((color=='W')?'q':'Q')||(board[x][i]==((color=='W')?'k':'K')&&i-y==1))
            return true;      
    for(i=1;max(x+i,y+i)<8;i++)//5
        if(board[x+i][y+i]!=' ')
            break;
    if(x+i<8&&y+i<8)
        if(board[x+i][y+i]==((color=='W')?'b':'B')||board[x+i][y+i]==((color=='W')?'q':'Q')||(board[x+i][y+i]==((color=='W')?'k':'K')&&i==1)||((color=='B')?(board[x+i][y+i]=='P'&&i==1):0))
            return true;
    for(i=1;min(x-i,y-i)>0;i++)//6
        if(board[x-i][y-i]!=' ')
            break;
    if(x+i>0&&y+i>0)
        if(board[x-i][y-i]==((color=='W')?'b':'B')||board[x-i][y-i]==((color=='W')?'q':'Q')||(board[x-i][y-i]==((color=='W')?'k':'K')&&i==1)||((color=='W')?(board[x-i][y-i]=='p'&&i==1):0))
            return true;        
    for(i=1;x-i>0&&y+i<8;i++)//7
        if(board[x-i][y+i]!=' ')
            break;
    if(x-i>0&&y-i<8)
        if(board[x-i][y+i]==((color=='W')?'b':'B')||board[x-i][y+i]==((color=='W')?'q':'Q')||(board[x-i][y+i]==((color=='W')?'k':'K')&&i==1)||((color=='W')?(board[x-i][y+i]=='p'&&i==1):0))
            return true;
    for(i=1;x+i<8&&y-i>0;i++)//8
        if(board[x+i][y-i]!=' ')
            break;
    if(x+i<8&&y-i>0)
        if(board[x+i][y-i]==((color=='W')?'b':'B')||board[x+i][y-i]==((color=='W')?'q':'Q')||(board[x+i][y-i]==((color=='W')?'k':'K')&&i==1)||((color=='B')?(board[x+i][y-i]=='P'&&i==1):0))
            return true;
    return false;        
}
bool clearance(char board[8][8],int x,int y,int m,int n)
{
    if(x==m)
    {
        if(y<n)
        {
            for(int i=y+1;i<n;i++)
                if(board[x][i]!=' ')
                    return false;
            return true;        
        }
        else if(n<y)
        {
            for(int i=n+1;i<y;i++)
                if(board[x][i]!=' ')
                    return false;
            return true;
        }
    }
    else if(y==n)
    {
        if(x<m)
        {
            for(int i=x+1;i<m;i++)
                if(board[i][y]!=' ')
                    return false;
            return true;        
        }
        else if(m<x)
        {
            for(int i=m+1;i<x;i++)
                if(board[i][y]!=' ')
                    return false;
            return true;
        }
    }
    else if(m-x==n-y)
    {
        if(m-x>0)
        {
            for(int i=1;x+i<m;i++)
                if(board[x+i][y+i]!=' ')
                    return false;
            return true;        
        }
        else if(x-m>0)
        {
            for(int i=1;x-i>m;i++)
                if(board[x-i][y-i]!=' ')
                    return false;
            return true;
        }
    }
    else if(x+y==m+n)
    {
        if(m>x)
        {
            for(int i=1;x+i<m;i++)
                if(board[x+i][y-i]!=' ')
                    return false;
            return true;
        }
        else if(x>m)
        {
            for(int i=1;x-i>m;i++)
                if(board[x-i][y+i]!=' ')
                    return false;
            return true;        
        }
    }
}
void castle_update(bool castle[2][3],int x,int y,char color)
{
    if(color=='W')
    {
        if(x==7&&y==0)
            castle[0][2]=false;
        else if(x==7&&y==7)
            castle[0][1]=false;
    }
    else if(color=='B')
    {
        if(x==0&&y==0)
            castle[1][2]=false;
        else if(x==0&&y==7)
            castle[1][1]=false;
    }
}
bool move_2(string move,char board[8][8],char color,bool castle[2][3],int k_pos[2][2])
{
    if(move[0]>='a'&&move[0]<='h'&&move[1]>='1'&&move[1]<='8')
    {
        if(board[8-(move[1]-'0')][move[0]-'a']!=' ')
            return false;
        if(board[8-(move[1]-'0')+(color=='W'?1:-1)][move[0]-'a']==((color=='W')?'P':'p')){
            swap(board[8-(move[1]-'0')+(color=='W'?1:-1)][move[0]-'a'],board[8-(move[1]-'0')][move[0]-'a']);
            if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                swap(board[8-(move[1]-'0')+(color=='W'?1:-1)][move[0]-'a'],board[8-(move[1]-'0')][move[0]-'a']);
                return false;}
            if(move[1]==(color=='W'?'8':'1'))
            {
                char temp;
                cout<<"What would you like to promote to? (Q/R/B/N)"<<endl;
                cin>>temp;
                board[8-(move[1]-'0')][move[0]-'a'] = temp+((color=='W')?0:('a'-'A'));
            }
            return true;}
        if(move[1]==((color=='W')?'4':'5')&&board[8-(move[1]-'0')+((color=='W')?2:-2)][move[0]-'a']==((color=='W')?'P':'p')&&board[8-(move[1]-'0')+((color=='W')?1:-1)][move[0]-'a']==' '){
            swap(board[8-(move[1]-'0')+((color=='W')?2:-2)][move[0]-'a'],board[8-(move[1]-'0')][move[0]-'a']);
            if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                swap(board[8-(move[1]-'0')+((color=='W')?2:-2)][move[0]-'a'],board[8-(move[1]-'0')][move[0]-'a']);
                return false;}
            return true;}    
        return false;    
    }
    return false;
}
bool move_3(string move,char board[8][8],char color,bool castle[2][3],int k_pos[2][2],int cond_row=-1,int cond_col=-1)
{
    if((move[0]=='O'||move[0]=='0')&&move[1]=='-'&&(move[2]=='O'||move[2]=='0'))
    {
            if(board[(color=='W')?7:0][4]==((color=='W')?'K':'k')&&board[(color=='W')?7:0][7]==((color=='W')?'R':'r')&&(castle[(color=='W')?0:1][0]&&castle[(color=='W')?0:1][1])&&clearance(board,(color=='W')?7:0,4,(color=='W')?7:0,7)&&!checked(board,color,(color=='W')?7:0,4)&&!checked(board,color,(color=='W')?7:0,5)&&!checked(board,color,(color=='W')?7:0,6))
            {
                swap(board[(color=='W')?7:0][4],board[(color=='W')?7:0][6]);
                swap(board[(color=='W')?7:0][7],board[(color=='W')?7:0][5]);
                if(!checked(board,color,(color=='W')?7:0,6))
                {
                    for(int i=0;i<3;i++)
                        castle[(color=='W')?0:1][i]=false;
                    k_pos[(color=='W')?0:1][0]=(color=='W')?7:0,k_pos[(color=='W')?0:1][1]=6;    
                    return true;
                }
                swap(board[(color=='W')?7:0][4],board[(color=='W')?7:0][6]);
                swap(board[(color=='W')?7:0][7],board[(color=='W')?7:0][5]);
            }
            return false;
    }
    if((move[0]=='R'||move[0]=='N'||move[0]=='B'||move[0]=='Q'||move[0]=='K')&&move[1]>='a'&&move[1]<='h'&&move[2]>='1'&&move[2]<='8')
    {
        if(board[8-(move[2]-'0')][move[1]-'a']!=' ')
                return false;
        if(move[0]=='R')
        {
            int x = 8-(move[2]-'0');
            int y = move[1]-'a',i;
            for(i=0;i<8;i++)
            {
                if(i!=x&&board[i][y]==((color=='W')?'R':'r'))
                {
                    if(clearance(board,x,y,i,y)&&((cond_row!=-1)?cond_row==i:true)){
                        swap(board[x][y],board[i][y]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[i][y]);
                            return false;}
                        castle_update(castle,i,y,color);
                        return true;}
                }
                if(i!=y&&board[x][i]==((color=='W')?'R':'r'))
                {
                    if(clearance(board,x,y,x,i)&&((cond_col!=-1)?cond_col==i:true)){
                        swap(board[x][y],board[x][i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x][i]);
                            return false;}
                        castle_update(castle,x,i,color);
                        return true;}
                }
            }
            return false;
        }
        if(move[0]=='N')
        {
            if((8-(move[2]-'0')+2)<8&&(move[1]-'a'+1)<8&&(board[8-(move[2]-'0')+2][move[1]-'a'+1]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')+2==cond_row:true)&&((cond_col!=-1)?move[1]-'a'+1==cond_col:true)){
                swap(board[8-(move[2]-'0')+2][move[1]-'a'+1],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')+2][move[1]-'a'+1],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')+2)<8&&(move[1]-'a'-1)<8&&(board[8-(move[2]-'0')+2][move[1]-'a'-1]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')+2==cond_row:true)&&((cond_col!=-1)?move[1]-'a'-1==cond_col:true)){
                swap(board[8-(move[2]-'0')+2][move[1]-'a'-1],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')+2][move[1]-'a'-1],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')-2)<8&&(move[1]-'a'+1)<8&&(board[8-(move[2]-'0')-2][move[1]-'a'+1]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')-2==cond_row:true)&&((cond_col!=-1)?move[1]-'a'+1==cond_col:true)){
                swap(board[8-(move[2]-'0')-2][move[1]-'a'+1],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')-2][move[1]-'a'+1],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')-2)<8&&(move[1]-'a'-1)<8&&(board[8-(move[2]-'0')-2][move[1]-'a'-1]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')-2==cond_row:true)&&((cond_col!=-1)?move[1]-'a'-1==cond_col:true)){
                swap(board[8-(move[2]-'0')-2][move[1]-'a'-1],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')-2][move[1]-'a'-1],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')+1)<8&&(move[1]-'a'+2)<8&&(board[8-(move[2]-'0')+1][move[1]-'a'+2]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')+1==cond_row:true)&&((cond_col!=-1)?move[1]-'a'+2==cond_col:true)){
                swap(board[8-(move[2]-'0')+1][move[1]-'a'+2],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')+1][move[1]-'a'+2],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')+1)<8&&(move[1]-'a'-2)<8&&(board[8-(move[2]-'0')+1][move[1]-'a'-2]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')+1==cond_row:true)&&((cond_col!=-1)?move[1]-'a'-2==cond_col:true)){
                swap(board[8-(move[2]-'0')+1][move[1]-'a'-2],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')+1][move[1]-'a'-2],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')-1)<8&&(move[1]-'a'+2)<8&&(board[8-(move[2]-'0')-1][move[1]-'a'+2]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')-1==cond_row:true)&&((cond_col!=-1)?move[1]-'a'+2==cond_col:true)){
                swap(board[8-(move[2]-'0')-1][move[1]-'a'+2],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')-1][move[1]-'a'+2],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}
            if((8-(move[2]-'0')-1)<8&&(move[1]-'a'-2)<8&&(board[8-(move[2]-'0')-1][move[1]-'a'-2]==((color=='W')?'N':'n'))&&((cond_row!=-1)?8-(move[2]-'0')-1==cond_row:true)&&((cond_col!=-1)?move[1]-'a'-2==cond_col:true)){
                swap(board[8-(move[2]-'0')-1][move[1]-'a'-2],board[8-(move[2]-'0')][move[1]-'a']);
                if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[8-(move[2]-'0')-1][move[1]-'a'-2],board[8-(move[2]-'0')][move[1]-'a']);
                            return false;}
                return true;}   
            return false;    
        }
        if(move[0]=='B')
        {
            int x = 8-(move[2]-'0');
            int y = move[1]-'a',i;
            for(i=1;i<8;i++)
            {
                if(x+i<8&&y+i<8&&board[x+i][y+i]==((color=='W')?'B':'b'))
                {
                    if(clearance(board,x,y,x+i,y+i)&&((cond_row!=-1)?x+i==cond_row:true)&&((cond_col!=-1)?y+i==cond_col:true)){
                        swap(board[x][y],board[x+i][y+i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x+i][y+i]);
                            return false;}
                        return true;}
                }
                if(x+i<8&&y-i>=0&&board[x+i][y-i]==((color=='W')?'B':'b'))
                {
                    if(clearance(board,x,y,x+i,y-i)&&((cond_row!=-1)?x+i==cond_row:true)&&((cond_col!=-1)?y-i==cond_col:true)){
                        swap(board[x][y],board[x+i][y-i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x+i][y-i]);
                            return false;}
                        return true;}
                }
                if(x-i>=0&&y+i<8&&board[x-i][y+i]==((color=='W')?'B':'b'))
                {
                    if(clearance(board,x,y,x-i,y+i)&&((cond_row!=-1)?x-i==cond_row:true)&&((cond_col!=-1)?y+i==cond_col:true)){
                        swap(board[x][y],board[x-i][y+i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x-i][y+i]);
                            return false;}
                        return true;}
                }
                if(x+i>=0&&y+i>=0&&board[x-i][y-i]==((color=='W')?'B':'b'))
                {
                    if(clearance(board,x,y,x-i,y-i)&&((cond_row!=-1)?x-i==cond_row:true)&&((cond_col!=-1)?y-i==cond_col:true)){
                        swap(board[x][y],board[x-i][y-i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x-i][y-i]);
                            return false;}
                        return true;}
                }
            }
            return false;
        }
        if(move[0]=='Q')
        {
            int x = 8-(move[2]-'0');
            int y = move[1]-'a',i;
            for(i=0;i<8;i++)
            {
                if(i!=x&&board[i][y]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,i,y)&&((cond_row!=-1)?i==cond_row:true)){
                        swap(board[x][y],board[i][y]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[i][y]);
                            return false;}
                        return true;}
                }
                if(i!=y&&board[x][i]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,x,i)&&((cond_col!=-1)?i==cond_col:true)){
                        swap(board[x][y],board[x][i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x][i]);
                            return false;}
                        return true;}
                }
            }
            for(i=1;i<8;i++)
            {
                if(x+i<8&&y+i<8&&board[x+i][y+i]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,x+i,y+i)&&((cond_row!=-1)?x+i==cond_row:true)&&((cond_col!=-1)?y+i==cond_col:true)){
                        swap(board[x][y],board[x+i][y+i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x+i][y+i]);
                            return false;}
                        return true;}
                }
                if(x+i<8&&y-i>=0&&board[x+i][y-i]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,x+i,y-i)&&((cond_row!=-1)?x+i==cond_row:true)&&((cond_col!=-1)?y-i==cond_col:true)){
                        swap(board[x][y],board[x+i][y-i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x+i][y-i]);
                            return false;}
                        return true;}
                }
                if(x-i>=0&&y+i<8&&board[x-i][y+i]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,x-i,y+i)&&((cond_row!=-1)?x-i==cond_row:true)&&((cond_col!=-1)?y+i==cond_col:true)){
                        swap(board[x][y],board[x-i][y+i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x-i][y+i]);
                            return false;}
                        return true;}
                }
                if(x+i>=0&&y+i>=0&&board[x-i][y-i]==((color=='W')?'Q':'q'))
                {
                    if(clearance(board,x,y,x-i,y-i)&&((cond_row!=-1)?x-i==cond_row:true)&&((cond_col!=-1)?y-i==cond_col:true)){
                        swap(board[x][y],board[x-i][y-i]);
                        if(checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                            swap(board[x][y],board[x-i][y-i]);
                            return false;}
                        return true;}
                }
            }
            return false;
        }
        if(move[0]=='K')
        {
            if(board[8-(move[2]-'0')+1][move[1]-'a'+1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a'+1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a'+1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')+1][move[1]-'a']==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a']);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a']);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')][move[1]-'a'+1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')][move[1]-'a'+1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')][move[1]-'a'+1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')-1][move[1]-'a'-1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a'-1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a'-1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')-1][move[1]-'a']==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a']);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a']);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')][move[1]-'a'-1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')][move[1]-'a'-1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')][move[1]-'a'-1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')-1][move[1]-'a'+1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a'+1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')-1][move[1]-'a'+1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}
            if(board[8-(move[2]-'0')+1][move[1]-'a'-1]==((color=='W')?'K':'k')){
                swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a'-1]);
                if(checked(board,color,8-(move[2]-'0'),move[1]-'a')){
                            swap(board[8-(move[2]-'0')][move[1]-'a'],board[8-(move[2]-'0')+1][move[1]-'a'-1]);
                            return false;}
                castle[(color=='W')?0:1][0]=false;
                k_pos[(color=='W'?0:1)][0]=8-(move[2]-'0'),k_pos[(color=='W'?0:1)][1]=move[1]-'a';
                return true;}    
        }
    }
    return false;
}
bool move_4(string move,char board[8][8],char color,bool castle[2][3],int k_pos[2][2],deque<string> game,int cond_row=-1,int cond_col=-1)
{
    char temp;
        if(move[1]=='x'&&((move[0]=='R'||move[0]=='N'||move[0]=='B'||move[0]=='Q'||move[0]=='K')||(move[0]>='a'&&move[0]<='h'))&&move[2]>='a'&&move[2]<='h'&&move[3]>='1'&&move[3]<='8')
        {
            int x = 8-(move[3]-'0');
            int y = move[2]-'a',i;
            if(board[x][y]==((color=='W')?'p':'P')||board[x][y]==((color=='W')?'n':'N')||board[x][y]==((color=='W')?'b':'B')||board[x][y]==((color=='W')?'r':'R')||board[x][y]==((color=='W')?'q':'Q'))
            {
                if(move[0]=='R')
                {
                    for(i=0;i<8;i++)
                    {
                        if(i!=x&&board[i][y]==((color=='W')?'R':'r'))
                        {
                        if(clearance(board,x,y,i,y)&&((cond_row!=-1)?cond_row==i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[i][y]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[i][y]);
                                    board[x][y]=temp;
                                    return false;}
                                castle_update(castle,i,y,color);
                                return true;}
                        }
                        if(i!=y&&board[x][i]==((color=='W')?'R':'r'))
                        {
                            if(clearance(board,x,y,x,i)&&((cond_col!=-1)?cond_col==i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x][i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x][i]);
                                    board[x][y]=temp;
                                    return false;}
                                castle_update(castle,x,i,color);
                                return true;}
                        }
                    }
                    return false;
                }
                if(move[0]=='N')
                {
                    if((x+2)<8&&(y+1)<8&&(board[x+2][y+1]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x+2:true)&&(cond_col!=-1?cond_col==y+1:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x+2][y+1],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x+2][y+1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x+2)<8&&(y-1)<8&&(board[x+2][y-1]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x+2:true)&&(cond_col!=-1?cond_col==y-1:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x+2][y-1],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x+2][y-1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x-2)<8&&(y+1)<8&&(board[x-2][y+1]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x-2:true)&&(cond_col!=-1?cond_col==y+1:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x-2][y+1],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x-2][y+1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x-2)<8&&(y-1)<8&&(board[x-2][y-1]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x-2:true)&&(cond_col!=-1?cond_col==y-1:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x-2][y-1],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x-2][y-1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x+1)<8&&(y+2)<8&&(board[x+1][y+2]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x+1:true)&&(cond_col!=-1?cond_col==y+2:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x+1][y+2],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x+1][y+2],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x+1)<8&&(y-2)<8&&(board[x+1][y-2]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x+1:true)&&(cond_col!=-1?cond_col==y-2:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x+1][y-2],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x+1][y-2],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x-1)<8&&(y+2)<8&&(board[x-1][y+2]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x-1:true)&&(cond_col!=-1?cond_col==y+2:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x-1][y+2],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x-1][y+2],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}
                    if((x-1)<8&&(y-2)<8&&(board[x-1][y-2]==((color=='W')?'N':'n'))&&(cond_row!=-1?cond_row==x-1:true)&&(cond_col!=-1?cond_col==y-2:true)){temp=board[x][y];board[x][y]=' ';
                        swap(board[x-1][y-2],board[x][y]);
                        if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x-1][y-2],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                        return true;}   
                    return false;    
                }
                if(move[0]=='B')
                {
                    for(i=1;i<8;i++)
                    {
                        if(x+i<8&&y+i<8&&board[x+i][y+i]==((color=='W')?'B':'b'))
                        {
                            if(clearance(board,x,y,x+i,y+i)&&(cond_row!=-1?cond_row==x+i:true)&&(cond_col!=-1?cond_col==y+i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x+i][y+i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x+i][y+i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x+i<8&&y-i>=0&&board[x+i][y-i]==((color=='W')?'B':'b')&&(cond_row!=-1?cond_row==x+i:true)&&(cond_col!=-1?cond_col==y-i:true))
                        {
                            if(clearance(board,x,y,x+i,y-i)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x+i][y-i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x+i][y-i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x-i>=0&&y+i<8&&board[x-i][y+i]==((color=='W')?'B':'b')&&(cond_row!=-1?cond_row==x-i:true)&&(cond_col!=-1?cond_col==y+i:true))
                        {
                            if(clearance(board,x,y,x-i,y+i)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x-i][y+i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x-i][y+i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x+i>=0&&y+i>=0&&board[x-i][y-i]==((color=='W')?'B':'b')&&(cond_row!=-1?cond_row==x-i:true)&&(cond_col!=-1?cond_col==y-i:true))
                        {
                            if(clearance(board,x,y,x-i,y-i)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x-i][y-i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x-i][y-i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                    }
                    return false;
                }
                if(move[0]=='Q')
                {
                    for(i=0;i<8;i++)
                    {
                        if(i!=x&&board[i][y]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,i,y)&&(cond_row!=-1?cond_row==i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[i][y]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[i][y]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(i!=y&&board[x][i]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,x,i)&&(cond_col!=-1?cond_col==i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x][i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x][i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                    }
                    for(i=1;i<8;i++)
                    {
                        if(x+i<8&&y+i<8&&board[x+i][y+i]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,x+i,y+i)&&(cond_row!=-1?cond_row==x+i:true)&&(cond_col!=-1?cond_col==y+i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x+i][y+i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x+i][y+i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x+i<8&&y-i>=0&&board[x+i][y-i]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,x+i,y-i)&&(cond_row!=-1?cond_row==x+i:true)&&(cond_col!=-1?cond_col==y-i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x+i][y-i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x+i][y-i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x-i>=0&&y+i<8&&board[x-i][y+i]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,x-i,y+i)&&(cond_row!=-1?cond_row==x-i:true)&&(cond_col!=-1?cond_col==y+i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x-i][y+i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x-i][y+i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                        if(x+i>=0&&y+i>=0&&board[x-i][y-i]==((color=='W')?'Q':'q'))
                        {
                            if(clearance(board,x,y,x-i,y-i)&&(cond_row!=-1?cond_row==x-i:true)&&(cond_col!=-1?cond_col==y-i:true)){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x][y],board[x-i][y-i]);
                                if(checked(board,color,k_pos[(color=='W'?0:1)][0],k_pos[(color=='W'?0:1)][1])){
                                    swap(board[x][y],board[x-i][y-i]);
                                    board[x][y]=temp;
                                    return false;}
                                return true;}
                        }
                    }
                    return false;
                }
                if(move[0]=='K')
                {
                    if(board[x+1][y+1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[x+1][y+1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[x+1][y+1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x+1][y]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')+1][move[2]-'a']);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0'+1)][move[2]-'a']);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x][y+1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')][move[2]-'a'+1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0')][move[2]-'a'+1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x-1][y-1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')-1][move[2]-'a'-1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0'-1)][move[2]-'a'-1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x-1][y]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')-1][move[2]-'a']);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0'-1)][move[2]-'a']);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x][y-1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')][move[2]-'a'-1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0')][move[2]-'a'-1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x-1][y+1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')-1][move[2]-'a'+1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0')][move[2]-'a'+1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}
                    if(board[x+1][y-1]==((color=='W')?'K':'k')){
                        temp=board[x][y];
                        board[x][y]=' ';
                        swap(board[x][y],board[8-(move[3]-'0')+1][move[2]-'a'-1]);
                        if(checked(board,color,x,y)){
                            swap(board[x][y],board[8-(move[3]-'0'+1)][move[2]-'a'-1]);
                            board[x][y]=temp;
                            return false;}
                        castle[(color=='W')?0:1][0]=false;
                        k_pos[(color=='W'?0:1)][0]=x,k_pos[(color=='W'?0:1)][1]=y;
                        return true;}    
                }
                if(move[0]>='a'&&move[0]<='h')
                {
                    if(move[0]+1==move[2])
                    {
                        if(color=='W')
                        {
                            if(board[x+1][y-1]=='P'){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x+1][y-1],board[x][y]);
                                if(checked(board,'W',k_pos[0][0],k_pos[0][1])){
                                    swap(board[x+1][y-1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                                if(move[3]=='8')
                                {
                                    cout<<"What would you like to promote to? (Q/R/B/N)"<<endl;
                                    cin>>board[x][y];
                                }    
                                return true;}
                            return false;    
                        }
                        else if(color=='B')
                        {
                            if(board[x-1][y-1]=='p'){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x-1][y-1],board[x][y]);
                                if(checked(board,'B',k_pos[1][0],k_pos[1][1])){
                                    swap(board[x-1][y-1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                                if(move[3]=='1')
                                {
                                    char temp;
                                    cout<<"What would you like to promote to? (Q/R/B/N)"<<endl;
                                    cin>>temp;
                                    board[x][y]=temp+('a'-'A');
                                }    
                                return true;}
                            return false;
                        }
                    }
                    if(move[0]-1==move[2])
                    {
                        if(color=='W')
                        {
                            if(board[x+1][y+1]=='P'){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x+1][y+1],board[x][y]);
                                if(checked(board,'W',k_pos[0][0],k_pos[0][1])){
                                    swap(board[x+1][y+1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                                if(move[3]=='8')
                                {
                                    cout<<"What would you like to promote to? (Q/R/B/N)"<<endl;
                                    cin>>board[x][y];
                                }     
                                return true;}
                            return false;
                        }
                        else if(color=='B')
                        {
                            if(board[x-1][y+1]=='p'){
                                temp=board[x][y];
                                board[x][y]=' ';
                                swap(board[x-1][y+1],board[x][y]);
                                if(checked(board,'B',k_pos[1][0],k_pos[1][1])){
                                    swap(board[x-1][y+1],board[x][y]);
                                    board[x][y]=temp;
                                    return false;}
                                if(move[3]=='1')
                                {
                                    char temp;
                                    cout<<"What would you like to promote to? (Q/R/B/N)"<<endl;
                                    cin>>temp;
                                    board[x][y]=temp+('a'-'A');
                                }     
                                return true;}
                            return false;
                        }
                    }
                }
            }
            else if(board[x][y]==' '&&move[0]>='a'&&move[0]<='h')
            {
                string tempo=game.back();
                if(tempo.length()==2&&board[x+((color=='W')?1:-1)][y]==((color=='W')?'p':'P')&&tempo[0]==move[2]&&tempo[1]==move[3]+((color=='W')?-1:1)&&(move[0]-tempo[0]==1||move[0]-tempo[0]==-1)&&tempo[1]==((color=='W')?'5':'4'))
                {
                    swap(board[x][y],board[x+((color=='W')?1:-1)][y]);
                    return move_4(move,board,color,castle,k_pos,game);
                }
            }
            return false;
        }
        return false;
}
bool move_5(string move,char board[8][8],char color,bool castle[2][3],int k_pos[2][2])
{
    if((move[0]=='O'||move[0]=='0')&&move[1]=='-'&&(move[2]=='O'||move[2]=='0')&&move[3]=='-'&&(move[4]=='O'||move[4]=='0'))
        {
            if(color=='W')
            {
                if(board[7][4]=='K'&&board[7][0]=='R'&&(castle[0][0]&&castle[0][2])&&clearance(board,7,4,7,0)&&!checked(board,'W',7,4)&&!checked(board,'W',7,3)&&!checked(board,'W',7,2))
                {
                    swap(board[7][4],board[7][2]);
                    swap(board[7][0],board[7][3]);
                    if(!checked(board,'W',7,2))
                    {
                        for(int i=0;i<3;i++)
                            castle[0][i]=false;
                        return true;
                    } 
                    swap(board[7][4],board[7][2]);
                    swap(board[7][0],board[7][3]);
                }
                return false;
            }
            else if(color=='B')
            {
                if(board[0][4]=='k'&&board[0][0]=='r'&&(castle[1][0]&&castle[1][2])&&clearance(board,0,4,0,0)&&!checked(board,'B',0,4)&&!checked(board,'B',0,3)&&!checked(board,'B',0,2))
                {
                    swap(board[0][4],board[0][2]);
                    swap(board[0][0],board[0][3]);
                    if(!checked(board,'B',0,2))
                    {
                        for(int i=0;i<3;i++)
                            castle[1][i]=false;
                        return true;
                    }
                    swap(board[0][4],board[0][2]);
                    swap(board[0][0],board[0][3]);
                }
                return false;
            }
        }
}
bool validate(string move,char board[8][8],char color,bool castle[2][3],int k_pos[2][2],deque<string> game)
{
    if(move.length()==2)
        return move_2(move,board,color,castle,k_pos);
    else if(move.length()==3)
        return move_3(move,board,color,castle,k_pos);
    else if(move.length()==4)
    {
        if(move[1]=='x')
            return move_4(move,board,color,castle,k_pos,game);
        else
        {
            string temp="";
            temp = temp+(move[0])+(move[2])+(move[3]);
            if(move[1]>='a'&&move[1]<='h')
                return move_3(temp,board,color,castle,k_pos,-1,move[1]-'a');
            else if(move[1]>='1'&&move[1]<='8')
                return move_3(temp,board,color,castle,k_pos,8-(move[1]-'0'),-1);
        }
    }
    else if(move.length()==5)
    {
        if(move=="0-0-0"||move=="O-O-O")
            return move_5(move,board,color,castle,k_pos);
        else if(move[2]=='x')
        {
            string temp="";
            temp = temp+(move[0])+(move[2])+(move[3])+(move[4]);
            if(move[1]>='a'&&move[1]<='h')
                return move_4(temp,board,color,castle,k_pos,game,-1,move[1]-'a');
            else if(move[1]>='1'&&move[1]<='8')
                return move_4(temp,board,color,castle,k_pos,game,8-(move[1]-'0'),-1);
        }
    }
    else
        return false;
}
bool check_mate(char board[8][8],char color,int k_pos[2][2])
{
    int i,j,k,l;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(1)
            {
                if(board[i][j]==((color=='W')?'P':'p'))
                {
                    if(board[i-1][j]==' ')
                    {
                        swap(board[i][j],board[i-1][j]);
                        if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                        {
                            swap(board[i][j],board[i-1][j]);
                            return false;
                        }
                        swap(board[i][j],board[i-1][j]);
                    }
                    if(i==6&&board[i-1][j]==' '&&board[i-2][j]==' ')
                    {
                        swap(board[i][j],board[i-2][j]);
                        if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                        {
                            swap(board[i][j],board[i-2][j]);
                            return false;
                        }
                        swap(board[i][j],board[i-2][j]);
                    }
                    if(i!=0&&j!=0&&(board[i-1][j-1]==((color=='W')?'p':'P')||board[i-1][j-1]==((color=='W')?'n':'N')||board[i-1][j-1]==((color=='W')?'b':'B')||board[i-1][j-1]==((color=='W')?'r':'R')||board[i-1][j-1]==((color=='W')?'q':'Q')))
                    {
                        char temp = board[i-1][j-1];
                        board[i-1][j-1]=' ';
                        swap(board[i][j],board[i-1][j-1]);
                        if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                        {
                            swap(board[i][j],board[i-1][j-1]);
                            board[i-1][j-1]=temp;
                            return false;
                        }
                        swap(board[i][j],board[i-1][j-1]);
                        board[i-1][j-1]=temp;
                    }
                    if(i!=0&&j!=7&&(board[i-1][j+1]==((color=='W')?'p':'P')||board[i-1][j+1]==((color=='W')?'n':'N')||board[i-1][j+1]==((color=='W')?'b':'B')||board[i-1][j+1]==((color=='W')?'r':'R')||board[i-1][j+1]==((color=='W')?'q':'Q')))
                    {
                        char temp = board[i-1][j+1];
                        board[i-1][j+1]=' ';
                        swap(board[i][j],board[i-1][j+1]);
                        if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                        {
                            swap(board[i][j],board[i-1][j+1]);
                            board[i-1][j+1]=temp;
                            return false;
                        }
                        swap(board[i][j],board[i-1][j+1]);
                        board[i-1][j+1]=temp;
                    }
                }
                else if(board[i][j]==((color=='W')?'R':'r'))
                {
                    for(int k=0;k<7;k++)
                    {
                        if(board[k][j]==' '&&k!=i&&clearance(board,i,j,k,j))
                        {
                            swap(board[i][j],board[k][j]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[k][j]);
                                return false;
                            }
                            swap(board[i][j],board[k][j]);
                        }
                        if(board[i][k]==' '&&k!=j&&clearance(board,i,j,i,k))
                        {
                            swap(board[i][j],board[i][k]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[i][k]);
                                return false;
                            }
                            swap(board[i][j],board[i][k]);
                        }
                        if(((board[k][j]==(color=='W')?'p':'P')||(board[k][j]==(color=='W')?'n':'N')||(board[k][j]==(color=='W')?'b':'B')||(board[k][j]==(color=='W')?'r':'R')||(board[k][j]==(color=='W')?'q':'Q'))&&clearance(board,i,j,k,j))
                        {
                            char temp = board[k][j];
                            board[k][j]=' ';
                            swap(board[i][j],board[k][j]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[k][j]);
                                board[k][j]=temp;
                                return false;
                            }
                            swap(board[i][j],board[k][j]);
                            board[k][j]=temp;
                        }
                        if(((board[i][k]==(color=='W')?'p':'P')||(board[i][k]==(color=='W')?'n':'N')||(board[i][k]==(color=='W')?'b':'B')||(board[i][k]==(color=='W')?'r':'R')||(board[i][k]==(color=='W')?'q':'Q'))&&clearance(board,i,j,i,k))
                        {
                            char temp = board[i][k];
                            board[i][k]=' ';
                            swap(board[i][j],board[i][k]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[i][k]);
                                board[i][k]=temp;
                                return false;
                            }
                            swap(board[i][j],board[i][k]);
                            board[i][k]=temp;
                        }
                    }
                }
                else if(board[i][j]==((color=='W')?'N':'n'))
                {
                    int t[2][2]={{2,-2},{1,-1}};
                    for(k=0;k<2;k++)
                    {
                        for(l=0;l<2;l++)
                        {
                            if(i+t[0][k]<8&&i+t[0][k]>=0&&j+t[1][l]<8&&j+t[1][l]>=0&&(board[i+t[0][k]][j+t[1][l]]==' '))
                            {
                                swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                                {
                                    swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                                    return false;
                                }
                                swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                            }
                            else if(i+t[1][k]<8&&i+t[1][k]>=0&&j+t[0][l]<8&&j+t[0][l]>=0&&(board[i+t[1][k]][j+t[0][l]]==' '))
                            {
                                swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                                {
                                    swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                                    return false;
                                }
                                swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                            }
                            else if(i+t[0][k]<8&&i+t[0][k]>=0&&j+t[1][l]<8&&j+t[1][l]>=0&&(board[i+t[0][k]][j+t[1][l]]==(color=='W')?'p':'P'||board[i+t[0][k]][j+t[1][l]]==(color=='W')?'n':'N'||board[i+t[0][k]][j+t[1][l]]==(color=='W')?'b':'B'||board[i+t[0][k]][j+t[1][l]]==(color=='W')?'r':'R'||board[i+t[0][k]][j+t[1][l]]==(color=='W')?'q':'Q'))
                            {
                                char temp = board[i+t[0][k]][j+t[1][k]];
                                board[i+t[0][k]][j+t[1][k]]=' ';
                                swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                                {
                                    swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                                    board[i+t[0][k]][j+t[1][k]]=temp;
                                    return false;
                                }
                                swap(board[i+t[0][k]][j+t[1][k]],board[i][j]);
                                board[i+t[0][k]][j+t[1][k]]=temp;
                            }
                            else if(i+t[1][k]<8&&i+t[1][k]>=0&&j+t[0][l]<8&&j+t[0][l]>=0&&(board[i+t[1][k]][j+t[0][l]]==(color=='W')?'p':'P'||board[i+t[1][k]][j+t[0][l]]==(color=='W')?'n':'N'||board[i+t[1][k]][j+t[0][l]]==(color=='W')?'b':'B'||board[i+t[1][k]][j+t[0][l]]==(color=='W')?'r':'R'||board[i+t[1][k]][j+t[0][l]]==(color=='W')?'q':'Q'))
                            {
                                char temp = board[i+t[1][k]][j+t[0][k]];
                                board[i+t[1][k]][j+t[0][k]]=' ';
                                swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                                {
                                    swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                                    board[i+t[1][k]][j+t[0][k]]=temp;
                                    return false;
                                }
                                swap(board[i+t[1][k]][j+t[0][k]],board[i][j]);
                                board[i+t[1][k]][j+t[0][k]]=temp;
                            }
                        }
                    }    
                }
                else if(board[i][j]==((color=='W')?'B':'b'))
                {
                    for(k=1;k<8;k++)
                    {
                        if(i+k<8&&j+k<8&&board[i+k][j+k]==' ')
                        {
                            if(clearance(board,i,j,i+k,j+k)){
                                swap(board[i][j],board[i+k][j+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i+k][j+k]);
                                    return false;}
                                swap(board[i][j],board[i+k][j+k]);    
                            }
                        }
                        if(i+k<8&&j-k>=0&&board[i+k][j-k]==' ')
                        {
                            if(clearance(board,i,j,i+k,j-k)){
                                swap(board[i][j],board[i+k][j-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i+k][j-k]);
                                    return false;}
                                swap(board[i][j],board[i+k][j-k]);    
                            }
                        }
                        if(i-k>=0&&j+k<8&&board[i-k][j+k]==' ')
                        {
                            if(clearance(board,i,j,i-k,j+k)){
                                swap(board[i][j],board[i-k][j+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i-k][j+k]);
                                    return false;}
                                swap(board[i][j],board[i-k][j+k]);    
                            }
                        }
                        if(i-k>=0&&j-k>=0&&board[i-k][j-k]==' ')
                        {
                            if(clearance(board,i,j,i-k,j-k)){
                                swap(board[i][j],board[i-k][j-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i-k][j-k]);
                                    return false;}
                                swap(board[i][j],board[i-k][j-k]);    
                            }
                        }
                        if(i+k<8&&j+k<8&&(board[i+k][j+k]==(color=='W')?'p':'P'||board[i+k][j+k]==(color=='W')?'n':'N'||board[i+k][j+k]==(color=='W')?'b':'B'||board[i+k][j+k]==(color=='W')?'r':'R'||board[i+k][j+k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,i,j,i+k,j+k)){
                                char temp=board[i+k][j+k];
                                board[i+k][j+k]=' ';
                                swap(board[i][j],board[i+k][j+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i+k][j+k]);
                                    board[i+k][j+k]=temp;
                                    return false;}
                                swap(board[i][j],board[i+k][j+k]);   
                                board[i+k][j+k]=temp;
                            }
                        }
                        if(i+k<8&&j-k>=0&&(board[i+k][j-k]==(color=='W')?'p':'P'||board[i+k][j-k]==(color=='W')?'n':'N'||board[i+k][j-k]==(color=='W')?'b':'B'||board[i+k][j-k]==(color=='W')?'r':'R'||board[i+k][j-k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,i,j,i+k,j-k)){
                                char temp=board[i+k][j-k];
                                board[i+k][j-k]=' ';
                                swap(board[i][j],board[i+k][j-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i+k][j-k]);
                                    board[i+k][j-k]=temp;
                                    return false;}
                                swap(board[i][j],board[i+k][j-k]);    
                                board[i+k][j-k]=temp;
                            }
                        }
                        if(i-k>=0&&j+k<8&&(board[i-k][j+k]==(color=='W')?'p':'P'||board[i-k][j+k]==(color=='W')?'n':'N'||board[i-k][j+k]==(color=='W')?'b':'B'||board[i-k][j+k]==(color=='W')?'r':'R'||board[i-k][j+k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,i,j,i-k,j+k)){
                                char temp=board[i-k][j+k];
                                board[i-k][j+k]=' ';
                                swap(board[i][j],board[i-k][j+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i-k][j+k]);
                                    board[i-k][j+k]=temp;
                                    return false;}
                                swap(board[i][j],board[i-k][j+k]);  
                                board[i-k][j+k]=temp;
                            }
                        }
                        if(i-k>=0&&j-k>=0&&(board[i-k][j-k]==(color=='W')?'p':'P'||board[i-k][j-k]==(color=='W')?'n':'N'||board[i-k][j-k]==(color=='W')?'b':'B'||board[i-k][j-k]==(color=='W')?'r':'R'||board[i-k][j-k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,i,j,i-k,j-k)){
                                char temp=board[i-k][j-k];
                                board[i-k][j-k]=' ';
                                swap(board[i][j],board[i-k][j-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[i][j],board[i-k][j-k]);
                                    board[i-k][j-k]=temp;
                                    return false;}
                                swap(board[i][j],board[i-k][j-k]); 
                                board[i-k][j-k]=temp;
                            }
                        }
                    }
                }
                else if(board[i][j]==((color=='W')?'Q':'q'))
                {
                    int yolo=256;
                    for(k=0;k<7;k++)
                    {
                        if(board[k][j]==' '&&k!=i&&clearance(board,i,j,k,j))
                        {
                            swap(board[i][j],board[k][j]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[k][j]);
                                return false;
                            }
                            swap(board[i][j],board[k][j]);
                        }
                        if(board[i][k]==' '&&k!=j&&clearance(board,i,j,i,k))
                        {
                            swap(board[i][j],board[i][k]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[i][k]);
                                return false;
                            }
                            swap(board[i][j],board[i][k]);
                        }
                        if((board[k][j]==(color=='W')?'p':'P')||(board[k][j]==(color=='W')?'n':'N')||(board[k][j]==(color=='W')?'b':'B')||(board[k][j]==(color=='W')?'r':'R')||(board[k][j]==(color=='W')?'q':'Q')&&clearance(board,i,j,k,j))
                        {
                            char temp = board[k][j];
                            board[k][j]=' ';
                            swap(board[i][j],board[k][j]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[k][j]);
                                board[k][j]=temp;
                                return false;
                            }
                            swap(board[i][j],board[k][j]);
                            board[k][j]=temp;
                        }
                        if((board[i][k]==(color=='W')?'p':'P')||(board[i][k]==(color=='W')?'n':'N')||(board[i][k]==(color=='W')?'b':'B')||(board[i][k]==(color=='W')?'r':'R')||(board[i][k]==(color=='W')?'q':'Q')&&clearance(board,i,j,i,k))
                        {
                            char temp = board[i][k];
                            board[i][k]=' ';
                            swap(board[i][j],board[i][k]);
                            if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1]))
                            {
                                swap(board[i][j],board[i][k]);
                                board[i][k]=temp;
                                return false;
                            }
                            swap(board[i][j],board[i][k]);
                            board[i][k]=temp;
                        }
                    }
                    for(k=1;k<8;k++)
                    {
                        int x=i,y=k;
                        if(x+k<8&&y+k<8&&board[x+k][y+k]==' ')
                        {
                            if(clearance(board,x,y,x+k,y+k)){
                                swap(board[x][y],board[x+k][y+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x+k][y+k]);
                                    return false;}
                                swap(board[x][y],board[x+k][y+k]);    
                            }
                        }
                        if(x+k<8&&y-k>=0&&board[x+k][y-k]==' ')
                        {
                            if(clearance(board,x,y,x+k,y-k)){
                                swap(board[x][y],board[x+k][y-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x+k][y-k]);
                                    return false;}
                                swap(board[x][y],board[x+k][y-k]);    
                            }
                        }
                        if(x-k>=0&&y+k<8&&board[x-k][y+k]==' ')
                        {
                            if(clearance(board,x,y,x-k,y+k)){
                                swap(board[x][y],board[x-k][y+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x-k][y+k]);
                                    return false;}
                                swap(board[x][y],board[x-k][y+k]);    
                            }
                        }
                        if(x-k>=0&&y-k>=0&&board[x-k][y-k]==' ')
                        {
                            if(clearance(board,x,y,x-k,y-k)){
                                swap(board[x][y],board[x-k][y-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x-k][y-k]);
                                    return false;}
                                swap(board[x][y],board[x-k][y-k]);    
                            }
                        }
                        if(x+k<8&&y+k<8&&(board[x+k][y+k]==(color=='W')?'p':'P'||board[x+k][y+k]==(color=='W')?'n':'N'||board[x+k][y+k]==(color=='W')?'b':'B'||board[x+k][y+k]==(color=='W')?'r':'R'||board[x+k][y+k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,x,y,x+k,y+k)){
                                char temp=board[x+k][y+k];
                                board[x+k][y+k]=' ';
                                swap(board[x][y],board[x+k][y+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x+k][y+k]);
                                    board[x+k][y+k]=temp;
                                    return false;}
                                swap(board[x][y],board[x+k][y+k]);   
                                board[x+k][y+k]=temp;
                            }
                        }
                        if(x+k<8&&y-k>=0&&(board[x+k][y-k]==(color=='W')?'p':'P'||board[x+k][y-k]==(color=='W')?'n':'N'||board[x+k][y-k]==(color=='W')?'b':'B'||board[x+k][y-k]==(color=='W')?'r':'R'||board[x+k][y-k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,x,y,x+k,y-k)){
                                char temp=board[x+k][y-k];
                                board[x+k][y-k]=' ';
                                swap(board[x][y],board[x+k][y-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x+k][y-k]);
                                    board[x+k][y-k]=temp;
                                    return false;}
                                swap(board[x][y],board[x+k][y-k]);    
                                board[x+k][y-k]=temp;
                            }
                        }
                        if(x-k>=0&&y+k<8&&(board[x-k][y+k]==(color=='W')?'p':'P'||board[x-k][y+k]==(color=='W')?'n':'N'||board[x-k][y+k]==(color=='W')?'b':'B'||board[x-k][y+k]==(color=='W')?'r':'R'||board[x-k][y+k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,x,y,x-k,y+k)){
                                char temp=board[x-k][y+k];
                                board[x-k][y+k]=' ';
                                swap(board[x][y],board[x-k][y+k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x-k][y+k]);
                                    board[x-k][y+k]=temp;
                                    return false;}
                                swap(board[x][y],board[x-k][y+k]);  
                                board[x-k][y+k]=temp;
                            }
                        }
                        if(x-k>=0&&y-k>=0&&(board[x-k][y-k]==(color=='W')?'p':'P'||board[x-k][y-k]==(color=='W')?'n':'N'||board[x-k][y-k]==(color=='W')?'b':'B'||board[x-k][y-k]==(color=='W')?'r':'R'||board[x-k][y-k]==(color=='W')?'q':'Q'))
                        {
                            if(clearance(board,x,y,x-k,y-k)){
                                char temp=board[x-k][y-k];
                                board[x-k][y-k]=' ';
                                swap(board[x][y],board[x-k][y-k]);
                                if(!checked(board,color,k_pos[(color=='W')?0:1][0],k_pos[(color=='W')?0:1][1])){
                                    swap(board[x][y],board[x-k][y-k]);
                                    board[x-k][y-k]=temp;
                                    return false;}
                                swap(board[x][y],board[x-k][y-k]); 
                                board[x-k][y-k]=temp;
                            }
                        }
                    }
                }
                else if(board[i][j]==((color=='W')?'K':'k'))
                {
                    if(i!=7&&j!=7&&board[i+1][j+1]==' '){
                        swap(board[i][j],board[i+1][j+1]);
                        if(!checked(board,color,i+1,j+1)){
                            swap(board[i][j],board[i+1][j+1]);
                            return false;}
                        swap(board[i][j],board[i+1][j+1]);    
                    }
                    if(i!=7&&board[i+1][j]==' '){
                        swap(board[i][j],board[i+1][j]);
                        if(!checked(board,color,i+1,j)){
                            swap(board[i][j],board[i+1][j]);
                            return false;}
                        swap(board[i][j],board[i+1][j]);    
                    }
                    if(j!=7&&board[i][j+1]==' '){
                        swap(board[i][j],board[i][j+1]);
                        if(!checked(board,color,i,j+1)){
                            swap(board[i][j],board[i][j+1]);
                            return false;}
                        swap(board[i][j],board[i][j+1]);    
                    }
                    if(i!=0&&j!=0&&board[i-1][j-1]==' '){
                        swap(board[i][j],board[i-1][j-1]);
                        if(!checked(board,color,i-1,j-1)){
                            swap(board[i][j],board[i-1][j-1]);
                            return false;}
                        swap(board[i][j],board[i-1][j-1]);    
                    }
                    if(i!=0&&board[i-1][j]==' '){
                        swap(board[i][j],board[i-1][j]);
                        if(!checked(board,color,i-1,j)){
                            swap(board[i][j],board[i-1][j]);
                            return false;}
                        swap(board[i][j],board[i-1][j]);    
                    }
                    if(j!=0&&board[i][j-1]==' '){
                        swap(board[i][j],board[i][j-1]);
                        if(!checked(board,color,i,j-1)){
                            swap(board[i][j],board[i][j-1]);
                            return false;}
                        swap(board[i][j],board[i][j-1]);    
                    }
                    if(i!=0&&j!=7&&board[i-1][j+1]==' '){
                        swap(board[i][j],board[i-1][j+1]);
                        if(!checked(board,color,i-1,j+1)){
                            swap(board[i][j],board[i-1][j+1]);
                            return false;}
                        swap(board[i][j],board[i-1][j+1]);    
                    }
                    if(i!=7&&j!=0&&board[i+1][j-1]==' '){
                        swap(board[i][j],board[i+1][j-1]);
                        if(!checked(board,color,i+1,j-1)){
                            swap(board[i][j],board[i+1][j-1]);
                            return false;}
                        swap(board[i][j],board[i+1][j-1]);    
                    }
                    //-------//
                    if((i!=7&&j!=7)&&(board[i+1][j+1]==((color=='W')?'p':'P')||board[i+1][j+1]==((color=='W')?'n':'N')||board[i+1][j+1]==((color=='W')?'b':'B')||board[i+1][j+1]==((color=='W')?'r':'R')||board[i+1][j+1]==((color=='W')?'q':'Q'))){
                        int temp = board[i+1][j+1];
                        board[i+1][j+1]=' ';
                        swap(board[i][j],board[i+1][j+1]);
                        if(!checked(board,color,i+1,j+1)){
                            swap(board[i][j],board[i+1][j+1]);
                            board[i+1][j+1]=temp;
                            return false;}
                        swap(board[i][j],board[i+1][j+1]);  
                        board[i+1][j+1]=temp;
                    }
                    if((i!=7)&&(board[i+1][j]==((color=='W')?'p':'P')||board[i+1][j]==((color=='W')?'n':'N')||board[i+1][j]==((color=='W')?'b':'B')||board[i+1][j]==((color=='W')?'r':'R')||board[i+1][j]==((color=='W')?'q':'Q'))){
                        int temp = board[i+1][j];
                        board[i+1][j]=' ';
                        swap(board[i][j],board[i+1][j]);
                        if(!checked(board,color,i+1,j)){
                            swap(board[i][j],board[i+1][j]);
                            board[i+1][j]=temp;
                            return false;}
                        swap(board[i][j],board[i+1][j]);  
                        board[i+1][j]=temp;
                    }
                    if((j!=7)&&(board[i][j+1]==((color=='W')?'p':'P')||board[i][j+1]==((color=='W')?'n':'N')||board[i][j+1]==((color=='W')?'b':'B')||board[i][j+1]==((color=='W')?'r':'R')||board[i][j+1]==((color=='W')?'q':'Q'))){
                        int temp = board[i][j+1];
                        board[i][j+1]=' ';
                        swap(board[i][j],board[i][j+1]);
                        if(!checked(board,color,i,j+1)){
                            swap(board[i][j],board[i][j+1]);
                            board[i][j+1]=temp;
                            return false;}
                        swap(board[i][j],board[i][j+1]);  
                        board[i][j+1]=temp;
                    }
                    if((i!=0&&j!=0)&&(board[i-1][j-1]==((color=='W')?'p':'P')||board[i-1][j-1]==((color=='W')?'n':'N')||board[i-1][j-1]==((color=='W')?'b':'B')||board[i-1][j-1]==((color=='W')?'r':'R')||board[i-1][j-1]==((color=='W')?'q':'Q'))){
                        int temp = board[i-1][j-1];
                        board[i-1][j-1]=' ';
                        swap(board[i][j],board[i-1][j-1]);
                        if(!checked(board,color,i-1,j-1)){
                            swap(board[i][j],board[i-1][j-1]);
                            board[i-1][j-1]=temp;
                            return false;}
                        swap(board[i][j],board[i-1][j-1]);  
                        board[i-1][j-1]=temp;
                    }
                    if((i!=0)&&(board[i-1][j]==((color=='W')?'p':'P')||board[i-1][j]==((color=='W')?'n':'N')||board[i-1][j]==((color=='W')?'b':'B')||board[i-1][j]==((color=='W')?'r':'R')||board[i-1][j]==((color=='W')?'q':'Q'))){
                        int temp = board[i-1][j];
                        board[i-1][j]=' ';
                        swap(board[i][j],board[i-1][j]);
                        if(!checked(board,color,i-1,j)){
                            swap(board[i][j],board[i-1][j]);
                            board[i-1][j]=temp;
                            return false;}
                        swap(board[i][j],board[i-1][j]);  
                        board[i-1][j]=temp;
                    }
                    if((j!=0)&&(board[i][j-1]==((color=='W')?'p':'P')||board[i][j-1]==((color=='W')?'n':'N')||board[i][j-1]==((color=='W')?'b':'B')||board[i][j-1]==((color=='W')?'r':'R')||board[i][j-1]==((color=='W')?'q':'Q'))){
                        int temp = board[i][j-1];
                        board[i][j-1]=' ';
                        swap(board[i][j],board[i][j-1]);
                        if(!checked(board,color,i,j-1)){
                            swap(board[i][j],board[i][j-1]);
                            board[i][j-1]=temp;
                            return false;}
                        swap(board[i][j],board[i][j-1]);  
                        board[i][j-1]=temp;
                    }
                    if((i!=0&&j!=7)&&(board[i-1][j+1]==((color=='W')?'p':'P')||board[i-1][j+1]==((color=='W')?'n':'N')||board[i-1][j+1]==((color=='W')?'b':'B')||board[i-1][j+1]==((color=='W')?'r':'R')||board[i-1][j+1]==((color=='W')?'q':'Q'))){
                        int temp = board[i-1][j+1];
                        board[i-1][j+1]=' ';
                        swap(board[i][j],board[i-1][j+1]);
                        if(!checked(board,color,i-1,j+1)){
                            swap(board[i][j],board[i-1][j+1]);
                            board[i-1][j+1]=temp;
                            return false;}
                        swap(board[i][j],board[i-1][j+1]);  
                        board[i-1][j+1]=temp;
                    }
                    if((i!=7&&j!=0)&&(board[i+1][j-1]==((color=='W')?'p':'P')||board[i+1][j-1]==((color=='W')?'n':'N')||board[i+1][j-1]==((color=='W')?'b':'B')||board[i+1][j-1]==((color=='W')?'r':'R')||board[i+1][j-1]==((color=='W')?'q':'Q'))){
                        int temp = board[i+1][j-1];
                        board[i+1][j-1]=' ';
                        swap(board[i][j],board[i+1][j-1]);
                        if(!checked(board,color,i+1,j-1)){
                            swap(board[i][j],board[i+1][j-1]);
                            board[i+1][j-1]=temp;
                            return false;}
                        swap(board[i][j],board[i+1][j-1]);  
                        board[i+1][j-1]=temp;
                    }
                }
                else
                    continue;
            }
        }
    }
    return true;
}
struct cryo
{
    char b[8][8];
    bool c[2][3];
    int k[2][2];
};
void command_check(string move,deque<string> &game,deque<cryo> &game_board,char board[8][8],bool castle[2][3],int k_pos[2][2])
{
    int i,j;
    if(move=="p"||move=="P")
    {
        deque<string> temp = game;
        cout<<"The Game is >";
        while(!temp.empty())
        {
            cout<<">";
            cout<<temp.front();
            temp.pop_front();
        }
    }
    if(move=="u"||move=="U")
    {
        if(!game.empty()&&!game_board.empty())
        {
            game.pop_back();
            game_board.pop_back();
            if(!game.empty())
            {
                cryo temp = game_board.back();
                for(i=0;i<8;i++)
                    for(j=0;j<8;j++)
                        board[i][j] = temp.b[i][j];
                for(i=0;i<2;i++)
                    for(j=0;j<3;j++)
                        castle[i][j] = temp.c[i][j];
                for(i=0;i<2;i++)
                    for(j=0;j<2;j++)
                        k_pos[i][j] = temp.k[i][j];
            }            
            else
                initialize_board(board,castle);
        }
        else
        {
            cout<<"Invalid move, please enter again"<<endl;
        }
    }
}
int main()
{
    char board[8][8];
    bool castle[2][3];
    deque<string> game;
    deque<cryo> game_board;
    cryo temp;
    int k_pos[2][2]={{7,4},{0,4}},i,j;
    string move;
    initialize_board(board,castle);  
    display_board(board);
    cout<<endl<<endl;
    cout<<"Game Starts!"<<endl;
    while(1)
    {
        while(1)
        {
            cout<<"White to move: ";
            cin>>move;
            if(move.length()==1&&!game.empty())
            {
                command_check(move,game,game_board,board,castle,k_pos);
                if(move=="u"||move=="U")
                    break;
            }    
            else if(move.length()==1&&game.empty())
                cout<<"Commands not allowed on move 1"<<endl;
            else
            {
                if(validate(move,board,'W',castle,k_pos,game))
                    break;
                cout<<"Invalid move, please enter again"<<endl;   
            }
            cout<<endl;
        }    
        if(move.length()!=1)
        {
            game.push_back(move);
            for(i=0;i<8;i++)
                for(j=0;j<8;j++)
                    temp.b[i][j]=board[i][j];
            for(i=0;i<2;i++)
                for(j=0;j<3;j++)
                    temp.c[i][j]=castle[i][j];
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    temp.k[i][j] = k_pos[i][j];        
            game_board.push_back(temp);
        }         
        cout<<"Success!"<<endl;  
        display_board(board);
        if(checked(board,'B',k_pos[1][0],k_pos[1][1])){
            if(check_mate(board,'B',k_pos)){
                cout<<"Black's King is Checkmated. White Wins!"<<endl;
                break;
            }
            cout<<"Black is in a check!";}
        else
        {
            if(check_mate(board,'B',k_pos)){
                cout<<"Black is Stalemated. The Game is a Draw!"<<endl;
                break;
            }
        }
            cout<<endl<<endl;
        while(1)
        {
            cout<<"Black to move: ";
            cin>>move;
            if(move.length()==1)
            {
                command_check(move,game,game_board,board,castle,k_pos);
                if(move=="u"||move=="U")
                    break;
            }    
            else
            {
                if(validate(move,board,'B',castle,k_pos,game))
                    break;
                cout<<"Invalid move, please enter again"<<endl;
            }    
            cout<<endl;
        }    
        if(move.length()!=1)
        {
            game.push_back(move);
            for(i=0;i<8;i++)
                for(j=0;j<8;j++)
                    temp.b[i][j]=board[i][j];
            for(i=0;i<2;i++)
                for(j=0;j<3;j++)
                    temp.c[i][j]=castle[i][j];
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    temp.k[i][j] = k_pos[i][j];        
            game_board.push_back(temp);
        }    
        cout<<"Success!"<<endl;
        display_board(board);
        if(checked(board,'W',k_pos[0][0],k_pos[0][1])){
            if(check_mate(board,'W',k_pos)){
                cout<<"White's King is Checkmated. Black Wins!"<<endl;
                break;
            }
            cout<<"White is in a check!";}
        else
        {
            if(check_mate(board,'W',k_pos)){
                cout<<"White is Stalemated. The Game is a Draw!"<<endl;
                break;
            }
        }    
            cout<<endl<<endl;
    }
    return 0;
}




