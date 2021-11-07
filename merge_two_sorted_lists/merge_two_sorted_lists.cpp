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

ListNode* merge2Lists(ListNode* a, ListNode *b) {
	List result;
	ListNode *next;

	while (a != nullptr && b != nullptr) {
		if (a->val < b->val) {
			next = a->next;
			result.add(a);
			a = next;
		} else {
			next = b->next;
			result.add(b);
			b = next;
		}
	}

	while (a != nullptr) {
		next = a->next;
		result.add(a);
		a = next;
	}

	while (b != nullptr) {
		next = b->next;
		result.add(b);
		b = next;
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