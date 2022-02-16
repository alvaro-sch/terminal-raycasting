#ifndef _PLAYER_H
#define _PLAYER_H

struct map;

struct player {
    float x, y; /* map position */
    float ang;  /* angle        */
};

/* update movement with 'collision detection' */
void p_update(struct player *self, struct map *map, int ch);

/* draw in top-down view */
void p_draw2d(struct player *self);

#endif /* _PLAYER_H */
