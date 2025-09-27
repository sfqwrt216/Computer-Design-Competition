# 分布式缓存系统设计方案

## 系统架构

### 核心组件
1. **缓存节点 (Cache Nodes)**
   - 数据存储和处理
   - 内存管理
   - 本地持久化

2. **协调服务 (Coordinator Service)**
   - 集群管理
   - 故障检测
   - 配置管理

3. **客户端代理 (Client Proxy)**
   - 负载均衡
   - 路由选择
   - 连接池管理

### 分片策略
- 使用一致性哈希 (Consistent Hashing)
- 虚拟节点减少数据迁移
- 支持动态扩缩容

### 复制策略
- 主从复制 (Master-Slave Replication)
- 异步复制提高性能
- 读写分离优化

### 故障处理
- 心跳检测机制
- 自动故障转移
- 数据恢复策略

## 简单实现示例

```python
import hashlib
import bisect
from typing import Dict, List, Any

class ConsistentHash:
    def __init__(self, nodes: List[str], replicas: int = 100):
        self.replicas = replicas
        self.ring = {}
        self.sorted_keys = []
        
        for node in nodes:
            self.add_node(node)
    
    def add_node(self, node: str):
        for i in range(self.replicas):
            key = self._hash(f"{node}:{i}")
            self.ring[key] = node
            self.sorted_keys.append(key)
        self.sorted_keys.sort()
    
    def remove_node(self, node: str):
        for i in range(self.replicas):
            key = self._hash(f"{node}:{i}")
            del self.ring[key]
            self.sorted_keys.remove(key)
    
    def get_node(self, key: str) -> str:
        if not self.ring:
            return None
        
        hash_key = self._hash(key)
        idx = bisect.bisect_right(self.sorted_keys, hash_key)
        if idx == len(self.sorted_keys):
            idx = 0
        return self.ring[self.sorted_keys[idx]]
    
    def _hash(self, key: str) -> int:
        return int(hashlib.md5(key.encode()).hexdigest(), 16)

class DistributedCache:
    def __init__(self, nodes: List[str]):
        self.hash_ring = ConsistentHash(nodes)
        self.nodes = {node: {} for node in nodes}
    
    def put(self, key: str, value: Any):
        node = self.hash_ring.get_node(key)
        if node:
            self.nodes[node][key] = value
    
    def get(self, key: str) -> Any:
        node = self.hash_ring.get_node(key)
        if node:
            return self.nodes[node].get(key)
        return None
    
    def delete(self, key: str):
        node = self.hash_ring.get_node(key)
        if node and key in self.nodes[node]:
            del self.nodes[node][key]
```