#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
class Mesh {
public:
    GLuint vao=0,vbo=0;
    GLsizei count=0;
    Mesh()=default;
    explicit Mesh(const std::vector<float>& data);
    void draw() const;
};
