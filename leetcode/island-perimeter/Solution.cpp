#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int M = grid.size();
        int N = grid[0].size();
        vector<vector<int>> direction = {{0,1},{0,-1},{1,0},{-1,0}};

        vector<vector<bool>> adjoinSet(N*M,vector<bool>(N*M,false));
        int sum = 0;
		int adjoinSize = 0;
        for (int i = 0; i<M; i++) {
            for (int j = 0; j<N; j++) {
                if (0 == grid[i][j]) continue;

                sum++;
                for (int k = 0; k<4; k++) {
                    if (i+direction[k][0] <0
                       || i+direction[k][0] >= M
                       || j+direction[k][1] <0
                       || j+direction[k][1] >= N)
                        continue;

                    int nxti = i+direction[k][0];
                    int nxtj = j+direction[k][1];
                    if (grid[nxti][nxtj] && !adjoinSet[i*M+j][nxti*M+nxtj]) {
						adjoinSize ++;
                        adjoinSet[i*M+j][nxti*M+nxtj] = true;
                        adjoinSet[nxti*M+nxtj][i*M+j] = true;
                    }
                }
            }
        }

        return 4*sum - 2*adjoinSize;
    }

	int islandPerimeter(vector<vector<int>>& grid) {
		int count=0, repeat=0;
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0; j<grid[i].size();j++)
                {
                    if(grid[i][j]==1)
                    {
                        count ++;
                        if(i!=0 && grid[i-1][j] == 1) repeat++;
                        if(j!=0 && grid[i][j-1] == 1) repeat++;
                    }
                }
        }
        return 4*count-repeat*2;
	}
};

int main(int argc, char *argv[])
{
	
	return 0;
}
