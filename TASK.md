
将shaders/test/conv2d.comp改成使用int8计算：

- 改好的shader放在shaders/test/conv2d_i8.comp
- 使用uint保存conv2d_i8的输入与输出，每个uint保存4个int8，使用int通过位运算实现int8的计算
- 支持NCHW和NHWC两种格式，通过宏USE_NHWC来控制，不使用cooperative matrix，即不要定义USE_COOPMAT
- 你只能改你生成的conv2d_i8.comp，不要改其它文件
- 如果需要python环境，则使用c:/apps/miniconda3/envs/ept
- 要求生成covn2d_i8.comp后通过just test rctx_cooperative_matrix可以正常编译和运行
- 要求使用NHWC时，just test rctx_cooperative_matrix运行的结果（stdout打印的倒数第二行yout后面的输出）为 0, 0, 0, 0, 0, 19, 48, 76, 52, 1, 39, 63
- 要求使用NCHW时，just test rctx_cooperative_matrix运行的结果（stdout打印的倒数第二行yout后面的输出）为 0, 50, 0, 126, 0, 0, 63, 0, 99, 113, 74, 14
- 如果just test rctx_cooperative_matrix的运行结果错误，你只应该修改conv2d_i8.comp，不可能是其它文件的原因导致的问题
