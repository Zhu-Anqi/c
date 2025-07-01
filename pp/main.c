#include <unistd.h>  
#include <stdio.h>
#include <errno.h>
#include"raw_mode.h"
int main() {
    //启用原始模式设置
    enableRawMode();
    printf("终端原始模式已启用。按任意键查看详细信息，如果按 'q' 则退出程序\r\n");
    char input_char;
    while(1) {
        ssize_t bytes_read = read(STDIN_FILENO, &input_char, 1);
        //错误处理机制
        if (bytes_read == -1) {
            // 系统调用被信号中断或资源暂时不可用
            if (errno == EINTR || errno == EAGAIN) {
                continue; // 继续等待输入
            } else {
                perror("错误：读取输入失败");
                break;
            }
        } else if (bytes_read == 0) {
            // 文件结束符（EOF）处理
            printf("\r\n检测到流结束,程序退出\r\n");
            break;
        }
        //显示按键信息 
        printf("检测到按键: ");
        displayKeyInfo(input_char);
        printf("\r\n");
        // 检查退出条件 ('q'键)
        if (input_char == 'q') {
            printf("\r\n已接收退出指令,正在关闭程序\r\n");
            break;
        }
    }
    return 0;
}