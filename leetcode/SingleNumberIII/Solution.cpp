#include <vector>
using namespace std;
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
	    int aXorb = 0;  // the result of a xor b;
	    for (auto item : nums) aXorb ^= item;
	    int lastBit = ((aXorb ^ (aXorb - 1))+1) >> 1;  // the last bit that a diffs b
		// or
		// int lastBit = (aXorb & (aXorb -1)) ^ aXorb;
	    int intA = 0, intB = 0;
	    for (auto item : nums) {
	        // based on the last bit, group the items into groupA(include a) and groupB
	        if (item & lastBit) intA = intA ^ item;
	        else intB = intB ^ item;
	    }
	    return vector<int>{intA, intB};
	}
};
