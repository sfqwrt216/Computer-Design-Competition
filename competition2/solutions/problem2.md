# 微服务架构设计方案

## 服务拆分方案

### 核心微服务
1. **用户服务 (User Service)**
   - 用户注册、登录、认证
   - 用户信息管理
   - 权限管理

2. **商品服务 (Product Service)**
   - 商品信息管理
   - 商品搜索
   - 分类管理

3. **订单服务 (Order Service)**
   - 订单创建、更新
   - 订单状态管理
   - 订单历史查询

4. **库存服务 (Inventory Service)**
   - 库存查询、更新
   - 库存预留、释放
   - 库存告警

5. **支付服务 (Payment Service)**
   - 支付处理
   - 退款处理
   - 支付状态跟踪

6. **通知服务 (Notification Service)**
   - 邮件通知
   - 短信通知
   - 推送通知

### 基础设施服务
- **API 网关**: 统一入口、路由、认证
- **配置中心**: 配置管理
- **服务注册中心**: 服务发现
- **监控服务**: 链路跟踪、指标监控

## 数据管理策略

### 数据库设计
- 每个服务独立的数据库
- 用户服务：PostgreSQL
- 商品服务：Elasticsearch + MySQL
- 订单服务：MySQL
- 库存服务：Redis + MySQL
- 支付服务：MySQL

### 分布式事务
使用 Saga 模式处理跨服务事务：
1. 订单创建 → 库存预留 → 支付处理 → 订单确认
2. 补偿机制处理失败情况

## API 设计示例

```yaml
# API Gateway 配置示例
routes:
  - path: /api/users/*
    service: user-service
    methods: [GET, POST, PUT, DELETE]
    auth_required: true
    
  - path: /api/products/*
    service: product-service
    methods: [GET, POST, PUT, DELETE]
    rate_limit: 1000/minute
    
  - path: /api/orders/*
    service: order-service
    methods: [GET, POST, PUT, DELETE]
    auth_required: true
    timeout: 30s
```

## 简单服务实现示例

```java
// 订单服务示例
@RestController
@RequestMapping("/api/orders")
public class OrderController {
    
    @Autowired
    private OrderService orderService;
    
    @PostMapping
    public ResponseEntity<Order> createOrder(@RequestBody CreateOrderRequest request) {
        try {
            Order order = orderService.createOrder(request);
            return ResponseEntity.ok(order);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
        }
    }
    
    @GetMapping("/{orderId}")
    public ResponseEntity<Order> getOrder(@PathVariable String orderId) {
        Order order = orderService.getOrder(orderId);
        return order != null ? ResponseEntity.ok(order) : ResponseEntity.notFound().build();
    }
}

@Service
public class OrderService {
    
    @Autowired
    private InventoryServiceClient inventoryClient;
    
    @Autowired
    private PaymentServiceClient paymentClient;
    
    @Transactional
    public Order createOrder(CreateOrderRequest request) {
        // 1. 验证用户
        // 2. 检查库存
        boolean stockAvailable = inventoryClient.checkStock(request.getProductId(), request.getQuantity());
        if (!stockAvailable) {
            throw new OutOfStockException();
        }
        
        // 3. 创建订单
        Order order = new Order(request);
        order = orderRepository.save(order);
        
        // 4. 预留库存
        inventoryClient.reserveStock(request.getProductId(), request.getQuantity(), order.getId());
        
        return order;
    }
}
```