#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    float position[3]; 
    float rotation[3]; 
    float fov;         
    bool isometric;    
} Camera;

void init_camera(Camera *cam);

void update_camera(Camera *cam, SDL_Event *event);

void project(float world[3], Camera *cam, int screen_width, int screen_height, int *screen_x, int *screen_y);

#endif // CAMERA_H