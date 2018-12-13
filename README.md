# 基于STM32端的ROS_Client
具体请参考https://blog.csdn.net/wubaobao1993/article/details/70808959

----
## 需要注意的问题
1. 确认keil中使用的标准是--cpp
2. 确认系统的中断函数上都添加了extern "C"的字样
3. 确认自己移植的时候STM32串口修改的是正确的，最好实际DEBUG一下看到能进入串口的中断
4. 确认PC端的USB口映射是正确的，特别是USB口上插入了多个设备的时候
5. 确认STM32的滴答定时器的频率是1KHz，同时里面不要有别的代码，仅做时间的累加