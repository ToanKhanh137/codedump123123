#include <iostream>

using namespace std;

int N, M, K;
int grid[51][51];
int query[30];
bool canDo[30];

struct Point {
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	int slot;
};

Point s1[5000];
int top1 = -1;

void push1(Point a) {
	top1++;
	s1[top1] = a;
}

Point pop1() {
	top1--;
	return s1[top1 + 1];
}

Point s2[5000];
int top2 = -1;

void push2(Point a) {
	top2++;
	s2[top2] = a;
}

Point pop2() {
	top2--;
	return s2[top2 + 1];
}

int cntSlot(int sr, int sc, int er, int ec) {
	int sum = 0;
	for(int i = sr; i <= er; i++) {
		for(int j = sc; j <= ec; j++) {
			sum+= grid[i][j];
		}
	}
	return sum;
}

bool isValid(int r, int c) {
	return r > 0 && c > 0 && r <= N && c <= M;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= M; j++) {
				cin >> grid[i][j];
				if(grid[i][j] == 1) grid[i][j] = 0;
				else grid[i][j] = 1;
			}
		}
		for(int i = 0; i < K; i++) {
			cin >> query[i];
			canDo[i] = false;
		}
		for(int idx = 0; idx < K; idx++) {
			top1 = -1; top2 = -1;
			for(int start_row = 1; start_row <= N; start_row++) {
				for(int start_col = 1; start_col <= M; start_col++) {
					for(int drow = 0; drow < 3; drow++) {
						for(int dcol = 0; dcol <= (M - start_col); dcol++) {
							int end_row = start_row + drow; int end_col = start_col + dcol;
							int countSlot = 0;
							if(!isValid(end_row, end_col)) continue;
							countSlot = cntSlot(start_row, start_col, end_row, end_col);
							if(countSlot >= query[idx]) {
								Point temp;
								temp.startRow = start_row; temp.startCol = start_col; temp.endRow = end_row; temp.endCol = end_col;
								temp.slot = (dcol + 1) * (drow + 1);
								push1(temp);
							}
						}
					}
				}
			}
			int minRow = 9999999;
			if(top1 >= 0) {
				canDo[idx] = true;
				for(int i = 0; i <= top1; i++) {
					minRow = min(s1[i].endRow - s1[i].startRow, minRow);
				}
				for(int i = 0; i <= top1; i++) {
					if((s1[i].endRow - s1[i].startRow) == minRow) push2(s1[i]);
				}
			} else continue;
			int minSlot = 9999999;
			for(int i = 0; i <= top2; i++) {
				minSlot = min(minSlot, s2[i].slot);
			}
			for(int i = 0; i <= top2; i++) {
				if(s2[i].slot == minSlot) query[idx] = (s2[i].endCol - s2[i].startCol + 1);
			}
			
		}
		cout << '#' << tc << ' ';
		for(int i = 0; i < K; i++) {
			if(canDo[i]) cout << query[i] << ' ';
			else cout << "-1 ";
		}
		cout << '\n';

	}
	return 0;
}
