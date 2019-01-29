#include <iostream>
#include <cstdlib>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool isPalindromeV1(ListNode* head) {
		if (!head || !head->next) {
			return true;
		}
        ListNode* prehead  = new ListNode(-1);;
        prehead->next = head;

        int N=0;
        while (head) {
            head = head->next;
            N++;
        }
        int half = N/2;
        ListNode *pre = prehead, *cur = pre->next;
		prehead->next = NULL;
        while (half--) {
            ListNode* nxt = cur->next;
            cur->next = pre;

            pre = cur;
            cur = nxt;
        }
        ListNode* tail = cur;
        if (N%2==1) {
            tail = tail->next;
        }
        while (pre && tail && pre->val == tail->val) {
            pre = pre->next;
            tail = tail->next;
        }

        return !tail;
    }
	bool isPalindrome(ListNode* head) {
		ListNode *tail, *pre = nullptr, *tmp, *slow = head, *fast = head;
		while (fast && fast->next) {
			fast = fast->next->next;
			tmp = slow->next;
			slow->next = pre;
			pre = slow;
			slow = tmp;
		}

		if (fast) {
			tail = slow->next;
		}
		while (pre && tail && pre->val == tail->val) {
			pre = pre->next;
			tail = tail->next;
		}

		return !pre;
	}
};

int main(int argc, char *argv[])
{
	ListNode head(1);
	ListNode n(1);
	head.next = &n;

	Solution s;
	cout << s.isPalindrome(&head) <<endl;
	return 0;
}







