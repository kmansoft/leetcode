#include <vector>
#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
	ListNode* head = nullptr;
	ListNode* tail = nullptr;

	while (true) {
		int minIndex = -1;
		int minValue = 0;

		for (int i = 0; i < lists.size(); i += 1) {
			ListNode* node = lists[i];
			if (node != nullptr) {
				if (minIndex == -1 || minValue > node->val) {
					minIndex = i;
					minValue = node->val;
				}
			}
		}

		if (minIndex == -1) {
			return head;
		}

		ListNode* node = lists[minIndex];
		lists[minIndex] = node->next;

		if (head == nullptr) {
			head = tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		node->next = nullptr;
	}
}

ListNode* make_list(const std::vector<int> init) {
	ListNode *head = nullptr;
	ListNode *tail = nullptr;

	for (int i : init) {
		ListNode *node = new ListNode(i);
		if (head == nullptr) {
			head = tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		node->next = nullptr;
	}

	return head;
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