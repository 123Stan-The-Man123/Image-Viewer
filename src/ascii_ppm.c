#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL3/SDL.h>

void ascii_ppm_size(int *width, int *height)
{
    char buf[1000];
    int space_index = 0;

    for (int i = 0; i < 1000; i++) {
        assert(read(STDIN_FILENO, (void*)&buf[i], 1) != -1);

        if (buf[i] == ' ') {
            space_index = i;
            buf[i] = '\0';
        }else if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }

    *width = atoi(buf);
    *height = atoi(&buf[space_index+1]);
}

void read_ppm_line(char *buf)
{
    for (int i = 0; i < 4; i++) {
        assert(read(STDIN_FILENO, (void*)&buf[i], 1) != -1);
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
}

void parse_ascii_ppm(SDL_Renderer *renderer, int width, int height)
{
    char buf[4];
    char red[4], green[4], blue[4];

    read_ppm_line(buf);
    int max_color = atoi(buf);

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            
            read_ppm_line(red);
            read_ppm_line(green);
            read_ppm_line(blue);

            SDL_SetRenderDrawColor(renderer, 255*atoi(red)/max_color, 255*atoi(green)/max_color, 255*atoi(blue)/max_color, 255);
            SDL_RenderPoint(renderer, column, row);
        }
    }

    SDL_RenderPresent(renderer);
}
