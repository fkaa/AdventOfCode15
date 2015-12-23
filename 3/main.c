#include <stdlib.h>
#include <stdio.h>

struct coord_t {
    int x;
    int y;
};

struct location_t {
    struct coord_t coord;
    int presents;
};

struct map_t {
    struct location_t *locations;
    int len;
    int cap;
};

struct map_t map_create(int count)
{
    struct map_t map = {
        .locations = calloc(sizeof(struct location_t), count),
        .len = 0,
        .cap = count
    };

    return map;
}

void map_free(struct map_t *map)
{
    free(map->locations);
}

void map_put(struct map_t *self, struct coord_t pos)
{
    for (int i = 0; i < self->len; ++i) {
        struct coord_t coord = self->locations[i].coord;
        if (pos.x == coord.x && pos.y == coord.y) {
            self->locations[i].presents++;
            return;
        }
    }

    if (self->len + 1 > self->cap) {
        self->locations = realloc(self->locations, sizeof(struct location_t) * (self->cap * 2));
        self->cap *= 2;
    }

    self->locations[self->len++] = (struct location_t) {
        .coord = pos,
        .presents = 1
    };
}

int main()
{
    struct map_t map = map_create(512);
    struct coord_t santa = {0};
    struct coord_t robo_santa = {0};
    struct coord_t *pos = NULL;

    int santa_turn = 0;
    char c;

    while ((c = fgetc(stdin)) != EOF) {
        pos = santa_turn++ & 1 ? &santa : &robo_santa;
        map_put(&map, *pos);

        switch (c) {
            case '<':
                pos->x--;
                break;
            case 'v':
                pos->y--;
                break;
            case '>':
                pos->x++;
                break;
            case '^':
                pos->y++;
                break;
            default:
                break;
        }
    }

    printf("Santa & Robo-santa has delivered presents to %d households\n", map.len);

    map_free(&map);
    return 0;
}
