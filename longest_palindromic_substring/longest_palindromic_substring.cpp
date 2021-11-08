#include <iostream>
#include <string>

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

std::string longestPalindrome(std::string s) {
	const int size = s.length();
	if (size <= 1) {
		return s;
	}

	int m = 0;
	int b = 0, e = 1;

	for (int start = 0; start <= size - 1; start += 1) {
		const char f = s[start];
		for (int end = start + 1 + m; end <= size; end += 1) {
			if (s[end - 1] == f && isPalindrome(s, start, end)) {
				if (m < end - start) {
					m = end - start;
					b = start;
					e = end;
				}
			}
		}
	}

	return s.substr(b, e - b);
}

void test(const std::string& s) {
	std::cout << s << " -> " << longestPalindrome(s) << std::endl;
}

int main() {
	test("babad");

	test("cbbd");

	test("a");

	test("ac");

	test("");

	return 0;
}