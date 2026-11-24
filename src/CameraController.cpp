#include "CameraController.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

void CameraController::setTop()
{
    player = false;
}

void CameraController::setPlayer()
{
    if (!player)
    {
        player = true;
        firstMouse = true;
    }
}

bool CameraController::isPlayer() const
{
    return player;
}

void CameraController::updateDirection()
{
    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) *
                  cos(glm::radians(pitch));

    direction.y = sin(glm::radians(pitch));

    direction.z = sin(glm::radians(yaw)) *
                  cos(glm::radians(pitch));

    front = glm::normalize(direction);
}

void CameraController::processKeyboard(GLFWwindow* window, float dt)
{
    float velocity = speed * dt;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        velocity *= 2.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * velocity;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * velocity;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position.y += velocity;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position.y -= velocity;
}

void CameraController::processMouse(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;

        firstMouse = false;
        return;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    updateDirection();
}

glm::mat4 CameraController::view() const
{
    if (player)
    {
        return glm::lookAt(
            position,
            position + front,
            up
        );
    }

    return glm::lookAt(
        glm::vec3(0.0f, 25.0f, 0.01f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f)
    );
}