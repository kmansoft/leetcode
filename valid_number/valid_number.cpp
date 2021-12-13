#include <iostream>
#include <string>

bool isNumber(const std::string &s) {
	const int len = s.length();
	if (len == 0) {
		return false;
	}

	bool have_exponent = false;
	bool have_dot = false;
	int main_digits = 0;
	int pos = 0;
	char ch = s[pos];
	if (ch == '+' || ch == '-') {
		pos += 1;
	}

	while (pos < len) {
		ch = s[pos];
		if (ch >= '0' && ch <= '9') {
			main_digits += 1;
		} else if (ch == '.') {
			if (have_dot) {
				return false;
			}
			have_dot = true;
		} else if (ch == 'e' || ch == 'E') {
			pos += 1;
			have_exponent = 1;
			break;
		} else {
			return false;
		}
		pos += 1;
	}

	if (main_digits == 0) {
		return false;
	}

	if (have_exponent) {
		int exponent_digits = 0;

		if (pos < len) {
			ch = s[pos];
			if (ch == '+' || ch == '-') {
				pos += 1;
			}
			while (pos < len) {
				ch = s[pos];
				if (ch >= '0' && ch <= '9') {
					exponent_digits += 1;
				} else {
					return false;
				}
				pos += 1;
			}
		}

		if (exponent_digits == 0) {
			return false;
		}
	}

	return true;
}

void test(bool check, const char *s) {
	const bool result = isNumber(s);
	std::cout << s << " -> " << result << std::endl;
	if (check != result) {
		std::cout << "FAILED: expected " << check << std::endl;
	}
}

int main() {
	test(false, "");
	test(false, "z");
	test(false, "1a");

	test(true, "123");
	test(true, "+456");
	test(true, "-789");

	test(false, "+");
	test(false, "+-456");
	test(false, "-+789");

	test(false, "+e1");
	test(false, "+1e");

	test(true, "123e1");
	test(true, "123e+1");
	test(true, "123e-1");

	test(true, "2");
	test(true, "0089");
	test(true, "-0.1");
	test(true, "+3.14");
	test(true, "4.");
	test(true, "-.9");
	test(true, "2e10");
	test(true, "-90E3");
	test(true, "3e+7");
	test(true, "+6e-1");
	test(true, "53.5e93");
	test(true, "-123.456e789");

	test(false, "abc");
	test(false, "1a");
	test(false, "1e");
	test(false, "e3");
	test(false, "99e2.5");
	test(false, "--6");
	test(false, "-+3");
	test(false, "95a54e53");

	return 0;
}
