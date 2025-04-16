#pragma once
#include "GL/glew.h" //Needed to use the GLEW library and it's function
#include "GLFW/glfw3.h" //Needed to use the GL3W library and it's functions
#include "glm/glm.hpp"

class Particle
{
public:

    glm::vec3 linearForce;

    float mass;

    glm::vec3 position;

    glm::vec3 acceleration;

    glm::vec3 velocity;

    // Constructors
    Particle();

    Particle(float _m, glm::vec3 pos);

    ~Particle();

    // Member function to update particle physics
    void Update(float dt);

    //Adding force
    void Addforce(glm::vec3 force);

    //Turns force to 0
    void ResetForce();
};
