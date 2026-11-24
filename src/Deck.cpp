#include "Deck.h"
#include <cstdlib>

Deck::Deck()
{

    for (int i = 0; i < 5; i++)
    {

        cards.emplace_back(
            "textures/card" + std::to_string(i + 1) + ".jpg",

            glm::vec3(
                -2.7f + i * 1.35f,
                1.41f,
                0.0f));
    }
}

void Deck::playRandom(bool playerView)
{
    if (cards.empty())
        return;

    int index = std::rand() % cards.size();

    Card c = cards[index];
    cards.erase(cards.begin() + index);

    glm::vec3 target(
        -2.5f + played.size() * 1.25f,
        2.40f,
        0.0f);

    // دائماً اقلب البطاقة باتجاه اللاعب
    // بغض النظر عن المنظور الحالي
    c.moveTo(target, true);

    played.push_back(c);
}

void Deck::setPlayerView(bool playerView)
{
}

void Deck::update(float dt)
{
    // تحديث البطاقات الموجودة بالمخزون
    for (auto &c : cards)
    {
        c.update(dt);
    }

    // تحديث البطاقات التي تم لعبها
    for (auto &c : played)
    {
        c.update(dt);
    }
}

void Deck::draw(
    const Shader &s,
    const glm::mat4 &v,
    const glm::mat4 &p) const
{
    for (const auto &c : cards)
    {
        c.draw(s, v, p);
    }

    for (const auto &c : played)
    {
        c.draw(s, v, p);
    }
}