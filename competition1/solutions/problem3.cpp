/**
 * 问题3解答: 动态规划问题
 * 使用 Kadane's 算法求最大子序列和
 */

#include <iostream>
#include <vector>
#include <algorithm>

class MaxSubarraySum {
public:
    int kadane(const std::vector<int>& arr) {
        int maxSoFar = arr[0];
        int maxEndingHere = arr[0];
        
        for (int i = 1; i < arr.size(); i++) {
            maxEndingHere = std::max(arr[i], maxEndingHere + arr[i]);
            maxSoFar = std::max(maxSoFar, maxEndingHere);
        }
        
        return maxSoFar;
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    MaxSubarraySum mss;
    int result = mss.kadane(arr);
    
    std::cout << result << std::endl;
    
    return 0;
}