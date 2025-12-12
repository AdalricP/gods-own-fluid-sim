#ifndef SCENE_H
#define SCENE_H

#include "voxel/voxel.h"

typedef struct {
    Voxel* voxels;
    int count;
    bool show_vertices;
    bool show_edges;
} Scene;

Scene* create_basic_scene();
void destroy_scene(Scene* scene);

#endif