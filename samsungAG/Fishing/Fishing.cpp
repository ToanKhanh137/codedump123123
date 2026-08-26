#include<iostream>
using namespace std;

#define MAX_SPOT 100
struct gate {
	int num;
	int pos;
};

int permutations[6][3] = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
gate Gate[4];
int spot[MAX_SPOT];
bool used[MAX_SPOT];
int min_cost;
int N;

int abs(int a) {
	if(a < 0) return -a;
	else return a;
}

int moveCost(int gatePos, int spotPos) {
	return abs(gatePos - spotPos) + 1;
}

void Try(int idx_perm, int row_perm, int current_cost) {
	if(idx_perm == 3) {
		min_cost = min(current_cost, min_cost);
		return;
	}
	if(current_cost >= min_cost) return;
	int gate_idx = permutations[row_perm][idx_perm];
	int people_left = Gate[gate_idx].num;
	int gate_pos = Gate[gate_idx].pos;
	int spot_used[MAX_SPOT];
	int count_spot_used = 0;
	int cost_this_gate = 0;
	int d = 0;
	bool split = false;
	while(people_left > 0) {
		int left_pos = gate_pos - d;
		int right_pos = gate_pos + d;
		bool left_check = (left_pos >= 1) && (!used[left_pos]);
		bool right_check = (right_pos <= N) && (!used[right_pos]);
		if(d == 0) {
			if(left_check) {
				used[left_pos] = true;
				cost_this_gate += moveCost(gate_pos, gate_pos);
				spot_used[count_spot_used] = left_pos;
				count_spot_used++;
				people_left--;
			}
		} else if(left_check && !right_check) {
			used[left_pos] = true;
			cost_this_gate += moveCost(gate_pos, left_pos);
			spot_used[count_spot_used] = left_pos;
			count_spot_used++;
			people_left--;
		} else if(!left_check && right_check) {
			used[right_pos] = true;
			cost_this_gate += moveCost(gate_pos, right_pos);
			spot_used[count_spot_used] = right_pos;
			count_spot_used++;
			people_left--;
		} else if(left_check && right_check) {
			if(people_left >=2) {
				used[left_pos] = true;
				cost_this_gate += moveCost(gate_pos, left_pos);
				spot_used[count_spot_used] = left_pos;
				count_spot_used++;
				people_left--;
				used[right_pos] = true;
				cost_this_gate += moveCost(gate_pos, right_pos);
				spot_used[count_spot_used] = right_pos;
				count_spot_used++;
				people_left--;
			} else if(people_left == 1) {
				split = true;
				used[left_pos] = true;
				int cost_left_branch = current_cost + cost_this_gate + moveCost(gate_pos, left_pos);
				Try(idx_perm + 1, row_perm, cost_left_branch);
				used[left_pos] = false;
				used[right_pos] = true;
				int cost_right_branch = current_cost + cost_this_gate + moveCost(gate_pos, right_pos);
				Try(idx_perm + 1, row_perm, cost_right_branch);
				used[right_pos] = false;
				break;
			}
		}
		d++;
	}
	if(!split) Try(idx_perm + 1, row_perm, current_cost + cost_this_gate);
	for(int k = 0; k < count_spot_used; k++) used[spot_used[k]] = false;

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for(int tc = 1; tc <= T; tc++) {
		cin >> N;
		for(int i = 1; i < 4; i++) {
			cin >> Gate[i].pos;
			cin >> Gate[i].num;
		}
		min_cost = 999999999;
		for(int i = 0; i < 6; i++) {
			for(int j = 1; j <= N; j++) used[j] = false;
			Try(0, i, 0);
		}
		cout << "Case #" << tc << '\n' << min_cost << '\n';
	}
	return 0;
}
