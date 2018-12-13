i/*
// Definition for a Node.
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
*/
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ret;
        if (!root) {
            return ret;
        }
        stack<pair<Node*,int>> hold;
        hold.push({root,0});
        
        while(!hold.empty()) {
            // NOTE: 这里是引用
            auto& cur = hold.top();
            
            if (cur.second == cur.first->children.size()) {
                ret.push_back(cur.first->val);
                hold.pop();
            } else {
                hold.push({cur.first->children[cur.second++],0});
            }
        }
        
        return ret;
    }
};
