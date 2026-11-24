#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Room {
    Mesh cube;
    Mesh tornPoster;

    Texture wood, wall, poster, floor, table;

    Mesh solidCube , floorMesh;

void solidObject(
    const Shader& s,
    const glm::mat4& v,
    const glm::mat4& p,
    glm::vec3 pos,
    glm::vec3 size,
    const Texture& t
) const;

void drawCeiling(
    const Shader&,
    const glm::mat4&,
    const glm::mat4&
) const;

    void object(
        const Shader&,
        const glm::mat4&,
        const glm::mat4&,
        glm::vec3,
        glm::vec3,
        const Texture&,
        float rotateX = 0.0f,
        float rotateZ = 0.0f
    ) const;

    void drawTornPoster(
        const Shader&,
        const glm::mat4&,
        const glm::mat4&
    ) const;

public:
    Room();

    void draw(
    const Shader&,
    const glm::mat4&,
    const glm::mat4&,
    bool topView
) const;
};