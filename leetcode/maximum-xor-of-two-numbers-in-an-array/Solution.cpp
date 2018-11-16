#include <iostream>
#include <vector>

using namespace std;

class TrieNode
{
public:
	TrieNode ():value(-1){
		cs.resize(2,nullptr);
	};
	virtual ~TrieNode (){
		for (size_t i = 0; i < cs.size(); ++i) {
			if (cs[i]) {
				free(cs[i]);
			}
		}
	};

	/* data */
	int value;
	vector<TrieNode*> cs;
private:
};

class Trie
{
public:
	Trie ():root(new TrieNode()){};
	virtual ~Trie (){
		free(root);
	};

	void buildTrie(vector<int> nums)
	{
		for (auto n : nums) {
			TrieNode* cur = root;
			for (int b = 31; b >=0 ; --b) {
				int nxt = (n >> b) & 1;
				if (!cur->cs[nxt]) {
					cur->cs[nxt] = new TrieNode();
				}
				cur = cur->cs[nxt];
			}
			cur->value = n;
		}
	}

	TrieNode* root;
private:
	/* data */
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
		Trie tr;
		tr.buildTrie(nums);

		int maxx = 0;
		for (auto n : nums) {
			TrieNode* cur = tr.root;
			for (int b = 31; b >=0 ; --b) {
				int nxt = (n >> b) & 1;
				if (cur->cs[1-nxt]) {
					cur = cur->cs[1-nxt];
				} else {
					cur = cur->cs[nxt];
				}
			}
			maxx = max(maxx, cur->value ^ n);
		}
		return maxx;
    }
};

int main()
{
	vector<int> nums = {3,10,5,25,2,8};

	Solution s;

	std::cout << s.findMaximumXOR(nums) << std::endl;
	return 0;
}
