# 问题2: 最短路径算法 (Shortest Path Algorithm)

## 题目描述 (Problem Description)
给定一个加权有向图，找出从起点到终点的最短路径。

## 输入格式 (Input Format)
第一行包含三个整数 n, m, s, t (2 ≤ n ≤ 1000, 1 ≤ m ≤ 10000)
- n: 节点数量
- m: 边的数量  
- s: 起点
- t: 终点

接下来 m 行，每行三个整数 u, v, w，表示从节点u到节点v有一条权重为w的有向边

## 输出格式 (Output Format)
输出最短路径的长度，如果不存在路径则输出-1

## 样例输入 (Sample Input)
```
4 5 1 4
1 2 2
1 3 4
2 3 1
2 4 5
3 4 1
```

## 样例输出 (Sample Output)
```
4
```

## 算法提示 (Algorithm Hints)
可以使用 Dijkstra 算法或 Bellman-Ford 算法