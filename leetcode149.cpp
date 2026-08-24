//https://leetcode.com/problems/max-points-on-a-line/description/
class Solution {
public:

    int maxPoints(vector<vector<int>>& points) {
        map<pair<int, int>, int> m;
        int n = points.size();
        int maxP = 0;
        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 1; j < n; j++) {
                int tu = points[i][0] - points[j][0];
                int mau = points[i][1] - points[j][1];
                if(tu < 0 && mau < 0) {
                    tu = -tu;
                    mau = -mau;
                }
                if(mau < 0) {
                    mau = -mau;
                    tu = -tu;
                }
                tu = tu / gcd(tu, mau);
                mau = mau / gcd(tu, mau);
                m[{tu, mau}]++;
                maxP = max(m[{tu, mau}], maxP);
            }
        }
        return maxP + 1;
    }
};
