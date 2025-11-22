// standard headers
#include <stdio.h>

// allegro5 headers
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "settings/settings.h"

int main()
{
    int window_width = RESOLUTION[0];
    int window_height = RESOLUTION[1];
    printf("Starting...\n");

    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *disp = al_create_display(window_width, window_height);
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_FONT *font = al_load_ttf_font("./FiraCodeNerdFont-Regular.ttf", 24, 0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    bool done = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    ALLEGRO_COLOR colour = al_map_rgb(255, 255, 255);

    while (!done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_text(font, al_map_rgb(0, 255, 255), window_width / 2, 0, ALLEGRO_ALIGN_CENTRE, "\ueb54 RUNNING \ueb54");

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
