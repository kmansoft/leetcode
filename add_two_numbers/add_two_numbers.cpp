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

std::ostream& operator<<(std::ostream& os, ListNode *list) {
	os << "[";

	ListNode *node = list;
	while (node != nullptr) {
		if (node != list) {
			os << ", ";
		}
		os << node->val;
		node = node->next;
	}

	os << "]";

	return os;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int carry = 0;
	List list;

	while (l1 != nullptr && l2 != nullptr) {
		int value = l1->val + l2->val + carry;
		carry = value / 10;
		ListNode *node = new ListNode(value % 10);
		list.add(node);

		l1 = l1->next;
		l2 = l2->next;
	}

	ListNode *tail = l1;
	if (tail == nullptr) {
		tail = l2;
	}
	while (tail != nullptr) {
		int value = tail->val + carry;
		carry = value / 10;
		ListNode *node = new ListNode(value % 10);
		list.add(node);

		tail = tail->next;
	}

	if (carry != 0) {
		ListNode *node = new ListNode(carry);
		list.add(node);
	}

	return list.head;
}

void test(const std::vector<int>& v1, const std::vector<int>& v2) {
	ListNode *l1 = make_list(v1);
	ListNode *l2 = make_list(v2);

	ListNode *sum = addTwoNumbers(l1, l2);

	std::cout << l1 << " + " << l2 << " = " << sum << std::endl;
}

int main() {
	test({2, 4, 3}, {5, 6, 4});

	test({0}, {0});

	test({9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9});

	return 0;
}
