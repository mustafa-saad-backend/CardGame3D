#include "Room.h"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/vec2.hpp>

static std::vector<float> createSolidCube()
{
    std::vector<float> vertices = {
        // Front
        -0.5f, -0.5f, 0.5f, 0, 0,
        0.5f, -0.5f, 0.5f, 1, 0,
        0.5f, 0.5f, 0.5f, 1, 1,
        -0.5f, -0.5f, 0.5f, 0, 0,
        0.5f, 0.5f, 0.5f, 1, 1,
        -0.5f, 0.5f, 0.5f, 0, 1,

        // Back
        0.5f, -0.5f, -0.5f, 0, 0,
        -0.5f, -0.5f, -0.5f, 1, 0,
        -0.5f, 0.5f, -0.5f, 1, 1,
        0.5f, -0.5f, -0.5f, 0, 0,
        -0.5f, 0.5f, -0.5f, 1, 1,
        0.5f, 0.5f, -0.5f, 0, 1,

        // Left
        -0.5f, -0.5f, -0.5f, 0, 0,
        -0.5f, -0.5f, 0.5f, 1, 0,
        -0.5f, 0.5f, 0.5f, 1, 1,
        -0.5f, -0.5f, -0.5f, 0, 0,
        -0.5f, 0.5f, 0.5f, 1, 1,
        -0.5f, 0.5f, -0.5f, 0, 1,

        // Right
        0.5f, -0.5f, 0.5f, 0, 0,
        0.5f, -0.5f, -0.5f, 1, 0,
        0.5f, 0.5f, -0.5f, 1, 1,
        0.5f, -0.5f, 0.5f, 0, 0,
        0.5f, 0.5f, -0.5f, 1, 1,
        0.5f, 0.5f, 0.5f, 0, 1,

        // Top
        -0.5f, 0.5f, 0.5f, 0, 0,
        0.5f, 0.5f, 0.5f, 1, 0,
        0.5f, 0.5f, -0.5f, 1, 1,
        -0.5f, 0.5f, 0.5f, 0, 0,
        0.5f, 0.5f, -0.5f, 1, 1,
        -0.5f, 0.5f, -0.5f, 0, 1,

        // Bottom
        -0.5f, -0.5f, -0.5f, 0, 0,
        0.5f, -0.5f, -0.5f, 1, 0,
        0.5f, -0.5f, 0.5f, 1, 1,
        -0.5f, -0.5f, -0.5f, 0, 0,
        0.5f, -0.5f, 0.5f, 1, 1,
        -0.5f, -0.5f, 0.5f, 0, 1};

    return vertices;
}

Room::Room()
    : wood("textures/wood.jpg"),
      wall("textures/wall.jpg"),
      poster("textures/poster.jpg"),
      floor("textures/floor.jpg"),
      table("textures/table.jpg")
{
    std::vector<float> d = {
        -0.5f, 0, -0.5f, 0, 0,
        0.5f, 0, -0.5f, 1, 0,
        0.5f, 0, 0.5f, 1, 1,

        -0.5f, 0, -0.5f, 0, 0,
        0.5f, 0, 0.5f, 1, 1,
        -0.5f, 0, 0.5f, 0, 1};

    cube = Mesh(d);
    solidCube = Mesh(createSolidCube());

    // أرضية بتكرار الخامة لإظهار التفاصيل
    std::vector<float> floorVertices = {
        -0.5f, 0, -0.5f, 0, 0,
        0.5f, 0, -0.5f, 10, 0,
        0.5f, 0, 0.5f, 10, 10,

        -0.5f, 0, -0.5f, 0, 0,
        0.5f, 0, 0.5f, 10, 10,
        -0.5f, 0, 0.5f, 0, 10};

    floorMesh = Mesh(floorVertices);

    std::vector<glm::vec2> points = {
        {-0.50f, -0.48f},
        {-0.35f, -0.50f},
        {-0.22f, -0.46f},
        {-0.08f, -0.50f},
        {0.08f, -0.47f},
        {0.22f, -0.50f},
        {0.38f, -0.46f},
        {0.50f, -0.50f},

        {0.48f, -0.32f},
        {0.50f, -0.16f},
        {0.46f, 0.00f},
        {0.50f, 0.16f},
        {0.47f, 0.32f},
        {0.50f, 0.48f},

        {0.30f, 0.50f},
        {0.15f, 0.46f},
        {0.00f, 0.50f},
        {-0.16f, 0.47f},
        {-0.32f, 0.50f},
        {-0.50f, 0.46f},

        {-0.47f, 0.30f},
        {-0.50f, 0.14f},
        {-0.46f, -0.02f},
        {-0.50f, -0.18f},
        {-0.46f, -0.34f}};

    glm::vec2 center(0.0f, 0.0f);
    std::vector<float> posterVertices;

    for (size_t i = 0; i < points.size(); i++)
    {
        glm::vec2 a = points[i];
        glm::vec2 b = points[(i + 1) % points.size()];

        posterVertices.insert(posterVertices.end(), {center.x, 0.0f, center.y, 0.5f, 0.5f});
        posterVertices.insert(posterVertices.end(), {a.x, 0.0f, a.y, a.x + 0.5f, 0.5f - a.y});
        posterVertices.insert(posterVertices.end(), {b.x, 0.0f, b.y, b.x + 0.5f, 0.5f - b.y});
    }

    tornPoster = Mesh(posterVertices);
}

void Room::object(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p,
    glm::vec3 pos,
    glm::vec3 size,
    const Texture &t,
    float rotateX,
    float rotateZ) const
{
    glm::mat4 m(1.0f);
    m = glm::translate(m, pos);
    m = glm::rotate(m, rotateZ, glm::vec3(0, 0, 1));
    m = glm::rotate(m, rotateX, glm::vec3(1, 0, 0));
    m = glm::scale(m, size);

    s.use();
    s.setMat4("model", m);
    s.setMat4("view", v);
    s.setMat4("projection", p);
    s.setInt("useTexture", 1);

    t.bind();
    cube.draw();
}

void Room::solidObject(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p,
    glm::vec3 pos,
    glm::vec3 size,
    const Texture &t) const
{
    glm::mat4 m(1.0f);
    m = glm::translate(m, pos);
    m = glm::scale(m, size);
    s.use();
    s.setMat4("model", m);
    s.setMat4("view", v);
    s.setMat4("projection", p);
    s.setInt("useTexture", 1);

    t.bind();
    solidCube.draw();
}

void Room::drawTornPoster(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p) const
{
    glm::mat4 m(1.0f);
    m = glm::translate(m, glm::vec3(0.0f, 8.2f, -16.93f));
    m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
    m = glm::scale(m, glm::vec3(10.0f, 10.0f, 5.5f));

    s.use();
    s.setMat4("model", m);
    s.setMat4("view", v);
    s.setMat4("projection", p);
    s.setInt("useTexture", 1);

    poster.bind();
    tornPoster.draw();
}


void Room::drawCeiling(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p) const
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(0.0f, 16.0f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(34.0f, 1.0f, 34.0f));

    s.use();

    s.setMat4("model", model);
    s.setMat4("view", v);
    s.setMat4("projection", p);
    s.setInt("useTexture", 1);

    wall.bind();

    // تكرار خامة السقف
    static const Mesh ceilingMesh(std::vector<float>{
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 2.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 2.0f, 2.0f,

        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 2.0f, 2.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 2.0f});

    ceilingMesh.draw();
}

void Room::draw(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p,
    bool topView) const
{
   
    glm::mat4 floorModel(1.0f);

    floorModel = glm::translate(
        floorModel,
        glm::vec3(0.0f, -0.15f, 0.0f));

    floorModel = glm::scale(
        floorModel,
        glm::vec3(34.0f, 1.0f, 34.0f));

    s.use();

    s.setMat4("model", floorModel);
    s.setMat4("view", v);
    s.setMat4("projection", p);

    s.setInt("useTexture", 1);

    floor.bind();
    floorMesh.draw();

    // الجدران بخامة مكررة لإظهار تفاصيل ورق الجدران

    auto drawWall = [&](glm::vec3 pos, glm::vec3 size,
                        float rotateX, float rotateZ,
                        float repeatX, float repeatY)
    {
        glm::mat4 model(1.0f);

        model = glm::translate(model, pos);
        model = glm::rotate(model, rotateZ, glm::vec3(0, 0, 1));
        model = glm::rotate(model, rotateX, glm::vec3(1, 0, 0));
        model = glm::scale(model, size);

        s.use();

        s.setMat4("model", model);
        s.setMat4("view", v);
        s.setMat4("projection", p);
        s.setInt("useTexture", 1);

        wall.bind();

        std::vector<float> wallVertices = {
            -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, -0.5f, repeatX, 0.0f,
            0.5f, 0.0f, 0.5f, repeatX, repeatY,

            -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.5f, repeatX, repeatY,
            -0.5f, 0.0f, 0.5f, 0.0f, repeatY};

        Mesh wallMesh(wallVertices);
        wallMesh.draw();
    };

    // الجدار الخلفي
    drawWall(
        {0.0f, 8.0f, -17.0f},
        {34.0f, 1.0f, 16.0f},
        glm::radians(90.0f),
        0.0f,
        1.0f,
        1.0f);

    // الجدار الأيسر
    drawWall(
        {-17.0f, 8.0f, 0.0f},
        {16.0f, 1.0f, 34.0f},
        0.0f,
        glm::radians(90.0f),
        2.0f,
        2.0f);

    // الجدار الأيمن
    drawWall(
        {17.0f, 8.0f, 0.0f},
        {16.0f, 1.0f, 34.0f},
        0.0f,
        glm::radians(90.0f),
        2.0f,
        2.0f);

    // اللوحة الممزقة
    drawTornPoster(s, v, p);

    // الطاولة الخشبية ثلاثية الأبعاد
    solidObject(s, v, p, {0.0f, 1.25f, 0.0f}, {11.0f, 0.30f, 8.0f}, table);

    // الإطار السفلي تحت السطح
    solidObject(s, v, p, {0.0f, 0.95f, 2.65f}, {8.4f, 0.45f, 0.30f}, table);
    solidObject(s, v, p, {0.0f, 0.95f, -2.65f}, {8.4f, 0.45f, 0.30f}, table);
    solidObject(s, v, p, {-4.05f, 0.95f, 0.0f}, {0.30f, 0.45f, 5.0f}, table);
    solidObject(s, v, p, {4.05f, 0.95f, 0.0f}, {0.30f, 0.45f, 5.0f}, table);

    // الأرجل الأربعة
    solidObject(s, v, p, {-4.0f, 0.48f, 2.5f}, {0.50f, 1.0f, 0.50f}, table);
    solidObject(s, v, p, {4.0f, 0.48f, 2.5f}, {0.50f, 1.0f, 0.50f}, table);
    solidObject(s, v, p, {-4.0f, 0.48f, -2.5f}, {0.50f, 1.0f, 0.50f}, table);
    solidObject(s, v, p, {4.0f, 0.48f, -2.5f}, {0.50f, 1.0f, 0.50f}, table);

    if (!topView)
    {
        drawCeiling(s, v, p);
    }
}