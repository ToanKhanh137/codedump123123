// Level 4
// Hugo
// Có thử thách dành cho Hugo như sau: Hugo được thả vào 1 khu rừng có rất nhiều kim cương, tuy nhiên đồng thời lúc đó có các đám cháy xuất hiện. Các đám cháy này sẽ lây lan ra các khu vực lân cận theo bốn hướng sau 1 giờ. Tuy nhiên trong khu rừng có một số hồ nhỏ, và lửa không thể cháy lan trên hồ.

// Thời gian để Hugo di chuyển giữa các khu đất là 1 giờ, qua khu hồ là 2 giờ. Hãy giúp Hugo thoát khỏi khu rừng cùng với số lượng kim cương lớn nhất có thể và đảm bảo Hugo không bị lửa thiêu.

// Lưu ý khu rừng chỉ tồn tại một số lượng nhất định lối thoát, tại danh giới của khu rừng, và Hugo không bao giờ quay lại khu vực mình đã đi qua.




// Input

// Dòng đầu là số lượng test case T (T <= 50).

// Dòng đầu của mỗi test case là 4 số N, M, SR, SC tương ứng là số hàng, số cột của khu rừng và tọa độ hàng, cột mà Hugo đang đứng. ( 4 <= N, M <= 15).

// 3 dòng tiếp theo, bắt đầu của mỗi dòng tương ứng là số lượng K các đám cháy hiện có, các hồ và các lối thoát, 2K số tiếp theo trên dòng là tọa độ tương ứng. N dòng tiếp theo sẽ là bản đồ mô tả số lượng kim cương D tại mỗi khu vực trong khu rừng. (0 <= D <= 1000)

// Output

// In mỗi test case trên 2 dòng, dòng đầu tiên là "Case #x", với x là số thứ tự của test case.

// Dòng tiếp theo là số lượng kim cương lớn nhất mà Hugo có thể thu được, nếu Hugo không thể thoát ra khỏi khu rừng, in ra -1.

// Sample

// Input

// 5 <- Số lượng test case

// 4 4 1 2 <- Test case 1, khu rừng có kích thước 4x4, Hugo đang ở ô (1, 2)

// 2 1 1 4 1 <- 2 Khu vực bắt đầu cháy ở (1, 1) và (4, 1)

// 4 1 3 2 1 3 3 3 4 <- 4 Khu vực là hồ ở (1, 3), (2, 1), (3, 3) và (3, 4)

// 2 2 4 3 4 <- 2 lối thoát ở ô (2, 4) và (3, 4)

// 0 0 10 20 <- Số lượng kim cương hàng 1

// 9 3 2 5 <- Số lượng kim cương hàng 2

// 0 0 0 0 <- Số lượng kim cương hàng 3

// 0 10 0 100 <- Số lượng kim cương hàng 4

// ...

// Output

// Case #1

// 10  <- Số lượng kim cương lớn nhất mà Hugo có thể thu được

// Case #2

// 45

// Case #3

// 250

// Case #4

// 643

// Case #5

// 328
#include <iostream>

using namespace std;

#define MAX_SIZE 20
#define KHONG_PHAI_LUA 999999

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
	if(grid[cur_row][cur_col] == 1) {
		visited[cur_row][cur_col] = false;
		maxDiamond = max(cur_diamond, maxDiamond);
		escape = true;
		return;
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
			grid[escapeRow][escapeCol] = 1; // grid = 1 la LOI THOAT
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
