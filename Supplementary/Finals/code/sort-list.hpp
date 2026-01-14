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
    ListNode* getMid(ListNode* head){
        if (head == nullptr){
            return nullptr;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        while (fast != nullptr && fast->next != nullptr){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = nullptr;
        return slow;
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode sent;
        ListNode* tail = &sent;

        while(list1 != nullptr && list2 != nullptr) {
            if ( list1->val > list2->val) {
                tail->next = list2; 
                list2 = list2->next;    
            }
            else {
                tail->next = list1;
                list1 = list1->next;
            }
            tail = tail->next;
        }
            if (!list1) tail->next = list2;
            else tail->next = list1;

            return sent.next;
    }

    ListNode* sortList(ListNode* head) {
        if(head == nullptr) {
            return nullptr;
        }
        if (head->next == nullptr) {
            return head;
        }
        ListNode* mid = getMid(head);
        ListNode* right = sortList(mid);
        ListNode* left = sortList(head);

        return mergeTwoLists(left, right);
    }
};