# 问题1: 数组排序优化 (Array Sorting Optimization)

## 题目描述 (Problem Description)
给定一个包含n个整数的数组，请实现一个高效的排序算法。

要求：
- 时间复杂度不超过 O(n log n)
- 空间复杂度不超过 O(log n)
- 处理重复元素

## 输入格式 (Input Format)
第一行包含一个整数 n (1 ≤ n ≤ 10^6)
第二行包含 n 个整数 a₁, a₂, ..., aₙ (-10^9 ≤ aᵢ ≤ 10^9)

## 输出格式 (Output Format)
输出排序后的数组，每个数字之间用空格分隔

## 样例输入 (Sample Input)
```
5
3 1 4 1 5
```

## 样例输出 (Sample Output)
```
1 1 3 4 5
```

## 评分标准 (Scoring Criteria)
- 正确性：50%
- 时间复杂度：30%
- 代码质量：20%