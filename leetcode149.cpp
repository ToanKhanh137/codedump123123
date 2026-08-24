//https://leetcode.com/problems/max-points-on-a-line/description/
class Solution {
public:

    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        int maxP = 0;
        for(int i = 0; i < n - 1; i++) {
            map<pair<int, int>, int> m;
            for(int j = i + 1; j < n; j++) {
                int tu = points[i][0] - points[j][0];
                int mau = points[i][1] - points[j][1];
                if(mau < 0) {
                    tu = -tu;
                    mau = -mau;
                }
                else if(mau == 0 && tu < 0) {
                    tu = -tu;
                }
                int a = gcd(tu, mau);
                tu = tu / a;
                mau = mau / a;
                m[{tu, mau}]++;
                maxP = max(m[{tu, mau}], maxP);
            }
        }
        return maxP + 1;
    }
};
