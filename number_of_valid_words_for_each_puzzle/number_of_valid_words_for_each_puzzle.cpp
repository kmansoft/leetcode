#include <iostream>
#include <string>
#include <vector>

std::vector<int> findNumOfValidWords(std::vector<std::string>& words,
									 std::vector<std::string>& puzzles) {
	const auto wordSize = words.size();
	const auto puzzleSize = puzzles.size();

	std::vector<int> wordContains['z' - 'a' + 1];
	std::vector<int> wordBits;
	wordBits.reserve(wordSize);

	for (int i = 0; i < wordSize; i += 1) {
		const auto& word = words[i];
		int bits = 0;
		for (const auto ch : word) {
			const int one = 1 << (ch - 'a');
			if ((bits & one) == 0) {
				wordContains[ch - 'a'].push_back(i);
				bits |= one;
			}
		}
		wordBits.push_back(bits);
	}

	std::vector<int> puzzleBits;
	puzzleBits.reserve(puzzleSize);

	for (int i = 0; i < puzzleSize; i += 1) {
		const auto& puzzle = puzzles[i];
		int bits = 0;
		for (const auto ch : puzzle) {
			bits |= 1 << (ch - 'a');
		}
		puzzleBits.push_back(bits);
	}

	std::vector<int> answer;
	answer.reserve(puzzleSize);

	for (int i = 0; i < puzzleSize; i += 1) {
		const auto& puzzle = puzzles[i];
		const auto first = puzzle[0];
		const auto puzzleBitsValue = puzzleBits[i];

		int count = 0;
		for (const auto j : wordContains[first - 'a']) {
			const auto wordBitsValue = wordBits[j];
			if ((puzzleBitsValue & wordBitsValue) == wordBitsValue) {
				count += 1;
			}
		}

		answer.push_back(count);
	}

	return answer;
}

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

void test(std::vector<std::string>& words, std::vector<std::string>& puzzles) {
	const auto answer = findNumOfValidWords(words, puzzles);

	std::cout << words << ", " << puzzles << " -> " << answer << std::endl;
}

int main() {
	std::vector<std::string> w0 = {"aaaa", "asas",	"able",	 "ability",
								   "actt", "actor", "access"};
	std::vector<std::string> p0 = {"aboveyz", "abrodyz", "abslute",
								   "absoryz", "actresz", "gaswxyz"};
	test(w0, p0);

	std::vector<std::string> w1 = {"apple", "pleas", "please"};
	std::vector<std::string> p1 = {"aelwxyz", "aelpxyz", "aelpsxy", "saelpxy",
								   "xaelpsy"};
	test(w1, p1);

	return 0;
}