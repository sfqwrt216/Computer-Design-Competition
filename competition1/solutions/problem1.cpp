/**
 * 问题1解答: 数组排序优化
 * 使用快速排序算法，时间复杂度 O(n log n)，空间复杂度 O(log n)
 */

#include <iostream>
#include <vector>
#include <algorithm>

class ArraySorter {
public:
    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
private:
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    ArraySorter sorter;
    sorter.quickSort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    return 0;
}