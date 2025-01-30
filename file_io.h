#ifndef FILE_IO_H
#define FILE_IO_H

void editorOpen(char *filename);
char* editorRowsToString(int *buflen);
void editorSave();

#endif