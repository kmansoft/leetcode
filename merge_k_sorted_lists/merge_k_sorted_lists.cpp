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

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
	ListNode *result = nullptr;
	int size = lists.size();

	if (size > 0) {
		result = lists[0];
		for (int i = 1; i < size; i += 1) {
			result = merge2Lists(result, lists[i]);
		}
	}

	return result;
}

ListNode* make_list(const std::vector<int> init) {
	List result;

	for (int i : init) {
		ListNode *node = new ListNode(i);
		result.add(node);
	}

	return result.head;
}

int main() {
	std::vector<std::vector<int>> init = {
		{ 1, 4, 5},
		{ 1, 3, 4},
		{ 2, 6}
	};

	std::vector<ListNode*> lists;
	for (auto &i : init) {
		lists.push_back(make_list(i));
	}

	ListNode *merged = mergeKLists(lists);

	std::cout << "[";
	for (ListNode *node = merged; node != nullptr; node = node->next) {
		if (node != merged) {
			std::cout << " ";
		}
		std::cout << node->val;
	}
	std::cout << "]" << std::endl;

	return 0;
}