#include <iostream>
#include <bitset>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
		int N = rooms.size();
		bitset<1000> seen(0);
		seen = ~seen;
		seen <<= N;
		seen[0] = 1;

		stack<int> todo;
		todo.push(0);

		while (!todo.empty()) {
			int curroom = todo.top();
			todo.pop();

			for (auto i : rooms[curroom]) {
				if (!seen[i]) {
					seen[i] = 1;
					todo.push(i);
				}
			}
		}

		return seen.all();
    }
};

int main(int argc, char *argv[])
{
	Solution s;

	vector<vector<int>> a = {{1},{2},{3},{}};
	cout << s.canVisitAllRooms(a) <<endl;
	return 0;
}
