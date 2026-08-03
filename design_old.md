## 硬件思想
所有硬件都是class CPU的一个类，对外仅暴露：run()，init()，update()
局部变量只用const
全局函数或变量用编译时常量
这次我们应该用不到模板类，我打算严格区分private和public
存在DEBUG宏时，所有private改为public
## something need to learn
LSQ中的CAM
优化嵌套预测如何回滚LSQ
mux以及反向mux和优先编码器是怎么实现的
## 模块设计
CPU：包含所有模块，大部分寄存器
fetch：从reg PC中取值，