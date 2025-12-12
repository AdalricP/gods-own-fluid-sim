#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "scenes/scene.h"
#include "camera/camera_movement.h"
#include "voxel/voxel.h"

int create_sdl_window(int width, int height, Scene* scene) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* sdl_window = SDL_CreateWindow("god's own fluid engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (sdl_window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(sdl_window);
    if (gl_context == NULL) {
        printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        return 1;
    }

    if (SDL_GL_MakeCurrent(sdl_window, gl_context) < 0) {
        printf("Failed to make context current: %s\n", SDL_GetError());
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glViewport(0, 0, width, height);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    Window window;
    window.sdl_window = sdl_window;
    window.gl_context = gl_context;
    window.width = width;
    window.height = height;
    init_camera(&window.cam);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            update_camera(&window.cam, &event);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(window.cam.fov, (float)window.width / window.height, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(-window.cam.pitch, 1, 0, 0);
        glRotatef(window.cam.yaw, 0, 1, 0);
        glRotatef(-window.cam.roll, 0, 0, 1);
        glTranslatef(-window.cam.position[0], -window.cam.position[1], -window.cam.position[2]);

        for(int i = 0; i < scene->count; i++) {
            Voxel* voxel = &scene->voxels[i];
            glPushMatrix();
            glTranslatef(voxel->x1, voxel->x2, voxel->x3);
            render_voxel(voxel, scene->show_vertices, scene->show_edges);
            glPopMatrix();
        }

        glFlush();

        SDL_GL_SwapWindow(sdl_window);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
    return 0;
}