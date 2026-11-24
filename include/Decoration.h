#pragma once

#include "Shader.h"
#include "Mesh.h"
#include <glm/glm.hpp>

class Decoration
{
public:

    enum Type
    {
        PLANT,
        LAMP,
        CRYSTAL
    };

private:

    Type type;
    glm::vec3 position;

    float rotationAngle = 0.0f;

    void drawPart(
        const Shader& shader,
        const glm::mat4& view,
        const glm::mat4& projection,
        const Mesh& mesh,
        glm::vec3 pos,
        glm::vec3 scale,
        glm::vec3 color,
        float rotation = 0.0f
    ) const;

public:

    Decoration(Type t, glm::vec3 p);

    void update(float dt);

    void draw(
        const Shader& shader,
        const glm::mat4& view,
        const glm::mat4& projection
    ) const;
};