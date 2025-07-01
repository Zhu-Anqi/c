#include "buffer.h"
#include <stdlib.h>
#include <string.h>

// 向缓冲区追加数据
void abAppend(struct abuf *ab, const char *s, size_t len) {
    // 重新分配内存
    char *new = realloc(ab->data, ab->len + len);
    if (new == NULL) return; 
    
    // 复制新数据到缓冲区尾部
    memcpy(new + ab->len, s, len);
    
    // 更新缓冲区指针和长度
    ab->data = new;
    ab->len += len;
}
void abFree(struct abuf *ab) {
    if (ab->data != NULL) {
        free(ab->data);   // 释放内存
        ab->data = NULL;  // 重置指针
        ab->len = 0;      // 重置长度
    }
}