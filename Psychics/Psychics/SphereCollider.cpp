#include "SphereCollider.h"
#include <cmath>

SphereCollider::SphereCollider(Mesh* m, float r, glm::vec3 _position) : mesh(m), radius(r), pos(_position){ 
    r = 0.5f;
}


SphereCollider::~SphereCollider() {}

//Creating a boolean function that returns weather the object has collided with another object
//Its a bool to return true or false weather they hit or not
//The maths just makes if the position intwine with each other they print out "It hits"

bool SphereCollider::CheckCollision(SphereCollider* otherCollider)
{
    //Object A will be the player and object b will be the other sphere colliders it hits
    float objectAr = radius;
    float objectBr = otherCollider->radius;

    glm::vec3 objectApos = pos;
    glm::vec3 objectBpos = otherCollider->pos;

    //Find distance between two sphere positions
    glm::vec3 distanceVector = objectApos - objectBpos;
    float distance = glm::length(distanceVector);
    float totalR = objectAr + objectBr;

    if (distance <= totalR)
    {
        //std::cout << "Its hitting" << std::endl;
        return true; // Collision detected
    }
    else
    {
        return false; // No collision
    }
}


void SphereCollider::Draw()
{
    // Assuming mesh has a Draw function that can draw a sphere at the specified position
    mesh->Draw(pos, glm::vec3(0), glm::vec3(1), glm::vec3(1));
}
