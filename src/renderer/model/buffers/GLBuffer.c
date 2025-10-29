#include "GLBuffer.h"


// for testing/debugging
  float simpleVerts[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    unsigned int simpleIndices[] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };


glBuffer_t *glBuffer_create_for_model(mesh_t *_meshes, size_t _mesh_count)
{

    glBuffer_t *buffers = malloc(sizeof(glBuffer_t) * _mesh_count);

    for (int i = 0; i < _mesh_count; i++)
    {
        glGenVertexArrays(1, &buffers[i].vao);
        glBindVertexArray(buffers[i].vao);

        glGenBuffers(1, &buffers[i].vbo);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, _meshes[i].vertCount * sizeof(vertex_t), _meshes[i].vertices, GL_STATIC_DRAW);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(simpleVerts),simpleVerts, GL_STATIC_DRAW);

        glGenBuffers(1, &buffers[i].ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[i].ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _meshes[i].trisCount * sizeof(triangle_t), _meshes[i].triangles, GL_STATIC_DRAW);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(simpleIndices), simpleIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(vertex_t), (void *)offsetof(vertex_t, position));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(vertex_t), (void *)offsetof(vertex_t, normal));
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    return buffers;
}
