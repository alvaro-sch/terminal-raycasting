#ifndef _DEFS_H
#define _DEFS_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ncurses.h>

#define PI    3.1415926
#define PI_8  (PI / 8.0)
#define PI_16 (PI / 16.0)

#ifdef DEBUG
# define DBG_PRINT(y, x, ...) mvprintw(y, x, "DEBUG: %s:%d:%s(): ", \
    __FILE__, __LINE__, __func__); printw(__VA_ARGS__); move(0, 0)
# define DBG_ASSERT(expr) assert(expr)
#else
# define DBG_PRINT(y, x, ...) do {} while (0)
# define DBG_ASSERT(expr) do {} while (0)
#endif

#define PANIC(code, ...) endwin(); fprintf(stderr, "panic! code: %d in %s:%d:%s()\nmessage: ", \
    code, __FILE__, __LINE__, __func__); fprintf(stderr, __VA_ARGS__); exit(code)

#endif /* _DEFS_H */
