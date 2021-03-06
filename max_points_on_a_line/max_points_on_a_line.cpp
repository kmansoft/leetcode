#include <cmath>
#include <unordered_set>
#include <vector>
#include <iostream>

class Line {
public:
	Line(int x0, int y0, int x1, int y1);
	int hash() const;
	bool equal_to(const Line& l) const;

	mutable int count;

private:
	int dy, dx;
	int hash_value;
};

Line::Line(int x0, int y0, int x1, int y1) {

	dx = x1 - x0;
	dy = y1 - y0;

	if (dx == 0) {
		hash_value = x0;
	} else {
		hash_value = std::round(double(dy) / dx);
	}

	count = 0;
}

int Line::hash() const {
	return hash_value;
}

bool Line::equal_to(const Line& l) const {
	return dy * l.dx == l.dy * dx;
}

template<>
struct std::hash<Line> {
	size_t operator()(const Line& l) const {
		return l.hash();
	}
};

template<>
struct std::equal_to<Line> {
	bool operator()(const Line& l0, const Line& l1) const {
		return l0.equal_to(l1);
	}
};

int maxPoints(const std::vector<std::vector<int>>& points) {
	auto size = points.size();
	if (size == 1) {
		return 1;
	}

	int maxCount = 0;
	std::unordered_set<Line> lineSet;

	for (int i = 0; i < size; i += 1) {
		const std::vector<int>& pt0 = points[i];
		lineSet.clear();

		for (int j = i + 1; j < size; j += 1) {
			const std::vector<int>& pt1 = points[j];

			Line line(pt0[0], pt0[1], pt1[0], pt1[1]);
			std::unordered_set<Line>::iterator iter = lineSet.find(line);

			if (iter == lineSet.end()) {
				line.count = 1;
				lineSet.insert(line);
			} else {
				(*iter).count += 1;
			}
		}

		for (auto &line : lineSet) {
			int lineCount = line.count;
			if (maxCount < lineCount) {
				maxCount = lineCount;
			}
		}
	}

	return maxCount + 1;
}

int main() {
	std::vector<std::vector<int>> points =
		{
			// {0,0},{5151,5150},{5152,5151}

			// {0,-72}, {12,-22}, {54,153}

			{54,153},{1,3},{0,-72},{-3,3},{12,-22},
			{-60,-322},{0,-5},{-5,1},{5,5},{36,78},
			{3,-4},{5,0},{0,4},{-30,-197},{-5,0},
			{60,178},{0,0},{30,53},{24,28},{4,5},
			{2,-2},{-18,-147},{-24,-172},{-36,-222},{-42,-247},
			{2,3},{-12,-122},{-54,-297},{6,-47},{-5,3},
			{-48,-272},{-4,-2},{3,-2},{0,2},{48,128},
			{4,3},{2,4}

			// {3,4},{4,5},{7,8}

			// {3,4},{4,5},{7,8},{8,9},{5,6},
			// {11, 13}, {12, 14}, {13, 15}, {14, 16}, {15, 17}, {16, 18}, {17, 19}, {18, 20},
			// { 1, 3}, { 2, 4}, { 3, 5}, { 4, 6}, {5, 7}, {6, 8}, {7, 9}, {8, 10}, {9, 11}, {10, 12}
			// {-6,-1},{3,1},{12,3}
			// { 1, 1}, { 2, 2}, { 3, 3},
			//
		};

	std::cout << maxPoints(points) << std::endl;

	return 0;
}
