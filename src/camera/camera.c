#include "camera.h"
#include <SDL2/SDL.h>
#include <math.h>

void init_camera(Camera *cam) {
    cam->position[0] = 0.0f;
    cam->position[1] = 1.0f;
    cam->position[2] = -2.0f;
    cam->rotation[0] = -M_PI / 4.0f;
    cam->rotation[1] = 0.0f;
    cam->rotation[2] = 0.0f;
    cam->fov = 45.0f;
    cam->isometric = false;
}

void update_camera(Camera *cam, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_w:
                cam->position[2] += 0.1f;
                break;
            case SDLK_s:
                cam->position[2] -= 0.1f;
                break;
            case SDLK_a:
                cam->position[0] -= 0.1f;
                break;
            case SDLK_d:
                cam->position[0] += 0.1f;
                break;
            case SDLK_SPACE:
                cam->position[1] += 0.1f;
                break;
            case SDLK_LSHIFT:
                cam->position[1] -= 0.1f;
                break;
            case SDLK_q:
                cam->rotation[2] += 0.1f;
                break;
            case SDLK_e:
                cam->rotation[2] -= 0.1f;
                break;
        }
    }
    if (event->type == SDL_MOUSEMOTION) {
        cam->rotation[1] += event->motion.xrel * 0.005f;
        cam->rotation[0] -= event->motion.yrel * 0.005f;
        if (cam->rotation[0] > M_PI / 2.0f) cam->rotation[0] = M_PI / 2.0f;
        if (cam->rotation[0] < -M_PI / 2.0f) cam->rotation[0] = -M_PI / 2.0f;
    }
}

void project(float world[3], Camera *cam, int screen_width, int screen_height, int *screen_x, int *screen_y) {
    float aspect = (float)screen_width / screen_height;
    float fov_rad = cam->fov * M_PI / 180.0f;
    float f = 1.0f / tanf(fov_rad / 2.0f);

    float x = world[0] - cam->position[0];
    float y = world[1] - cam->position[1];
    float z = world[2] - cam->position[2];

    float cos_pitch = cosf(cam->rotation[0]);
    float sin_pitch = sinf(cam->rotation[0]);
    float y1 = y * cos_pitch - z * sin_pitch;
    float z1 = y * sin_pitch + z * cos_pitch;

    float cos_yaw = cosf(cam->rotation[1]);
    float sin_yaw = sinf(cam->rotation[1]);
    float rx = x * cos_yaw - z1 * sin_yaw;
    float ry = y1;
    float rz = x * sin_yaw + z1 * cos_yaw;

    float cos_roll = cosf(cam->rotation[2]);
    float sin_roll = sinf(cam->rotation[2]);
    float rx2 = rx * cos_roll - ry * sin_roll;
    float ry2 = rx * sin_roll + ry * cos_roll;

    if (rz > 0.1f) {
        float px = rx2 / rz;
        float py = ry2 / rz;

        *screen_x = (int)((px * f / aspect + 1.0f) * screen_width / 2.0f);
        *screen_y = (int)((1.0f - py * f) * screen_height / 2.0f);
    } else {
        *screen_x = -1;
        *screen_y = -1;
    }
}