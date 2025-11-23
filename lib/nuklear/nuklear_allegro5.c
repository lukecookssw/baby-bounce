#include "nuklear_allegro5.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"
#include <string.h>
#include <stdlib.h>

static float
nk_allegro5_font_width(nk_handle handle, float height, const char *text, int len)
{
    struct nk_allegro5_context *ctx = (struct nk_allegro5_context*)handle.ptr;
    if (!ctx || !ctx->font || !text || len <= 0) return 0;
    
    char buffer[512];
    int text_len = (len < 511) ? len : 511;
    memcpy(buffer, text, text_len);
    buffer[text_len] = '\0';
    
    return al_get_text_width(ctx->font, buffer);
}

struct nk_context* nk_allegro5_get_ctx(struct nk_allegro5_context *ctx)
{
    return ctx->ctx;
}

struct nk_allegro5_context* nk_allegro5_init(ALLEGRO_FONT *font, float font_height)
{
    struct nk_allegro5_context *ctx = malloc(sizeof(struct nk_allegro5_context));
    ctx->font = font;
    ctx->font_height = font_height;
    ctx->ctx = malloc(sizeof(struct nk_context));
    
    struct nk_user_font *nk_font = malloc(sizeof(struct nk_user_font));
    nk_font->userdata.ptr = ctx;
    nk_font->height = font_height;
    nk_font->width = nk_allegro5_font_width;
    
    nk_init_default(ctx->ctx, nk_font);
    return ctx;
}

void nk_allegro5_handle_event(struct nk_allegro5_context *ctx, ALLEGRO_EVENT *event)
{
    struct nk_context *nk_ctx = ctx->ctx;
    
    switch(event->type) {
        case ALLEGRO_EVENT_MOUSE_AXES:
            nk_input_motion(nk_ctx, event->mouse.x, event->mouse.y);
            nk_input_scroll(nk_ctx, nk_vec2(0, event->mouse.dz));
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (event->mouse.button == 1)
                nk_input_button(nk_ctx, NK_BUTTON_LEFT, event->mouse.x, event->mouse.y, 1);
            else if (event->mouse.button == 2)
                nk_input_button(nk_ctx, NK_BUTTON_RIGHT, event->mouse.x, event->mouse.y, 1);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (event->mouse.button == 1)
                nk_input_button(nk_ctx, NK_BUTTON_LEFT, event->mouse.x, event->mouse.y, 0);
            else if (event->mouse.button == 2)
                nk_input_button(nk_ctx, NK_BUTTON_RIGHT, event->mouse.x, event->mouse.y, 0);
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            if (event->keyboard.unichar >= 32 && event->keyboard.unichar < 127)
                nk_input_char(nk_ctx, (char)event->keyboard.unichar);
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
                nk_input_key(nk_ctx, NK_KEY_BACKSPACE, 1);
            else if (event->keyboard.keycode == ALLEGRO_KEY_DELETE)
                nk_input_key(nk_ctx, NK_KEY_DEL, 1);
            else if (event->keyboard.keycode == ALLEGRO_KEY_ENTER)
                nk_input_key(nk_ctx, NK_KEY_ENTER, 1);
            break;
    }
}

void nk_allegro5_render(struct nk_allegro5_context *ctx)
{
    const struct nk_command *cmd;
    struct nk_context *nk_ctx = ctx->ctx;
    
    nk_foreach(cmd, nk_ctx) {
        switch (cmd->type) {
            case NK_COMMAND_NOP: break;
            case NK_COMMAND_SCISSOR: {
                const struct nk_command_scissor *s = (const struct nk_command_scissor*)cmd;
                al_set_clipping_rectangle(s->x, s->y, s->w, s->h);
            } break;
            case NK_COMMAND_LINE: {
                const struct nk_command_line *l = (const struct nk_command_line*)cmd;
                al_draw_line(l->begin.x, l->begin.y, l->end.x, l->end.y,
                    al_map_rgba(l->color.r, l->color.g, l->color.b, l->color.a), l->line_thickness);
            } break;
            case NK_COMMAND_RECT: {
                const struct nk_command_rect *r = (const struct nk_command_rect*)cmd;
                al_draw_rounded_rectangle(r->x, r->y, r->x + r->w, r->y + r->h, r->rounding, r->rounding,
                    al_map_rgba(r->color.r, r->color.g, r->color.b, r->color.a), r->line_thickness);
            } break;
            case NK_COMMAND_RECT_FILLED: {
                const struct nk_command_rect_filled *r = (const struct nk_command_rect_filled*)cmd;
                al_draw_filled_rounded_rectangle(r->x, r->y, r->x + r->w, r->y + r->h, r->rounding, r->rounding,
                    al_map_rgba(r->color.r, r->color.g, r->color.b, r->color.a));
            } break;
            case NK_COMMAND_CIRCLE: {
                const struct nk_command_circle *c = (const struct nk_command_circle*)cmd;
                al_draw_ellipse(c->x + c->w/2, c->y + c->h/2, c->w/2, c->h/2,
                    al_map_rgba(c->color.r, c->color.g, c->color.b, c->color.a), c->line_thickness);
            } break;
            case NK_COMMAND_CIRCLE_FILLED: {
                const struct nk_command_circle_filled *c = (const struct nk_command_circle_filled*)cmd;
                al_draw_filled_ellipse(c->x + c->w/2, c->y + c->h/2, c->w/2, c->h/2,
                    al_map_rgba(c->color.r, c->color.g, c->color.b, c->color.a));
            } break;
            case NK_COMMAND_TRIANGLE: {
                const struct nk_command_triangle *t = (const struct nk_command_triangle*)cmd;
                al_draw_triangle(t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y,
                    al_map_rgba(t->color.r, t->color.g, t->color.b, t->color.a), t->line_thickness);
            } break;
            case NK_COMMAND_TRIANGLE_FILLED: {
                const struct nk_command_triangle_filled *t = (const struct nk_command_triangle_filled*)cmd;
                al_draw_filled_triangle(t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y,
                    al_map_rgba(t->color.r, t->color.g, t->color.b, t->color.a));
            } break;
            case NK_COMMAND_TEXT: {
                const struct nk_command_text *t = (const struct nk_command_text*)cmd;
                al_draw_text(ctx->font, al_map_rgba(t->foreground.r, t->foreground.g, t->foreground.b, t->foreground.a),
                    t->x, t->y, 0, t->string);
            } break;
            default: break;
        }
    }
    nk_clear(nk_ctx);
}

void nk_allegro5_shutdown(struct nk_allegro5_context *ctx)
{
    if (ctx->ctx->memory.pool.userdata.ptr)
        free(ctx->ctx->memory.pool.userdata.ptr);
    nk_free(ctx->ctx);
    free(ctx->ctx);
    free(ctx);
}
