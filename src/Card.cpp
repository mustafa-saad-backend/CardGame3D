#include "Card.h"
#include <glm/gtc/matrix_transform.hpp>
Card::Card(const std::string &image, const glm::vec3 &pos) : texture(image), position(pos), rotation(glm::radians(90.0f), 0, 0), scale(1, 1.4f, 1)
{
    std::vector<float> v = {
        -0.5f, -0.7f, 0, 0, 0,
        0.5f, -0.7f, 0, 1, 0,
        0.5f, 0.7f, 0, 1, 1,
        -0.5f, -0.7f, 0, 0, 0,
        0.5f, 0.7f, 0, 1, 1,
        -0.5f, 0.7f, 0, 0, 1};
    mesh = Mesh(v);
}

void Card::moveTo(const glm::vec3 &t, bool standUp)
{
    startPos = position;
    targetPos = t;

    startAngle = rotation.x;
    targetAngle = standUp ? 0.0f : glm::radians(90.0f);

    progress = 0.0f;
    moving = true;
    isArcMove = true; // تفعيل الحركة القوسية والدوران عند اللعب بـ G
    vertical = standUp;
    played = true;
}

void Card::update(float dt)
{
    if (!moving)
        return;

    progress += dt * 1.5f;
    float a = glm::clamp(progress, 0.0f, 1.0f);

    // 1. التحريك الأفقي الأساسي
    position = glm::mix(startPos, targetPos, a);

    // 2. إضافة القوس في الهواء + الدوران الكامل إذا كانت حركة لعب (زر G)
    if (isArcMove)
    {
        float arcHeight = 1.6f * std::sin(a * 3.14159265f); // ترتفع للأعلى بمقدار 1.6 ثم تهبط بنعومة
        position.y += arcHeight;

        rotation.y = a * glm::radians(360.0f); // دورة كاملة 360 درجة في الهواء حول محور Y
    }
    else
    {
        rotation.y = 0.0f;
    }

    // 3. تدوير زاوية الوقوف والتسطيح تدريجياً
    rotation.x = glm::mix(startAngle, targetAngle, a);

    if (progress >= 1.0f)
    {
        moving = false;
        isArcMove = false;
        rotation.y = 0.0f; // استقرار الزاوية النهائية بدقة
    }
}

void Card::setOrientation(bool standUp)
{
    startPos = position;
    targetPos = position;

    targetPos.y = standUp ? 2.18f : 1.41f;

    startAngle = rotation.x;
    targetAngle = standUp ? 0.0f : glm::radians(90.0f);

    progress = 0.0f;
    moving = true;
    isArcMove = false; // حركة وقوف/تسطيح عادية بدون قفز في الهواء
    vertical = standUp;
}

void Card::draw(const Shader &s, const glm::mat4 &view, const glm::mat4 &projection) const
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0)); // تطبيق الدوران حول محور Y أثناء الطيران
    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0)); // تطبيق زاوية الوقوف/التسطيح
    model = glm::scale(model, scale);

    s.use();
    s.setMat4("model", model);
    s.setMat4("view", view);
    s.setMat4("projection", projection);
    s.setInt("useTexture", 1);

    texture.bind();
    mesh.draw();
}
