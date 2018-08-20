#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
		if (k==1) {
			res.resize(n);
			for (int i = 0; i < n; ++i) {
				res[i].push_back(i+1);
			}
			return res;
		}
        if (n <= k) {
			res.resize(1);
			for (int i = 0; i < n; ++i) {
				res[0].push_back(i+1);
			}
            return res;
        }

		res= combine(n-1,k);
		auto cres = combine(n-1,k-1);
		for (auto i : cres) {
			i.push_back(n);
			res.push_back(i);
		}

		return res;
    }
};

int main()
{
	Solution s;
	auto a = s.combine(5,2);
	return 0;
}
