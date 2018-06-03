#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>

#include <vector>
#include <array>

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

struct XorShift {
	unsigned int x;
	XorShift() : x(2463534242U) {}
	unsigned int rand() {
		x ^= (x << 13);
		x ^= (x >> 17);
		x ^= (x << 5);
		return x;
	}

};

const double inline random() {

	static random_device rnd;
	static mt19937 mt(rnd());

	static uniform_real_distribution<> bet(0, 1.0);

	return bet(mt);
}

class Mountain {
private:

	/// <summary>
	/// 実行時間(ms)
	/// </summary>
	const int T = 10000;

	const double TempStart = 10000.0;
	const double TempEnd = 1.0;
	const double Time = T;
	const double TempDiff = (TempStart - TempEnd) / Time;

	XorShift random;
	int size;

	bool probability(const double& base, const double& next, const long long& t) {

		const double diff = base - next;

		if (diff > 0) return true;

		return false;
	}

	const double getScore(const array<int, 1000>& index, const vector<Point>& points) const {

		double r = 0;

		for (int i = 0; i < size - 1; i++)
			r += range(points[index[i]], points[index[i + 1]]);
		r += range(points[index[0]], points[index[size - 1]]);

		return r;
	}

	void change(const int index, const int width, array<int, 1000>& field) {

		for (int i = 0; i < width / 2 - 1; i++)
		{
			int p1 = (index + (i + 1)) % size;
			int p2 = (index + (width - 1) - (i + 1)) % size;

			swap(field[p1], field[p2]);
		}
	}

public:

	Mountain() {

	}

	vector<int> think(const vector<Point>& points) {

		size = static_cast<int>(points.size());

		array<int, 1000> field;
		for (int i = 0; i < size; i++)
		{
			field[i] = points[i].id;
		}
		array<int, 1000> best = field;

		random_device rnd;
		mt19937 mt(rnd());

		uniform_int_distribution<> randIndex(0, size - 1);

		Timer timer(chrono::milliseconds(this->T));

		double bestScore = getScore(best, points);
		double score = getScore(field, points);

		long long count = 0;

		timer.start();
		while (!timer)
		{
			const auto diff = timer.diff();

			for (int i = 0; i < 100; i++)
			{
				const int index = randIndex(mt);

				int width = 4;

				for (int i = 0; i < 8; i++)
				{
					if (random.rand() % 4 == 0) break;
					width += random.rand() % 8 + 1;
				}

				count++;

				const int p0 = index;
				const int p1 = (index + 1) % size;
				const int p2 = (index + width - 2) % size;
				const int p3 = (index + width - 1) % size;

				const double baseRange = range(points[field[p0]], points[field[p1]]) + range(points[field[p2]], points[field[p3]]);
				const double deffRange = range(points[field[p0]], points[field[p2]]) + range(points[field[p1]], points[field[p3]]);

				if (probability(baseRange, deffRange, diff))
				{
					change(p0, width, field);

					score -= baseRange - deffRange;

					if (bestScore > score)
					{
						best = field;
						bestScore = score;
					}
				}
			}
		}

		cerr << count << endl;

		vector<int> ans(size);
		for (int i = 0; i < size; i++)
		{
			ans[i] = best[i];
		}

		return ans;
	}

};

class Annealing {
private:

	/// <summary>
	/// 実行時間(ms)
	/// </summary>
	const int T = 100000;

	const double TempStart = 10000.0;
	const double TempEnd = 1.0;
	const double Time = T;
	const double TempDiff = (TempStart - TempEnd) / Time;

	XorShift random;
	int size;

	bool probability(const double& base, const double& next, const long long& t) {

		const double diff = base - next;

		if (diff > 0) return true;

		const double temp = TempStart - TempDiff * t;

		const double p = exp(diff / temp) * 4294967295.0;

		return p > random.rand();
	}

	const double getScore(const array<int, 1000>& index, const vector<Point>& points) const {

		double r = 0;

		for (int i = 0; i < size - 1; i++)
			r += range(points[index[i]], points[index[i + 1]]);
		r += range(points[index[0]], points[index[size - 1]]);

		return r;
	}

	void change(const int index, const int width, array<int, 1000>& field) {

		for (int i = 0; i < width / 2 - 1; i++)
		{
			int p1 = (index + (i + 1)) % size;
			int p2 = (index + (width - 1) - (i + 1)) % size;

			swap(field[p1], field[p2]);
		}
	}

public:

	Annealing() {

	}

	vector<int> think(const vector<Point>& points) {

		size = static_cast<int>(points.size());

		array<int, 1000> field;
		for (int i = 0; i < size; i++)
		{
			field[i] = points[i].id;
		}
		array<int, 1000> best = field;

		random_device rnd;
		mt19937 mt(rnd());

		uniform_int_distribution<> randIndex(0, size - 1);

		Timer timer(chrono::milliseconds(this->T));

		double bestScore = getScore(best, points);
		double score = getScore(field, points);

		long long count = 0;

		timer.start();
		while (!timer)
		{
			const auto diff = timer.diff();

			for (int i = 0; i < 5000; i++)
			{
				const int index = randIndex(mt);

				int width = 4;

				for (int i = 0; i < 8; i++)
				{
					if (random.rand() % 4 == 0) break;
					width += random.rand() % 8 + 1;
				}

				count++;

				const int p0 = index;
				const int p1 = (index + 1) % size;
				const int p2 = (index + width - 2) % size;
				const int p3 = (index + width - 1) % size;

				const double baseRange = range(points[field[p0]], points[field[p1]]) + range(points[field[p2]], points[field[p3]]);
				const double deffRange = range(points[field[p0]], points[field[p2]]) + range(points[field[p1]], points[field[p3]]);

				if (probability(baseRange, deffRange, diff))
				{
					change(p0, width, field);

					score -= baseRange - deffRange;

					if (bestScore > score)
					{
						best = field;
						bestScore = score;
					}
				}
			}
		}

		cerr << count << endl;

		vector<int> ans(size);
		for (int i = 0; i < size; i++)
		{
			ans[i] = best[i];
		}

		return ans;
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
		cout << pos << endl;
	}

	return 0;
}
