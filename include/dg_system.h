/*
** EPITECH PROJECT, 2019
** libdragon
** File description:
** define the dg_system struct
*/

#ifndef DG_SYSTEM_H_
#define DG_SYSTEM_H_

#include "dg_entity.h"
#include "dg_window.h"

typedef struct dg_system {
    void (*system)(dg_entity_t *, dg_window_t *, dg_entity_t **, sfTime);
} dg_system_t;

dg_system_t *dg_system_create(void (*)(dg_entity_t *, dg_window_t *,
    dg_entity_t **, sfTime));

void dg_system_destroy(dg_system_t *);

int dg_system_require(dg_entity_t *, unsigned int, ...);

void system_player_animator(dg_entity_t *, dg_window_t *,
    dg_entity_t **, sfTime);

#endif /*DG_SYSTEM_H*/
