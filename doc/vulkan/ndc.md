
## NDC

Vulkan的NDC坐标系：

```
       Z
      /
     /
    *-----> X
    |
    |
    v
    Y
```

- Y轴向下为正方向，所以Vulkan中使用纹理有时需要flip Y轴。
- Culling操作在NDC坐标系进行，Z轴正方向为Front，Z轴负方向为Back，从Front/Back各自方向上再判定ClockWise或CounterClockWise。
- NDC之前的矩阵变换均会影响Culling。
- 集成Vulkan时，常用的flip NDC Y轴的方法：
    - 把flip Y轴的矩阵，合入到投影矩阵中；
    - 使用`VK_KHR_maintenance1`；
