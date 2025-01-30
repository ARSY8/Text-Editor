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


int main(int argc, char *argv[]){

    enableRawMode();
    initEditor();
    if(argc >= 2){
        editorOpen(argv[1]);
    }

    editorSetStatusMessage("HELP: Ctrl-S = сохранить | Ctrl-Q = выход");

    while (1){
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}