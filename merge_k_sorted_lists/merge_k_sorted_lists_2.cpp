#include <vector>
#include <iostream>
#include <queue>

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

template<>
struct std::less<ListNode*> {
	bool operator()( const ListNode* lhs, const ListNode* rhs ) const {
		return lhs->val > rhs->val;
	}
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
	int size = lists.size();
	std::priority_queue<ListNode*> queue;

	for (int i = 0; i < size; i += 1) {
		ListNode *node = lists[i];
		while (node != nullptr) {
			queue.push(node);
			node = node->next;
		}
	}

	List result;
	while (!queue.empty()) {
		ListNode *node = queue.top();
		queue.pop();
		result.add(node);
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