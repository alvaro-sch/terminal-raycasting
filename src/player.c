#include <math.h>
#include <ncurses.h>

#include "defs.h"
#include "map.h"
#include "player.h"

void p_update(struct player *self, struct map *map, int ch) {
    int dirx = 0, diry = 0;
    float theta = 0;

    switch (ch) {
    case 'q':
        theta += 0.1;
        break;

    case 'e':
        theta -= 0.1;
        break;

    case 'w':
        diry -= 1;
        break;

    case 's':
        diry += 1;
        break;

    case 'a':
        dirx -= 1;
        break;

    case 'd':
        dirx += 1;
        break;

    default: break;
    }

    self->ang += theta;

    float dx = cos(self->ang);
    float dy = sin(self->ang);

    int old_x = self->x;
    self->x += dy * dirx - dx * diry;
    if (map_xy(map, self->x, self->y) == '#') {
        self->x = old_x;
    }

    int old_y = self->y;
    self->y += dy * diry + dx * dirx;
    if (map_xy(map, self->x, self->y) == '#') {
        self->y = old_y;
    }
}

void p_draw2d(struct player *self) {
    char pchar = '-';
    float angle = remainderf(self->ang, PI);
    if (angle < 0.0) {
        angle += PI;
    }

    if (PI_16 <= angle && angle < 7.0*PI_16) {
        pchar = '/';
    }
    else if (7.0*PI_16 <= angle && angle < 9.0*PI_16) {
        pchar = '|';
    }
    else if (9.0*PI_16 <= angle && angle < 15.0*PI_16) {
        pchar = '\\';
    }

    DBG_PRINT(0, 0, "[%.2f %.2f]@%.2f", self->x, self->y, self->ang);
    mvaddch(self->y, self->x, pchar);
    move(0, 0);
}
