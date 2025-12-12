#include "camera.h"
#include "camera_movement.h"
#include <SDL2/SDL.h>
#include <math.h>

void init_camera(Camera *cam) {
    cam->position[0] = 0.0f;
    cam->position[1] = 0.0f;
    cam->position[2] = 5.0f;
    cam->yaw = 0.0f;
    cam->pitch = 0.0f;
    cam->roll = 0.0f;
    cam->fov = 90.0f;
    cam->isometric = false;
}

void project(float world[3], Camera *cam, int screen_width, int screen_height, int *screen_x, int *screen_y) {
    float aspect = (float)screen_width / screen_height;
    float fov_rad = cam->fov * M_PI / 180.0f;
    float f = 1.0f / tanf(fov_rad / 2.0f);

    float x = world[0] - cam->position[0];
    float y = world[1] - cam->position[1];
    float z = world[2] - cam->position[2];

    float cos_pitch = cosf(cam->pitch * M_PI / 180.0f);
    float sin_pitch = sinf(cam->pitch * M_PI / 180.0f);
    float y1 = y * cos_pitch - z * sin_pitch;
    float z1 = y * sin_pitch + z * cos_pitch;

    float cos_yaw = cosf(cam->yaw * M_PI / 180.0f);
    float sin_yaw = sinf(cam->yaw * M_PI / 180.0f);
    float x2 = x * cos_yaw - z1 * sin_yaw;
    float z2 = x * sin_yaw + z1 * cos_yaw;

    float roll_rad = cam->roll * M_PI / 180.0f;
    float cos_roll = cosf(roll_rad);
    float sin_roll = sinf(roll_rad);
    float x3 = x2 * cos_roll - y1 * sin_roll;
    float y3 = x2 * sin_roll + y1 * cos_roll;

    if (z2 > 0.1f) {
        float px = x3 / z2;
        float py = y3 / z2;

        *screen_x = (int)((px * f / aspect + 1.0f) * screen_width / 2.0f);
        *screen_y = (int)((1.0f - py * f) * screen_height / 2.0f);
    } else {
        *screen_x = -1;
        *screen_y = -1;
    }
}