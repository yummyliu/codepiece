package main

import (
	"fmt"
	"sort"
)

//Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
//
//For example,
//Given [100, 4, 200, 1, 3, 2],
//The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
//
//Your algorithm should run in O(n) complexity.

func longestConsecutive(nums []int) int {
	// accept
	if len(nums) < 1 {
		return 0
	}

	sort.Ints(nums)
	fmt.Println(nums)

	curLen := 1
	maxLen := 1
	index := 1
	curNum := nums[0]
	for {
		if index >= len(nums) {
			if maxLen < curLen {
				maxLen = curLen
			}
			break
		}
		if nums[index] == curNum+1 {
			curLen++
			curNum = nums[index]
			index++
			continue
		}
		if nums[index] == curNum {
			index++
			continue
		}
		if maxLen < curLen {
			maxLen = curLen
		}
		curLen = 1
		curNum = nums[index]
		index++
	}
	return maxLen
}

func longestConsecutive(nums []int) int {
	m := make(map[int]int)
	ret := 0

	for _, n := range nums[:] {
		if m[n] != 0 {
			continue
		}

		if m[n+1] == 0 && m[n-1] == 0 {
			m[n] = 1
			if ret < m[n] {
				ret = m[n]
			}
			continue
		}
		if m[n+1] == 0 {
			m[n] = m[n-1] + 1
			m[n-m[n-1]] = m[n]
			if ret < m[n] {
				ret = m[n]
			}
			continue
		}
		if m[n-1] == 0 {
			m[n] = m[n+1] + 1
			m[n+m[n+1]] = m[n]
			if ret < m[n] {
				ret = m[n]
			}
			continue
		}
		m[n] = m[n-1] + 1 + m[n+1]
		m[n-m[n-1]] = m[n]
		m[n+m[n+1]] = m[n]
		if ret < m[n] {
			ret = m[n]
		}
	}
	return ret
}

func main() {
	//nums := [...]int{100, 4, 200, 1, 3, 2}
	nums := [...]int{1, 2, 0, 1}

	l := longestConsecutiveV2(nums[:])
	fmt.Println(l)
}
