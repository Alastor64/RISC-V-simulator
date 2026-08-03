我们约定：
存储（硬件思想）：
1. 全局变量必须是常量
2. 除内存以外，不使用stl
3. 同一个寄存器读写消耗一周期，读无限制，写限制一次
4. 对于上一条可以理解为我们把周期拉的足够长，使我们支持一周期内最长的寄存器串行读写
5. 内存读写消耗MAT(Memory Access Time)周期，所有内存读写总数限一次（取指除外）
6. 局部变量随意
模块：
1. 所有模块都是一个CPU的内置类，对外仅暴露run()和update()
2. 一个模块一周期仅能run()一次
3. 模块内出现意外输入时，默认是预热导致的，不终止程序，在BEBUG=true时输出。
指令执行流程：
1. fetch：如果（reg block=false）取指至reg ins，然后令block=false
2. decode：将ins解码，存储至reg（op，v1，v2，rd_addr）
3. issue：检查能否发布op，v1，v2，rd_addr，若能成功令block=true
4. RS：检查就绪情况，调用相关指令
5. ROB：广
Tomasulo：
1. ROB模块：
2. RSV模块：（RS）实际规划执行指令的模块
3. STA模块：