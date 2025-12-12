#include <SDL2/SDL.h>
#include <stdbool.h>
#include "window.h"
#include "voxels/voxel.h"

int create_sdl_window(int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* sdl_window = SDL_CreateWindow("god's own fluid engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (sdl_window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    Window window;
    window.sdl_window = sdl_window;
    window.sdl_renderer = sdl_renderer;
    window.width = width;
    window.height = height;
    init_camera(&window.cam);

    Voxel voxel = {0, 0, 0, 255, 0, 0};

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            update_camera(&window.cam, &event);
        }

        SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdl_renderer);

        float size = 1.0f;
        float vx = voxel.x1, vy = voxel.x2, vz = voxel.x3;
        float points[8][3] = {
            {vx, vy, vz}, {vx+size, vy, vz}, {vx+size, vy+size, vz}, {vx, vy+size, vz},
            {vx, vy, vz+size}, {vx+size, vy, vz+size}, {vx+size, vy+size, vz+size}, {vx, vy+size, vz+size}
        };
        int screen_points[8][2];
        for(int i = 0; i < 8; i++) {
            project(points[i], &window.cam, window.width, window.height, &screen_points[i][0], &screen_points[i][1]);
        }
        SDL_SetRenderDrawColor(sdl_renderer, voxel.r, voxel.g, voxel.b, 255);
        int edges[12][2] = {
            {0,1},{1,2},{2,3},{3,0},
            {4,5},{5,6},{6,7},{7,4},
            {0,4},{1,5},{2,6},{3,7}
        };
        for(int i = 0; i < 12; i++) {
            int p1 = edges[i][0], p2 = edges[i][1];
            if(screen_points[p1][0] >= 0 && screen_points[p1][1] >= 0 && screen_points[p1][0] < window.width && screen_points[p1][1] < window.height &&
               screen_points[p2][0] >= 0 && screen_points[p2][1] >= 0 && screen_points[p2][0] < window.width && screen_points[p2][1] < window.height) {
                SDL_RenderDrawLine(sdl_renderer, screen_points[p1][0], screen_points[p1][1], screen_points[p2][0], screen_points[p2][1]);
            }
        }

        SDL_RenderPresent(sdl_renderer);
    }

    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
    return 0;
}