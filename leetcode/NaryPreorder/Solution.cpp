#include <vector>
using namespace std;
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:

    vector<int> preorder0(Node* root) {
        vector<int> out;

        if (!root) {
            return out;
        }

        out.push_back(root->val);
        for(auto& i : root->children) {
            vector<int> tmpout = preorder(i);
            out.insert(out.end(), tmpout.begin(), tmpout.end());
        }

        return out;
    }

    vector<int> preorder1(Node* root) {
        vector<int> out;
        if (!root) {
            return out;
        }

        stack<pair<Node*,int>> countStack; // 记录每个点相应子节点的访问次数，判断是否已经访问结束
        auto nxtPair = make_pair(root,0);
        while (true) {
            countStack.push(nxtPair);
            out.push_back(nxtPair.first->val);

            auto& curPair = countStack.top();
            while (curPair.second == curPair.first->children.size()) {
                countStack.pop();
                if (countStack.empty()) {
                    return out;
                }
				// XXX: c++ 中的引用不能重新赋值
				// 这里本意是想维护一个curPair，作为一直指向当前的top的引用，但是引用不能重新赋值，
				// 一开始curPair指向最开始的topNode，那么这里的重新赋值，相当于将一开始的topNode的值重新替换为当前的topNode的值
                curPair = countStack.top();
            }

            nxtPair = make_pair(curPair.first->children[curPair.second++],0);
        }
    }

    vector<int> preorder(Node* root) {
        vector<int> out;
        if (!root) {
            return out;
        }

        stack<pair<Node*,int>> countStack; // 记录每个点相应子节点的访问次数，判断是否已经访问结束
        auto nxtPair = make_pair(root,0);
        while (true) {
            countStack.push(nxtPair);
            out.push_back(nxtPair.first->val);

            auto curPair = countStack.top();
            while (curPair.second == curPair.first->children.size()) {
                countStack.pop();
                if (countStack.empty()) {
                    return out;
                }
                curPair = countStack.top();
            }

            auto& topp = countStack.top();
            nxtPair = make_pair(topp.first->children[topp.second++],0);
        }

        return out;
    }
};
