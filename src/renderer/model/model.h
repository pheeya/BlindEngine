#ifndef MODEL
#define MODEL

#include <stdio.h>
#include "mesh.h"
#include "vertex.h"
#include "triangle.h"
#include "buffers/GLBuffer.h"

typedef struct
{
    uint32_t mesh_count;
    mesh_t *meshes;
    glBuffer_t *buffers;
} model_t;

model_t component_model_get_prototype();
model_t *model_load_gltf(const char *_path);
/// @brief Allocate memory for model yourself and pass it as parameter
/// @param _path path to model asset
/// @param
/// @return
void model_load_gltf_preallocated(const char *_path, model_t *_model);
model_t model_create_default_instance();

#endif