#pragma once

#include "glm/glm.hpp"

enum class ObjectType { CUBE, SPHERE };

class Object
{
private:

public:

    //Making Objects using a class
    Object(ObjectType objectType, glm::vec3 pos, glm::vec3 rot, glm::vec3 col,
        glm::vec3 size = glm::vec3(1, 1, 1)) :
        colour(col), type(objectType), position(pos), rotation(rot), scale(size)
    {};

    ObjectType type;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 colour;
};