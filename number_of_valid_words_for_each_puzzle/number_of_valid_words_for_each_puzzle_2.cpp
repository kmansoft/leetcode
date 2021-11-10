#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int wordToMask(const std::string& word) {
	int mask = 0;
	for (const auto ch : word) {
		mask |= 1 << (ch - 'a');
	}
	return mask;
}

std::vector<int> findNumOfValidWords(std::vector<std::string>& words,
									 std::vector<std::string>& puzzles) {
	const auto wordSize = words.size();
	const auto puzzleSize = puzzles.size();

	std::unordered_map<int, int> wordMaskCounts;

	for (int i = 0; i < wordSize; i += 1) {
		const auto& word = words[i];
		wordMaskCounts[wordToMask(word)] += 1;
	}

	std::vector<int> answer;
	answer.reserve(puzzleSize);

	for (int i = 0; i < puzzleSize; i += 1) {
		const auto& puzzle = puzzles[i];
		const int firstBit = 1 << (puzzle[0] - 'a');
		const int mask = wordToMask(puzzle);

		int count = 0;
		for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
			if ((submask & firstBit) != 0) {
				count += wordMaskCounts[submask];
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