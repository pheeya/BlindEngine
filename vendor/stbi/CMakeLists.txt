cmake_minimum_required(VERSION 3.31.5)

project(stbi)


add_library(stbi
include/stbi/stbi_truetype.h
include/stbi/stbi_rect_pack.h
)
  
set_target_properties(stbi PROPERTIES LINKER_LANGUAGE C)
target_include_directories(stbi PUBLIC include/)
