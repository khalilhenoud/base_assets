cmake_minimum_required(VERSION 3.22)

# set the project name
project(acsu VERSION 1.0)

# add the executable
add_library(${PROJECT_NAME} SHARED
        ./include/acsu/internal/module.h
        ./source/animation/animation_asset.c
        ./source/font/font_asset.c
        ./source/material/material_asset.c
        ./source/mesh/mesh_asset.c
        ./source/skinned_mesh/skinned_mesh_asset.c
        ./source/texture/texture_asset.c
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC library
        PUBLIC math)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        )