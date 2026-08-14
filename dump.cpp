#include <iostream>

using namespace std;

struct Point {
	int row;
	int col;
	int time;
};

Point q[100000];
int front, rear;
void enQueue(Point p) {
	rear++;
	q[rear] = p;
}

Point deQueue() {
	front++;
	return q[front];
}

int grid[50][50];
bool visited[50][50];
int N, M;
int SR, SC;
int P;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void init() {
	front = -1;
	rear = -1;
}

bool isEmpty() {
	return front == rear;
}

int pipe[8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 0, 1, 0},
	{0, 1, 0, 1},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1}
};

int oppPipe(int k) {
	return (k + 2) % 4;
}

bool isValid(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		int cnt = 0;
		cin >> N >> M >> SR >> SC >> P;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				cin >> grid[i][j];
				visited[i][j] = false;
			}
		}
		Point start_pos;
		start_pos.row = SR;
		start_pos.col = SC;
		start_pos.time = 1;
		enQueue(start_pos);
		cnt++;
		visited[SR][SC] = true;
		while(!isEmpty()) {
			Point cur = deQueue();
			int cur_row = cur.row;
			int cur_col = cur.col;
			int cur_time = cur.time;
			if(grid[cur_row][cur_col] == 0) continue;
			for(int i = 0; i < 4; i++) {
				if(!pipe[grid[cur_row][cur_col]][i]) continue;
				int next_row = cur_row + dr[i];
				int next_col = cur_col + dc[i];
				int next_time = cur_time + 1;
				if((pipe[grid[next_row][next_col]][oppPipe(i)]) && (next_time <= P) && !visited[next_row][next_col]) {
					Point next;
					next.row = next_row;
					next.col = next_col;
					next.time = next_time;
					enQueue(next);
					visited[next_row][next_col] = true;
					cnt++;
				}
			}
		}
		cout << "Case #" << tc << '\n' << cnt << '\n';
	}
	return 0;
}
