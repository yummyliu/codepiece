#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& v1, vector<string>& v2) {
		size_t i, j;
		int sum=-1;
		vector<string> out;

		map<string,int> v1map;
		for (i = 0; i < v1.size(); ++i) {
			v1map[v1[i]] = i;
		}

		int minval = INT_MAX;
		map<int, vector<string>> scoremap;
		for (j = 0; j < v2.size(); ++j) {
			if (v1map.find(v2[j]) != v1map.end()) {
				if (v1map[v2[j]] + j < minval) minval = v1map[v2[j]] + j;
				scoremap[v1map[v2[j]] + j].push_back(v2[j]);
			}
		}

		return scoremap[minval];
	}
    vector<string> findRestaurant2(vector<string>& v1, vector<string>& v2) {
        size_t i, j;
        int sum=-1;
        vector<string> out;

        map<string,int> v1map;
        for (i = 0; i < v1.size(); ++i) {
            v1map[v1[i]] = i;
        }

        map<int, vector<string>> scoremap;
        for (j = 0; j < v2.size(); ++j) {
            if (v1map.find(v2[j]) != v1map.end()) {
                scoremap[v1map[v2[j]] + j].push_back(v2[j]);
            }
        }

        return scoremap.begin()->second;
    }
};

int main(int argc, char *argv[])
{
	
	return 0;
}
