#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    Solution (){};
    virtual ~Solution (){};
    int slidingPuzzle(vector<vector<int>>& board) {
        // local var
        const vector<int> action{1,-1,3,-3};

        for (auto ac : action) {
            std::cout << ac << std::endl;
        }


        return -1;
    }
private:
    /* data */
};

int main()
{
    
    return 0;
}
