#ifndef ENTITY_DEFS_TABLE
#define ENTITY_DEFS_TABLE

#include <stdint.h>

enum{
    ENT_TEST,
    ENT_COUNT
};

typedef struct Entity_Def{
    int max_life;
    uint64_t flags;
    const char *name;
}Entity_Def;

extern Entity_Def g_entity_defs[ENT_COUNT];

#endif