#include <iostream>
#include <numeric>
#include <locale>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	bool isPossible (int m, int sum, int n) {
		bool possible = false;
		for (int i = 1; i < m; ++i) {
			if (sum*i%n == 0) possible = true;
		}

		return possible;
	}

    bool splitArraySameAverage(vector<int>& A) {
		int n = A.size();
		int m = n / 2;
		int sum = accumulate(A.begin(), A.end(), 0);

		if (!isPossible(m,sum,n)) return false;

		vector<unordered_set<int>> sums(m+1);
		sums[0].insert(0);
		for (auto num : A) {
			for (int i = m; i >= 1; --i) {
				// for (int t : sums[i-1]) {
				// 	sums[i].insert(t+num);
				// }
				transform(sums[i-1].begin(), sums[i-1].end(),
						inserter(sums[i], sums[i].end()),
						[num](int t) {return t + num;});
			}
		}

		for (int i = 1; i <= m; ++i) {
			if (sum*i%n == 0 && sums[i].count(sum*i/n)) return true;
		}

		return false;
    }


private:
	/* data */
};
