#include <iostream>
#include <stack>
#include <vector>

// https://www.geeksforgeeks.org/largest-rectangle-under-histogram/

int largestRectangleArea(const std::vector<int> &heights) {
	std::stack<int> s;

	const int size = heights.size();
	int max_area = 0, area, tp;
	int i = 0;

	while (i < size) {
		if (s.empty() || heights[s.top()] <= heights[i]) {
			s.push(i);
			i += 1;
		} else {
			tp = s.top();
			s.pop();

			area = heights[tp] * (s.empty() ? i : i - s.top() - 1);
			max_area = std::max(max_area, area);
		}
	}

	while (!s.empty()) {
		tp = s.top();
		s.pop();

		area = heights[tp] * (s.empty() ? i : i - s.top() - 1);
		max_area = std::max(max_area, area);
	}

	return max_area;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T>& v) {
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

void test(int check, const std::initializer_list<int> &init) {
	const std::vector<int> heights(init);
	const int area = largestRectangleArea(heights);

	std::cout << heights << " -> " << area << std::endl;
	if (check != area) {
		std::cout << "FAILED: expected " << check << std::endl;
	}
}

int main() {
	test(10, {2, 1, 5, 6, 2, 3});

	test(4, {2, 4});

	return 0;
}
