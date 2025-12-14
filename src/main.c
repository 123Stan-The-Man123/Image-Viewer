#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL3/SDL.h>

#include "ascii_ppm.h"

#define MAX_SIG_LENGTH 3

void get_image_size(char*, int*, int*);
void parse_image(char*, int, int, SDL_Renderer*);

int main(void)
{
    char signature[MAX_SIG_LENGTH];

    for (int i = 0; i < MAX_SIG_LENGTH; i++) {
        assert(read(STDIN_FILENO, (void*)&signature[i], 1) != -1);
        if (signature[i] == '\n') {
            signature[i] = '\0';
            break;
        }
    }

    int width, height;
    get_image_size(signature, &width, &height);

    SDL_Window *window = SDL_CreateWindow("Image Viewer", width, height, SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    parse_image(signature, width, height, renderer);

    int running = 1;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT)
                running = 0;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}

void get_image_size(char *signature, int *width, int *height)
{
    if (strcmp(signature, "P3") == 0)
        ascii_ppm_size(width, height);
}

void parse_image(char *signature, int width, int height, SDL_Renderer *renderer)
{
    if (strcmp(signature, "P3") == 0)
        parse_ascii_ppm(renderer, width, height);
}
