#include "transform.h"

transform_t component_transform_get_prototype() {

  transform_t trans;
  glm_mat4_identity(trans.matrix); 
  return trans;
}
