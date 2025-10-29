
#ifndef GLBUFFER
#define GLBUFFER
#include <glad/glad.h>
#include <renderer/model/mesh.h>
typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

} glBuffer_t;

glBuffer_t *glBuffer_create_for_model(mesh_t *_mesh, size_t _mesh_count);

#endif