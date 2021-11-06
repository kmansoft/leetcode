#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>

class Board {
friend class Output;

public:
	Board();
	bool set(int col, int row);

private:
	unsigned char mRow[9];
};

Board::Board() {
	memset(mRow, 0, sizeof(mRow));
}

bool Board::set(int col, int row) {
	for (int c = 0; c < col; c += 1) {
		int r = mRow[c];

		if (r == row) {
			return false;
		}

		if (row - r == col - c) {
			return false;
		}

		if (row - r == c - col) {
			return false;
		}
	}

	mRow[col] = row;
	return true;
}

class Output {
public:
	Output();

	void output(const Board& board, int size);
	std::vector<std::vector<std::string>> getOutput();

private:
	std::vector<std::vector<std::string>> mOutput;
};

Output::Output() {
}

void Output::output(const Board& board, int size) {
	std::vector<std::string> out;

	for (int row = size - 1; row >= 0; row -= 1) {
		std::string line;
		for (int col = 0; col < size; col += 1) {
			if (board.mRow[col] == row) {
				line.append("Q");
			} else {
				line.append(".");
			}
		}
		out.push_back(line);
	}

	mOutput.push_back(out);
}

std::vector<std::vector<std::string>> Output::getOutput() {
	return mOutput;
}

void generate(Board board,
	int curr, int size,
	Output& output) {

	for (int row = 0; row < size; row += 1) {
		if (board.set(curr, row)) {
			if (curr + 1 == size) {
				output.output(board, size);
			} else {
				generate(board, curr + 1, size, output);
			}
		}
	}
}

void queens(int size) {
	Board board;
	Output output;

	generate(board, 0, size, output);

	auto solutionList = output.getOutput();
	for (auto solutionIt = solutionList.begin(); solutionIt != solutionList.end(); solutionIt++) {
		if (solutionIt != solutionList.begin()) {
			puts("");
		}

		auto solution = *solutionIt;
		for (auto lineIt = solution.begin(); lineIt != solution.end(); lineIt ++) {
			puts((*lineIt).c_str());
		}
	}
}
