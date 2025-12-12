#include <stdio.h>
#include "window/window.h"
#include "scenes/scene.h"

int main() {
    Scene* scene = create_basic_scene();
    scene->show_vertices = false;
    scene->show_edges = false;
    int code = create_sdl_window(800, 600, scene);
    destroy_scene(scene);
    printf("\n:Exited with success code %d\n", code);
    return 0;
}