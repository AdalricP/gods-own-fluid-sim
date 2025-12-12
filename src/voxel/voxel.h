#ifndef VOXEL_H
#define VOXEL_H

#include <stdbool.h>

typedef struct {
    float x1, x2, x3; 
    int r, g, b, a; 
    bool transparent;
} Voxel;

void render_voxel(Voxel* voxel, bool show_vertices, bool show_edges);

#endif // VOXEL_H