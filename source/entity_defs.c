#include "entity_defs.h"
#include "entity.h"

Entity_Def g_entity_defs[ENT_COUNT] = {
    [ENT_TEST] = {.max_life = 40, .flags = ENTF_SOLID_TO_MAP, .name = "test"},
};