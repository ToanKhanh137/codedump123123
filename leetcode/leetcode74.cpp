//https://leetcode.com/problems/search-a-2d-matrix/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int left = 0;
        int right = m*n - 1;
        while(left <= right) {
            int mid = (left + right) / 2;
            int idx = matrix[mid/n][mid%n];
            if(idx == target) return true;
            else if(idx > target) {
                right = mid - 1;
            } else left = mid + 1;
        }
        return false;
    }
};
