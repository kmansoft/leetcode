#include <iostream>
#include <string>

int longestValidParentheses(std::string s) {
	const int size = s.length();
	int maxSegment = 0, l, r;

	for (int i = 0, l = 0, r = 0; i < size; i += 1) {
		const char ch = s[i];
		if (ch == '(') {
			l += 1;
		} else if (ch == ')') {
			r += 1;
		}

		if (l == r) {
			maxSegment = std::max(maxSegment, l + r);
		} else if (l < r) {
			l = r = 0;
		}
	}

	for (int i = size - 1, l = 0, r = 0; i >= 0; i -= 1) {
		const char ch = s[i];
		if (ch == '(') {
			l += 1;
		} else if (ch == ')') {
			r += 1;
		}

		if (l == r) {
			maxSegment = std::max(maxSegment, l + r);
		} else if (l > r) {
			l = r = 0;
		}
	}

	return maxSegment;
}

void test(int expected, const std::string& s) {
	const int n = longestValidParentheses(s);

	std::cout << "\"" << s << "\" -> " << n << std::endl;

	if (expected != n) {
		std::cout << "FAILURE, expected " << expected << std::endl;
	}
}

int main() {
	test(6, "()(())");

	test(14, "()(((()(()))))");

	test(6, "())(())()");

	test(2, "(()");

	test(6, "(()())");

	test(2, "()(()");

	test(4, ")()())");

	test(0, "");

	test(0, "((((((((((");

	test(2, "(((((((((()");

	test(6, "(((((((((()())");

	test(2, "(((((((((()(((");

	return 0;
}
