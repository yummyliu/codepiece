package main

import (
	"fmt"
)

type unionFindSet struct {
	id []int
	size []int
	maxSize int
}

func (uf *unionFindSet) init(length int) {
	uf.id = make([]int, length)
	uf.size = make([]int, length)
	for i,_ := range uf.id {
		uf.size[i] = 1
		uf.id[i] = i
	}
	uf.maxSize = 0
}

func (uf *unionFindSet) root(i int) int {
	for {
		if i != uf.id[i] {
			uf.id[i] = uf.id[uf.id[i]] // Keeps tree almost completely flat.
			i = uf.id[i]
		} else {
			break
		}
	}
	return i
}

func (uf *unionFindSet) unite(p, q int) {
	i := uf.root(p)
	j := uf.root(q)
	if uf.size[i] > uf.size[j] { // merge smaller tree into larger tree
		uf.id[j] = i
		uf.size[i] += uf.size[j]
		if uf.size[i] > uf.maxSize {
			uf.maxSize = uf.size[i]
		}
	} else {
		uf.id[i] = j
		uf.size[j] += uf.size[i]
		if uf.size[j] > uf.maxSize {
			uf.maxSize = uf.size[j]
		}
	}
}

// unionFind way
func longestConsecutive(nums []int) int {
	uf := unionFindSet{}
	uf.init(len(nums))

	m := make(map[int]bool)
	for _,n := range nums {
		if _,flag := m[n]; flag {
			continue
		}
		if m[n-1] {
			uf.unite(n,n-1)
		}
		if m[n+1] {
			uf.unite(n,n+1)
		}
		m[n] = true
	}
	return uf.maxSize
}

// sort and search
func longestConsecutiveV1(nums []int) int {
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

// one simple way
func longestConsecutiveV2(nums []int) int {
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
	//nums := [...]int{1, 2, 0, 1}
	nums := [...]int{100, 4, 200, 1, 3, 2}

	l := longestConsecutive(nums[:])
	fmt.Println(l)

}
