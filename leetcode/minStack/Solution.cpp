class MinStack {
public:
    /** initialize your data structure here. */
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
        
        long t = mys.top();
        mys.pop();
        if (t<0)
            min = min-t;
    }
    
    int top() {
        return min+mys.top();
    }
    
    int getMin() {
        return min;
    }
    
    long min;
    stack<long> mys;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
