// There are N children standing in a line. Each child is assigned a rating value.
//
// You are giving candies to these children subjected to the following requirements:
//
// + Each child must have at least one candy.
// + Children with a higher rating get more candies than their neighbors.
// + What is the minimum candies you must give?
//
// Example 1:
//
// Input: [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
//
// Example 2:
//
// Input: [1,2,2]
// Output: 4
// Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
//              The third child gets 1 candy because it satisfies the above two conditions.
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int candy(vector<int>& ratings) {
		int N = ratings.size();
        int ret = N;

		vector<int> cs(N,1);
		for (int i = 1; i < N; ++i) {
			if (ratings[i] > ratings[i-1]) {
				ret += cs[i-1]+1-cs[i];
				cs[i] = cs[i-1]+1;
			}
		}

		for (int i = N-2; i >=0; --i) {
			if (ratings[i] > ratings[i+1]
				&& cs[i] <= cs[i+1] ) {
				ret += cs[i+1]+1-cs[i];
				cs[i] = cs[i+1]+1;
			}
		}

		return ret;
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	vector<int> a = {1,3,4,5,2};
	s.candy(a);
	return 0;
}
