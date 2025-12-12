#ifndef VOXEL_H
#define VOXEL_H

typedef struct {
    int x1, x2, x3;
    int r, g, b;
    bool transparent;
} Voxel;

#endif // VOXEL_H