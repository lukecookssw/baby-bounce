// standard headers
#include <stdio.h>

// allegro5 headers
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "settings/settings.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#include "lib/nuklear/nuklear.h"
#include "lib/nuklear/nuklear_allegro5.h"

int main()
{

    int setting_1 = 10;
    int setting_2 = 20;

    int window_width = RESOLUTION[0];
    int window_height = RESOLUTION[1];
    printf("Starting...\n");

    al_init();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *disp = al_create_display(window_width, window_height);
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_FONT *font = al_load_ttf_font("./FiraCodeNerdFont-Regular.ttf", 24, 0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    struct nk_allegro5_context *nk_ctx = nk_allegro5_init(font, 24.0f);

    bool redraw = true;
    bool done = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    ALLEGRO_COLOR colour = al_map_rgb(255, 255, 255);

    char c1[10];
    char c2[10];

    while (!done)
    {
        al_wait_for_event(queue, &event);

        struct nk_context *ctx = nk_allegro5_get_ctx(nk_ctx);
        nk_input_begin(ctx);
        nk_allegro5_handle_event(nk_ctx, &event);
        nk_input_end(ctx);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            int settings_panel_width = 250;
            int main_area_width = window_width - settings_panel_width;
            
            struct nk_context *ctx = nk_allegro5_get_ctx(nk_ctx);

            if (nk_begin(ctx, "Settings", nk_rect(main_area_width, 0, settings_panel_width, window_height),
                NK_WINDOW_BORDER|NK_WINDOW_TITLE|NK_WINDOW_NO_SCROLLBAR))
            {
                nk_layout_row_dynamic(ctx, 25, 1);
                nk_label(ctx, "Setting 1:", NK_TEXT_LEFT);
                nk_property_int(ctx, "#", 0, &setting_1, 1000, 1, 1);
                
                nk_layout_row_dynamic(ctx, 25, 1);
                nk_label(ctx, "Setting 2:", NK_TEXT_LEFT);
                nk_property_int(ctx, "#", 0, &setting_2, 1000, 1, 1);
            }
            nk_end(ctx);

            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_text(font, al_map_rgb(0, 255, 255), main_area_width / 2, 0, ALLEGRO_ALIGN_CENTRE, "\ueb54 RUNNING \ueb54");
            sprintf(c1, "%d", setting_1);
            sprintf(c2, "%d", setting_2);

            al_draw_text(font, al_map_rgb(255, 0, 0), main_area_width / 2, (window_height /3), ALLEGRO_ALIGN_CENTRE, c1);
            al_draw_text(font, al_map_rgb(0, 255, 0), main_area_width / 2, (window_height /2), ALLEGRO_ALIGN_CENTRE, c2);

            nk_allegro5_render(nk_ctx);

            al_flip_display();

            redraw = false;
        }
    }

    nk_allegro5_shutdown(nk_ctx);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
