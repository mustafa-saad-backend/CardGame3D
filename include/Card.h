#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
class Card {
    Mesh mesh; Texture texture;
    glm::vec3 position,rotation,scale;
    glm::vec3 startPos,targetPos;
    float progress=1.0f;
     float startAngle=0.0f,targetAngle=0.0f; 
     bool moving=false,played=false,vertical=false,isArcMove = false;
public:
    Card(const std::string& image,const glm::vec3& pos);
    void moveTo(const glm::vec3& target,bool standUp);
    void update(float dt);
    void setOrientation(bool standUp);
    void draw(const Shader& shader,const glm::mat4& view,const glm::mat4& projection) const;
    bool isPlayed()const{return played;}
    
};
