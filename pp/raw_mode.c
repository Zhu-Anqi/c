#include "raw_mode.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
struct termios orig_termios; 

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // 禁用回显/规范模式/信号
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_cc[VMIN] = 1;   // 最少读取1个字符
    raw.c_cc[VTIME] = 10; // 超时时间(1/10秒)
    raw.c_oflag &= ~(OPOST);

     if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr失败");
        exit(EXIT_FAILURE);
    }
}

void displayKeyInfo(int c) {
    if (iscntrl(c)) {
        if (c == '\n') {
            printf("\\n");
        } else if (c == '\t') {
            printf("\\t");
        } else if (c == 127) {
            printf("DEL");
        } else {
            printf("^%c", c + 64);
        }
    } else {
        printf("%c", c);
    }
    printf(" (Dec: %d, Hex: 0x%02x)", c, c);
}

bool isFileDescriptorValid(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}
