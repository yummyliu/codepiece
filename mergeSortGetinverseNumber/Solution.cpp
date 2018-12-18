#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	vector<int> getInverseNum(string s) {
		vector<int> inverses;
		if (s.size()==0) {
			return inverses;
		}
		if (s.size() == 1) {
			return {0};
		}

		int mid = s.size()/2;
		string ls = s.substr(0,mid);
		string rs = s.substr(mid);
		vector<int> inversesLeft = getInverseNum(ls);
		vector<int> inversesRight = getInverseNum(rs);

		int il =0;
		while (il<inversesLeft.size()) {
			int ir = 0;
			while (ir<inversesRight.size() ) {
				if (ls[il] > rs[ir]) {
					inversesLeft[il] += 1;
				}
				ir ++;
			}
			il ++;
		}

		inversesLeft.insert(inversesLeft.end(), inversesRight.begin(), inversesRight.end());
		return inversesLeft;
	}

	string MergeSort(string s, int& inverseNum) {
		if (s.size() < 2) {
			return s;
		}

		int mid = s.size()/2;
		string ls = MergeSort(s.substr(0, mid), inverseNum);
		string rs = MergeSort(s.substr(mid), inverseNum);

		string outs;
		int il=0;
		int ir=0;
		while (il<ls.size() && ir<rs.size()) {
			if (ls[il] <= rs[ir]) {
				outs.push_back(ls[il]);
				il++;
			} else {
				outs.push_back(rs[ir]);
				inverseNum += (ls.size()-il);
				ir ++;
			}
		}

		if (il<ls.size()) {
			outs.append(ls.substr(il));
		}
		if (ir<rs.size()) {
			outs.append(rs.substr(ir));
		}

		return outs;
	}

private:
	/* data */
};

int main(int argc, char *argv[])
{
	string abc = "snabasdlkfjalksdjfuasdfasdf";

	Solution s;
	std::cout << abc.size() << std::endl;
	std::cout << abc << std::endl;
	int inverseNum=0;
	std::cout << s.MergeSort(abc, inverseNum) << std::endl;
	auto vs = s.getInverseNum(abc);

	int sum=0;
	for (auto i : vs) {
		sum+=i;
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	std::cout << sum << ":" << inverseNum<< std::endl;
	std::cout << std::endl;
	return 0;
}
