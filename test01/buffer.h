#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

// 追加缓冲区结构
struct abuf {
    char *data;     // 缓冲区指针
    size_t len;     // 缓冲区长度
};

// 初始化宏定义
#define ABUF_INIT (struct abuf){NULL, 0}

void abAppend(struct abuf *ab, const char *s, size_t len);
void abFree(struct abuf *ab);

#endif