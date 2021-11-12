#include <iostream>
#include <vector>

int removeElement(std::vector<int>& nums, int val) {
	size_t i = 0, k = 0, size = nums.size();
	while (i < size) {
		if (nums[i] != val) {
			nums[k] = nums[i];
			k += 1;
		}
		i += 1;
	}

	return k;

	/*
	size_t start = 0, end = nums.size();

	while (start < end) {
		if (nums[start] == val) {
			std::swap(nums[start], nums[end - 1]);
			end -= 1;
		} else {
			start += 1;
		}
	}

	return start;
	*/
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

void test(const std::initializer_list<int>& init, int val) {
	std::vector<int> nums = init;

	std::cout << nums << ", " << val << " -> ";

	const int k = removeElement(nums, val);

	nums.erase(nums.begin() + k, nums.end());

	std::cout << k << ", " << nums << std::endl;
}

int main() {
	test({3, 2, 2, 3}, 3);

	test({0, 1, 2, 2, 3, 0, 4, 2}, 2);

	return 0;
}