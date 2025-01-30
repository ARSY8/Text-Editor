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


struct editorConfig E;

void initEditor(){
    E.cx = 0;
    E.cy = 0;
    E.rx = 0;
    E.rowoff = 0;
    E.coloff = 0;
    E.numrows = 0;
    E.row = NULL;
    E.dirty = 0;
    E.filename = NULL;
    E.statusmsg[0] = '\0';
    E.statusmsg_time = 0;

    if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
    E.screenrows -= 2;
}
