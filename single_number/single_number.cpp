#include <vector>
#include <iostream>

int find_single_number(const std::vector<int>& nums) {
	int n = 0;

	for (auto i : nums) {
		n ^= i;
	}

	return n;
}

int main() {
	std::vector l = { 1, 2, 3, 4, 1, 2, 3};

	std::cout << find_single_number(l) << std::endl;
}
