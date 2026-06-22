#include "entity.h"
#include "entity_defs.h"
#include <stdio.h>

Entity g_entities[MAX_ENTITIES];

void create_entity(int x, int y, int vx, int vy, int type_id){
    int n;
    for(n = 0; n <= MAX_ENTITIES; n++){
        if(g_entities[n].flags & ENTF_ALIVE) { continue;}
    }
    if(n == MAX_ENTITIES){return;}
    set_specific_data(n, type_id);
    g_entities[n].flags |= ENTF_ALIVE;
    g_entities[n].x = x;
    g_entities[n].y = y;
    g_entities[n].vx = vx;
    g_entities[n].vy = vy;
    printf("Instantiated entity of type: \"%s\" at:\nx: %d\ny%d\n", g_entity_defs[type_id].name, x, y);
}

void set_specific_data(int n, int type_id){
    g_entities[n].max_life = g_entity_defs[type_id].max_life;
}