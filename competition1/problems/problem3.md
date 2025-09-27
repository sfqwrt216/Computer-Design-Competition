# 问题3: 动态规划问题 (Dynamic Programming Problem)

## 题目描述 (Problem Description)
给定一个数组，求最大子序列和。

## 输入格式 (Input Format)
第一行包含一个整数 n (1 ≤ n ≤ 10^5)
第二行包含 n 个整数 a₁, a₂, ..., aₙ (-10^4 ≤ aᵢ ≤ 10^4)

## 输出格式 (Output Format)
输出最大子序列和

## 样例输入 (Sample Input)
```
6
-2 1 -3 4 -1 2
```

## 样例输出 (Sample Output)
```
5
```

## 解释 (Explanation)
最大子序列为 [4, -1, 2]，和为 5

## 算法提示 (Algorithm Hints)
可以使用 Kadane's 算法，时间复杂度 O(n)