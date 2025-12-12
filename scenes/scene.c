#include "scene.h"
#include <stdlib.h>

Scene* create_basic_scene() {
    Scene* scene = malloc(sizeof(Scene));
    scene->count = 3;
    scene->voxels = malloc(sizeof(Voxel) * scene->count);
    scene->voxels[0] = (Voxel){0, 0, 0, 255, 0, 0, false};
    scene->voxels[1] = (Voxel){1, 0, 0, 0, 255, 0, false};
    scene->voxels[2] = (Voxel){0, 1, 0, 0, 0, 255, false};
    scene->show_vertices = true;
    scene->show_edges = true;
    return scene;
}

void destroy_scene(Scene* scene) {
    free(scene->voxels);
    free(scene);
}