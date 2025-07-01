#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"

// 窗口尺寸结构
struct screen_size {
    int rows;
    int cols;
};

// 函数声明
struct screen_size getScreenSize(void);
void clearScreen(struct abuf *ab);
void positionCursor(struct abuf *ab, int row, int col);
void drawText(struct abuf *ab, const char *text);
void refreshDisplay(struct abuf *ab);
void hideCursor(struct abuf *ab);
void showCursor(struct abuf *ab);

#endif