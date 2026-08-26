#include<iostream>
#define INT_MAX 99999999
using namespace std;

int dp[41][601];
int W, D;
struct style {
	int time;
	int energy;
};
style run[5];

void initDP() {
	dp[0][0] = 0;
	for(int i = 0; i <= D; i++) {
		for(int j = 0; j <= W; j++) {
			if(i == 0 && j == 0) continue;
			dp[i][j] = INT_MAX;
		}
	}
}

int main()
{
	int test_case;
	int T;
	cin >> T;
	//freopen("input.txt", "r", stdin);
	for(test_case = 1; test_case <= T; ++test_case) {
		cin >> W >> D;
		for(int i = 0; i < 5; i++) {
			int phut;
			int giay;
			cin >> phut >> giay >> run[i].energy;
			run[i].time = 60 * phut + giay;
		}
		initDP();
		for(int i = 1; i <= D; i++) {
			for(int j = 0; j <= W; j++) {
				for(int k = 0; k < 5; k++) {
					if(j >= run[k].energy) dp[i][j] = min(dp[i-1][j-run[k].energy] + run[k].time, dp[i][j]);
				}
			}
		}
		int minAns = INT_MAX;
		for(int i = 0; i <= W; i++) {
			minAns = min(minAns, dp[D][i]);
		}
		if(minAns == INT_MAX) {
			cout << "Case #" << test_case << endl << -1 << endl;
			continue;
		}
		int minute = minAns / 60;
		int second = minAns % 60;
		cout << "Case #" << test_case << endl << minute << ' ' << second << endl;
	}
	return 0;
}
