class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int roomNum = rooms.size();
        bool visited[roomNum];
        memset(visited, false, sizeof(visited));
        visited[0] = true;
        queue<int> q;
        for(int i = 0; i < rooms[0].size(); i++) {
            if(!visited[rooms[0][i]]) {
                q.push(rooms[0][i]);
                visited[rooms[0][i]] = true;
            }
        }
        while(!q.empty()) {
            int temp = q.front();
            q.pop();
            if(!visited[temp]) {
                for(int i = 0; i < rooms[temp].size(); i++) {
                    if(!visited[rooms[temp][i]]) {
                        q.push(rooms[temp][i]);
                        visited[rooms[temp][i]] = true;
                    }
                }
            }
        }
        bool flag = true;
        for(int i = 0; i < roomNum; i++) if(!visited[i]) flag = false;
        return flag;
    }
};
