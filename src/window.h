#ifndef WINDOW_H
#define WINDOW_H

#include "camera/camera.h"

int create_sdl_window(int width, int height);

typedef struct {
    void* sdl_window;
    void* sdl_renderer;
    int width;
    int height;
    Camera cam;
} Window;

#endif // WINDOW_H