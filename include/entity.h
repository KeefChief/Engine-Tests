#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#define MAX_ENTITIES 2048

enum {
    ENTF_ALIVE = (1 << 0),
    ENTF_SOLID_TO_MAP = (1 << 1),
    ENTF_SOLID_TO_ENT = (1 << 2)
};

typedef struct Entity{
    int type_id;
    int x;
    int y;
    int vx;
    int vy;
    int life;
    int max_life;
    uint64_t flags;
}Entity;

typedef struct Entity_Specifics{
    int max_life;
    uint64_t flags;
}Entity_Specifics;


extern Entity g_entities[MAX_ENTITIES];
void create_entity(int x, int y, int vx, int vy, int type_id);
void set_specific_data(int n, int type_id);

#endif