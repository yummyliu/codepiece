class DSU {
public:
    DSU(int N) {
        ps.resize((N+1)*(N+1));
        
        for (int i=0; i<ps.size(); i++) {
            if (i<=N || i>=(N+1)*N || (i%(N+1)==0) || (i%(N+1)==N))
                ps[i] = 0;
            else
                ps[i] = i;
        }
    }
    
    int getParent(int i) {
        while (ps[i] != i) {
            i = ps[i];
        }
        
        return i;
    }
    
    void Union(int pa, int pb) {
        // pa <= pb
        
        ps[pb] = pa;
    }
    
private:
    vector<int> ps;
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int N = grid.size();
        DSU dsu(N);

        int ret=1;
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                char curc = grid[i][j];
                if (curc==' ') continue;
                
                if (curc=='\\') {
                    int pa = dsu.getParent(i*(N+1)+j);
                    int pb = dsu.getParent((i+1)*(N+1)+j+1);
                    if (pa == pb)
                        ret++;
                    else
                        dsu.Union(min(pa, pb), max(pa, pb));
                } else if (curc=='/') {
                    int pa = dsu.getParent(i*(N+1)+j+1);
                    int pb = dsu.getParent((i+1)*(N+1)+j);
                    if (pa == pb)
                        ret++;
                    else
                        dsu.Union(min(pa, pb), max(pa, pb));
                }
            }
        }        
        
        return ret;
    }
};
