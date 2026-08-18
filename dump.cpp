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

    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<Point> q;
        queue<Point> q2;
        for(int i = 0; i < n; i++) {
            bool flag = false;
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    q.push({i, j, 0});
                    grid[i][j] = 2;
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        while(!q.empty()) {
            Point temp = q.front();
            q.pop();
            for(int i = 0; i < 4; i++) {
                int next_r = temp.r + dr[i];
                int next_c = temp.c + dc[i];
                if(isValid(next_r, next_c, n, n) && (grid[next_r][next_c] != 2)) {
                    if(grid[next_r][next_c] == 1) {
                        q.push({next_r, next_c, 0});
                        grid[next_r][next_c] = 2;
                    } else {
                        q2.push({next_r, next_c, 1});
                        grid[next_r][next_c] = 2;
                    }
                }
            }
        }
        int minTime = 0;
        bool flag = false;
        while(!q2.empty()) {
            if(flag) break;
            Point temp = q2.front();
            q2.pop();
            for(int i = 0; i < 4; i++) {
                int next_r = temp.r + dr[i];
                int next_c = temp.c + dc[i];
                int next_time = temp.time + 1;
                if(isValid(next_r, next_c, n, n) && (grid[next_r][next_c] != 2)) {
                    if(grid[next_r][next_c] == 0) {
                        q.push({next_r, next_c, next_time});
                        minTime = max(minTime, next_time);
                        grid[next_r][next_c] = 2;
                    } else {
                        minTime = temp.time;
                        flag = true;
                        break;
                    }
                }
            }
        }
        return minTime;
    }
};
