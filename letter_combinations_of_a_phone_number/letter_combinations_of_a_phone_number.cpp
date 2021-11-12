#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Digit {
	const char* syms;
	int count;
	int current;

	Digit() : syms(nullptr), count(0), current(0) {}
	void setSyms(const char* s) {
		syms = s;
		count = strlen(s);
	}
	bool increment(bool inc) {
		if (inc) {
			if (current == count - 1) {
				current = 0;
				return true;
			} else {
				current += 1;
				return false;
			}
		}
		return false;
	}
	char asChar() { return syms[current]; }
};

const char* const DIGITS[10] = {
	/* 0 */ "#",
	/* 1 */ "#",
	/* 2 */ "abc",
	/* 3 */ "def",
	/* 4 */ "ghi",
	/* 5 */ "jkl",
	/* 6 */ "mno",
	/* 7 */ "pqrs",
	/* 8 */ "tuv",
	/* 9 */ "wxyz"};

constexpr size_t MAX_COUNT = 4;

std::vector<std::string> letterCombinations(std::string digits) {
	std::vector<std::string> results;

	const size_t count = digits.length();
	if (count > 0) {
		Digit list[MAX_COUNT];

		for (int i = count - 1; i >= 0; i -= 1) {
			const char* syms = DIGITS[digits[i] - '0'];
			list[i].setSyms(syms);
		}

		while (true) {
			std::string s;
			s.reserve(count);
			for (int i = 0; i < count; i += 1) {
				s.push_back(list[i].asChar());
			}
			results.push_back(s);

			bool inc = true;
			for (int i = count - 1; i >= 0; i -= 1) {
				inc = list[i].increment(inc);
			}

			if (inc) {
				break;
			}
		}
	}

	return results;
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

void test(const char* digits) {
	std::vector<std::string> combinations = letterCombinations(digits);

	std::cout << digits << " -> " << combinations << std::endl;
}

int main() {
	test("23");

	test("");

	test("2");

	test("423");

	return 0;
}