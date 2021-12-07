#include <deque>
#include <iostream>
#include <vector>

// https://algo.monster/problems/sliding_window_maximum

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
	const size_t size = nums.size();

	std::vector<int> res;
	std::deque<size_t> q;

	for (size_t i = 0; i < size; i += 1) {
		int cur = nums[i];
		while (!q.empty() && nums[q.back()] <= cur) {
			q.pop_back();
		}
		q.push_back(i);

		if (q.front() == i - k) {
			q.pop_front();
		}

		if (i >= k - 1) {
			res.push_back(nums[q.front()]);
		}
	}

	return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[";

	for (int i = 0; i < v.size(); i += 1) {
		if (i != 0) {
			os << ", ";
		}
		os << v[i];
	}

	os << "]";

	return os;
}

void test(const std::initializer_list<int>& init, int k) {
	std::vector<int> nums = init;

	std::cout << nums << ", " << k << " -> " << maxSlidingWindow(nums, k) << std::endl;
}

int main() {
	test({1, 3, -1, -3, 5, 3, 6, 7}, 3);

	test({1}, 1);

	test({1, -1}, 1);

	test({9, 11}, 2);

	test({4, -2}, 2);

	return 0;
}