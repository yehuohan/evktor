
Android图形系统中定义的相关概念：

- View: 绘制到屏幕上的内容，如TextView、Button等；
- Window: View的载体，View不能单独存在，需要依附在Window上；
- WindowManager: 管理Window；
- Surface: 一个Window对应一个Surface，可以生成图形缓存用于缓图；
- Canvas: 提供对Surface的绘图API，最终可以由软件渲染或硬件渲染实现绘图操作；
- Layer: 一个Surface对应一个Layer，是SurfaceFlinger合成的基本操作单元；多个Layer按照z-order混合即为屏幕显示的内容；
- SurfaceView: 特殊的View，不是与宿主的Window共享Surface，有自己独立的Surface，可以在独立的线程中绘图UI；
- SurfaceFlinger: 管理Surface，基于WindowManager的信息对Surface进行合成；
- Choreographer: 收到VSync信号后开始绘制，控制刷新频率为60Hz；
- HWComposer: 将SurfaceFlinger计算后的Layer合成到显示Buffer中；
- OpenGL ES: 嵌入式设备的图形库；
- Display: 显示设备；

