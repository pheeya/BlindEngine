#ifndef MESH 
#define MESH

#include "vertex.h"
#include "triangle.h"
#include "surface/shader.h"


typedef struct {
vertex_t* vertices;
triangle_t* triangles;
shader_t* shader;
size_t vertCount;
size_t trisCount;

} mesh_t;

#endif