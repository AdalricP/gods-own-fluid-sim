#include "camera_movement.h"
#include <math.h>

void update_camera(Camera *cam, SDL_Event *event) {
    float speed = 0.1f;
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_w:
                cam->position[2] -= speed;
                break;
            case SDLK_s:
                cam->position[2] += speed;
                break;
            case SDLK_a:
                cam->position[0] -= speed;
                break;
            case SDLK_d:
                cam->position[0] += speed;
                break;
            case SDLK_SPACE:
                cam->position[1] += speed;
                break;
            case SDLK_LSHIFT:
                cam->position[1] -= speed;
                break;
            case SDLK_q:
                cam->roll += 3.0f;
                break;
            case SDLK_e:
                cam->roll -= 3.0f;
                break;
        }
    }
    if (event->type == SDL_MOUSEMOTION) {
        cam->yaw += event->motion.xrel * 0.2f;
        cam->pitch -= event->motion.yrel * 0.2f;
        if (cam->pitch > 89.0f) cam->pitch = 89.0f;
        if (cam->pitch < -89.0f) cam->pitch = -89.0f;
    }
}