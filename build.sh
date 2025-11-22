#!/usr/bin/env bash
gcc -g -O0 -o main.out \
main.c \
settings/settings.c \
lib/baby/baby.c \
lib/entity/entity.c \
$(pkg-config --cflags --libs allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5) -lm
