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

ListNode* merge2Lists(ListNode* l1, ListNode *l2) {
	List result;
	ListNode *next;

	while (l1 != nullptr && l2 != nullptr) {
		if (l1->val < l2->val) {
			next = l1->next;
			result.add(l1);
			l1 = next;
		} else {
			next = l2->next;
			result.add(l2);
			l2 = next;
		}
	}

	while (l1 != nullptr) {
		next = l1->next;
		result.add(l1);
		l1 = next;
	}

	while (l2 != nullptr) {
		next = l2->next;
		result.add(l2);
		l2 = next;
	}

	return result.head;
}

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

int main() {
	ListNode *l1 = make_list({1,2,4});
	ListNode *l2 = make_list({1,3,4});

	print_list(l1);
	print_list(l2);

	ListNode *lm = merge2Lists(l1, l2);
	print_list(lm);
}