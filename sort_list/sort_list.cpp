#include <initializer_list>
#include <iostream>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

std::ostream& operator<<(std::ostream& os, ListNode* list) {
	os << "[";

	for (ListNode* node = list; node != nullptr; node = node->next) {
		if (node != list) {
			os << ", ";
		}
		os << node->val;
	}

	os << "]";

	return os;
}

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
	void addList(ListNode* list) {
		if (head == nullptr) {
			head = tail = list;
		} else {
			tail->next = list;
			tail = list;
		}
		while (tail->next != nullptr) {
			tail = tail->next;
		}
	}
};

ListNode* mergeList(ListNode* l1, ListNode* l2) {
	List list;
	ListNode* next;

	while (l1 != nullptr && l2 != nullptr) {
		if (l1->val < l2->val) {
			next = l1->next;
			list.add(l1);
			l1 = next;
		} else {
			next = l2->next;
			list.add(l2);
			l2 = next;
		}
	}

	if (l1 != nullptr) {
		list.addList(l1);
	}
	if (l2 != nullptr) {
		list.addList(l2);
	}

	return list.head;
}

ListNode* sortList(ListNode* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	ListNode *x1 = head, *x2 = head->next;
	while (x2->next != nullptr && x2->next->next != nullptr) {
		x1 = x1->next;
		x2 = x2->next->next;
	}

	ListNode* next = x1->next;
	x1->next = nullptr;

	ListNode* sorted1 = sortList(head);
	ListNode* sorted2 = sortList(next);

	return mergeList(sorted1, sorted2);
}

void test(const std::initializer_list<int>& v) {
	List list;

	for (auto value : v) {
		ListNode* node = new ListNode(value);
		list.add(node);
	}

	std::cout << list.head << " -> ";

	ListNode* sorted = sortList(list.head);

	std::cout << sorted << std::endl;
}

int main() {
	test({4, 2, 1, 3});

	test({-1, 5, 3, 4, 0});

	test({3, 2, 4, 5, 1});

	test({});
}