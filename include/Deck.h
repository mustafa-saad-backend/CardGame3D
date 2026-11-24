#pragma once
#include "Card.h"
#include <vector>
class Deck {
    std::vector<Card> cards;
    std::vector<Card> played;
public:
    Deck();
    void playRandom(bool playerView);
    void update(float dt);
    void setPlayerView(bool playerView);
    void draw(const Shader&,const glm::mat4&,const glm::mat4&)const;
};
