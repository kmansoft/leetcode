#include <iostream>
#include <unordered_map>
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

bool isPalindrome(const std::string& s, int start, int end) {
	while (start < end) {
		if (s[start] != s[end - 1]) {
			return false;
		}
		start += 1;
		end -= 1;
	}

	return true;
}

std::string reverse(const std::string& s) {
	const size_t l = s.length();
	std::string q;
	q.reserve(l);

	for (int i = l - 1; i >= 0; i -= 1) {
		q.push_back(s[i]);
	}

	return q;
}

std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words) {
	std::vector<std::vector<int>> pairs;
	std::unordered_map<std::string, int> reverseIndex;

	const int size = words.size();

	for (int i = 0; i < size; i += 1) {
		const auto& word = words[i];
		const auto len = word.length();
		if (len != 0) {
			reverseIndex[reverse(word)] = i;
		}
	}

	std::unordered_map<std::string, int>::iterator end = reverseIndex.end();

	for (int i = 0; i < size; i += 1) {
		const auto& word = words[i];
		const auto len = word.length();

		if (len == 0) {
			for (int j = 0; j < size; j += 1) {
				const auto& word = words[j];
				if (i != j && isPalindrome(word, 0, word.length())) {
					pairs.push_back({i, j});
					if (word.length() != 0) {
						pairs.push_back({j, i});
					}
				}
			}
		} else {
			for (int j = 0; j <= len; ++j) {
				const auto prefixFind = reverseIndex.find(word.substr(0, j));
				if (prefixFind != end) {
					const auto pair = *prefixFind;
					if (pair.second != i && isPalindrome(word, j, len)) {
						pairs.push_back({i, pair.second});
					}
				}

				if (j != len) {
					const auto suffixFind = reverseIndex.find(word.substr(len - j, len));
					if (suffixFind != end) {
						const auto pair = *suffixFind;
						if (pair.second != i && isPalindrome(word, 0, len - j)) {
							pairs.push_back({pair.second, i});
						}
					}
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

	std::vector<std::string> v5 = {"a", "abc", "aba", ""};
	test(v5);

	return 0;
}
