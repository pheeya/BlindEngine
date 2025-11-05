#ifndef SYSTEM_FUNCTION_POINTER
#define SYSTEM_FUNCTION_POINTER

#include <engine/engine.h>
typedef void (*BeSystemFunction)(BeEngine* _engine);
typedef void (*BeSystemTimedFunction)(BeEngine* _engine, float _deltaTime, float _unscaledDeltaTime);

#endif 
