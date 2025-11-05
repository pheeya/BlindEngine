

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
} BeShader;

/// @brief Load shader from file
/// @param _pathWithoutExt Path to file without file extension
/// @return 
BeShader *shader_load_from_file(const char *_pathWithoutExt);
void shader_bind(BeShader *_shader);
void shader_unbind();
#endif
