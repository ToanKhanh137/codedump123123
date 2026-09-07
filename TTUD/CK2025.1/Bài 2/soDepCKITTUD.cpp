#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

int N, W;
vector<int> res;

bool flag = true;
void printSol(const vector<int>& a) {
    for(int i = 0; i < N; ++i) {
        cout << a[i];
    }
    cout << '\n';
}

int mod10(int a) {
    return (a+100) % 10;
}

void backtrack(int idx, int sum, int last) {
    if((sum > W) || (sum + 9 * (N - idx) < W)) return;
    if((sum == W) && (idx == N)) {
        printSol(res);
        flag = false;
        return;
    }
    if(idx > N) return;
    vector<int> candidates(3);
    candidates[0] = mod10(2 * last - 1);
    candidates[1] = mod10(2 * last);
    candidates[2] = mod10(2 * last + 1);
    sort(candidates.begin(), candidates.end());
    for(auto num : candidates) {
        res.push_back(num);
        backtrack(idx + 1, sum + num, num);
        res.pop_back();
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> W;
    res.reserve(N);
    for(int i = 1; i <= 9; i++) {
        res.push_back(i);
        backtrack(1, i, i);
        res.pop_back();
    }
    if(flag) cout << -1;
    return 0;
}
