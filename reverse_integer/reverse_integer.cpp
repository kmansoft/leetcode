#include <climits>
#include <iostream>

constexpr int MAX_VALUE = 0x7fffffff;
constexpr int MIN_VALUE = -MAX_VALUE - 1;

int reverse(int x) {
	if (x <= MIN_VALUE || x > MAX_VALUE || x == 0) {
		return 0;
	}

	const bool neg = x < 0;
	unsigned int abs = neg ? -x : x;

	unsigned int high = 1, low = 1, accum = 0;
	while (high < abs && high < 1000000000) {
		high *= 10;
	}
	if (high > abs) {
		high /= 10;
	}

	while (high > 0 && abs > 0) {
		unsigned int digit = abs / high;
		unsigned int add = digit * low;
		if (digit != 0 && add / digit != low) {
			return 0;
		}

		accum += add;
		if (accum > MAX_VALUE) {
			return 0;
		}

		abs -= digit * high;
		high /= 10;
		low *= 10;
	}

	return neg ? -accum : accum;
}

void test(int value, int expected) {
	int z = reverse(value);

	std::cout << value << " -> " << z << std::endl;
	if (z != expected) {
		std::cout << "FAILURE: expected " << expected << std::endl;
	}
}

int main() {
	test(1563847412, 0);

	test(1534236469, 0);

	test(2147483641, 1463847412);

	test(2147483647, 0);

	test(-2147483641, -1463847412);

	test(123, 321);

	test(-123, -321);

	test(120, 21);

	test(500000, 5);

	test(0, 0);

	test(901000, 109);

	return 0;
}