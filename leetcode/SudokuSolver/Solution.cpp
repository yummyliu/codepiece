#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
	Solution() : blocks(9), rows(9), cols(9) {
		all = {'1','2','3','4','5','6','7','8','9'};
	}
	bool backstrace(int i, int j, vector<vector<char>>& bd) {
		if (i==8 && j == 8) {
			if (bd[i][j] != '.') {
				return true;
			}
			std::set<char> candidate;
			set_difference(all.begin(), all.end(),
					rows[8].begin(),rows[8].end(),
					inserter(candidate, candidate.begin()));
			bd[i][j] = *(candidate.begin());
			return true;
		}

		if (bd[i][j] != '.') {
			if (j<8)
				return backstrace(i,j+1,bd);
			else
				return backstrace(i+1,0,bd);

		}

		int ib = (i/3)*3 + (j/3);
		set<char> candidate, tmp, tmp1;
		set_union(blocks[ib].begin(), blocks[ib].end(),
				rows[i].begin(), rows[i].end(),
				inserter(tmp,tmp.begin()));
		set_union(tmp.begin(), tmp.end(),
				cols[j].begin(), cols[j].end(),
				inserter(tmp1,tmp1.begin()));
		set_difference(all.begin(),all.end(),
				tmp1.begin(),tmp1.end(),
				inserter(candidate, candidate.begin()));

		for (auto &e : candidate) {

			bd[i][j] = e;
			blocks[ib].insert(e);
			rows[i].insert(e);
			cols[j].insert(e);

			bool isfind = false;
			if (j<8)
				isfind = backstrace(i, j+1, bd);
			else
				isfind = backstrace(i+1, 0, bd);

			if (isfind) {
				return true;
			} else {
				blocks[ib].erase(e);
				rows[i].erase(e);
				cols[j].erase(e);
				bd[i][j] = '.';
			}
		}

		return false;
	}
    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] != '.') {
					int ib = (i/3)*3 + (j/3);
					blocks[ib].insert(board[i][j]);
					rows[i].insert(board[i][j]);
					cols[j].insert(board[i][j]);
				}
			}
        }

		backstrace(0,0, board);
    }
private:
	vector<set<char>> blocks;
	vector<set<char>> rows;
	vector<set<char>> cols;
	set<char> all;
};

int main()
{
	vector<vector<char>> board = {
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'}};
	Solution s;
	s.solveSudoku(board);

	for (int i = 0; i < 9; ++i) {
		for (int j = 0;j < 9; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout  << std::endl;
	}

	return 0;
}
