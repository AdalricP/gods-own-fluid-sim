#ifndef CAMERA_MOVEMENT_H
#define CAMERA_MOVEMENT_H

#include "camera.h"
#include <SDL2/SDL.h>

void update_camera(Camera *cam, SDL_Event *event);

#endif // CAMERA_MOVEMENT_H