#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL3/SDL.h>

#define MAX_SIG_LENGTH 3

int main(void)
{
    char buf[MAX_SIG_LENGTH];

    for (int i = 0; i < MAX_SIG_LENGTH; i++) {
        assert(read(STDIN_FILENO, (void*)&buf[i], 1) != -1);
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }

    SDL_Window *window = SDL_CreateWindow("Image Viewer", 800, 600, SDL_WINDOW_RESIZABLE);

    int running = 1;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT)
                running = 0;
        }
    }

    SDL_DestroyWindow(window);
    return 0;
}
