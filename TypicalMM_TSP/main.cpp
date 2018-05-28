#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include <vector>

using namespace std;

struct Point {

	Point() {}
	Point(int _id, int _x, int _y) {
		id = _id;
		x = _x;
		y = _y;
	}

	int id = -1;

	int x = -1;
	int y = -1;
};

ostream& operator<<(ostream& os, const Point& pos) {
	os << "{" << pos.id << ", (" << pos.x << " " << pos.y << ")";
	return os;
}

const double inline range(const Point& p1, const Point& p2) {
	const double dx = p1.x - p2.x;
	const double dy = p1.y - p2.y;
	return dx * dx + dy * dy;
}

class Mountain {
private:


public:

	Mountain() {

	}

	vector<Point> think(const vector<Point>& points) {



		return vector<Point>();
	}

};

class Annealing {
private:


public:

	Annealing() {

	}

	vector<Point> think(const vector<Point>& points) {



		return vector<Point>();
	}

};

int main() {

	int n;

	cin >> n;
	vector<Point> points(n);

	for (int i = 0; i < n; i++)
	{
		points[i].id = i;
		cin >> points[i].x >> points[i].y;
	}

	for (const auto& pos : points)
	{
		cout << pos.id << endl;
	}

	return 0;
}
