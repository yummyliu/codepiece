#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    Solution (){};

    static bool sort_helper(const vector<int>& a, const vector<int>& b)
    {
        if (a[0] != b[0]) {
            return a[0] < b[0];
        } else {
            return a[1] < b[1];
        }
    }

    int maxCount(int m, int n, vector<vector<int>>& ops) {
        std::sort(ops.begin(), ops.end(), this->sort_helper);

        int min_m = m;
        int min_n = n;
        for (auto i : ops) {
            if (min_m > i[0]) {
                min_m = i[0];
            }
            if (min_n > i[1]) {
                min_n = i[1];
            }
        }
        return min_n * min_m;
    }

private:
    /* data */
};

int main()
{
    vector<vector<int>> param{{4,5},
                              {4,3},
                              {2,4},
                              {3,3}};

    Solution s;
    std::cout << s.maxCount(6, 7, param) << std::endl;

    return 0;
}
