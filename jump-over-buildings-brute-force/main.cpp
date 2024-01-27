#include <iostream>
#include <vector>
using namespace std;
void play(vector<int> heights, int bricks, int ladders,int curr,int &max)
    {
        if(curr>max)
            max=curr;
        if(curr<heights.size()-1)
        {
            if(heights[curr]>=heights[curr+1])
                play(heights,bricks,ladders,curr+1,max);
            else
            {
                if(ladders!=0)
                    play(heights,bricks,ladders-1,curr+1,max);
                if((heights[curr+1]-heights[curr])<=bricks)
                    play(heights,bricks-(heights[curr+1]-heights[curr]),ladders,curr+1,max);
            }        
        }
    }
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) 
    {
        int max=0;
        play(heights,bricks,ladders,0,max);
        return max;
    }
int main()
{
    vector<int> heights{4,12,2,7,3,18,20,3,19};
    cout<<furthestBuilding(heights,10,2)<<endl;
    return 0;
}