#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

void combine(std::stack<std::pair<int, int>>& segments,
			 const std::pair<int, int> match) {
	if (segments.empty()) {
		segments.push(match);
	} else {
		const std::pair<int, int> top = segments.top();
		if (top.second == match.first) {
			segments.pop();
			combine(segments, std::pair<int, int>(top.first, match.second));
		} else if (top.first == match.first + 1 &&
				   top.second == match.second - 1) {
			segments.pop();
			combine(segments, match);
		} else {
			segments.push(match);
		}
	}
}

int longestValidParentheses(std::string s) {
	std::stack<int> parens;
	std::stack<std::pair<int, int>> segments;
	int maxSegment = 0;

	const int end = s.length();
	for (int cur = 0; cur < end; cur += 1) {
		const char ch = s[cur];
		if (ch == '(') {
			parens.push(cur);
		} else if (ch == ')' && !parens.empty()) {
			const int pos = parens.top();
			parens.pop();

			const std::pair<int, int> match(pos, cur + 1);
			combine(segments, match);
		}
	}

	while (!segments.empty()) {
		const std::pair<int, int> match = segments.top();
		segments.pop();

		maxSegment = std::max(maxSegment, match.second - match.first);
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
