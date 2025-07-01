#include "raw_mode.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        perror("tcsetattr disable failed");
        exit(EXIT_FAILURE);
    }
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr failed");
        exit(EXIT_FAILURE);
    }
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;
    
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 10;
    raw.c_cflag |= (CS8);
    
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr enable failed");
        exit(EXIT_FAILURE);
    }
}

int readKey() {
    int nread;
    char c;
    
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            perror("read");
            return -1;
        }
    }
    
    if (c == '\x1b') {
        char seq[3];
        
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
        
        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return KEY_HOME;
                        case '3': return KEY_DEL;
                        case '4': return KEY_END;
                        case '5': return KEY_PAGE_UP;
                        case '6': return KEY_PAGE_DOWN;
                        case '7': return KEY_HOME;
                        case '8': return KEY_END;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A': return KEY_ARROW_UP;
                    case 'B': return KEY_ARROW_DOWN;
                    case 'C': return KEY_ARROW_RIGHT;
                    case 'D': return KEY_ARROW_LEFT;
                    case 'H': return KEY_HOME;
                    case 'F': return KEY_END;
                }
            }
        }
        return '\x1b'; // 未知ESC序列
    }
    
    return c;
}