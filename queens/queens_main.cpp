#include <cstdlib>
#include <cstdio>

extern int queens(int size);

int main(int argc, const char** argv) {
	if (argc != 2) {
		printf("Usage: queens [size]\n");
		return 1;
	}

	int size = atoi(argv[1]);
	if (size < 1 || size > 9) {
		printf("Size must be 1 to 9\n");
		return 1;
	}

	queens(size);

	return 0;
}
