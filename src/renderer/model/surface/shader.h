

#ifndef SHADER
#define SHADER

#include <renderer/gpu_id.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>


typedef struct
{
    gpu_id_t id;
    const char* filePath;
} shader_t;

/// @brief Load shader from file
/// @param _pathWithoutExt Path to file without file extension
/// @return 
shader_t *shader_load_from_file(const char *_pathWithoutExt);
void shader_bind(shader_t *_shader);
void shader_unbind();
#endif
