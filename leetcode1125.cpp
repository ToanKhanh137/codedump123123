//https://leetcode.com/problems/smallest-sufficient-team/description/
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        vector<int> dp((1 << n), 99999);
        dp[0] = 0;
        vector<int> skill_mask(people.size(), 0);
        vector<int> trace_mask(1 << n);
        vector<int> trace_action(1 << n);
        vector<int> res;
        unordered_map<string, int> m;
        for(int i = 0; i < n; i++) {
            m.insert({req_skills[i], (1 << i)});
        }
        for(int i = 0; i < people.size(); i++) {
            for(int j = 0; j < people[i].size(); j++) {
                skill_mask[i] |= m[people[i][j]];
            }
        }
        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < people.size(); j++) {
                int next_mask = i | skill_mask[j];
                if(dp[i] + 1 < dp[next_mask]) {
                    dp[next_mask] = dp[i] + 1;
                    trace_mask[next_mask] = i;
                    trace_action[next_mask] = j;
                }
            }
        }
        int curr = (1 << n) - 1;
        while(curr > 0) {
            res.push_back(trace_action[curr]);
            curr = trace_mask[curr];
        }
        return res;
    }
};
