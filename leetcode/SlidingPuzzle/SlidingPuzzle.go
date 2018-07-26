// On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.
//
// A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
//
// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
//
// Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
//
// Examples:
//
// Input: board = [[1,2,3],[4,0,5]]
// Output: 1
// Explanation: Swap the 0 and the 5 in one move.
// Input: board = [[1,2,3],[5,4,0]]
// Output: -1
// Explanation: No number of moves will make the board solved.
// Input: board = [[4,1,2],[5,0,3]]
// Output: 5
// Explanation: 5 is the smallest number of moves that solves the board.
// An example path:
// After move 0: [[4,1,2],[5,0,3]]
// After move 1: [[4,1,2],[0,5,3]]
// After move 2: [[0,1,2],[4,5,3]]
// After move 3: [[1,0,2],[4,5,3]]
// After move 4: [[1,2,0],[4,5,3]]
// After move 5: [[1,2,3],[4,5,0]]
// Input: board = [[3,2,4],[1,5,0]]
// Output: 14
// Note:
//
// board will be a 2 x 3 array as described above.
// board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].

package main

import (
	"container/list"
	"fmt"
)

type Snapshot struct {
	zeroPos int
	board [6]int
}

func (ss Snapshot) oneStep(ac int) (Snapshot, bool) {
	if ( ss.zeroPos == 2 && ac == 1 ) ||
	( ss.zeroPos == 3 && ac == -1 ) {
		return ss,false
	}
	newPos := ss.zeroPos + ac
	if newPos < 0 || newPos > 5 {
		return ss, false
	}
	// make one step
	ss.board[ss.zeroPos],ss.board[newPos] = ss.board[newPos],ss.board[ss.zeroPos]

	ss.zeroPos = newPos

	return ss,true
}

func slidingPuzzle(board [][]int) int {
	// local var
	ac := []int{1, -1, 3, -3}
	final := Snapshot{5,[6]int{1, 2, 3, 4, 5, 0}}
	var cur Snapshot
	ti := 0
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			cur.board[ti] = board[i][j]
			if board[i][j] == 0 {
				cur.zeroPos = ti
			}
			ti++
		}
	}

	closedSet := make(map[[6]int]bool)
	openSet_odd := list.New()
	openSet_even := list.New()

	openSet_odd.PushBack(cur)
	closedSet[cur.board] = true
	step_len := -1
	for openSet_odd.Len() > 0 || openSet_even.Len() > 0 {
		if openSet_odd.Len() > 0 {
			for openSet_odd.Len() > 0 {

				cur = openSet_odd.Front().Value.(Snapshot)
				openSet_odd.Remove(openSet_odd.Front())

				if cur.board== final.board {
					step_len++
					return step_len
				}
				for i := 0; i < len(ac); i++ {
					tmp,stepOk := cur.oneStep(ac[i])
					if !closedSet[tmp.board] &&
						stepOk {
						openSet_even.PushBack(tmp)
						closedSet[tmp.board] = true
					}
				}
			}
		} else if openSet_even.Len() > 0 {
			for openSet_even.Len() > 0 {

				cur = openSet_even.Front().Value.(Snapshot)
				openSet_even.Remove(openSet_even.Front())

				if cur.board == final.board {
					step_len++
					return step_len
				}
				for i := 0; i < len(ac); i++ {
					tmp,stepOk := cur.oneStep(ac[i])
					if !closedSet[tmp.board] &&
						stepOk {
						openSet_odd.PushBack(tmp)
						closedSet[tmp.board] = true
					}
				}
			}
		}
		step_len++
	}

	return -1
}

func main() {
	board := [][]int{
		{3, 2, 4},
		{1, 5, 0},
//		{4, 1, 2},
//		{5, 0, 3},
//		{1, 2, 3},
//		{4, 0, 5},
	}

	fmt.Println(slidingPuzzle(board))
}
