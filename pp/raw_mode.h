#ifndef RAW_MODE_H
#define RAW_MODE_H

#include <termios.h>
#include <stdbool.h>

extern struct termios orig_termios;

void enableRawMode(void);
void disableRawMode(void);
void displayKeyInfo(int c);
bool isFileDescriptorValid(int fd);

#endif