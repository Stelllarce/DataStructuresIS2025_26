class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pMin;
        for(int i = 0; i < nums.size(); i++)
        {
            pMin.push(nums[i]);
            if(pMin.size() > k)
            {
                pMin.pop();
            }
        }
        return pMin.top();
    }
};