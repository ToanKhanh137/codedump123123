#include <iostream>

using namespace std;

const char* num[10] = {"ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN"};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("GNS_test_input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		char trash[10];
		int N;
		int cnt[10];
		for(int i = 0; i < 10; i++) cnt[i] = 0;
		cin >> trash >> N;
		for(int i = 0; i < N; i+= 4) {
			char s[5];
			cin >> s;
			if(s[0] == 'Z') {
				cnt[0]++;
			} else if(s[0] == 'O') {
				cnt[1]++;
			} else if(s[0] == 'T') {
				if(s[1] == 'W') cnt[2]++;
				else cnt[3]++;
			} else if(s[0] == 'F') {
				if(s[1] == 'O') cnt[4]++;
				else cnt[5]++;
			} else if(s[0] == 'S') {
				if(s[1] == 'I') cnt[6]++;
				else cnt[7]++;
			} else if(s[0] == 'E') {
				cnt[8]++;
			} else if(s[0] == 'N') {
				cnt[9]++;
			}
		}
		cout << '#' << tc << '\n';
		for(int i = 0; i < 10; i++) {
			while(cnt[i] > 0) {
				cout << num[i] << ' ';
				cnt[i]--;
			}
		}
		cout << '\n';
	}
	return 0;
}
