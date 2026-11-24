#include "Game.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Game::Game()

    : shader("shaders/vertex.vs", "shaders/fragment.fs"),

      //شجرة البونساي 
      plant(
          Decoration::PLANT,
          {-9.0f, -0.15f, -5.5f}),

      // المصباح 
      lamp(
          Decoration::LAMP,
          {8.0f, -0.15f, 4.5f}),

      // البلورة السحرية 
      crystal(
          Decoration::CRYSTAL,
          {-8.0f, -0.15f, 4.5f})
{
}

void Game::process(GLFWwindow *window)
{
    static double lastFrame = glfwGetTime();

    double currentFrame = glfwGetTime();

    float dt = (float)(currentFrame - lastFrame);

    lastFrame = currentFrame;

    if (dt > 0.05f)
        dt = 0.05f;

    // المنظور العلوي
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.setTop();

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (lastPlayerView)
        {
            deck.setPlayerView(false);
            lastPlayerView = false;
        }
    }

    // منظور اللاعب
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        camera.setPlayer();

        if (!lastPlayerView)
        {
            deck.setPlayerView(true);
            lastPlayerView = true;
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // تحريك الكاميرا
    if (camera.isPlayer())
    {
        camera.processKeyboard(window, dt);

        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        camera.processMouse(xpos, ypos);
    }

    // سحب بطاقة باستخدام G
    bool down = glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS;

    if (down && !gWasDown)
    {
        deck.playRandom(camera.isPlayer());
    }

    gWasDown = down;
}

void Game::update(float dt)
{
    deck.update(dt);

    plant.update(dt);
    lamp.update(dt);
    crystal.update(dt);
}

void Game::draw(int width, int height)
{
    if (height <= 0)
        return;

    glm::mat4 v = camera.view();

    glm::mat4 p = glm::perspective(
        glm::radians(55.0f),
        (float)width / (float)height,
        0.1f,
        100.0f);

    shader.use();

    shader.setInt("imageTexture", 0);

    room.draw(
        shader,
        v,
        p,
        !camera.isPlayer());

    // الديكورات الجديدة
    plant.draw(shader, v, p);

    lamp.draw(shader, v, p);

    crystal.draw(shader, v, p);

    deck.draw(shader, v, p);
}