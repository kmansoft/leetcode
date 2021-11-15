#include <iostream>
#include <stack>
#include <vector>

std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
	const size_t size = temperatures.size();
	std::vector<int> result(size);

	std::stack<int> st;
	for (int i = size - 1; i >= 0; i -= 1) {
		const int t = temperatures[i];
		while (!st.empty() && temperatures[st.top()] <= t) {
			st.pop();
		}

		const int r = st.empty() ? 0 : st.top() - i;
		result[i] = r;

		st.push(i);
	}

	return result;
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

void test(const std::initializer_list<int>& init) {
	std::vector<int> temperatures = init;
	std::cout << temperatures << " -> " << dailyTemperatures(temperatures)
			  << std::endl;
}

int main() {
	test({73, 74, 75, 71, 69, 72, 76, 73});

	test({30, 40, 50, 60});

	test({30, 60, 90});

	return 0;
}