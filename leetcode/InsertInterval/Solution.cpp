// Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
//
// You may assume that the intervals were initially sorted according to their start times.
//
// Example 1:
//
// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
// Example 2:
//
// Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// Output: [[1,2],[3,10],[12,16]]
// Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
//
#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for an interval.
 */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> ret;

		int N = intervals.size();
		if (!N) {
			ret.push_back(newInterval);
			return ret;
		}

		int p = 0;
		while (p<N && newInterval.start > intervals[p].end) {
			ret.push_back(intervals[p]);
			p++;
		}
		int newstart = -1;
		if (p==N) {
			ret.push_back(newInterval);
			return ret;
		} else {
			newstart = min(newInterval.start, intervals[p].start);
		}

		while (p < N && newInterval.end >= intervals[p].start) {
			p++;
		}
		int newend = -1;
		if (p==N) {
			newend = max(newInterval.end, intervals[N-1].end);
			ret.push_back(Interval(newstart, newend));
		} else {
			newend = max(newInterval.end, intervals[p-1].end);
			ret.push_back(Interval(newstart, newend));

			while (p < N) {
				ret.push_back(intervals[p]);
				p++;
			}
		}

		return ret;
    }
};
