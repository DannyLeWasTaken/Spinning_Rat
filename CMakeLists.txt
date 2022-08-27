cmake_minimum_required(VERSION 3.23.2)
project(Spinning_Rat
        LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(includes/glfw)
add_subdirectory(includes/glm)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
        GIT_TAG v5.2.4)
FetchContent_MakeAvailable(assimp)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} OpenGL::GL)

add_library(glad includes/glad/glad.h includes/glad/glad.c includes/glad/KHR/khrplatform.h)
target_include_directories(glad PUBLIC includes/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

#add_library(KHR includes/glad/khrplatform.h)
#target_include_directories(KHR PUBLIC includes/KHR)
#target_link_libraries(${PROJECT_NAME} PRIVATE KHR)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)