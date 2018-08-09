#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    Solution (){
		for (int i = 0; i < 10000; ++i) {
			ps[i] = i;
		}
    };
    virtual ~Solution (){};

	int parent(int i) {
		while (ps[i] != i) {
			i = ps[i];
		}
		return i;
	}

	void merge(int pid, vector<int> mids) {
		for (size_t i = 0; i < mids.size(); ++i) {
			int mpid = parent(mids[i]);
			ps[mpid] = pid;
		}
	}

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
		int accountsNum = accounts.size();
		std::map<string, vector<int>> mailmap;	// Inverted index of mail -> accountId

		for (int i = 0; i < accountsNum; ++i) {
			for (size_t imail = 1;
					imail < accounts[i].size();
					imail ++) {
				string curMail = accounts[i][imail];
				if (mailmap.find(curMail) != mailmap.end()) {
					merge(i,mailmap[curMail]);
				}
				mailmap[curMail].push_back(i);
			}
		}

        vector<vector<string>> res;
		std::map<int, int> accountMap; // accountMap[i] = j : id=i的account的resid为j
		for (int i = accountsNum-1; i >= 0; --i) {
			if (i==ps[i]) {
				res.push_back(accounts[i]);
				accountMap[i] = res.size()-1;
			} else {
				int pid  = parent(i);
				int resid= accountMap[pid];

				res[resid].reserve(res[resid].size() + accounts[i].size());
				res[resid].insert(
						res[resid].end(),
						accounts[i].begin()+1,
						accounts[i].end());
			}
		}

		for (auto &i : res) {
			sort(i.begin(), i.end());
			auto last = unique(i.begin(), i.end());
			i.erase(last, i.end());
		}
        return res;
    }
private:
	int ps[10000];
};

int main()
{
    std::vector<vector<string>> v = {
		{"David","David0@m.co","David4@m.co","David3@m.co"},
		{"David","David5@m.co","David6@m.co","David0@m.co"},
		{"David","David1@m.co","David4@m.co","David0@m.co"},
		{"David","David0@m.co","David1@m.co","David3@m.co"},
		{"David","David4@m.co","David1@m.co","David3@m.co"}};

	std::vector<vector<string>> v3= {
		{"David","David0@m.co","David1@m.co"},
		{"David","David3@m.co","David4@m.co"},
		{"David","David4@m.co","David5@m.co"},
		{"David","David2@m.co","David3@m.co"},
		{"David","David1@m.co","David2@m.co"}};

	std::vector<vector<string>> v4 = {
		{"Hanzo","Hanzo9@m.co","Hanzo2@m.co","Hanzo4@m.co","Hanzo12@m.co","Hanzo5@m.co"},
		{"John","John11@m.co","John3@m.co","John4@m.co","John3@m.co","John12@m.co"},
		{"Bob","Bob0@m.co","Bob5@m.co","Bob11@m.co","Bob9@m.co","Bob7@m.co"},
		{"Gabe","Gabe2@m.co","Gabe6@m.co","Gabe7@m.co","Gabe7@m.co","Gabe9@m.co"},
		{"Gabe","Gabe11@m.co","Gabe5@m.co","Gabe12@m.co","Gabe2@m.co","Gabe4@m.co"},
		{"David","David7@m.co","David7@m.co","David0@m.co","David3@m.co","David4@m.co"},
		{"David","David2@m.co","David0@m.co","David2@m.co","David8@m.co","David9@m.co"},
		{"Gabe","Gabe7@m.co","Gabe1@m.co","Gabe10@m.co","Gabe5@m.co","Gabe8@m.co"},
		{"Isa","Isa0@m.co","Isa1@m.co","Isa12@m.co","Isa0@m.co","Isa8@m.co"},
		{"Isa","Isa5@m.co","Isa3@m.co","Isa8@m.co","Isa7@m.co","Isa3@m.co"},
		{"Celine","Celine2@m.co","Celine9@m.co","Celine9@m.co","Celine2@m.co","Celine12@m.co"},
		{"Kevin","Kevin1@m.co","Kevin1@m.co","Kevin4@m.co","Kevin10@m.co","Kevin12@m.co"}};

	std::vector<vector<string>> v5 = {
		{"Hanzo","Hanzo2@m.co","Hanzo3@m.co"},
		{"Hanzo","Hanzo4@m.co","Hanzo5@m.co"},
		{"Hanzo","Hanzo0@m.co","Hanzo1@m.co"},
		{"Hanzo","Hanzo3@m.co","Hanzo4@m.co"},
		{"Hanzo","Hanzo7@m.co","Hanzo8@m.co"},
		{"Hanzo","Hanzo1@m.co","Hanzo2@m.co"},
		{"Hanzo","Hanzo6@m.co","Hanzo7@m.co"},
		{"Hanzo","Hanzo5@m.co","Hanzo6@m.co"}};

    Solution s;
    auto r = s.accountsMerge(v3);
    for (auto i : r) {
        for (auto j : i) {
            std::cout << j << " ";
        }
		std::cout <<  ""<< std::endl;
    }
    return 0;
}
