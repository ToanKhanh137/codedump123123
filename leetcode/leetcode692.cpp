//https://leetcode.com/problems/top-k-frequent-words/description/
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> res;
        unordered_map<string, int> m;
        for(auto it : words) {
            m[it]--;
        }
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        for(auto it : m) {
            pq.push({it.second, it.first});
        }
        while(k > 0) {
            res.push_back(pq.top().second);
            pq.pop();
            k--;
        }
        return res;
    }
};
