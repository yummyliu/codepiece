#ifndef SOLUTION_H
#define SOLUTION_H

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int v) {
		val = v;
	}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int k) {
        ListNode tmph(0);
        tmph.next = head;
        ListNode* lesser = &tmph;

        ListNode* pre = &tmph;
        while (head) {
            if (head->val < k) {
                if (lesser->next == head) {
                    lesser = head;
                    pre = head;
                    head = head->next;
                } else {
                    auto* a = lesser->next;
                    lesser->next = head;
                    auto* b = head->next;
                    head->next = a;
                    head = b;
                    pre->next = b;
					lesser = lesser->next;
                }
            } else {
                pre = head;
                head = head->next;
            }
        }

        return tmph.next;
    }
};

#endif /* SOLUTION_H */
