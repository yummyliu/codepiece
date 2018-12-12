#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    bool canReorderDoubled(vector<int>& A) {
        sort(A.begin(),A.end());
        
        while (A.size() > 0) {
            int n = A[0];
            int j=0;
            if (n>0)
                for (; j<A.size() && A[j] != 2*n; j++);
            else
                for (; j<A.size() && A[j] != n/2; j++);
            
            if (j<A.size()) {
                A.erase(A.begin()+j);
                A.erase(A.begin());
            } else
                return false;
        }
        
        return true;
    }
};
int main(int argc, char *argv[])
{
	vector<int> as = {4,-2,2,-4};

	Solution s;
	s.canReorderDoubled(as);
	return 0;
}
