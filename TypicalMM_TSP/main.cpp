#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>

#include <vector>

using namespace std;

/// <summary>
/// 一定時間の経過したか確認するクラス
/// </summary>
class Timer {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Timer() = default;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(ナノ秒)</param>
	Timer(const std::chrono::nanoseconds& _time) { type = Type::nanoseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(マイクロ秒)</param>
	Timer(const std::chrono::microseconds& _time) { type = Type::microseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	Timer(const std::chrono::milliseconds& _time) { type = Type::milliseconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(秒)</param>
	Timer(const std::chrono::seconds& _time) { type = Type::seconds; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(分)</param>
	Timer(const std::chrono::minutes& _time) { type = Type::minutes; time = _time.count(); }
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(時)</param>
	Timer(const std::chrono::hours& _time) { type = Type::hours; time = _time.count(); }

	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(ナノ秒)</param>
	void set(const std::chrono::nanoseconds& _time) { type = Type::nanoseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(マイクロ秒)</param>
	void set(const std::chrono::microseconds& _time) { type = Type::microseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	void set(const std::chrono::milliseconds& _time) { type = Type::milliseconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(秒)</param>
	void set(const std::chrono::seconds& _time) { type = Type::seconds; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(分</param>
	void set(const std::chrono::minutes& _time) { type = Type::minutes; time = _time.count(); }
	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(時)</param>
	void set(const std::chrono::hours& _time) { type = Type::hours; time = _time.count(); }

	/// <summary>
	/// タイマーを開始させる
	/// </summary>
	void start() { s = std::chrono::high_resolution_clock::now(); }

	inline long long diff() const {
		const auto e = std::chrono::high_resolution_clock::now();
		switch (type)
		{
		case Type::nanoseconds: return std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count();
		case Type::microseconds: return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
		case Type::milliseconds: return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
		case Type::seconds: return std::chrono::duration_cast<std::chrono::seconds>(e - s).count();
		case Type::minutes: return std::chrono::duration_cast<std::chrono::minutes>(e - s).count();
		case Type::hours: return std::chrono::duration_cast<std::chrono::hours>(e - s).count();
		default: return true;
		}
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	inline const bool check() const {
		return diff() >= time;
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	operator bool() const { return check(); }

private:

	enum class Type {
		nanoseconds,
		microseconds,
		milliseconds,
		seconds,
		minutes,
		hours
	};

	std::chrono::time_point<std::chrono::high_resolution_clock> s;
	long long time;
	Type type;

};

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

const double inline random() {

	static random_device rnd;
	static mt19937 mt(rnd());

	static uniform_real_distribution<> bet(0, 1.0);

	return bet(mt);
}

class Mountain {
private:



public:

	Mountain() {

	}

	vector<Point> think(const vector<Point>& points) {

		vector<Point> field = points;
		vector<Point> best = field;

		const int size = static_cast<int>(points.size());

		random_device rnd;
		mt19937 mt(rnd());

		uniform_int_distribution<> randBetween(0, size - 1);

		Timer timer(10000ms);

		timer.start();
		while (!timer)
		{
			const int index = randBetween(mt);

			const int p0 = index;
			const int p1 = (index + 1) % size;
			const int p2 = (index + 2) % size;
			const int p3 = (index + 3) % size;

			const double baseRange = range(field[p0], field[p1]) + range(field[p1], field[p2]) + range(field[p2], field[p3]);
			const double deffRange = range(field[p0], field[p2]) + range(field[p2], field[p1]) + range(field[p1], field[p3]);

			if (baseRange > deffRange)
			{
				swap(field[p1], field[p2]);
				best = field;
			}
		}

		return best;
	}

};

class Annealing {
private:

	const int T = 10000;

	bool probability(const double& base, const double& next, const long long& t) const {

		if (base > next) return true;

		const double pro = static_cast<double>(T - t) / T;

		return pro > random();
	}

public:

	Annealing() {

	}

	vector<Point> think(const vector<Point>& points) {

		vector<Point> field = points;
		vector<Point> best = field;

		const int size = static_cast<int>(points.size());

		random_device rnd;
		mt19937 mt(rnd());

		uniform_int_distribution<> randBetween(0, size - 1);

		Timer timer(chrono::milliseconds(this->T));

		timer.start();
		while (!timer)
		{
			const auto diff = timer.diff();
			const int index = randBetween(mt);

			const int p0 = index;
			const int p1 = (index + 1) % size;
			const int p2 = (index + 2) % size;
			const int p3 = (index + 3) % size;

			const double baseRange = range(field[p0], field[p1]) + range(field[p1], field[p2]) + range(field[p2], field[p3]);
			const double deffRange = range(field[p0], field[p2]) + range(field[p2], field[p1]) + range(field[p1], field[p3]);

			if (probability(baseRange, deffRange, diff))
			{
				swap(field[p1], field[p2]);
				best = field;
			}
		}

		return best;
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

	//Mountain ai;
	Annealing ai;

	const auto answer = ai.think(points);
	//const auto answer = points;

	for (const auto& pos : answer)
	{
		cout << pos.id << endl;
	}

	return 0;
}
