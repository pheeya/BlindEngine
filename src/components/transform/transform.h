#ifndef ECS_COMPONENT_TRANSFORM
#define ECS_COMPONENT_TRANSFORM

#include <cglm/cglm.h>
typedef struct
{
    mat4 matrix;
} transform_t;


transform_t component_transform_get_prototype();
 

#endif
