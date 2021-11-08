#include <iostream>
#include <string>

std::string longestPalindrome(std::string s) {
	const int size = s.length();
	if (size <= 1) {
		return s;
	}

	int max = 1;
	int b = 0, e = 1;

	for (int i = 0; i < size; i += 1) {
		int m = i, n = i;
		while (m >= 0 && n < size) {
			if (s[m] == s[n]) {
				if (max < n - m + 1) {
					max = n - m + 1;
					b = m;
					e = n + 1;
				}
				m -= 1;
				n += 1;
			} else {
				break;
			}
		}
	}

	for (int i = 0; i < size; i += 1) {
		int m = i, n = i + 1;
		while (m >= 0 && n < size) {
			if (s[m] == s[n]) {
				if (max < n - m + 1) {
					max = n - m + 1;
					b = m;
					e = n + 1;
				}
				m -= 1;
				n += 1;
			} else {
				break;
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