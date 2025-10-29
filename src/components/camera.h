#ifndef BE_CAMERA 

#define BE_CAMERA
#include <cglm/cglm.h>

typedef enum be_camera_projection {
BE_CAM_PROJECTION_PERSPECTIVE,
BE_CAM_PROJECTION_ORTHO,
BE_CAM_PROJECTION_WONKY,
} projection_type_e;

typedef struct camera_t {
projection_type_e projection_type;
mat4 projection;
float fov;
} camera_t;


camera_t camera_get_prototype();

void camera_set_fov(camera_t* _cam, float _fov);
#endif 
