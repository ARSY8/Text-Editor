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


void abAppend(struct abuf *ab, const char *s, int len){
    char *new = realloc(ab->b, ab->len +len);

    if (new == NULL) return;
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;

}

void abFree(struct abuf *ab){
    free(ab->b);
}