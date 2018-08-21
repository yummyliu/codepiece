/**
 * Definition for singly-linked list.
 */
#include <iostream>
#include <map>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return NULL;
 		map<ListNode*, ListNode*> root;
		root[head] = head;

		ListNode* nxt = head->next;
		while (nxt) {
			if (root.find(nxt) == root.end()) {
				root[nxt] = root[head];
			} else {
				return nxt;
			}
            nxt = nxt->next;
		}
		return NULL;
    }
};
