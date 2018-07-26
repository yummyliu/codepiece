// You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:
//
// 0 represents the obstacle can't be reached.
// 1 represents the ground can be walked through.
// The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
// You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree with lowest height first. And after cutting, the original place has the tree will become a grass (value 1).
//
// You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees. If you can't cut off all the trees, output -1 in that situation.
//
// You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.
//
// Example 1:
// Input:
// [
//  [1,2,3],
//  [0,0,4],
//  [7,6,5]
// ]
// Output: 6
// Example 2:
// Input:
// [
//  [1,2,3],
//  [0,0,0],
//  [7,6,5]
// ]
// Output: -1
// Example 3:
// Input:
// [
//  [2,3,4],
//  [0,0,5],
//  [8,7,6]
// ]
// Output: 6
// Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
// Hint: size of the given matrix will not exceed 50x50.
//
// 题意解释：
// 有一个不大于50*50的迷宫，其中有若干数；找到迷宫中大于1的最小数的位置[i,j]和最大数[m,n]，按顺序从[i,j]走到[m,n]的步数。
// 1可以走，0不可以走，走过的位置都是1
package main

import (
	"container/heap"
	"container/list"
	"fmt"
)

type TreePos struct {
	X int
	Y int
	h int
}

type Point struct {
	X int
	Y int
}

type TreeHeap []TreePos

func (t TreeHeap) Len() int {
	return len(t)
}

func (t TreeHeap) Less(i, j int) bool {
	return t[i].h < t[j].h
}

func (t TreeHeap) Swap(i, j int) {
	t[i], t[j] = t[j], t[i]
}

func (t *TreeHeap) Push(p interface{}) {
	// insert in the last
	*t = append(*t, p.(TreePos))
	// Fix the min heap property if it is violated
	i := len(*t) - 1
	for i >= 0 && t.Less(i, (i-1)/2) {
		t.Swap((i-1)/2, i)
		i = (i - 1) / 2
	}
}

func (t *TreeHeap) Pop() interface{} {
	x := (*t)[0]

	newheapSize := len(*t) - 1
	(*t)[0] = (*t)[newheapSize]
	*t = (*t)[0:newheapSize]

	// Fix it
	i := 0
	for i < newheapSize && (2*i)+1 < newheapSize {
		upPos := (2 * i) + 1
		if (2*i)+2 < newheapSize && t.Less((2*i)+2, (2*i)+1) {
			upPos = (2 * i) + 2
		}
		if t.Less(upPos, i) {
			t.Swap(i, upPos)
		}
		i = upPos
	}

	return x
}

func bfs(maze [][]int, p1, p2 Point) int {

	// local var
	action := [][2]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}
	colsize := len(maze[0])
	rowsize := len(maze)

	// BFS init
	opened_set_odd := list.New()
	opened_set_even := list.New()
	closed_set := make([]bool, len(maze)*len(maze[0]))

	opened_set_odd.PushBack(p1)
	closed_set[p1.X*colsize+p1.Y] = true
	step_len := 0
	for opened_set_even.Len() > 0 || opened_set_odd.Len() > 0 {
		if opened_set_even.Len() > 0 {
			for opened_set_even.Len() > 0 {
				cur := opened_set_even.Front().Value.(Point)
				opened_set_even.Remove(opened_set_even.Front())

				if cur.X == p2.X && cur.Y == p2.Y {
					return step_len
				}

				for i := 0; i < len(action); i++ {
					// go on next step
					if cur.X+action[i][0] < 0 ||
						cur.X+action[i][0] >= rowsize ||
						cur.Y+action[i][1] < 0 ||
						cur.Y+action[i][1] >= colsize ||
						closed_set[(cur.X+action[i][0])*colsize+cur.Y+action[i][1]] ||
						maze[cur.X+action[i][0]][cur.Y+action[i][1]] == 0 {
						continue
					}

					opened_set_odd.PushBack(Point{cur.X + action[i][0], cur.Y + action[i][1]})
					closed_set[(cur.X+action[i][0])*colsize+cur.Y+action[i][1]] = true
				}
			}
		} else {
			for opened_set_odd.Len() > 0 {
				cur := opened_set_odd.Front().Value.(Point)
				opened_set_odd.Remove(opened_set_odd.Front())

				if cur.X == p2.X && cur.Y == p2.Y {
					return step_len
				}

				for i := 0; i < len(action); i++ {
					if cur.X+action[i][0] < 0 ||
						cur.X+action[i][0] >= rowsize ||
						cur.Y+action[i][1] < 0 ||
						cur.Y+action[i][1] >= colsize ||
						closed_set[(cur.X+action[i][0])*colsize+cur.Y+action[i][1]] ||
						maze[cur.X+action[i][0]][cur.Y+action[i][1]] == 0 {
						continue
					}

					opened_set_even.PushBack(Point{cur.X + action[i][0], cur.Y + action[i][1]})
					closed_set[(cur.X+action[i][0])*colsize+cur.Y+action[i][1]] = true
				}
			}
		}
		step_len++
	}

	return -1
}

func cutOffTree(forest [][]int) int {
	minTreeHeap := &TreeHeap{}
	heap.Init(minTreeHeap)

	for i := 0; i < len(forest); i++ {
		for j := 0; j < len(forest[0]); j++ {
			if forest[i][j] > 1 {
				heap.Push(minTreeHeap, TreePos{i, j, forest[i][j]})
			}
		}
	}

	last := minTreeHeap.Pop()
	sum := bfs(forest, Point{0, 0}, Point{last.(TreePos).X, last.(TreePos).Y})
	for minTreeHeap.Len() > 0 {
		cur := minTreeHeap.Pop()
		next_step := bfs(forest, Point{last.(TreePos).X, last.(TreePos).Y}, Point{cur.(TreePos).X, cur.(TreePos).Y})
		if next_step == -1 {
			return -1
		}
		sum += next_step
		last = cur
	}
	return sum
}

func main() {
	forest := [][]int{
		{3, 2, 1},
		{0, 0, 0},
		{7, 6, 5},
	}

	res := cutOffTree(forest)
	fmt.Println(res)
}
