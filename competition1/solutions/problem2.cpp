/**
 * 问题2解答: 最短路径算法
 * 使用 Dijkstra 算法求单源最短路径
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class ShortestPath {
public:
    int dijkstra(int n, const std::vector<std::vector<std::pair<int, int>>>& graph, int start, int end) {
        std::vector<int> dist(n + 1, INF);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist[end] == INF ? -1 : dist[end];
    }
};

int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    
    std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    
    ShortestPath sp;
    int result = sp.dijkstra(n, graph, s, t);
    
    std::cout << result << std::endl;
    
    return 0;
}