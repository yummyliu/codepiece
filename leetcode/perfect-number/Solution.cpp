#include <iostream>
#include <cmath>
using namespace std;

#ifndef SOLUTION_H
#define SOLUTION_H

class Solution
{
private:
	

public:
	Solution(){};
	virtual ~Solution(){};
	bool checkPerfectNumber(int num) {
        if (num <= 1) return false;
        int rooting = sqrt(num);
        
		int sum = 0;
		for (int i = 1; i <= rooting; ++i) {
			if (!(num%i)) sum += i==1?i:(i + num/i);
		}

		if (sum == num) return true;
		return false;
    }
};

#endif /* SOLUTION_H */
