#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include <ncurses.h>

#include "map.h"
#include "defs.h"
#include "player.h"

struct context {
    int width, height;
    bool running;

    struct map map;
    struct player ply;
};

void c_init(struct context *self) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int m_result = map_from_file(&self->map, "demo.txt");
    if (m_result != MAP_OK) {
        PANIC(m_result, "could not load map with err: %s\n",
            map_errstr(m_result));
    }

    getmaxyx(stdscr, self->height, self->width);

    self->ply = (struct player) {
        .x = self->width / 2.0,
        .y = self->height / 2.0,
        .ang = PI/2.0,
    };

    self->running = true;
}

void c_end(struct context *self) {
    map_free(&self->map);
    endwin();
}

int main(int argc, char **argv) {
    (void) argc, (void) argv;
    struct context ctx;
    c_init(&ctx);

    while (ctx.running) {
        int ch = tolower(getch());

        if (ch == 'p') {
            ctx.running = false;
        }

        map_print2d(&ctx.map);
        p_update(&ctx.ply, &ctx.map, ch);
        p_draw2d(&ctx.ply);
    }

    c_end(&ctx);

    return 0;
}
