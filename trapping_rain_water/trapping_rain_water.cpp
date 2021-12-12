#include <iostream>
#include <vector>

// https://www.geeksforgeeks.org/trapping-rain-water/

int trap(const std::vector<int> &height) {
	const int size = height.size();
	if (size <= 2) {
		return 0;
	}

	std::vector<int> left(size);
	left[0] = height[0];
	for (int i = 1; i < size; i += 1) {
		left[i] = std::max(left[i - 1], height[i]);
	}

	std::vector<int> right(size);
	right[size - 1] = height[size - 1];
	for (int i = size - 2; i >= 0; i -= 1) {
		right[i] = std::max(right[i + 1], height[i]);
	}

	int water = 0;
	for (int i = 0; i < size; i += 1) {
		water += std::min(left[i], right[i]) - height[i];
	}

	return water;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> v) {
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

void test(int check, const std::initializer_list<int> &init) {
	const std::vector<int> height(init);
	const int water = trap(height);

	std::cout << height << " -> " << water << std::endl;
	if (water != check) {
		std::cout << "FAILED, expected " << check << std::endl;
	}
}

int main() {

	test(6, {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});

	test(9, {4, 2, 0, 3, 2, 5});

	return 0;
}
