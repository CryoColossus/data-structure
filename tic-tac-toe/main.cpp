#include <iostream>
#include<time.h>
using namespace std;
void display_board(char board[3][3])
{
    cout<<"  "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<" 1"<<endl;
    cout<<" ---|---|--- "<<endl;
    cout<<"  "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<" 2"<<endl;
    cout<<" ---|---|--- "<<endl;
    cout<<"  "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<" 3"<<endl;
    cout<<"  A   B   C  "<<endl;
}
void declare_winner(char winner,bool s,char board[3][3])
{
    cout<<"The Board is:"<<endl<<endl;
    display_board(board);
    cout<<endl<<endl;
    if(winner=='-')
        cout<<"The game ends in a draw! Good Game!"<<endl;
    else if(winner=='X'&&s)
        cout<<"Congratulations!!! You won the Game!"<<endl;
    else if(winner=='X'&&!s)
        cout<<"Better Luck next time!"<<endl;
    else if(winner=='O'&&!s)
        cout<<"Congratulations!!! You won the Game!"<<endl;
    else if(winner=='O'&&s)
        cout<<"Better Luck next time!"<<endl;
}
void win_check(char board[3][3],char &winner)
{
    int i,j,check=false;
    for(i=0;i<3;i++)
    {
        char temp=board[i][0];
        if(temp==board[i][1]&&temp==board[i][2]&&temp!=' ')
        {
            winner=temp;
            return;
        }
        temp=board[0][i];
        if(temp==board[1][i]&&temp==board[2][i]&&temp!=' ')
        {
            winner=temp;
            return;
        }
    }
    if(board[0][0]==board[1][1]&&board[0][0]==board[2][2]&&board[0][0]!=' ')
    {
        winner=board[0][0];
        return;
    }    
    if(board[0][2]==board[1][1]&&board[0][2]==board[2][0]&&board[0][2]!=' ')
    {
        winner=board[0][2];
        return;
    }  
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(board[i][j]==' ')
                check=true;
    if(!check)
    {
        winner='-';
        return;
    }
}
void player_move(char board[3][3],bool s,int c)
{
    cout<<"The Board is:"<<endl<<endl;
    display_board(board);
    if(c==0)
        cout<<"Where would you like to play your move?"<<endl;
    else
        cout<<"Where would you like to play your move player "<<c<<"?"<<endl;
    string str;
    cin>>str;
    while(1)
    {
        if(str.length()==2&&(str[0]=='A'||str[0]=='B'||str[0]=='C')&&(str[1]=='1'||str[1]=='2'||str[1]=='3')&&board[str[1]-'0'-1][str[0]-'A']==' ')
        {
            board[str[1]-'0'-1][str[0]-'A'] = (s)?'X':'O';
            break;
        }   
        else if(str.length()==2&&(str[0]=='a'||str[0]=='b'||str[0]=='c')&&(str[1]=='1'||str[1]=='2'||str[1]=='3')&&board[str[1]-'0'-1][str[0]-'a']==' ')
        {
            board[str[1]-'0'-1][str[0]-'a'] = (s)?'X':'O';
            break;
        } 
        else
        {
            if(board[str[1]-'0'-1][str[0]-'A']!=' ')
                cout<<"Position already filled, pick another spot"<<endl;
            else    
                cout<<"Invalid Input, try again"<<endl;
            cin>>str;
        }
    }
}
void egenerate(char board[3][3],int &x,int &y,bool s)
{
    int count=0,i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(board[i][j]==' ')
                count++;
    int a[count][2],iter=0;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(board[i][j]==' ')
            {
                a[iter][0]=i;
                a[iter][1]=j;
                iter++;
            }    
    srand(time(0));
    int gen = rand()%count;
    if(count==1)
        gen=0;
    x=a[gen][0];
    y=a[gen][1];
}
void generate(char board[3][3],int &x,int &y,bool s)
{
    char sym = (s)?'O':'X';
    char asym = (s)?'X':'O';
    int counter,t=2;
    int i,j;
    while(t--)
    {
        for(i=0;i<3;i++)
        {
            counter=0;
            for(j=0;j<3;j++)
                if(board[i][j]==sym)
                    counter++;
                else if(board[i][j]==asym)
                    counter--;
            if(counter==2)
            {
                x=i;
                if(board[i][0]==' ')
                    y=0;
                else if(board[i][1]==' ')
                    y=1;
                else if(board[i][2]==' ')
                    y=2;
                cout<<endl;    
                return;    //1
            }
            counter=0;
            for(j=0;j<3;j++)
                if(board[j][i]==sym)
                    counter++;
                else if(board[j][i]==asym)
                    counter--;
            if(counter==2)
            {
                y=i;
                if(board[0][i]==' ')
                    x=0;
                else if(board[1][i]==' ')
                    x=1;
                else if(board[2][i]==' ')
                    x=2;
                cout<<endl;    
                return;    //2
            }
        }
        counter=0;
        for(j=0;j<3;j++)
            if(board[j][j]==sym)
                counter++;
            else if(board[j][j]==asym)
                counter--;
        if(counter==2)
        {
            if(board[0][0]==' ')
                x=0,y=0;
            else if(board[1][1]==' ')
                x=1,y=1;
            else if(board[2][2]==' ')
                x=2,y=2;
            cout<<endl;    
            return;    //3
        }    
        counter=0;
        for(j=0;j<3;j++)
            if(board[2-j][j]==sym)
                counter++;
            else if(board[2-j][j]==asym)
                counter--;
        if(counter==2)
        {
            if(board[2][0]==' ')
                x=2,y=0;
            else if(board[1][1]==' ')
                x=1,y=1;
            else if(board[0][2]==' ')
                x=0,y=2;
            cout<<endl;    
            return;    //4
        }
        char temp = sym;
        sym = asym;
        asym = temp;
    }
    egenerate(board,x,y,s);
}
void pgenerate(char board[3][3],int &x,int &y,bool s,int move)
{
    int m,n,i,j;
    char temp_board[3][3];
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            temp_board[i][j]=board[i][j];
    generate(temp_board,m,n,s);
    temp_board[m][n] = (s)?'O':'X';
    char w=' ';
    win_check(temp_board,w);
    if(w!=' ')
    {
        x=m;
        y=n;
        return;
    }
    temp_board[m][n] = (s)?'X':'O';
    w=' ';
    win_check(temp_board,w);
    if(w!=' ')
    {
        x=m;
        y=n;
        return;
    }
    srand(time(0));
    if(move==1)
    {
        int a[5][2]={{0,0},{0,2},{1,1},{2,0},{2,2}};
        int gen = rand()%5;
        x=a[gen][0];
        y=a[gen][1];
        return;
    }
    if(move==2)
    {
        if(board[1][1]==' ')
        {
            x=1,y=1;
            return;
        }    
        else
        {
            int a[4][2]={{0,0},{0,2},{2,0},{2,2}};
            int gen = rand()%4;
            x=a[gen][0];
            y=a[gen][1];
            return;
        }
    }
    if(move==3)
    {
        if(board[1][1]==((s)?'O':'X'))
        {
            if(board[0][0]==' '&&board[2][2]==' '&&board[2][0]==' '&&board[0][2]==' ')
            {
                int a[4][2]={{0,0},{0,2},{2,0},{2,2}};
                int gen = rand()%4;
                x=a[gen][0];
                y=a[gen][1];
                return;
            }
            else
            {
                int a[3][2],t=0;
                if(board[0][0]==' ')
                {
                    a[t][0]=0,a[t][1]=0;
                    t++;
                }  
                if(board[2][0]==' ')
                {
                    a[t][0]=2,a[t][1]=0;
                    t++;
                }
                if(board[0][2]==' ')
                {
                    a[t][0]=0,a[t][1]=2;
                    t++;
                } 
                if(board[2][2]==' ')
                {
                    a[t][0]=2,a[t][1]=2;
                    t++;
                } 
                int gen = rand()%4;
                x=a[gen][0];
                y=a[gen][1];
                return;
            }
        }
        else
        {
            if(board[1][1]==((s)?'X':'O'))
            {
                if(board[0][0]==((s)?'O':'X'))
                {
                    x=2,y=2;
                    return;
                }
                if(board[0][2]==((s)?'O':'X'))
                {
                    x=2,y=0;
                    return;
                }
                if(board[2][0]==((s)?'O':'X'))
                {
                    x=0,y=2;
                    return;
                }
                if(board[2][2]==((s)?'O':'X'))
                {
                    x=0,y=0;
                    return;
                }
            }
            else
            {
                if(board[0][0]==((s)?'X':'O')||board[2][0]==((s)?'X':'O')||board[0][2]==((s)?'X':'O')||board[2][2]==((s)?'X':'O'))
                {
                    int a[2][2],t=0;
                    if(board[0][0]==' ')
                    {
                        a[t][0]=0,a[t][1]=0;
                        t++;
                    }  
                    if(board[2][0]==' ')
                    {
                        a[t][0]=2,a[t][1]=0;
                        t++;
                    }
                    if(board[0][2]==' ')
                    {
                        a[t][0]=0,a[t][1]=2;
                        t++;
                    } 
                    if(board[2][2]==' ')
                    {
                        a[t][0]=2,a[t][1]=2;
                        t++;
                    }
                    int gen = rand()%2;
                    x=a[gen][0];
                    y=a[gen][1];
                    return;
                }
                else
                {
                    int i,j,x1,y1,x2,y2;
                    for(i=0;i<3;i++)
                        for(j=0;j<3;j++)
                            if(board[i][j]==((s)?'O':'X'))
                                x1=i,y1=j;
                            else if(board[i][j]==((s)?'X':'O'))
                                x2=i,y2=j;
                    if(x1==x2||y1==y2)
                    {
                        if(x1==x2)
                        {
                            y=y1;
                            x=2-x1;
                            return;
                        }
                        if(y1==y2)
                        {
                            x=x1;
                            y=2-y1;
                            return;
                        }
                    }
                    else
                    {
                        if(x2==1)
                        {
                            x=x1;
                            y=2-y1;
                            return;
                        }
                        if(y2==1)
                        {
                            y=y1;
                            x=2-x1;
                            return;
                        }
                    }
                }
            }
        }
    }
    if(move==4)
    {
        if((board[0][0]==((s)?'X':'O')&&board[2][2]==((s)?'X':'O'))||(board[2][0]==((s)?'X':'O')&&board[2][0]==((s)?'X':'O')))
        {
            int a[4][2]={{1,0},{1,2},{0,1},{2,1}};
            int gen = rand()%2;
            x=a[gen][0];
            y=a[gen][1];
            return;
        }
        else
        {
            int count=0,t=0;
            if(board[0][0]==' ')
                count++;
            if(board[0][2]==' ')
                count++;
            if(board[2][0]==' ')
                count++;
            if(board[2][2]==' ')
                count++;  
            int a[count][2];
            if(board[0][0]==' ')
                a[t][0]=0,a[t][1]=0,t++;
            if(board[0][2]==' ')
                a[t][0]=0,a[t][1]=2,t++;
            if(board[2][0]==' ')
                a[t][0]=2,a[t][1]=0,t++;
            if(board[2][2]==' ')
                a[t][0]=2,a[t][1]=2,t++; 
            int gen = rand()%count;
            x=a[gen][0];
            y=a[gen][1];
            return;    
        }
    }
    if(move==5)
    {
        if(board[0][0]==((s)?'O':'X')&&board[0][2]==((s)?'O':'X'))
        {
            if(board[1][0]==((s)?'X':'O'))
            {
                x=2;
                y=2;
                return;
            }
            else if(board[1][2]==((s)?'X':'O'))
            {
                x=2;
                y=0;
                return;
            }
        }
        if(board[0][2]==((s)?'O':'X')&&board[2][2]==((s)?'O':'X'))
        {
            if(board[0][1]==((s)?'X':'O'))
            {
                x=2;
                y=0;
                return;
            }
            else if(board[2][1]==((s)?'X':'O'))
            {
                x=0;
                y=0;
                return;
            }
        }
        if(board[2][2]==((s)?'O':'X')&&board[2][0]==((s)?'O':'X'))
        {
            if(board[1][0]==((s)?'X':'O'))
            {
                x=0;
                y=2;
                return;
            }
            else if(board[1][2]==((s)?'X':'O'))
            {
                x=0;
                y=0;
                return;
            }
        }
        if(board[2][0]==((s)?'O':'X')&&board[0][0]==((s)?'O':'X'))
        {
            if(board[0][1]==((s)?'X':'O'))
            {
                x=2;
                y=2;
                return;
            }
            else if(board[2][1]==((s)?'X':'O'))
            {
                x=0;
                y=2;
                return;
            }
        }
        if(board[1][1]==((s)?'O':'X'))
        {
            if(board[0][0]==((s)?'O':'X'))
            {
                if(board[1][0]==((s)?'X':'O'))
                {
                    x=0;
                    y=2;
                    return;
                }
                if(board[0][1]==((s)?'X':'O'))
                {
                    x=2;
                    y=0;
                    return;
                }
            }
            if(board[0][2]==((s)?'O':'X'))
            {
                if(board[1][2]==((s)?'X':'O'))
                {
                    x=0;
                    y=0;
                    return;
                }
                if(board[0][1]==((s)?'X':'O'))
                {
                    x=2;
                    y=2;
                    return;
                }
            }
            if(board[2][0]==((s)?'O':'X'))
            {
                if(board[1][2]==((s)?'X':'O'))
                {
                    x=2;
                    y=0;
                    return;
                }
                if(board[2][1]==((s)?'X':'O'))
                {
                    x=0;
                    y=2;
                    return;
                }
            }
            if(board[2][2]==((s)?'O':'X'))
            {
                if(board[1][2]==((s)?'X':'O'))
                {
                    x=2;
                    y=0;
                    return;
                }
                if(board[2][1]==((s)?'X':'O'))
                {
                    x=0;
                    y=2;
                    return;
                }
            }
        }
        int count=0;
        if(board[0][0]==' ')
            count++;
        if(board[0][2]==' ')
            count++;
        if(board[2][0]==' ')
            count++;
        if(board[2][2]==' ')
            count++;  
        int a[count][2],t=0;
        if(board[0][0]==' ')
            a[t][0]=0,a[t][1]=0,t++;
        if(board[0][2]==' ')
            a[t][0]=0,a[t][1]=2,t++;
        if(board[2][0]==' ')
            a[t][0]=2,a[t][1]=0,t++;
        if(board[2][2]==' ')
            a[t][0]=2,a[t][1]=2,t++;  
    }
    x=m;
    y=n;
}
void perfect_program_move(char board[3][3],bool s,int move)
{
    int x,y;
    pgenerate(board,x,y,s,move);
    board[x][y] = (s)?'O':'X';
}
void medium_program_move(char board[3][3],bool s)
{
    int x,y;
    generate(board,x,y,s);        
    board[x][y] = (s)?'O':'X'; 
}
void easy_program_move(char board[3][3],bool s)
{
    int x,y;
    egenerate(board,x,y,s);        
    board[x][y] = (s)?'O':'X'; 
}
void initialize_board(char board[3][3])
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j]=' ';
}
int main()
{
    char symbol,board[3][3],winner='_';
    initialize_board(board);
    bool s;
    int d,move=1;
    cout<<"WELCOME TO TIC-TAC-TOE"<<endl;
    cout<<"----------------------"<<endl<<endl;
    cout<<"Enter Difficulty (1 for easy, 2 for medium, 3 for perfect, 4 for 2-Player)"<<endl;
    cin>>d;
    if(d!=4)
    {
        cout<<"Select your symbol 'X' or 'O' to begin"<<endl;
        cin>>symbol;
        if(symbol=='X'||symbol=='x')
            s=true;
        else if(symbol=='O'||symbol=='o')
            s=false;
        else
            cout<<"Invalid Symbol Entered!"<<endl;
    }
    else
        s=true;
    if(s)
    {
        while(1)
        {
            player_move(board,s,(d==4)?1:0);
            move++;
            win_check(board,winner);
            if(winner!='_')
                break;
            if(d==1)    
                easy_program_move(board,s);
            else if(d==2)
                medium_program_move(board,s);
            else if(d==3)    
                perfect_program_move(board,s,move);
            else if(d==4)    
                player_move(board,!s,(d==4)?2:0);
            move++;    
            win_check(board,winner);
            if(winner!='_')
                break;
        }    
    }
    else
    {
        while(1)
        {
            if(d==1)    
                easy_program_move(board,s);
            else if(d==2)
                medium_program_move(board,s);
            else if(d==3)    
                perfect_program_move(board,s,move); 
            else if(d==4)
                player_move(board,!s,(d==4)?1:0);
            move++;    
            win_check(board,winner);
            if(winner!='_')
                break;
            player_move(board,s,(d==4)?2:0);
            move++;
            win_check(board,winner);
            if(winner!='_')
                break;
        }    
    }
    declare_winner(winner,s,board);
    return 0;
}


