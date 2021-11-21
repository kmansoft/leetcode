#include <iostream>
#include <string>

int matchSegment(const std::string& s, int start) {
	const int end = s.length();
	int segment = 0;
	int cur = start;
	int elevation = 0;

	while (cur < end) {
		const char ch = s[cur];
		if (ch == '(') {
			elevation += 1;
		} else if (ch == ')') {
			if (elevation == 0) {
				break;
			}
			elevation -= 1;
			if (elevation == 0) {
				segment = cur - start + 1;
			}
		}

		cur += 1;
	}

	return segment;
}

int longestValidParentheses(std::string s) {
	int maxSegment = 0;
	int cur = 0, end = s.length();
	while (cur < end) {
		int curSegment = matchSegment(s, cur);
		if (maxSegment < curSegment) {
			maxSegment = curSegment;
		}

		cur += 1 + curSegment;
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
	test(2, "(()");

	test(6, "(()())");

	test(6, "()(())");

	test(2, "()(()");

	test(4, ")()())");

	test(0, "");

	test(0, "((((((((((");

	test(2, "(((((((((()");

	test(6, "(((((((((()())");

	test(2, "(((((((((()(((");

	return 0;
}
