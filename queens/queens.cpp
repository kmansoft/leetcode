#include <cstdlib>
#include <cstring>
#include <cstdio>

class Board {
friend class Printer;

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

class Printer {
public:
	Printer();

	void print(const Board& board, int size);

private:
	int mCount;
};

Printer::Printer(): mCount(0) {
}

void Printer::print(const Board& board, int size) {
	if (mCount++ > 0) {
		putchar('\n');
	}

	for (int row = size - 1; row >= 0; row -= 1) {
		for (int col = 0; col < size; col += 1) {
			if (board.mRow[col] == row) {
				putchar('*');
			} else {
				putchar('-');
			}
		}
		putchar('\n');
	}
}

void generate(Board board,
	int curr, int size,
	Printer& printer) {

	for (int row = 0; row < size; row += 1) {
		if (board.set(curr, row)) {
			if (curr + 1 == size) {
				printer.print(board, size);
			} else {
				generate(board, curr + 1, size, printer);
			}
		}
	}
}

void queens(int size) {
	Board board;
	Printer printer;


	generate(board, 0, size, printer);
}
