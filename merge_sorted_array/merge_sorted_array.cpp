#include <vector>
#include <iostream>

void mergeSortedArrays(std::vector<int> &nums1, int m,
					   std::vector<int> &nums2, int n) {

	int out = m + n - 1;
	int in1 = m - 1;
	int in2 = n - 1;

	while (in1 >= 0 && in2 >= 0) {
		if (nums1[in1] > nums2[in2]) {
			nums1[out] = nums1[in1];
			in1 -= 1;
		} else {
			nums1[out] = nums2[in2];
			in2 -= 1;
		}
		out -= 1;
	}

	while (in1 >= 0) {
		nums1[out] = nums1[in1];
		in1 -= 1;
		out -= 1;
	}

	while (in2 >= 0) {
		nums1[out] = nums2[in2];
		in2 -= 1;
		out -= 1;
	}
}

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


int main() {
	// std::vector nums1 = {1,2,3,0,0,0};
	// std::vector nums2 = {2,5,6};

	std::vector nums1 = {0};
	std::vector nums2 = {1};

	mergeSortedArrays(nums1, 0, nums2, 1);

	std::cout << nums1 << std::endl;

	return 0;
}