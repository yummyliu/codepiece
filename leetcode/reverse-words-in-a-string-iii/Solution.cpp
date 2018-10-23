#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution () {};

    string reverseWords(string s) {
		int N = s.size();
        int i = 0;
        while (i<N && s[i]==' ') i++;

        while (i < N) {
            int l = i;
            while (i<N && s[i]!=' ') i++;
            int r = i-1;
            reverseInplace(s, l, r);
            i++;
        }

        return s;
    }
    void reverseInplace(string& s,int l, int r) {
		int i,j;
        for (i=l, j=r; i<j; i++,j--) {
            char tmp = s[j];
            s[j] = s[i];
            s[i] = tmp;
        }
    }
	string reverseWordsII(string s) {
		size_t startPos = s.find_first_not_of(' ');
        if (std::string::npos == startPos)
            return s;
        string out;
		s = s.substr(startPos);

		while (true) {
			string word = s.substr(0,s.find_first_of(' '));
			reverse(word.begin(), word.end());

			size_t nxt = s.find_first_of(' ',1);
			if (std::string::npos == nxt) {
				out.append(word);
				break;
			} else {
				out.append(word+" ");
				s = s.substr(nxt+1);
			}
		}

		return out;
    }

private:
	/* data */
};

int main(int argc, char *argv[])
{
	string ss = "Let's take LeetCode tontesc";
	Solution s;
	cout << s.reverseWordsII(ss) <<endl;
	return 0;
}
