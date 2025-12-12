#ifndef WINDOW_H
#define WINDOW_H

#include "camera/camera.h"
#include "scenes/scene.h"

int create_sdl_window(int width, int height, Scene* scene);

typedef struct {
    void* sdl_window;
    void* gl_context;
    int width;
    int height;
    Camera cam;
} Window;

#endif // WINDOW_H