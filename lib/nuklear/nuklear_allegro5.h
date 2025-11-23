#ifndef NK_ALLEGRO5_H
#define NK_ALLEGRO5_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR

struct nk_context;
struct nk_user_font;

struct nk_allegro5_context {
    struct nk_context *ctx;
    ALLEGRO_FONT *font;
    float font_height;
};

struct nk_allegro5_context* nk_allegro5_init(ALLEGRO_FONT *font, float font_height);
void nk_allegro5_handle_event(struct nk_allegro5_context *ctx, ALLEGRO_EVENT *event);
void nk_allegro5_render(struct nk_allegro5_context *ctx);
void nk_allegro5_shutdown(struct nk_allegro5_context *ctx);
struct nk_context* nk_allegro5_get_ctx(struct nk_allegro5_context *ctx);

#endif
