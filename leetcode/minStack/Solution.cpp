#include <stack>
using namespace std;

class MinStack {
public:
    MinStack() {
    }
    void push(int x) {
        if (mys.empty()) {
            mys.push(0);
            min = x;
        } else {
            mys.push(x-min);
            if (x<min) min = x;
        }
    }
    void pop() {
        if (mys.empty())
            return;
        long long t = mys.top();
        mys.pop();
        if (t<0)
            min = min-t;
    }
    int top() {
		long long t = mys.top();
		if (t<0) {
			return min;
		}
        return min+t;
    }
    int getMin() {
        return min;
    }
    long long min;
    stack<long long> mys;
};

class MinStackV2 {
private:
    stack<int> s1;
    stack<int> s2;
public:
    void push(int x) {
	    s1.push(x);
	    if (s2.empty() || x <= getMin())  s2.push(x);
    }
    void pop() {
	    if (s1.top() == getMin())  s2.pop();
	    s1.pop();
    }
    int top() {
	    return s1.top();
    }
    int getMin() {
	    return s2.top();
    }
};
