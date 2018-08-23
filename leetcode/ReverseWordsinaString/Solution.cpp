#include <iostream>
#include <string>
using namespace std;

// class Solution {
// public:
// 	void reverseSubstr(string &s, int b, int e) {
// 		for (int i = b, j=e; i<j; ++i, --j) {
// 			char tmpc = s[j];
// 			s[j] = s[i];
// 			s[i] = tmpc;
// 		}
// 	}
//     void reverseWords(string &s) {
// 		int i = 0;
// 		int curbegin=-1;
// 		int curend=-1;
// 		while (s[i] != '\0') {
// 			if (s[i]!=' ' && -1==curbegin) {
// 				curbegin = i;
// 				i++;
// 			} else if (s[i]!=' ' && -1!=curbegin) {
// 				i++;
// 			} else if (s[i] == ' ') {
// 				curend = i-1;
// 				reverseSubstr(s, curbegin, curend);
// 				curbegin = -1;
// 				curend = -1;
// 				i++;
// 			}
// 		}
// 		if (curbegin != -1) {
// 			curend = s.size()-1;
// 			reverseSubstr(s, curbegin, curend);
// 		}
//     }
// };

class Solution {
	public:

		void shink(string &s) {
			int posi = 0;
			int i = 0;
			while (s[i] != '\0'){
				if (s[i] != ' ') {
					s[posi] = s[i];
					s[posi++] = s[i++];
				} else {
					while (s[i] == ' ') {
						i++;
					}
					s[posi] = ' ';
					posi ++;
				}
			}
			s.resize(posi);
			s.erase(0,s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
		}
		void reverseWords(string &s) {
			shink(s);
			size_t i = 0;
			auto curbegin= s.end();
			while (s[i] != '\0') {
				if (s[i]!=' ' && curbegin == s.end()) {
					curbegin = s.begin()+i;
					i++;
				} else if (s[i]!=' ' && s.end()!=curbegin) {
					i++;
				} else if (s[i] == ' ') {
					reverse(curbegin, s.begin()+i);
					curbegin = s.end();
					i++;
				}
			}
			if (curbegin != s.end()) {
				reverse(curbegin, s.end());
			}

			reverse(s.begin(), s.end());
		}
};
int main(int argc, char *argv[])
{
	string ss = "  hi!a    the  sky is blue  dd4   ";
	std::cout << ss << std::endl;

	Solution s;
	s.reverseWords(ss);
	std::cout << ss << std::endl;
	return 0;
}

// Given an input string, reverse the string word by word.
//
// Example:
//
// Input: "the sky is blue",
// Output: "blue is sky the".
// Note:
//
// A word is defined as a sequence of non-space characters.
// Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
// You need to reduce multiple spaces between two words to a single space in the reversed string.
// Follow up: For C programmers, try to solve it in-place in O(1) space.
