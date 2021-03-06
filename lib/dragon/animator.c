/*
** EPITECH PROJECT, 2019
** libdragon
** File description:
** animator
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "dg_window.h"
#include "animator.h"
#include "epitech_tools.h"

animator_t *animator_create(void)
{
    animator_t *animator = malloc(sizeof(animator_t));

    if (!animator)
        return 0;
    animator->current = 0;
    animator->length = 0;
    animator->animations = 0;
    animator->keys = 0;
    animator->time = 0;
    return animator;
}

void animator_add(animator_t * animator, char * key, animation_t *animation)
{
    animation_t **new_anim_list = 0;
    char **new_key_list = 0;

    new_anim_list = malloc(sizeof(animation_t *) * (animator->length + 1));
    new_key_list = malloc(sizeof(char *) * (animator->length + 1));
    if (animator->length != 0) {
        for (int i = 0; i < animator->length; i++) {
            new_anim_list[i] = animator->animations[i];
            new_key_list[i] = animator->keys[i];
        }
        free(animator->animations);
        free(animator->keys);
    }
    new_anim_list[animator->length] = animation;
    new_key_list[animator->length] = key;
    animator->animations = new_anim_list;
    animator->keys = new_key_list;
    animator->length++;
}

void animator_update_sprite(
    animator_t *animator,
    sfSprite *sprite,
    int dt
    )
{
    animation_t *animation = 0;
    spritesheet_t *sheet = 0;
    animator->time += dt / 1000000.0;
    int index = 0;

    if (!animator || animator->length <= animator->current)
        return;
    animation = animator->animations[animator->current];
    sheet = animation->sheet;
    index = (int)(animator->time / (1 / animation->speed));
    if (index >= animation->size) {
        index = 0;
        animator->time = 0;
    }
    int frame = animation->frames[index];
    spritesheet_to_sprite(sheet, sprite, frame);
}

void animator_set_animation(animator_t *animator, char *key)
{
    int index = 0;

    for (int i = 0; i < animator->length; i++) {
        if (!dg_strcmp(animator->keys[i], key))
            index = i;
    }
    animator->current = index;
}

void animator_free(animator_t *animator)
{
    if (animator->length > 0) {
        for (int i = 0; i < animator->length; i++)
            animation_free(animator->animations[i]);
        free(animator->animations);
        free(animator->keys);
    }
    free(animator);
}
