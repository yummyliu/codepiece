#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
	Solution(){};
	virtual ~Solution (){};

	int numMatchingSubseq(string S, vector<string>& words) {
		vector<vector<const char*>> waits(128, vector<const char*>());

		for (auto& w : words) {
			waits[w[0]].push_back(w.c_str());
		}

		for (auto c : S) {
			auto advance = waits[c];
			waits[c].clear();

			for (auto& p : advance) {
				waits[*++p].push_back(p);
			}
		}

		return waits[0].size();
	}
private:
	/* data */
};

int main(int argc, char *argv[])
{

	return 0;
}
