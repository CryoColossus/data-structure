#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
int RNG(int mod)
{
    return (rand()%mod);
}
void Game(vector<string> hiragana, vector<string> romanji, int size, int &points)
{
    points = 0;
    int rounds = 100;
    string answer;
    cout<<"Write the pronunciation of the following hiragana characters:"<<endl;
    while(rounds--)
    {
        int pos = RNG(size);
        cout<<hiragana[pos]<<endl;
        cin>>answer;
        if(answer != romanji[pos])
        {
            cout<<"That is the wrong answer, the correct pronunciation is "<<romanji[pos]<<endl;
        }
        else
        {
            cout<<"Correct!"<<endl;
            points++;
        }    
    }
}
int main()
{
    srand(time(0));
    vector<string> hiragana {"あ","い","う","え","お","か","き","く","け","こ","さ","し","す","せ","そ","た","ち","つ","て","と","な","に","ぬ","ね","の","は","ひ","ふ","へ","ほ","ま","み","む","め","も","や","ゆ","よ","ら","り","る","れ","ろ","わ","ゐ","を"};
    vector<string> romanji {"a","i","u","e","o","ka","ki","ku","ke","ko","sa","shi","su","se","so","ta","chi","tsu","te","to","na","ni","nu","ne","no","ha","hi","fu","he","ho","ma","mi","mu","me","mo","ya","yu","yo","ra","ri","ru","re","ro","wa","wi","wo"};
    int size = hiragana.size();
    int points = 0;
    for(int i=0;i<size;i++)
        cout<<hiragana[i]<<" ";
    cout<<endl;    
    Game(hiragana,romanji,size,points);
    cout<<"Game Over! You scored "<<points<<" points."<<endl;
    return 0;
}

