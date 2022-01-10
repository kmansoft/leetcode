#include <iostream>
#include <queue>
#include <vector>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
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

template <>
struct std::less<ListNode*> {
	bool operator()(const ListNode* lhs, const ListNode* rhs) const {
		return lhs->val > rhs->val;
	}
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
	int size = lists.size();
	std::priority_queue<ListNode*> queue;

	for (int i = 0; i < size; i += 1) {
		if (lists[i] != nullptr) {
			queue.push(lists[i]);
		}
	}

	List result;

	while (!queue.empty()) {
		ListNode* curr = queue.top();
		ListNode* next = curr->next;

		queue.pop();
		result.add(curr);

		if (next != nullptr) {
			queue.push(next);
		}
	}

	return result.head;
}

std::ostream& operator<<(std::ostream& out, ListNode* node) {
	out << "[";

	ListNode* curr = node;
	while (curr != nullptr) {
		if (curr != node) {
			out << ", ";
		}
		out << curr->val;
		curr = curr->next;
	}

	out << "]";

	return out;
}

ListNode* make_list(const std::initializer_list<int> init) {
	List result;

	for (int i : init) {
		ListNode* node = new ListNode(i);
		result.add(node);
	}

	return result.head;
}

void test(const std::initializer_list<int> i0,
		  const std::initializer_list<int> i1,
		  const std::initializer_list<int> i2) {
	std::vector<ListNode*> lists;
	lists.push_back(make_list(i0));
	lists.push_back(make_list(i1));
	lists.push_back(make_list(i2));

	std::cout << lists[0] << ", " << lists[1] << ", " << lists[2] << " -> ";

	ListNode* merged = mergeKLists(lists);
	std::cout << merged << std::endl;
}

int main() {
	test({1, 4, 5}, {1, 3, 4}, {2, 6});

	test({1, 3, 5, 7, 200}, {2, 4, 6}, {100, 300});

	return 0;
}