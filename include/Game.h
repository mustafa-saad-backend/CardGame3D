#pragma once

#include "Shader.h"
#include "Room.h"
#include "Deck.h"
#include "CameraController.h"
#include "Decoration.h"

#include <GLFW/glfw3.h>

class Game
{
    Shader shader;
    Room room;
    Deck deck;

    CameraController camera;

    Decoration plant;
    Decoration lamp;
    Decoration crystal;

    bool gWasDown = false;

public:

    Game();

    void process(GLFWwindow* window);

    void update(float dt);

    void draw(int width, int height);

    bool lastPlayerView = false;
};