cmake_minimum_required(VERSION 3.31.5)
project(blindgui)


add_library(blindgui 
include/blindgui/blindgui.h
include/blindgui/blindgui.c
)
  
target_include_directories(blindgui PUBLIC include/)
