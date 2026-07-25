class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater = 0;
        int lp = 0; int rp = height.size()-1;
        while(lp < rp){
            int width = rp - lp;
            int length = min(height[lp], height[rp]);
            int area = length * width;
            maxWater = max(maxWater, area);

            height[lp] < height[rp] ? lp++ : rp--;
        }
        return maxWater;
    }
};