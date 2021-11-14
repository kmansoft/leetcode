#include <climits>
#include <iostream>
#include <vector>

double findMedianHelper(std::vector<int>& a, std::vector<int>& b) {
	size_t sizea = a.size(), sizeb = b.size();
	size_t l = 0, r = sizea;
	while (true) {
		size_t i = (l + r) / 2;
		size_t j = (sizea + sizeb + 1) / 2 - i;

		const int max_left_a = (i == 0) ? INT_MIN : a[i - 1];
		const int min_right_a = (i == sizea) ? INT_MAX : a[i];
		const int max_left_b = (j == 0) ? INT_MIN : b[j - 1];
		const int min_right_b = (j == sizeb) ? INT_MAX : b[j];

		if (max_left_a <= min_right_b && max_left_b <= min_right_a) {
			if (((sizea + sizeb) % 2) == 0) {
				return (std::max(max_left_a, max_left_b) +
						std::min(min_right_a, min_right_b)) /
					   2.0;
			}
			return std::max(max_left_a, max_left_b);
		} else if (max_left_a > min_right_b) {
			r = i - 1;
		} else {
			l = i + 1;
		}
	}
}

double findMedianSortedArrays(std::vector<int>& nums1,
							  std::vector<int>& nums2) {
	if (nums1.size() <= nums2.size()) {
		return findMedianHelper(nums1, nums2);
	}
	return findMedianHelper(nums2, nums1);
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