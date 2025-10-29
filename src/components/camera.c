#include "camera.h"

void update_projection(camera_t *_cam) {
  if (_cam->projection_type == BE_CAM_PROJECTION_PERSPECTIVE) {
    glm_perspective(_cam->fov, 16.0 / 9, 0, 100, _cam->projection);
  }
}

camera_t camera_get_prototype() {
  camera_t cam;
  cam.projection_type = BE_CAM_PROJECTION_PERSPECTIVE;
  update_projection(&cam);
  return cam;
}
void camera_set_fov(camera_t *_cam, float _fov) {
  _cam->fov = _fov;
  update_projection(_cam);
}
