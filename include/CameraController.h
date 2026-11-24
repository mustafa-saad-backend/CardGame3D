#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class CameraController
{
private:

    bool player = false;

    // موقع الكاميرا
    glm::vec3 position = glm::vec3(0.0f, 5.5f, 17.0f);

    // اتجاه النظر
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // زوايا دوران الكاميرا
    float yaw = -90.0f;
    float pitch = 0.0f;

    // حساسية الماوس
    float sensitivity = 0.1f;

    // سرعة الحركة
    float speed = 5.0f;

    // الماوس
    bool firstMouse = true;

    float lastX = 640.0f;
    float lastY = 360.0f;

    void updateDirection();

public:

    void setTop();

    void setPlayer();

    bool isPlayer() const;

    void processKeyboard(GLFWwindow* window, float dt);

    void processMouse(double xpos, double ypos);

    glm::mat4 view() const;
};