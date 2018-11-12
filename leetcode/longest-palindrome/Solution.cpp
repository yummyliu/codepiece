#include <map>
#include <string>
using namespace std;

class Solution {
public:
    int longestPalindromeV1(string s) {
        map<char,int> count;

        for (char c : s) {
            count[c]++;
        }

        bool hasOdd = false;
        int countAns = 0;
        for (auto p : count) {
            if (p.second & 1) {
                hasOdd = true;
                countAns += p.second-1;
                continue;
            }

            countAns += p.second;
        }

        return (hasOdd)? countAns+1 : countAns;
    }
    int longestPalindrome(string s) {
        int odds = 0;
        for (char c='A'; c<='z'; c++)
            odds += count(s.begin(), s.end(), c) & 1;
        
        return s.size() - odds + (odds > 0);
    }
};
int main(int argc, char *argv[])
{
	
	return 0;
}
