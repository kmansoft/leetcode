#include <vector>
#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct List {
	ListNode *head, *tail;

	List() : head(nullptr), tail(nullptr) {}
	void add(ListNode* node) {
		if (head == nullptr) {
			head = tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		node->next = nullptr;
	}
};

ListNode* make_list(const std::vector<int> init) {
	List result;

	for (int i : init) {
		ListNode *node = new ListNode(i);
		result.add(node);
	}

	return result.head;
}

void print_list(ListNode *list) {
	std::cout << "[";

	ListNode *node = list;
	while (node != nullptr) {
		if (node != list) {
			std::cout << ", ";
		}
		std::cout << node->val;
		node = node->next;
	}

	std::cout << "]" << std::endl;
}

ListNode* reverseKGroup(ListNode* head, int k) {
	ListNode *resHead = nullptr, *resTail = nullptr;

	ListNode *curr = head;
	while (curr != nullptr) {
		int i = 0;
		ListNode *subHead = nullptr, *subTail = nullptr;
		while (i < k && curr != nullptr) {
			ListNode *next = curr->next;

			if (subHead == nullptr) {
				curr->next = nullptr;
				subHead = subTail = curr;
			} else {
				curr->next = subHead;
				subHead = curr;
			}

			curr = next;
			i += 1;
		}

		if (i < k) {
			ListNode *iter = subHead;
			ListNode *revHead = nullptr, *revTail = nullptr;
			while (iter != nullptr) {
				ListNode *next = iter->next;

				if (revHead == nullptr) {
					iter->next = nullptr;
					revHead = revTail = iter;
				} else {
					iter->next = revHead;
					revHead = iter;
				}

				iter = next;
			}

			subHead = revHead;
			subTail = revTail;
		}

		if (resHead == nullptr) {
			resHead = subHead;
			resTail = subTail;
		} else {
			resTail->next = subHead;
			resTail = subTail;
		}
	}

	return resHead;
}

void reverseAndPrint(const std::vector<int>& init, int k) {
	ListNode *list = make_list(init);
	print_list(list);

	ListNode *revl = reverseKGroup(list, k);
	print_list(revl);
}

int main() {

	reverseAndPrint({1,2,3,4,5}, 2);
	reverseAndPrint({1,2,3,4,5}, 3);
	reverseAndPrint({1,2,3,4,5}, 1);
	reverseAndPrint({1}, 2);

	return 0;
}