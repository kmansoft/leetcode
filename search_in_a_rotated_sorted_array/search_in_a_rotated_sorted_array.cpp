#include <iostream>
#include <vector>

int search(const std::vector<int> &nums, int target) {
	const int size = nums.size();
	int l = 0, r = size - 1;

	while (l <= r) {
		const int m = (l + r) >> 1;
		const int v = nums[m];

		if (v > target) {
			if (nums[l] <= target) {
				r = m - 1;
			} else {
				l = m + 1;
			}
		} else if (v < target) {
			if (nums[r] >= target) {
				l = m + 1;
			} else {
				r = m - 1;
			}
		} else {
			return m;
		}
	}

	return -1;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	os << "[";

	for (int i = 0; i < v.size(); i += 1) {
		if (i != 0) {
			std::cout << ", ";
		}
		os << v[i];
	}

	os << "]";

	return os;
}

void test(int check, const std::initializer_list<int> &init, int target) {
	const std::vector<int> nums(init);
	const int result = search(nums, target);

	std::cout << nums << ", " << target << " -> " << result << std::endl;
	if (check != result) {
		std::cout << "FALIED: expected " << check << std::endl;
	}
}

int main() {

	test(4, {4, 5, 6, 7, 8, 1, 2, 3}, 8);

	test(4, {4, 5, 6, 7, 0, 1, 2}, 0);

	test(5, {4, 5, 6, 7, 0, 1, 2}, 1);

	test(-1, {4, 5, 6, 7, 0, 1, 2}, 3);

	test(3, {0, 1, 2, 3, 4, 5, 6, 7}, 3);

	test(-1, {1}, 0);

	return 0;
}
