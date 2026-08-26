	#include <iostream>

	using namespace std;

	#define MAX_SIZE 20
	#define KHONG_PHAI_LUA 999999

	bool escapeGrid[MAX_SIZE][MAX_SIZE];
	int grid[MAX_SIZE][MAX_SIZE];
	int dia_grid[MAX_SIZE][MAX_SIZE];
	bool visited[MAX_SIZE][MAX_SIZE];
	int fire_time[MAX_SIZE][MAX_SIZE];
	int maxDiamond;
	int totalDiamond;
	int dr[4] = {0, -1, 0, 1};
	int dc[4] = {-1, 0, 1, 0};
	int rowNum, colNum;
	bool escape;

	struct point {
		int r;
		int c;
	};

	point q[1000];
	int front = 0;
	int rear = 0;

	bool isEmpty() {
		return front == rear;
	}

	void enQueue(int r, int c) {
		q[rear].r = r;
		q[rear].c = c;
		rear++;
	}

	void deQueue() {
		if(front < rear) {
			front++;
		}
	}

	bool checkValid(int r, int c) {
		if(r == 0 || c == 0 || r > rowNum || c > colNum) return false;
		return true;
	}

	void dfs(int cur_row, int cur_col, int cur_time, int cur_diamond) {
		if(totalDiamond == maxDiamond) return;
		visited[cur_row][cur_col] = true;
		cur_diamond += dia_grid[cur_row][cur_col];
		if(escapeGrid[cur_row][cur_col] == 1) {
			maxDiamond = max(cur_diamond, maxDiamond);
			escape = true;
		}
		for(int i = 0; i < 4; i++) {
			int next_row = cur_row + dr[i];
			int next_col = cur_col + dc[i];
			if(checkValid(next_row, next_col) && !visited[next_row][next_col]) {
				int move_time = (grid[next_row][next_col] == 2) ? 2 : 1;
				int next_time = cur_time + move_time;
				if (next_time < fire_time[next_row][next_col]) dfs(next_row, next_col, next_time, cur_diamond);
			}
		}
		visited[cur_row][cur_col] = false;
	}

	void reset() {
		maxDiamond = -1;
		totalDiamond = 0;
		front = 0;
		rear = 0;
		escape = false;
		for(int i = 0; i < MAX_SIZE; i++) {
			for(int j = 0; j < MAX_SIZE; j++) {
				visited[i][j] = false;
				fire_time[i][j] = KHONG_PHAI_LUA;
				grid[i][j] = 0;
				dia_grid[i][j] = 0;
				escapeGrid[i][j] = false;
			}
		}
	}

	int main() {
		//freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
		int T;
		cin >> T;
		for(int tc = 1; tc <= T; tc++) {
			reset();
			int SR, SC;
			cin >> rowNum >> colNum >> SR >> SC;
			int fireNum;
			cin >> fireNum;
			for(int i = 0; i < fireNum; i++) {
				int fireRow, fireCol;
				cin >> fireRow >> fireCol;
				fire_time[fireRow][fireCol] = 0;
				enQueue(fireRow, fireCol);
			}
			int pondNum;
			cin >> pondNum;
			for(int i = 0; i < pondNum; i++) {
				int pondRow, pondCol;
				cin >> pondRow >> pondCol;
				grid[pondRow][pondCol] = 2; // grid = 2 la HO
			}
			int escapeNum;
			cin >> escapeNum;
			for(int i = 0; i < escapeNum; i++) {
				int escapeRow, escapeCol;
				cin >> escapeRow >> escapeCol;
				escapeGrid[escapeRow][escapeCol] = 1; // grid = 1 la LOI THOAT
			}
			for(int i = 1; i <= rowNum; i++) {
				for(int j = 1; j <= colNum; j++) {
					cin >> dia_grid[i][j];
					totalDiamond += dia_grid[i][j];
				}
			}
			while(!isEmpty()) {       // Cho lan lua truoc
				int cur_fire_row = q[front].r;
				int cur_fire_col = q[front].c;
				int next_fire_time = fire_time[cur_fire_row][cur_fire_col] + 1;
				for(int i = 0; i < 4; i++) {
					int next_fire_row = cur_fire_row + dr[i];
					int next_fire_col = cur_fire_col + dc[i];
					if(checkValid(next_fire_row, next_fire_col) && (fire_time[next_fire_row][next_fire_col] >= KHONG_PHAI_LUA) && (grid[next_fire_row][next_fire_col] != 2)) {
						fire_time[next_fire_row][next_fire_col] = next_fire_time;
						enQueue(next_fire_row, next_fire_col);
					}
				}
				deQueue();
			}
			if(fire_time[SR][SC] <= 0) {
				maxDiamond = -1;
			} else dfs(SR, SC, 0, 0);
			if(!escape) maxDiamond = -1;
			cout << "Case #" << tc << endl << maxDiamond << endl;
		}
		return 0;
	}
