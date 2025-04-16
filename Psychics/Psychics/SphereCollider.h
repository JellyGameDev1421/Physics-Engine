#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "Mesh.h" // Assuming Mesh is defined in this header
#include <iostream>

class SphereCollider
{
public:

    //Collider in the shape of a sphere
    Mesh* mesh;
    float radius;
    glm::vec3 pos;

    //Float r makes a more detailed sphere
    //Mesh is the mesh of what shape we will be using can give it a cube
    SphereCollider(Mesh* m, float r, glm::vec3 _position);

    ~SphereCollider();

    bool CheckCollision(SphereCollider* otherCollider);

    void Draw();
};
