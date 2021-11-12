#include <initializer_list>
#include <iostream>
#include <unordered_set>
#include <vector>

struct Word {
	std::string s;
	mutable int seed;
	mutable int count;
	mutable int used;

	Word(const std::string& word) : s(word), count(1), used(0) {}
};

template <>
struct std::hash<Word> {
	std::hash<string> stringHash;

	size_t operator()(const Word& w) const { return stringHash(w.s); }
};

template <>
struct std::equal_to<Word> {
	bool operator()(const Word& w0, const Word& w1) const {
		return w0.s == w1.s;
	}
};

bool isSubstring(const std::string& s, int start, size_t wordSize,
				 size_t wordLen, std::unordered_set<Word>& wordSet) {
	const std::unordered_set<Word>::const_iterator wordSetEnd = wordSet.end();

	const size_t end = start + wordSize * wordLen;
	for (size_t i = start; i < end; i += wordLen) {
		const Word subWord(s.substr(i, wordLen));
		const std::unordered_set<Word>::iterator subFind =
			wordSet.find(subWord);

		if (subFind == wordSetEnd) {
			return false;
		}
		const Word& subFound = *subFind;
		if (subFound.seed != start) {
			subFound.seed = start;
			subFound.used = 0;
		}
		if (subFound.used >= subFound.count) {
			return false;
		}
		subFound.used += 1;
	}

	return true;
}

std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
	std::vector<int> result;

	size_t wordSize = words.size(), wordLen;
	std::unordered_set<Word> wordSet(wordSize);
	const std::unordered_set<Word>::const_iterator wordSetEnd = wordSet.end();

	for (const auto& w : words) {
		const Word word(w);
		const std::unordered_set<Word>::iterator find = wordSet.find(word);
		if (find == wordSetEnd) {
			wordSet.insert(Word(word));
		} else {
			const Word& found = *find;
			found.count += 1;
		}
		wordLen = w.length();
	}

	int end = s.length() - wordSize * wordLen;
	for (int i = 0; i <= end; i += 1) {
		if (isSubstring(s, i, wordSize, wordLen, wordSet)) {
			result.push_back(i);
		}
	}

	return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
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

void test(const std::string s,
		  const std::initializer_list<std::string>& wordsInit) {
	std::vector<std::string> wordsList(wordsInit);
	std::vector<int> result = findSubstring(s, wordsList);

	std::cout << s << ", " << wordsList << " -> " << result << std::endl;
}

int main() {
	test("a", {"a", "a"});

	test("a", {"a"});

	test("wordgoodgoodgoodbestword", {"word", "good", "best", "good"});

	test("barfoothefoobarman", {"foo", "bar"});

	test("wordgoodgoodgoodbestword", {"word", "good", "best", "word"});

	test("barfoofoobarthefoobarman", {"bar", "foo", "the"});

	return 0;
}