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
	if len(nums) <1 {
		return 0
	}

	sort.Ints(nums)
	fmt.Println(nums)

	curLen := 0
	maxLen := 0
	index  := 0
	curNum := nums[0]-1
	for {
		if maxLen < curLen {
			maxLen = curLen
			curLen = 0
			if index >= len(nums) {
				break
			}
			curNum = nums[index]-1
		}
		if index < len(nums) && nums[index] == curNum +1 {
			curLen ++
			curNum = nums[index]
		}
		index ++
	}
	return maxLen
}

func main() {
//	nums := [...]int{100, 4, 200, 1, 3, 2}
	nums := [...]int{9,1,4,7,3,-1,0,5,8,-1,6}

	l := longestConsecutive(nums[:])
	fmt.Println(l)
}
