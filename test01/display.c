#include "display.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

// 获取终端窗口大小
struct screen_size getScreenSize(void) {
    struct winsize ws;
    struct screen_size size = {24, 80}; // 默认值
    
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        size.rows = ws.ws_row;
        size.cols = ws.ws_col;
    }
    return size;
}

// 清除屏幕
void clearScreen(struct abuf *ab) {
    abAppend(ab, "\x1b[2J", 4);
}

// 定位光标位置
void positionCursor(struct abuf *ab, int row, int col) {
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", row, col);
    abAppend(ab, buf, len);
}

// 绘制文本 
void drawText(struct abuf *ab, const char *text) {
    size_t len = strlen(text);
    abAppend(ab, text, len);
}

// 刷新显示（修复指针类型不匹配问题）
void refreshDisplay(struct abuf *ab) {
    write(STDOUT_FILENO, ab->data, ab->len);
    abFree(ab);
}

void hideCursor(struct abuf *ab) {
    abAppend(ab, "\x1b[?25l", 6);
}

void showCursor(struct abuf *ab) {
    abAppend(ab, "\x1b[?25h", 6);
}