#ifndef TERMINAL_H
#define TERMINAL_H

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
int editorReadKey(void);
int getWindowSize(int *rows, int *cols);

#endif