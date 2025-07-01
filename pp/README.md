代码包含main文件，raw_mode的c语言文件和头文件，在main文件里是程序的主体，
raw_mode的C文件里是函数的定义，头文件里包含函数声明。
解题思路：
任务:

实现原始模式设置（disableRawMode和enableRawMode函数）

读取用户输入，直到用户按下'q'退出

实现错误处理机制

显示按键的ASCII值，包括控制字符
在raw_mode的c语言文件中定义disableRawMode和enableRawMode函数，以便在主程序中的调用
enableRawMode函数里有对题目要求的对应
displayKetInfo中定义了读入字符的特殊情况和相应的处理策略。
在main函数里是程序主循环，读入用户输入，并设定错误处理机制，在非q 条件下，输出检测到按键是哪个和他对应的ASCLL码值。到输入q，break.