cmake_minimum_required(VERSION 3.20)

project(CardGame3D LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glfw STATIC IMPORTED GLOBAL)

set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)

add_executable(CardGame3D
    src/main.cpp
    src/Game.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Room.cpp
    src/Decoration.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Texture.cpp
    src/CameraController.cpp
    src/glad.c
)

target_include_directories(CardGame3D PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(CardGame3D PRIVATE
    glfw
    opengl32
    gdi32
    user32
    shell32
)

file(COPY "${CMAKE_SOURCE_DIR}/textures"
     DESTINATION "${CMAKE_BINARY_DIR}")

file(COPY "${CMAKE_SOURCE_DIR}/shaders"
     DESTINATION "${CMAKE_BINARY_DIR}")