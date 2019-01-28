#include <iostream>
#include <map>
using namespace std;
void func(int * a) {
	*a ++;
}

void func1(int& a) {
	a ++;
}

class Solution {
public:
    bool isIsomorphic(string s, string t) {

        int Sn = s.size();
        int Tn = t.size();
        if (Sn != Tn) return false;
        if (Sn == Tn && Sn<2) return true;

        map<char,char> uniqm;
        uniqm[s[0]] = t[0];
        int i=1;
        while (i<Sn) {
            if ((s[i] ==s[i-1] && t[i] == t[i-1])
				|| (s[i] !=s[i-1] && t[i] != t[i-1])) {

				if (s[i] != t[i] && uniqm.find(s[i]) == uniqm.end()) {
                    uniqm[s[i]] = t[i];
				} else if (s[i]!=t[i] && uniqm[s[i]] != t[i]) {
					return false;
				}
            } else
				return false;
            i++;
        }

        return true;
    }
};

int main(int argc, char *argv[])
{
	int a = 10;
	func(&a);
	std::cout << a << std::endl;

	int b = 10;
	func1(b);
	std::cout << b << std::endl;


	cout << "----" <<endl;

	cout << sizeof(long long) << endl;
	cout << sizeof(long) << endl;
	return 0;
}
