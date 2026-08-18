class Solution {
public:
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    bool isValid(int r, int c, int m, int n) {
        return r >= 0 && c >= 0 && r < m && c < n;
    }
    struct Point {
        int r;
        int c;
        int time;
    };
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        bool visited[m][n];
        queue<Point> q;
        memset(visited, false, sizeof(visited));
        int cntOrange = 0;
        int cntTime = 0;
        int cntRotten = 0;
        int minTime = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 2) {
                    q.push({i, j, 0});
                    visited[i][j] = true;
                    cntOrange++;
                    cntRotten++;
                } else if(grid[i][j] == 1) cntOrange++;
            }
        }
        while(!q.empty()) {
            Point temp = q.front();
            q.pop();
            for(int k = 0; k < 4; k++) {
                int next_r = temp.r;
                int next_c = temp.c;
                int next_time = temp.time + 1;
                if(isValid(next_r, next_c, m, n) && (grid[next_r][next_c] == 1) && !visited[next_r][next_c]) {
                    minTime = max(minTime, next_time);
                    q.push({next_r, next_c, next_time});
                    visited[next_r][next_c] = true;
                    cntRotten++;
                }
            }
        }
        return (cntRotten == cntOrange) ? minTime : -1;
    }
};
