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
	const int max = size + 1;

	for (int i = 0; i < size; i += 1) {
		int v = nums[i];
		if (v < 1 || v > max) {
			nums[i] = max;
		}
	}

	std::sort(nums.begin(), nums.end());

	int expected = 0;
	for (int i = 0; i < size; i += 1) {
		int v = nums[i];
		if (v != expected) {
			if (v == expected + 1) {
				expected += 1;
			} else {
				return expected + 1;
			}
		}
	}

	return expected + 1;
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

	return 0;
}