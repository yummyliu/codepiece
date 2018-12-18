#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        if (matrix.size() == 0)
            return true;

        int M = matrix.size();
        int N = matrix[0].size();

        int i=0;
        for (int j=0; j<N; j++) {
            int pre=matrix[i][j];
            for (;i<M && j<N && pre==matrix[i][j]; j++,i++);
            if (i<M && j<N && pre!=matrix[i][j]){
                return false;
            }
        }

        int j=0;
        for (int i=1; i<M; i++) {
            int pre = matrix[i][j];
            for (;i<M && j<N && pre==matrix[i][j]; j++,i++);
            if (i<M && j<N && pre!=matrix[i][j]){
                return false;
            }
        }

        return true;
    }
};

int main(int argc, char *argv[])
{
	Solution s;
	vector<vector<int>> mm = {{1,2,3,4},{5,1,2,3},{9,5,1,2}};
	std::cout <<s.isToeplitzMatrix(mm)<< std::endl;
	return 0;
}
