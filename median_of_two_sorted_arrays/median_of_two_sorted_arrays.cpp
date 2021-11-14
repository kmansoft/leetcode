#include <iostream>
#include <vector>

double findMedianSortedArrays(std::vector<int>& nums1,
							  std::vector<int>& nums2) {
	const size_t size1 = nums1.size(), size2 = nums2.size();
	const size_t combinedSize = size1 + size2;
	size_t medianIndex1, medianIndex2;
	if ((combinedSize % 2) == 0) {
		medianIndex1 = combinedSize / 2 - 1;
		medianIndex2 = medianIndex1 + 1;
	} else {
		medianIndex1 = medianIndex2 = combinedSize / 2;
	}
	double medianSum = 0.0;

	size_t out = 0, in1 = 0, in2 = 0;
	while (out <= medianIndex2) {
		int value;
		if (in1 < size1 && in2 < size2) {
			if (nums1[in1] < nums2[in2]) {
				value = nums1[in1];
				in1 += 1;
			} else {
				value = nums2[in2];
				in2 += 1;
			}
		} else if (in1 < size1) {
			value = nums1[in1];
			in1 += 1;
		} else if (in2 < size2) {
			value = nums2[in2];
			in2 += 1;
		}

		if (out == medianIndex1) {
			medianSum += value;
		}
		if (out == medianIndex2) {
			medianSum += value;
		}

		out += 1;
	}

	return medianSum / 2.0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v) {
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

void test(const std::initializer_list<int>& l1,
		  const std::initializer_list<int>& l2) {
	std::vector<int> nums1 = l1;
	std::vector<int> nums2 = l2;

	std::cout << nums1 << ", " << nums2 << " -> " << std::flush;

	const double median = findMedianSortedArrays(nums1, nums2);

	std::cout << median << std::endl;
}

int main() {
	test({1, 3}, {2});

	test({1, 2}, {3, 4});

	test({0, 0}, {0, 0});

	test({}, {1});

	test({2}, {});

	return 0;
}