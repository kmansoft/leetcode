#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

std::vector<int> nextGreaterElement(std::vector<int>& nums1,
									std::vector<int>& nums2) {
	std::stack<int> st;

	std::unordered_map<int, int> m;
	m.reserve(nums2.size());

	for (int i = nums2.size() - 1; i >= 0; i -= 1) {
		const int n2 = nums2[i];
		while (!st.empty() && st.top() <= n2) {
			st.pop();
		}

		const int res = st.empty() ? -1 : st.top();
		m[n2] = res;

		st.push(n2);
	}

	std::vector<int> result;
	result.reserve(nums1.size());

	for (const auto n1 : nums1) {
		result.push_back(m[n1]);
	}

	return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v) {
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

void test(std::vector<int>& nums1, std::vector<int>& nums2) {
	const auto answer = nextGreaterElement(nums1, nums2);

	std::cout << nums1 << ", " << nums2 << " -> " << answer << std::endl;
}

int main() {
	std::vector<int> n1_0 = {4, 1, 2};
	std::vector<int> n2_0 = {1, 3, 4, 2};
	test(n1_0, n2_0);

	std::vector<int> n1_1 = {2, 4};
	std::vector<int> n2_1 = {1, 2, 3, 4};
	test(n1_1, n2_1);

	return 0;
}