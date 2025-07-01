#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw); // 获取当前终端设置
    raw.c_lflag &= ~(ECHO | ICANON); // 关闭回显和规范输入模式
    tcsetattr(STDIN_FILENO, TCSANOW, &raw); // 应用修改
}

void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term); // 获取当前终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // 恢复终端设置
}
int main(){
    enableRawMode();
    char c;
    while(read(STDIN_FILENO,&c,1)==1&&c!="q");
    return 0;

}