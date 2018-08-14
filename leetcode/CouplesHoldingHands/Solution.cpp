#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

    int minSwapsCouples(vector<int>& row) {
		/*
		 * 从一个乱的状态，变到了一个有序的状态；求这其中的最小步骤；
		 * 可以反过来看，从一个有序的状态变到一个乱的状态的过程。
		 * 原来是两两一组，每次交换就将两个组整合成一个组；这看做是一次union；
		 * 现在从一个最终状态，反推出进行了多少次union。
		 */
		vector<int> root(row.size()/2,0);
		for (size_t i = 0; i < root.size(); ++i) {
			root[i] = i;
		}

		int cnt = 0;
		for (size_t i = 0; i < row.size(); i+=2) {
			int rootx = find(root, row[i]/2);
			int rooty = find(root, row[i+1]/2);

			if (rootx != rooty) {
				root[rooty] = root[rootx];
				cnt ++;
			}
		}

		return cnt;
    }
private:
	/* data */
	int find(vector<int>& root, int i) {
		return (i == root[i]) ? i : find(root,root[i]);
	}
};
