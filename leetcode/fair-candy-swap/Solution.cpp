#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
		int sumB = accumulate(B.begin(), B.end(), 0);

		set<int> setA;
		int sumA=0;
		for (auto a : A) {
			setA.insert(a);
			sumA+=a;
		}

		int diff = (sumB - sumA)/2;
		for (int b : B) {
			if (setA.count(b-diff)) {
				return vector<int>({b-diff, b});
			}
		}

		return vector<int>();
    }
};
