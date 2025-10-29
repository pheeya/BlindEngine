#ifndef MODEL_VERTEX
#define MODEL_VERTEX

#include <cglm/vec3.h>
#include <cglm/vec2.h>

 
typedef struct {
    vec3 position;
    vec3 normal;
    vec2 texcoord;
} vertex_t;
#endif