#pragma once
#include "Particle.h"
#include "RigidBody3d.h"
#include "Mesh.h"
#include <map>
#include <iostream>
#include "SphereCollider.h"

enum class Tags {Player , Boost, Wall, Bouncy, Item};

class GameObject
{
public:
    //Public Variables could make some private
    Mesh* mesh;
    Particle* particle;
    RigidBody3d* rigidbody;
    SphereCollider* sphereCollider;

    glm::vec3 pos;
    glm::vec3 rotation;
    glm::vec3 color;
    glm::vec3 scale;

    Tags tag; // Tag of the GameObject


    //Constructor
    GameObject(Mesh* m, float mass, glm::vec3 position, float r, glm::vec3 _scale, glm::vec3 _color);
    
    //Deconstructor
    ~GameObject();

    //Idk why these are virtual
    virtual void Draw(); // Changed the function declaration to make it virtual
    virtual void Update(float deltaTime);

    //Key inputs
    static std::map<int, bool> KeyInputs;

};