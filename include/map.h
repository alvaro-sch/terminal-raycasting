#ifndef _MAP_H
#define _MAP_H

#include <stdlib.h>

/**
 * a map is a file with the following format
 * - line 1 contains <cols rows> of the map in sepparated with a space
 *   it should not include newlines
 *
 * - the next lines will contain at least widthxheight characters
 * '#' may be used for walls and ' ' for empty spaces
 *
 * - there must be a newline between each row
 *
 * not following the guidelines may segfoult the program,
 * if it doesn't it will return a map_err error code
*/

extern int map_res;

struct map {
    int width, height;
    char *data;
};

enum map_err {
    MAP_OK = 0,     /* no error            */
    MAP_NSFILE,     /* no such file        */
    MAP_ENOMEM,     /* insufficient memory */
    MAP_BAD_SIZE,   /* bad specified size  */
    MAP_EARLY_EOF,  /* EOF before expected */
    _MAP_NUM_ERRS,
};

/* str representation of error code */
const char *map_errstr(int err);

/* loads map from file */
int map_from_file(struct map *self, const char *filepath);

/* returns [x,y] coords of map returning '\0' if out of bounds */
char map_xy(struct map *self, int x, int y);

/* print map in top-down view */
void map_print2d(struct map *self);

/* frees map data */
void map_free(struct map *self);

#endif /* _MAP_H */
