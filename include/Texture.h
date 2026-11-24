#pragma once
#include <glad/glad.h>
#include <string>
class Texture {
public:
    GLuint id=0;
    Texture()=default;
    explicit Texture(const std::string& path);
    void bind(unsigned int unit=0) const;
};
