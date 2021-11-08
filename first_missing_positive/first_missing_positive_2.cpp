#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v) {
	os << "[";

	for (int i = 0; i < v.size(); i += 1) {
		if (i != 0) {
			std::cout << ", ";
		}
		os << v[i];
	}

	os << "]" << std::endl;

	return os;
}

int firstMissingPositive(std::vector<int>& nums) {
	const int size = nums.size();
	int start = 0;

	while (start < size) {
		int v = nums[start];
		if (v > 0 && v <= size && v != nums[v-1]) {
			std::swap(nums[start], nums[v-1]);
		} else {
			start += 1;
		}
	}

	for (int i = 0; i < size; i += 1) {
		if (nums[i] != i + 1) {
			return i + 1;
		}
	}

	return size + 1;
}

void test(std::vector<int>& v) {
	std::cout << v << firstMissingPositive(v) << " " << v << std::endl;
}

int main() {
	std::vector<int> n0 = {1,2,0};
	test(n0);

	std::vector<int> n1 = {3,4,-1,1};
	test(n1);

	std::vector<int> n2 = {7,8,9,11,12};
	test(n2);

	std::vector<int> n3 = {0, 2, 1};
	test(n3);

	std::vector<int> n4 = {0, 2, 2, 1, 1};
	test(n4);

	std::vector<int> n5 = {1, 1};
	test(n5);

	std::vector<int> n6 = {0, 2, 2, 1, 1, 3};
	test(n6);

	return 0;
}