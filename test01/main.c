#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "raw_mode.h"
#include "display.h"
#include "buffer.h"

struct editor_state {
    int cx, cy;             // 光标位置
    struct abuf ab;         // 输出缓冲区
    struct screen_size size; // 终端尺寸
};

void initEditor(struct editor_state *e);
void drawEditorScreen(struct editor_state *e); 
void refreshEditorScreen(struct editor_state *e);

// 初始化编辑器状态
void initEditor(struct editor_state *e) {
    e->cx = 0;
    e->cy = 0;
    e->ab = ABUF_INIT; // 使用正确的初始化宏
    e->size = getScreenSize();
}

// 绘制编辑器界面
void drawEditorScreen(struct editor_state *e) {
    abFree(&e->ab);
    e->ab = ABUF_INIT;
    
// 隐藏光标
    hideCursor(&e->ab);
// 清屏
    clearScreen(&e->ab);
// 定位到顶部
    positionCursor(&e->ab, 1, 1);
// 绘制标题
    drawText(&e->ab, "终端编辑器 - 按ESC退出");
// 绘制文本内容
    for (int i = 0; i < e->size.rows - 2; i++) {
        positionCursor(&e->ab, i + 2, 1);
        char line[128];
        snprintf(line, sizeof(line), "第 %3d 行: 示例内容...", i + 1);
        drawText(&e->ab, line);
    }
// 状态栏
    positionCursor(&e->ab, e->size.rows, 1);
    drawText(&e->ab, "状态栏: 就绪");
// 显示光标
    positionCursor(&e->ab, e->cy + 2, e->cx + 1);
    showCursor(&e->ab);
}

// 刷新编辑器屏幕
void refreshEditorScreen(struct editor_state *e) {
    drawEditorScreen(e);
    refreshDisplay(&e->ab); // 传递正确的指针类型
}

int main() {
    // 启用原始模式
    enableRawMode();
    
    // 初始化编辑器状态
    struct editor_state editor;
    initEditor(&editor);
    
    // 首次刷新屏幕
    refreshEditorScreen(&editor);
    
    while (1) {
        int c = readKey();
        
        // 处理特殊键
        switch (c) {
            case KEY_ARROW_UP:
                if (editor.cy > 0) editor.cy--;
                break;
            case KEY_ARROW_DOWN:
                if (editor.cy < editor.size.rows - 3) editor.cy++;
                break;
            case KEY_ARROW_LEFT:
                if (editor.cx > 0) editor.cx--;
                break;
            case KEY_ARROW_RIGHT:
                if (editor.cx < editor.size.cols - 1) editor.cx++;
                break;
            case 27: // ESC键
                printf("退出编辑器\n");
                return 0;
        }
        
        // 刷新屏幕
        refreshEditorScreen(&editor);
    }
    
    return 0;
}