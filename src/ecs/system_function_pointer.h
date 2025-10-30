#ifndef SYSTEM_FUNCTION_POINTER
#define SYSTEM_FUNCTION_POINTER

#include <engine/engine.h>
typedef void (*BeSystemFunction)(engine_t* _engine);
typedef void (*BeSystemTimedFunction)(engine_t* _engine, float _deltaTime, float _unscaledDeltaTime);

#endif 
