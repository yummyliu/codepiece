#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
		int N = citations.size();
		int e = N-1;
		int s = 0;

		while (s <= e) {
			int ph=(s+e)/2;
			if (N - ph > citations[ph]) {
				s = ph+1;
			} else {
				e = ph -1;
			}
		}

		return N - s;
    }
};
