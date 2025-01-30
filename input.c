#include "config.h"
#include "editor_data.h"
#include "terminal.h"
#include "row_operations.h"
#include "file_io.h"
#include "append_buffer.h"
#include "output.h"
#include "input.h"
#include "init.h"
#include "editor_operations.h"


void editorMoveCursor(int key){
    erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];

    switch (key){
        case ARROW_LEFT:
            if(E.cx != 0){
                E.cx--;
            }
            else if(E.cy > 0){
                E.cy--;
                E.cx = E.row[E.cy].size;
            }
            break;
        case ARROW_RIGHT:
            if(row && E.cx < row->size){
                E.cx++;
            }
            else if(row && E.cx == row->size){
                E.cy++;
                E.cx = 0;
            }
            break;
        case ARROW_UP:
            if(E.cy != 0){
                E.cy--;
            }
            break;
        case ARROW_DOWN:
            if(E.cy < E.numrows){
                E.cy++;
            }
            break;
    }

    row  = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
    int rowlen = row ? row->size : 0;
    if(E.cx > rowlen){
        E.cx = rowlen;
    }
}

void editorProcessKeypress(void){
    static int quit_times = QUIT_TIMES;

    int input = editorReadKey();

    switch(input){
        case '\r':
            editorInsertNewline();
            break;

        case CTRL_KEY('q'):
            if(E.dirty && quit_times > 0){
                editorSetStatusMessage("ПРЕДУПРЕЖДЕНИЕ!!! Изменения в файле не сохранены."
                "Нажмите Ctrl-Q %d раз чтобы выйти.", quit_times);
                quit_times--;
                return;
            }
            write(STDIN_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;

        case CTRL_KEY('s'):
            editorSave();
            break;

        case HOME_KEY:
            E.cx = 0;
            break;

        case END_KEY:
            if(E.cy < E.numrows)
                E.cx = E.row[E.cy].size;
            break;

        case BACKSPACE:
        case CTRL_KEY('h'):
        case DEL_KEY:
            if(input == DEL_KEY) editorMoveCursor(ARROW_RIGHT);
            editorDelChar();
            break;

        case PAGE_UP:
        case PAGE_DOWN:
            {
                if(input == PAGE_UP){
                    E.cy = E.rowoff;
                }
                else if(input == PAGE_DOWN){
                    E.cy = E.rowoff + E.screencols - 1;
                    if(E.cy > E.numrows) E.cy = E.numrows;
                }

                int times = E.screenrows;
                while (times--)
                    editorMoveCursor(input == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorMoveCursor(input);
            break;

        case CTRL_KEY('l'):
        case '\x1b':
            break;

        default:
            editorInsertChar(input);
            break;
    }
    quit_times = QUIT_TIMES;
}

char *editorPrompt(char *prompt){
    size_t bufsize = 128;
    char *buf = malloc(bufsize);

    size_t buflen = 0;
    buf[0] = '\0';

    while(1){
        editorSetStatusMessage(prompt, buf);
        editorRefreshScreen();

        int input = editorReadKey();
        if(input == DEL_KEY || input == CTRL_KEY('h') || input == BACKSPACE){
            if(buflen != 0) buf[--buflen] = '\0';
        }
        else if (input == '\x1b'){
            editorSetStatusMessage("");
            free(buf);
            return NULL;
        }
        else if(input == '\r'){
            if(buflen != 0){
                editorSetStatusMessage("");
                return buf;
            }
        }
        else if(!iscntrl(input) && input < 128){
            if(buflen == bufsize - 1){
                bufsize *= 2;
                buf = realloc(buf, bufsize);
            }
            buf[buflen++] = input;
            buf[buflen] = '\0';
        }
    }
}