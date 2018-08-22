// Implement a basic calculator to evaluate a simple expression string.
//
// The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
//
// Example 1:
//
// Input: "1 + 1"
// Output: 2
// Example 2:
//
// Input: " 2-1 + 2 "
// Output: 3
// Example 3:
//
// Input: "(1+(4+50+2)-3)+(6+8)"
// Output: 23
// Note:
// You may assume that the given expression is always valid.
// Do not use the eval built-in library function.
//
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
//class Solution {
//public:
//	Solution(){}
//    int calculate(string s) {
//		int i = 0;
//		int N = s.size();
//		int curret = 0;
//		char curops = '#';
//
//		while (i<N) {
//			if (isdigit(s[i])) {
//				int tmpret = 0;
//				while (isdigit(s[i])) {
//					tmpret = (tmpret)*10 + s[i] - '0';
//					i++;
//				}
//				if (curops == '#') {
//					curret = tmpret;
//				} else if (curops == '+') {
//					curret += tmpret;
//					curops = '#';
//				} else if (curops == '-') {
//					curret -= tmpret;
//					curops = '#';
//				}
//			}
//			else if (s[i] == '+' || s[i] == '-') {
//				curops = s[i];
//				i ++;
//			}
//			else if (s[i] == '(') {
//				int j = i+1;
//				int lcount = 1;
//				while (lcount != 0) {
//					if (s[j] == '(') {
//						lcount ++;
//					}
//					else if (s[j] == ')') {
//						lcount --;
//					}
//					j++;
//				}
//				int tmpret = calculate(s.substr(i+1,j-i-2));
//				if (curops == '#') {
//					curret = tmpret;
//				} else if (curops == '+') {
//					curret += tmpret;
//					curops = '#';
//				} else if (curops == '-') {
//					curret -= tmpret;
//					curops = '#';
//				}
//				i = j;
//			} else {
//				i ++;
//			}
//		}
//
//		return curret;
//    }
//};
class Solution {
	public:
		Solution(){}
		int calculate(string s) {
			int i = 0;
			int N = s.size();
			int curret = 0;
			char curops = '#';

			while (i<N) {
				if (isdigit(s[i])) {
					int tmpret = 0;
					while (isdigit(s[i])) {
						tmpret = (tmpret)*10 + s[i] - '0';
						i++;
					}
					if (curops == '#') {
						curret = tmpret;
					} else if (curops == '+') {
						curret += tmpret;
						curops = '#';
					} else if (curops == '-') {
						curret -= tmpret;
						curops = '#';
					}
				}
				else if (s[i] == '+' || s[i] == '-') {
					curops = s[i];
					i ++;
				}
				else if (s[i] == '(') {
					int j = i+1;
					while (s[j] != ')') {
						j++;
					}
					int tmpret = calculate(s.substr(i+1,j-i-1));
					if (curops == '#') {
						curret = tmpret;
					} else if (curops == '+') {
						curret += tmpret;
						curops = '#';
					} else if (curops == '-') {
						curret -= tmpret;
						curops = '#';
					}
					i = j+1;
				} else {
					i ++;
				}
			}

			return curret;
		}
};
string stringToString(string input) {
	//    assert(input.length() >= 2);
	string result;
	int N = input.length() -1;
	for (int i = 1; i < N; i++) {
		char currentChar = input[i];
		if (input[i] == '\\') {
			char nextChar = input[i+1];
			switch (nextChar) {
				case '\"': result.push_back('\"'); break;
				case '/' : result.push_back('/'); break;
				case '\\': result.push_back('\\'); break;
				case 'b' : result.push_back('\b'); break;
				case 'f' : result.push_back('\f'); break;
				case 'r' : result.push_back('\r'); break;
				case 'n' : result.push_back('\n'); break;
				case 't' : result.push_back('\t'); break;
				default: break;
			}
			i++;
		} else {
			result.push_back(currentChar);
		}
	}
	return result;
}

int main() {
	string line;
	while (getline(cin, line)) {
		string s = stringToString(line);

		int ret = Solution().calculate(s);

		string out = to_string(ret);
		cout << out << endl;
	}
	return 0;
}

