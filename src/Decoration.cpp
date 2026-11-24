#include "Decoration.h"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cmath>

// =====================================================
// Geometry generators
// =====================================================

static Mesh createSphere()
{
    std::vector<float> v;

    const int sectors = 24;
    const int stacks = 16;

    const float PI = 3.14159265359f;

    for (int i = 0; i < stacks; i++)
    {
        float phi1 = PI * i / stacks;
        float phi2 = PI * (i + 1) / stacks;

        for (int j = 0; j < sectors; j++)
        {
            float theta1 = 2.0f * PI * j / sectors;
            float theta2 = 2.0f * PI * (j + 1) / sectors;

            auto point = [](float phi, float theta)
            {
                return glm::vec3(
                    sin(phi) * cos(theta),
                    cos(phi),
                    sin(phi) * sin(theta)
                );
            };

            glm::vec3 a = point(phi1, theta1);
            glm::vec3 b = point(phi2, theta1);
            glm::vec3 c = point(phi2, theta2);
            glm::vec3 d = point(phi1, theta2);

            auto add = [&](glm::vec3 p)
            {
                v.insert(v.end(), {
                    p.x, p.y, p.z,
                    0.0f, 0.0f
                });
            };

            add(a); add(b); add(c);
            add(a); add(c); add(d);
        }
    }

    return Mesh(v);
}

static Mesh createCylinder()
{
    std::vector<float> v;

    const int segments = 32;
    const float PI = 3.14159265359f;

    for (int i = 0; i < segments; i++)
    {
        float a = 2.0f * PI * i / segments;
        float b = 2.0f * PI * (i + 1) / segments;

        glm::vec3 p1(cos(a), -0.5f, sin(a));
        glm::vec3 p2(cos(b), -0.5f, sin(b));
        glm::vec3 p3(cos(b), 0.5f, sin(b));
        glm::vec3 p4(cos(a), 0.5f, sin(a));

        auto add = [&](glm::vec3 p)
        {
            v.insert(v.end(), {
                p.x, p.y, p.z,
                0.0f, 0.0f
            });
        };

        add(p1); add(p2); add(p3);
        add(p1); add(p3); add(p4);
    }

    return Mesh(v);
}

static Mesh createCone()
{
    std::vector<float> v;

    const int segments = 32;
    const float PI = 3.14159265359f;

    for (int i = 0; i < segments; i++)
    {
        float a = 2.0f * PI * i / segments;
        float b = 2.0f * PI * (i + 1) / segments;

        glm::vec3 p1(cos(a), -0.5f, sin(a));
        glm::vec3 p2(cos(b), -0.5f, sin(b));
        glm::vec3 top(0.0f, 0.5f, 0.0f);

        auto add = [&](glm::vec3 p)
        {
            v.insert(v.end(), {
                p.x, p.y, p.z,
                0.0f, 0.0f
            });
        };

        add(p1);
        add(p2);
        add(top);
    }

    return Mesh(v);
}

static Mesh createTorus()
{
    std::vector<float> v;

    const int majorSegments = 48;
    const int minorSegments = 12;

    const float PI = 3.14159265359f;

    const float majorRadius = 0.8f;
    const float minorRadius = 0.045f;

    for (int i = 0; i < majorSegments; i++)
    {
        float a1 = 2.0f * PI * i / majorSegments;
        float a2 = 2.0f * PI * (i + 1) / majorSegments;

        for (int j = 0; j < minorSegments; j++)
        {
            float b1 = 2.0f * PI * j / minorSegments;
            float b2 = 2.0f * PI * (j + 1) / minorSegments;

            auto point = [&](float a, float b)
            {
                float r = majorRadius + minorRadius * cos(b);

                return glm::vec3(
                    r * cos(a),
                    minorRadius * sin(b),
                    r * sin(a)
                );
            };

            glm::vec3 p1 = point(a1, b1);
            glm::vec3 p2 = point(a2, b1);
            glm::vec3 p3 = point(a2, b2);
            glm::vec3 p4 = point(a1, b2);

            auto add = [&](glm::vec3 p)
            {
                v.insert(v.end(), {
                    p.x, p.y, p.z,
                    0.0f, 0.0f
                });
            };

            add(p1); add(p2); add(p3);
            add(p1); add(p3); add(p4);
        }
    }return Mesh(v);
}

// بلورة ذات أوجه هندسية
static Mesh createCrystal()
{
    std::vector<float> v;

    glm::vec3 top(0, 1, 0);
    glm::vec3 bottom(0, -1, 0);

    glm::vec3 p1(0.65f, 0, 0);
    glm::vec3 p2(0, 0, 0.65f);
    glm::vec3 p3(-0.65f, 0, 0);
    glm::vec3 p4(0, 0, -0.65f);

    auto triangle = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c)
    {
        for (auto p : {a, b, c})
        {
            v.insert(v.end(), {
                p.x, p.y, p.z,
                0.0f, 0.0f
            });
        }
    };

    triangle(top, p1, p2);
    triangle(top, p2, p3);
    triangle(top, p3, p4);
    triangle(top, p4, p1);

    triangle(bottom, p2, p1);
    triangle(bottom, p3, p2);
    triangle(bottom, p4, p3);
    triangle(bottom, p1, p4);

    return Mesh(v);
}


static const Mesh& sphereMesh()
{
    static Mesh mesh = createSphere();
    return mesh;
}

static const Mesh& cylinderMesh()
{
    static Mesh mesh = createCylinder();
    return mesh;
}

static const Mesh& coneMesh()
{
    static Mesh mesh = createCone();
    return mesh;
}

static const Mesh& torusMesh()
{
    static Mesh mesh = createTorus();
    return mesh;
}

static const Mesh& crystalMesh()
{
    static Mesh mesh = createCrystal();
    return mesh;
}



Decoration::Decoration(Type t, glm::vec3 p)
    : type(t), position(p)
{
}

void Decoration::update(float dt)
{
    if (type == CRYSTAL)
    {
        rotationAngle += dt * 0.8f;

        if (rotationAngle > 6.28318f)
            rotationAngle -= 6.28318f;
    }
}

void Decoration::drawPart(
    const Shader& shader,
    const glm::mat4& view,
    const glm::mat4& projection,
    const Mesh& mesh,
    glm::vec3 pos,
    glm::vec3 size,
    glm::vec3 color,
    float rotation
) const
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, pos);

    if (rotation != 0.0f)
    {
        model = glm::rotate(
            model,
            rotation,
            glm::vec3(0, 1, 0)
        );
    }

    model = glm::scale(model, size);

    shader.use();

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    shader.setInt("useTexture", 0);
    shader.setVec3("objectColor", color);

    mesh.draw();
}



void Decoration::draw(
    const Shader& shader,
    const glm::mat4& view,
    const glm::mat4& projection
) const
{
    
    if (type == PLANT)
    {
        glm::vec3 base = position;

        // أصيص حجري
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0, 0.45f, 0),
            {0.75f, 0.9f, 0.75f},
            {0.30f, 0.16f, 0.10f}
        );

        // حافة الأصيص
        drawPart(
            shader, view, projection,
            torusMesh(),
            base + glm::vec3(0, 0.85f, 0),
            {0.48f, 0.10f, 0.48f},
            {0.68f, 0.42f, 0.19f}
        );

        // جذع الشجرة
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0, 1.35f, 0),
            {0.18f, 1.25f, 0.18f},
            {0.27f, 0.12f, 0.055f},
            glm::radians(-12.0f)
        );

        // الفروع
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(-0.38f, 1.75f, 0),
            {0.09f, 0.85f, 0.09f},
            {0.30f, 0.15f, 0.07f},
            glm::radians(-48.0f)
        );drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0.38f, 1.85f, 0),
            {0.09f, 0.8f, 0.09f},
            {0.30f, 0.15f, 0.07f},
            glm::radians(48.0f)
        );

        // مجموعات الأوراق
        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(-0.55f, 2.05f, 0),
            {0.60f, 0.38f, 0.50f},
            {0.025f, 0.42f, 0.22f}
        );

        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0.55f, 2.15f, 0),
            {0.65f, 0.42f, 0.55f},
            {0.04f, 0.52f, 0.25f}
        );

        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0, 2.55f, 0),
            {0.65f, 0.42f, 0.60f},
            {0.12f, 0.48f, 0.34f}
        );

        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0.1f, 1.85f, 0.4f),
            {0.38f, 0.30f, 0.38f},
            {0.04f, 0.35f, 0.20f}
        );
    }

    else if (type == LAMP)
    {
        glm::vec3 base = position;

        // القاعدة المعدنية
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0, 0.12f, 0),
            {1.0f, 0.24f, 1.0f},
            {0.38f, 0.20f, 0.08f}
        );

        // زخرفة القاعدة
        drawPart(
            shader, view, projection,
            torusMesh(),
            base + glm::vec3(0, 0.27f, 0),
            {0.48f, 0.08f, 0.48f},
            {0.85f, 0.55f, 0.16f}
        );

        // العمود الرئيسي
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0, 1.35f, 0),
            {0.13f, 2.3f, 0.13f},
            {0.55f, 0.32f, 0.10f}
        );

        // حلقات فلكية
        drawPart(
            shader, view, projection,
            torusMesh(),
            base + glm::vec3(0, 2.65f, 0),
            {1.75f, 0.75f, 1.75f},
            {0.85f, 0.58f, 0.20f},
            glm::radians(25.0f)
        );

        drawPart(
            shader, view, projection,
            torusMesh(),
            base + glm::vec3(0, 2.65f, 0),
            {1.30f, 1.30f, 1.30f},
            {0.95f, 0.72f, 0.30f},
            glm::radians(-50.0f)
        );

        // الكرة المضيئة
        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0, 2.65f, 0),
            {0.70f, 0.70f, 0.70f},
            {1.0f, 0.78f, 0.30f}
        );

        // رأس زخرفي
        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0, 3.15f, 0),
            {0.35f, 0.30f, 0.35f},
            {1.00f, 1.00f, 1.00f}
        );
    }

   
    else if (type == CRYSTAL)
    {
        glm::vec3 base = position;

        // القاعدة الحجرية
        drawPart(
            shader, view, projection,
            cylinderMesh(),
            base + glm::vec3(0, 0.15f, 0),
            {1.35f, 0.30f, 1.35f},
            {0.18f, 0.15f, 0.25f}
        );

        // الحلقة الذهبية
        drawPart(
            shader, view, projection,
            torusMesh(),
            base + glm::vec3(0, 0.34f, 0),
            {0.78f, 0.15f, 0.78f},
            {0.75f, 0.48f, 0.16f}
        );

        // أعمدة القاعدة
        drawPart(
            shader, view, projection,
            coneMesh(),
            base + glm::vec3(0.0f, 0.55f, 0),
            {0.75f, 0.65f, 0.75f},
            {0.30f, 0.20f, 0.40f}
        );// البلورة العائمة
        drawPart(
            shader, view, projection,
            crystalMesh(),
            base + glm::vec3(
                0,
                1.45f + 0.12f * sin(rotationAngle * 2.0f),
                0
            ),
            {0.85f, 1.15f, 0.85f},
            {0.48f, 0.16f, 0.85f},
            rotationAngle
        );

        // بلورة صغيرة علوية
        drawPart(
            shader, view, projection,
            crystalMesh(),
            base + glm::vec3(0, 2.45f, 0),
            {0.22f, 0.30f, 0.22f},
            {0.72f, 0.40f, 1.0f},
            -rotationAngle * 1.5f
        );

        // أحجار صغيرة حول البلورة
        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(0.9f, 1.25f, 0),
            {0.12f, 0.12f, 0.12f},
            {0.55f, 0.30f, 0.95f}
        );

        drawPart(
            shader, view, projection,
            sphereMesh(),
            base + glm::vec3(-0.9f, 1.55f, 0),
            {0.12f, 0.12f, 0.12f},
            {0.70f, 0.35f, 1.0f}
        );
    }
}