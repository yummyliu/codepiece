#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
	Solution() : blocks(9), rows(9), cols(9) {}
    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				int ib = (i/3)*3 + (j/3)*3;
				blocks[ib].insert(board[i][j]);
				rows[i].insert(board[i][j]);
				cols[i].insert(board[i][j]);
			}
        }


    }
private:
	vector<set<int>> blocks;
	vector<set<int>> rows;
	vector<set<int>> cols;
};
