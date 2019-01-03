#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Group {

	Group(char c, int n) {
		pre = NULL;
		nxt = NULL;
		m_c = c;
		m_n = n;
	}
	char m_c;
	int  m_n;
	Group *pre, *nxt;
};
class Solution {
public:
	virtual ~Solution() {
		Group* nxt = ghead;
		while (nxt) {
			Group* tmp = nxt;
			delete tmp;
			nxt = nxt->nxt;
		}
	}
    int findMinStep(string board, string hand) {
		ghead = new Group('#', 0);
		gtail = ghead;

		for (int i=0; i<board.size();){
			int count = 1;
			int j = i+1;
			while (j<board.size() && board[j] == board[i]) {
				count ++;
				j++;
			}

			gtail->nxt = new Group(board[i], count);
			gtail->nxt->pre = gtail;

			gtail = gtail->nxt;
			i=j;
		}

		Group* g = ghead;
		while (g) {
			std::cout << g->m_c << ": " << g->m_n << std::endl;
			g = g->nxt;
		}
		std::cout << "---" << std::endl;
		g = gtail;
		while (g) {
			std::cout << g->m_c << ": " << g->m_n << std::endl;
			g = g->pre;
		}

		for (auto c : hand) {
			hmap[c] ++;
		}

		minstep = INT_MAX;
		dfs(0);

		return (minstep==INT_MAX)? -1 : minstep;
    }

	void dfs(int curstep) {
		if (!ghead->nxt) {
			minstep = min(minstep, curstep);
			return ;
		}

		Group* cur = ghead->nxt;
		Group *delLeft, *delRight;
		while (cur) {
			if (hmap[cur->m_c] > 0) {
				cur->m_n ++;
				hmap[cur->m_c] --;
				if (cur->m_n > 2) {
					delLeft = cur->pre;
					delRight = cur->nxt;
					while ( delLeft && delRight
							&& delLeft->pre->m_c == delRight->nxt->m_c
							&& delLeft->pre->m_n + delRight->nxt->m_n > 2) {
						delLeft = delLeft->pre;
						delRight = delRight->nxt;
					}
					delLeft = delLeft->nxt;
					delRight = delRight->pre;
					delLeft->pre->nxt = delRight->nxt;
					delRight->nxt->pre = delLeft->pre;
				}

				dfs(curstep+1);

				if (cur->m_n > 2) {
					delLeft->pre->nxt = delLeft;
					delRight->nxt->pre = delRight;
				}
				cur->m_n --;
				hmap[cur->m_c] ++;
			}

			cur = cur->nxt;
		}
	}


	Group* ghead;
	Group* gtail;
	unordered_map<char, int> hmap;

	int minstep;
};

int main(int argc, char *argv[])
{
	string bs = "RBYYBBRRB";
	string hand = "YRBGB";

	Solution s;

	std::cout << s.findMinStep(bs, hand) << std::endl;
	return 0;
}
