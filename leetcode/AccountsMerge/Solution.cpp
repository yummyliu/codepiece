#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    Solution (){
    };
    virtual ~Solution (){};

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> res(accounts.size());

        std::map<int, string> nameMap;

        int num = accounts.size();
        for (int i = 0; i < num; ++i) {
            nameMap[i] = accounts[i][0];

            int mailNum = accounts[i].size();
            for (int j = 0; j < mailNum; ++j) {
                if (mailParents.find(accounts[i][j]) == mailParents.end()) {
                    mailParents[accounts[i][j]] = i;
                    res[i].insert(res[i].end(),accounts[i].begin(),accounts[i].end());
                } else {
                    // 该邮件已经出现在另一个用户中，将该这两个用户合并
                    auto newparent = min(i,mailParents[accounts[i][j]]);
                    auto oldparent = max(i,mailParents[accounts[i][j]]);

                    res[newparent].insert(res[newparent].end(),accounts[oldparent].begin()+1,accounts[oldparent].end());
                    res.erase(res.begin()+oldparent);
                }
            }
        }

        for (auto &i : res) {
            sort(i.begin(), i.end());
            auto last = unique(i.begin(),i.end());
            i.erase(last,i.end());
        }
        return res;
    }
private:
    /* data */
    std::map<string, int> mailParents;
};

int main(int argc, char *argv[])
{
    std::vector<vector<string>> v = {{"David","David0@m.co","David4@m.co","David3@m.co"},{"David","David5@m.co","David5@m.co","David0@m.co"},{"David","David1@m.co","David4@m.co","David0@m.co"},{"David","David0@m.co","David1@m.co","David3@m.co"},{"David","David4@m.co","David1@m.co","David3@m.co"}};

    Solution s;
    auto r = s.accountsMerge(v);
    for (auto i : r) {
        for (auto j : i) {
            std::cout << j ;
        }
        std::cout  << std::endl;
    }
    return 0;
}
