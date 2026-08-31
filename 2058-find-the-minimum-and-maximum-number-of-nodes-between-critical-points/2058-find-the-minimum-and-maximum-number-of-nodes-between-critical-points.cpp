/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1, last = -1;
        int minDist = INT_MAX;
        int index = 1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr->next) {
            ListNode* next = curr->next;

            bool critical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (critical) {
                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - last);
                }
                last = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        if (first == -1 || first == last) return {-1, -1};

        return {minDist, last - first};
    }
};