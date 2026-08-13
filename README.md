#include <iostream>

using namespace std;

int N;
int a[100][100];
int cnt[100];
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};
bool visited[100][100];
bool isValid(int r, int c) {
	return r >= 1 && c >= 1 && r <= N && c <= N;
}

void dfs(int r, int c, int val) {
	if(isValid(r, c)) {
		a[r][c] = -1;
		dfs(r+1,c,val); dfs(r-1,c,val); dfs(r,c-1,val); dfs(r+1,c+1,val);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		cin >> N;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				a[i][j] = 0;
				visited[i][j] = false;
			}
		}
		for(int i = 1; i <= N - 1; i++) {
			for(int j = 1; j <= N; j++) {
				int row_idx; cin >> row_idx;
				int col_idx; cin >> col_idx;
				a[row_idx][col_idx] = i;
			}
		}
		int so_cum = 0;
		for(int r = 1; r <= N; r++) {
			for(int c = 1; c <= N; c++) {
				if(a[r][c] != 0 && a[r][c] != - 1) {
					so_cum++;
					dfs(r, c, a[r][c]);
				}
			}
		}
		cout << "Case #" << tc << '\n';
		if(so_cum == N) cout << "good\n";
		else cout << "wrong\n";
	}
	return 0;
}
