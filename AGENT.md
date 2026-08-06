# ai需知

本项目中,ai不能修改任何代码或文件，本项目对ai而言是只读的
本项目目标是用软件描述一个CPU（RISC-V 小端序 32位 五级流水线 tomasulo 无分支预测）
ai的回答应尽可能简洁
对于 “S_to_byte 不识别小写 a-f”的问题，请忽略，因为当前测试数据用大写，暂不影响
对于 “0x73 分支 对所有系统指令均抛异常（含 ECALL/EBREAK/CSR），未区分处理”的问题，请忽略，因为本项目不实现这些指令
design_old_easy_unfinished.md 与 design_old.md 属于过时的设计，务必忽略它们
当你静态检查时，要注意每周期所有模块、port、tempor、register都要update，且port、tempor要在register之前update
注意到port、tempor、register在一周期内有使用次数限制，你要特别关注
