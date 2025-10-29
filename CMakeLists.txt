cmake_minimum_required(VERSION 3.31.5)

project(BLIND_ENGINE)


# source

add_library(${PROJECT_NAME} STATIC
src/main.c

src/be_assert.h

src/sparse_set/sparse_set.h
src/sparse_set/sparse_set.c

src/list/list.h
src/list/list.c


src/window/window.h
src/window/window.c

src/application/application.h
src/application/application.c

src/engine/engine.h
src/engine/engine.c

src/blindengine.h
src/engine_api/api.c

src/renderer/rendererSystem.h
src/renderer/rendererSystem.c

src/ecs/entity.h
src/ecs/entity.c

src/ecs/component.h
src/ecs/component.c

src/ecs/system.h
src/ecs/system.c

src/ecs/systems_run.h
src/ecs/systems_run.c

src/components/component_list.h

src/components/transform/transform.h
src/components/transform/transform.c

src/renderer/gpu_id.h

src/renderer/model/mesh.h
src/renderer/model/mesh.c

src/renderer/model/triangle.h
src/renderer/model/triangle.c


src/renderer/model/vertex.h
src/renderer/model/vertex.c


src/renderer/model/model.h
src/renderer/model/model.c


src/renderer/model/surface/shader.h
src/renderer/model/surface/shader.c


src/renderer/model/surface/surface.h
src/renderer/model/surface/surface.c


src/renderer/model/texture.h
src/renderer/model/texture.c


src/renderer/model/buffers/GLBuffer.h
src/renderer/model/buffers/GLBuffer.c

src/ecs/system_function_pointer.h
src/ecs/system_registry.h
src/ecs/system_registry.c

src/systems/testsystem/testsystem.h
src/systems/testsystem/testsystem.c


src/font/Font.h
src/font/Font.c


)


# Compile definitions
target_compile_definitions(BLIND_ENGINE PRIVATE BLIND_ENGINE_COMPILING)

# For IDE to know which files are sources 
#target_sources(BLIND_ENGINE PUBLIC)



# Import CMakeLists.txt to get the library
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/cglm)
add_subdirectory(vendor/cgltf)
add_subdirectory(lib/blindgui)
add_subdirectory(vendor/stbi)
add_subdirectory(vendor/freetype)
# Link library to our project 
target_link_libraries(BLIND_ENGINE PUBLIC glfw glad cglm cgltf blindgui stbi freetype)


# Directory of header files
target_include_directories(BLIND_ENGINE PUBLIC  
"${PROJECT_SOURCE_DIR}/src"
)


set_property(TARGET BLIND_ENGINE PROPERTY C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall")


set_target_properties(BLIND_ENGINE PROPERTIES 
PREFIX ""
OUTPUT_NAME "libblindengine"
)
