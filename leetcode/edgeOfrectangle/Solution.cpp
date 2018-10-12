// xy的坐标系，给出N个矩形的坐标（以左下顶点和右上顶点为输入），
// 所有矩形都在第一象限，底边都在X轴上，
// 可以简化认为这些矩形一定都挨着，请输出这些矩形的外轮廓点
// 样例输入： A (0, 0), (2, 1), B (1, 0), (3, 2)
// 样例输出：(0,0), (1,0) (1,1) (1,2) (3,2), (3,0)

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Point
{
public:
	Point (int x, int y): x(x),y(y) {};
	virtual ~Point (){};

	int x;
	int y;
};

class Solution
{
public:
	Solution (){};
	virtual ~Solution (){};

	vector<Point> Outlines(vector<pair<Point, Point>>& rects)
	{
		vector<Point> out;

		std::sort(rects.begin(), rects.end(), [](pair<Point,Point> a, pair<Point, Point> b) {
			if (a.first.x != b.first.x) {
				return a.first.x < b.first.x;
			} else {
				return a.second.y < b.second.y;
			}
		});

		out.push_back(rects[0].first);
		int prerectId = 0;

		char dest = 'u'; // upward
		int currectId = 0;
		while (true) {
			currectId = prerectId;
			switch (dest) {
				case 'u':
					while (最大的high) {
						
					}
					out.push_back();
					dest = 'f';
					break;
				case 'f':
					while (< size() && <prerectId.dest && <prerectId.high) {
						
					}
					交点;
					dest = 'u or d'; // 取决于是最后添加的还是中途添加的
					break;
				case 'd':
					第一个比上个点矮的点
					dest = 'f';
					break;
			}
		}

		return out;
	}

	void printRects(vector<pair<Point, Point>>& rects)
	{

	}

private:
	/* data */
};

int main(int argc, char *argv[])
{
	vector<pair<Point, Point>> rects = {{{1,0},{3,1}},{{2,0},{10,4}},{{2,0},{9,5}},{{3,0},{4,9}}};
	Solution s;

	return 0;
}
