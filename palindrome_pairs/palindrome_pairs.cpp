#include <iostream>
#include <vector>

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

bool isPalindrome(const std::string& s) {
	int start = 0;
	int end = s.length();

	while (start < end) {
		if (s[start] != s[end - 1]) {
			return false;
		}
		start += 1;
		end -= 1;
	}

	return true;
}

std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words) {
	std::vector<std::vector<int>> pairs;

	const int size = words.size();
	std::string candidate;

	for (int i = 0; i < size; i += 1) {
		for (int j = 0; j < size; j += 1) {
			if (i != j) {
				candidate = words[i] + words[j];
				if (isPalindrome(candidate)) {
					pairs.push_back({i, j});
				}
			}
		}
	}

	return pairs;
}

void test(std::vector<std::string>& words) {
	auto pairs = palindromePairs(words);

	std::cout << words << " -> " << pairs << std::endl;
}

int main() {
	std::vector<std::string> v0 = {"abcd", "dcba", "lls", "s", "sssll"};
	test(v0);

	std::vector<std::string> v1 = {"bat", "tab", "cat"};
	test(v1);

	std::vector<std::string> v2 = {"a", ""};
	test(v2);

	return 0;
}