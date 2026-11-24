#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
int main()
{
   if (!glfwInit())
   {
      std::cerr << "GLFW init failed\n";
      return -1;
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow *window = glfwCreateWindow(1280, 720, "Card Game 3D", nullptr, nullptr);
   if (!window)
   {
      std::cerr << "Window creation failed\n";
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cerr << "GLAD failed\n";
      return -1;
   }
   glEnable(GL_DEPTH_TEST);
   glViewport(0, 0, 1280, 720);
   std::srand((unsigned)::time(nullptr));
   Game game;
   float last = 0;
   while (!glfwWindowShouldClose(window))
   {

      float now = (float)glfwGetTime();
      float dt = now - last;
      last = now;
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(window, true);
      game.process(window);
      game.update(dt);
      int w, h;
      glfwGetFramebufferSize(window, &w, &h);
      glViewport(0, 0, w, h);
      glClearColor(0.12f, 0.14f, 0.18f, 1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      game.draw(w, h);
      glfwSwapBuffers(window);
      glfwPollEvents();
   }
   glfwTerminate();
   return 0;
}
