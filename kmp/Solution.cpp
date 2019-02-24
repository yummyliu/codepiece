#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getNext(string pat) {
	int N = pat.size();
	vector<int> nxt(N);

	nxt[0] = -1;
	int j=1, i=0;
	while (j<N) {
		if (pat[j] == pat[i]) {
			nxt[j] = i;
			j++;i++;
		} else if (i==0) {
			nxt[j] = -1;
			j++;
		} else {
			i = nxt[i-1]+1;
		}
	}

	return nxt;
}

int kmpSearch(string str, string pat) {
	vector<int> nxt = getNext(pat);
	int M = str.size();
	int N = pat.size();

	int j=0;
	for (int i = 0; i < M;) {
		if (str[i] == pat[j]) {
			j++;
			i++;
		}
		if (j==N) {
			return i-N;
		} else if (i<M && pat[j] != str[i]) {
			if (j==0) {
				i++;
			} else {
				j = nxt[j-1]+1;
			}
		}
	}

	return -1;
}

int main()
{
	string str = "ABABDABACDABABCABAB";
	string pat = "ABABCABAB";

	cout << kmpSearch(str,pat) << endl;
	return 0;
}
