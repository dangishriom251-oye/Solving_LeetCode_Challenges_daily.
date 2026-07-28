class Solution {
public:
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> ans;
        
        // first window
        int n = nums.size();
        for(int i=0; i<k; i++){
            while(dq.size() > 0 && nums[dq.back()] <= nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
        }

        for(int i=k; i<n; i++){
            ans.push_back(nums[dq.front()]);

            // remove elements not part of curr wind

            while(dq.size() > 0 && dq.front() <= i-k){
                dq.pop_front();
            }

                while(dq.size() > 0 && nums[dq.back()] <= nums[i]){
                    dq.pop_back();
                }
             
                dq.push_back(i);
            }
            ans.push_back(nums[dq.front()]);

        return ans;
    }
};