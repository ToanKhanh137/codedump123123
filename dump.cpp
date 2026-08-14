// There is an airplane game which to avoid enemies and gather coins.

// The game's map has height is N and width is 5 (5 ≤ N ≤ 12), but due to the limit of the screen, the gaming zone is 5x5. Below the gaming zone, there is control zone, which is one line at the bottom of the screen where airplane move.

// At the start of game, the airplane locates at center point of control zone.

// Game rule :

//          - Movement of airplane can be one of 3 options : left - right - stay at current column

//          - In each turn, after airplane move, game map will move down one line

//          - There is an option to use Bomb : bomb can be used to destroy all enemies in gaming zone, after used, all enemies will disappear and all coins will remain in the map. Bomb can be used only one.

//          - When airplane meets a cell with coin, number of coins collected will increase by 1, if it meet an enemy, number of coins will decrease by 1. If number of coins < 0 -> Game Over.

// Given the map Nx5 with C is value of each cell (0: nothing, 1: coin, 2:enemy), find out the maximum amount of coins can be achieved after finishing the game. If the game can not be finished (Game Over), return -1.

// [Input]

// The first line is the total number of test cases T ( T <= 50)

// The first line of each test case contain N, which is the height of the map, then the N lines following descript the map's data.

// [Output]

// The maximum number of coins that can be collected after finishing the game.

// If the game can not be finished, print -1.

 

 

// Ex:



// Input

// 2

// 5

// 1 1 0 0 0

// 1 2 2 2 1

// 1 1 2 2 1

// 2 2 2 1 2

// 2 2 0 2 0

// 8

// 2 0 2 0 2

// 1 0 1 2 0

// 0 0 0 2 1

// 2 0 2 0 1

// 1 2 1 2 0

// 0 2 2 0 2

// 2 1 1 2 2

// 0 2 1 2 0

 

// Output

// Case #1

// 3

// Case #2

// 4
#include <iostream>

using namespace std;

#define MAX_SIZE 20

struct Point {
	int row;
	int col;
};

int N;
int maxCoins;
int grid[13][5];
Point bombed[100];

bool isValid(int r, int c) {
	return r >= 0 && c >=0 && r < N && r < 5;
}

void dfs(int cur_row, int cur_col, int cur_coin, int bomb_count) {
	if(bomb_count) {
		int bombed_count = 0;
		for(int i = cur_row; i >= cur_row - 4; i--) {
			for(int j = 0; j <= 4; j++) {
				if(isValid(i, j) && grid[i][j] == -1) {
					bombed[bombed_count].row = i;
					bombed[bombed_count].col = j;
					bombed_count++;
					grid[i][j] = 1;
				}
			}
		}
		dfs(cur_row, cur_col, cur_coin, 0);
		for(int i = 0; i < bombed_count; i++) {
			grid[bombed[bombed_count].row][bombed[bombed_count].col] = -1;
		}
	}
	cur_coin += grid[cur_row][cur_col];
	if(cur_coin < 0) return;
	if(cur_row == 0) {
		maxCoins = max(maxCoins, cur_coin);
		return;
	}
	if(isValid(cur_row - 1, cur_col)) dfs(cur_row - 1, cur_col, cur_coin, bomb_count);
	if(isValid(cur_row - 1, cur_col - 1)) dfs(cur_row - 1, cur_col - 1, cur_coin, bomb_count);
	if(isValid(cur_row - 1, cur_col + 1)) dfs(cur_row - 1, cur_col + 1, cur_coin, bomb_count);
}
void reset() {
	maxCoins = -9999999;	
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		reset();
		cin >> N;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < 5; j++) {
				cin >> grid[i][j];
				if(grid[i][j] == 2) grid[i][j] = -1;
			}
		}
		dfs(N - 1, 2, 0, 1);	
		dfs(N - 1, 3, 0, 1);
		dfs(N - 1, 1, 0, 1);
		cout << "Case #" << tc << '\n';
		if(maxCoins >= 0) cout << maxCoins << '\n';
		else cout << "-1\n";
	}
	return 0;
}
