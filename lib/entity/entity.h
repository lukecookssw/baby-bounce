#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>

typedef struct Entity
{
    int id;
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
    float radius;
    ALLEGRO_COLOR colour;

} Entity;

Entity *entity_create(int id, float radius);

#endif
