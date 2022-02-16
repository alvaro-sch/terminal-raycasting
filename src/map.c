#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "defs.h"

char *const _map_errstr[] = {
    [MAP_OK] = "MAP_OK",
    [MAP_NSFILE] = "MAP_NSFILE",
    [MAP_ENOMEM] = "MAP_ENOMEM",
    [MAP_BAD_SIZE] = "MAP_BAD_SIZE",
    [MAP_EARLY_EOF] = "MAP_EARLY_EOF",
};

const char *map_errstr(int err) {
    return 0 <= err && err < _MAP_NUM_ERRS ?
        _map_errstr[err] : "(INVALID ERROR CODE)";
}

int map_from_file(struct map *self, const char *filepath) {
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL) {
        return MAP_NSFILE;
    }

    int width = 0, height = 0;
    if (fscanf(fp, "%d %d\n", &width, &height) < 2 || width <= 0 || height <= 0) {
        fclose(fp);
        return MAP_BAD_SIZE;
    }

    char *map = calloc(width * height, sizeof(*map));
    if (map == NULL) {
        fclose(fp);
        return MAP_BAD_SIZE;
    }

    int bytes_read = 0;
    for (int i = 0; !feof(fp) && i < height; ++i) {
        bytes_read += fread(map+bytes_read, sizeof(*map), width, fp);
        fscanf(fp, "\n"); /* should work in windows rather than fgetc */
    }

    if (bytes_read < width * height) {
        free(map);
        fclose(fp);
        return MAP_EARLY_EOF;
    }

    self->width = width;
    self->height = height;
    self->data = map;

    fclose(fp);
    return MAP_OK;
}

char map_xy(struct map *self, int x, int y) {
    return
        0 <= x && x < self->width &&
        0 <= y && y < self->height
            ? self->data[x + y * self->width] : 0;
}

void map_print2d(struct map *self) {
    for (int y = 0; y < self->height; ++y) {
        move(y, 0);
        for (int x = 0; x < self->width; ++x) {
            addch(map_xy(self, x, y));
        }
    }
}

void map_free(struct map *self) {
    self->width = 0;
    self->height = 0;
    free(self->data);
    self->data = NULL;
}
