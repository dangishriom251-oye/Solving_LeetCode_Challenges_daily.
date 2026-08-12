class Solution {
public:
    void getAllSubsets(vector<int> &arr, vector<int> &ans, int i, vector<vector<int>>& allSubsets){
        if(i == arr.size()){
            allSubsets.push_back({ans});
            return ;
        }
        // inclusion
        ans.push_back(arr[i]);
        getAllSubsets(arr, ans, i+1, allSubsets);
        ans.pop_back();  // backtrack

        // exclusion
        getAllSubsets(arr, ans, i+1, allSubsets);
    }

    vector<vector<int>> subsets(vector<int>& arr) {
        vector<vector<int>> allSubsets;
        vector<int> ans;
        getAllSubsets(arr, ans, 0, allSubsets);

        return allSubsets;
    }
};