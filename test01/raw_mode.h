#ifndef RAW_MODE_H
#define RAW_MODE_H
#include <termios.h>
#include <stdbool.h>

// 特殊键
enum editorKey {
    KEY_ARROW_LEFT = 1000,
    KEY_ARROW_RIGHT,
    KEY_ARROW_UP,
    KEY_ARROW_DOWN,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_DEL
};

void enableRawMode(void);
void disableRawMode(void);
int readKey(void);

#endif