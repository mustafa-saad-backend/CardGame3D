#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
Shader::Shader(const char *vp, const char *fp)
{
    auto read = [](const char *p)
    {std::ifstream f(p);std::stringstream s;if(!f){std::cerr<<"Cannot open "<<p<<"\n";return std::string();}s<<f.rdbuf();return s.str(); };
    std::string vs = read(vp), fs = read(fp);
    const char *v = vs.c_str();
    const char *f = fs.c_str();
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &v, nullptr);
    glCompileShader(vert);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &f, nullptr);
    glCompileShader(frag);
    auto check = [](GLuint x, const char *label)
    {GLint ok;glGetShaderiv(x,GL_COMPILE_STATUS,&ok);if(!ok){char log[1024];glGetShaderInfoLog(x,1024,nullptr,log);std::cerr<<label<<": "<<log<<"\n";} };
    check(vert, "Vertex shader");
    check(frag, "Fragment shader");
    ID = glCreateProgram();
    glAttachShader(ID, vert);
    glAttachShader(ID, frag);
    glLinkProgram(ID);
    GLint ok;
    glGetProgramiv(ID, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[1024];
        glGetProgramInfoLog(ID, 1024, nullptr, log);
        std::cerr << "Link: " << log << "\n";
    }
    glDeleteShader(vert);
    glDeleteShader(frag);
}
void Shader::use() const { glUseProgram(ID); }
void Shader::setMat4(const std::string &n, const glm::mat4 &m) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, n.c_str()), 1, GL_FALSE, &m[0][0]);
}
void Shader::setVec3(const std::string &n, const glm::vec3 &v) const
{
    glUniform3fv(glGetUniformLocation(ID, n.c_str()), 1, &v[0]);
}
void Shader::setInt(const std::string &n, int v) const
{
    glUniform1i(glGetUniformLocation(ID, n.c_str()), v);
}
