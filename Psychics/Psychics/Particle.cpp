#include "Particle.h"
#include <iostream>

Particle::Particle()
{
    linearForce = glm::vec3(0, 0, 0);
    mass = 1;
    acceleration = glm::vec3(0, 0, 0);
    velocity = glm::vec3(0, 0, 0);
    position = glm::vec3(0, 0, 0);
}

Particle::Particle(float _m, glm::vec3 pos)
{
    linearForce = glm::vec3(0, 0, 0);
    mass = _m;
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    position = pos;
}

Particle::~Particle()
{

}

void Particle::Update(float dt)
{
    //More maths and apparently brackets matter here
    
    //Newtons first law f = ma
    acceleration = linearForce / mass;
    
    //updates position using the ititinal position and velocity
    position = position + (velocity) * dt;
    
    //Same thing for velocity
    velocity = velocity + (acceleration) * dt;
    
    //Turn forces to 0
    ResetForce();
}


void Particle::Addforce(glm::vec3 force)
{
    linearForce += force;
}

void Particle::ResetForce()
{
    linearForce = glm::vec3(0);
}