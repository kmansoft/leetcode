#include <initializer_list>
#include <iostream>
#include <unordered_map>
#include <vector>

bool isSubstring(const std::string& s, int start, size_t wordSize,
				 size_t wordLen, std::unordered_map<std::string, int>& wordMap,
				 std::unordered_map<std::string, int>& wordUsed) {
	wordUsed.clear();

	const std::unordered_map<std::string, int>::const_iterator wordMapEnd =
		wordMap.end();

	const size_t end = start + wordSize * wordLen;
	for (size_t i = start; i < end; i += wordLen) {
		const std::string sub = s.substr(i, wordLen);
		const std::unordered_map<std::string, int>::iterator subFind =
			wordMap.find(sub);
		if (subFind == wordMapEnd) {
			return false;
		}

		int& used = wordUsed[sub];
		if (used >= subFind->second) {
			return false;
		}
		used += 1;
	}

	return true;
}

std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
	std::vector<int> result;

	const size_t wordSize = words.size();
	if (wordSize == 0) {
		return result;
	}

	std::unordered_map<std::string, int> wordMap(wordSize), wordUsed(wordSize);
	const std::unordered_map<std::string, int>::const_iterator wordMapEnd =
		wordMap.end();

	for (const auto& w : words) {
		wordMap[w] += 1;
	}
	const size_t wordLen = wordMap.begin()->first.length();

	int end = s.length() - wordSize * wordLen;
	for (int i = 0; i <= end; i += 1) {
		if (isSubstring(s, i, wordSize, wordLen, wordMap, wordUsed)) {
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
