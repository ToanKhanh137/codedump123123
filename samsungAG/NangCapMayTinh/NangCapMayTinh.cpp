#include <iostream>
#define MIN_INT 99999999

using namespace std;

bool combo[30][20];
int comboMask[30];
int comboPrice[30];
int price[20];
int M, N, L;
int indexMap[20];
int priceMap[20];
int dp[(1 << 20)];

void init() {
	for(int i = 0; i < 30; i++) {
		comboMask[i] = 0;
		for(int j = 0; j < 20; j++) {
			combo[i][j] = false;
		}
	}
	for(int i = 1; i < (1 << 20); i++) {
		dp[i] = MIN_INT;
	}
	dp[0] = 0;
	for(int i = 0; i < 20; i++) indexMap[i] = -1;
}

int main() {
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		init();
		cin >> N;
		for(int i = 0; i < N; i++) cin >> price[i];
		cin >> M;
		for(int i = 0; i < M; i++) {
			cin >> comboPrice[i];
			int K;
			cin >> K;
			for(int k = 0; k < K; k++) {
				int temp;
				cin >> temp;
				temp--;
				combo[i][temp] = true;
			}
		}
		cin >> L;
		for(int k = 0; k < L; k++) {
				int temp;
				cin >> temp;
				temp--;
				indexMap[temp] = k;
				priceMap[k] = price[temp];
		}
		for(int i = 0; i < M; i++) {
			for(int j = 0; j < 20; j++) {
				if(combo[i][j] && (indexMap[j] != -1)) {
					comboMask[i] = comboMask[i] | (1 << indexMap[j]);
				}
			}
		}
		for(int i = 0; i < (1 << L); i++) {
			for(int k = 0; k < L; k++) {
				int next_mask = 0;
				next_mask = i | (1 << k);
				dp[next_mask] = min(dp[next_mask], dp[i] + priceMap[k]);
			}
			for(int k = 0; k < M; k++) {
				int next_mask = 0;
				next_mask = i | comboMask[k];
				dp[next_mask] = min(dp[next_mask], dp[i] + comboPrice[k]);
			}
		}
		cout << '#' << tc << ' ' << dp[((1 << L) - 1)] << '\n';
	}
	return 0;
}
