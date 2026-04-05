cmake_minimum_required(VERSION 3.22)

# set the project name
project(base_assets VERSION 1.0)

# add the executable
add_library(${PROJECT_NAME} SHARED
        ./source/texture/texture_asset.c
        ./include/base_assets/internal/module.h
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC library
        PUBLIC math)

target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        )