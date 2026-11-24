#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
class Shader {
public:
    GLuint ID=0;
    Shader(const char* vertexPath,const char* fragmentPath);
    void use() const;
    void setMat4(const std::string&,const glm::mat4&) const;
    void setVec3(const std::string&,const glm::vec3&) const;
    void setInt(const std::string&,int) const;
};
