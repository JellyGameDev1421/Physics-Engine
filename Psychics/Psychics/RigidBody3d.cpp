#include "RigidBody3d.h"

RigidBody3d::RigidBody3d(float m, glm::vec3 pos)
{
    //Changing rigidbody 2d to 3d is annoying
    
    //
    TotalLinearForce = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    position = pos;
    mass = m;

    AngularForce = glm::vec3(0);
    rAcceleration = glm::vec3(0);
    rVelocity = glm::vec3(0);
    orientation = glm::vec3(0, 0, 0);
    heading = glm::vec3(0, 0, 1);
    height = 1.0f;
    length = 1.0f;
    width = 1.0f;

    //Inertia is the distrubution of mass among an object
    //Using dimenstions if the object to make inertia determins how objects respond to rotational movement
    
    Intertia = glm::mat3(
        1.0f / 12 * mass * (pow(height, 2) + pow(width, 2)), 0, 0,
        0, 1.0f / 12 * mass * (pow(length, 2) + pow(width, 2)), 0,
        0, 0, 1.0f / 12 * mass * (pow(height, 2) + pow(length, 2))
    );

    dampingFactor = 0.8f; // Adjust this value to control damping rate
}

RigidBody3d::~RigidBody3d()
{
}

void RigidBody3d::Update(float deltaTime)
{
    // Reduce forces and update linear and angular acceleration
    acceleration = TotalLinearForce / mass;                 // Compute linear acceleration using Newton's second law
    rAcceleration = AngularForce * glm::inverse(Intertia);  // Compute angular acceleration using torque and the inverse of the inertia tensor

    // Update position and orientation
    position = position + (velocity)*deltaTime;           // Update position using the current velocity and the elapsed time
    orientation = orientation + (rVelocity)*deltaTime;    // Update orientation (rotation) using the current angular velocity and the elapsed time

    // Update linear and angular velocity
    velocity = velocity + (acceleration)*deltaTime;        // Update linear velocity using the current acceleration and the elapsed time
    rVelocity = rVelocity + (rAcceleration)*deltaTime;    // Update angular velocity using the current angular acceleration and the elapsed time

    // Apply damping to linear and angular velocity
    velocity *= pow(dampingFactor, deltaTime);              // Dampen linear velocity over time to simulate friction or air resistance
    rVelocity *= pow(dampingFactor, deltaTime);             // Dampen angular velocity over time to simulate rotational friction or air resistance

    // Recalculate heading (direction the object is facing) based on orientation
    heading = glm::normalize(glm::rotate(glm::vec3(0, 0, 1), glm::radians(orientation.y), glm::vec3(0, 1, 0)));
    // The above line rotates the unit vector (0, 0, 1) around the y-axis by the object's yaw (orientation.y) angle, 
    // resulting in a new vector representing the object's heading direction. This vector is then normalized to ensure it has a unit length.

    resetForce();  // Reset accumulated forces for the next frame or iteration of the simulation

}

void RigidBody3d::Addforce(glm::vec3 LinearForce, glm::vec3 forcePos)
{
    glm::vec3 torque = glm::cross(LinearForce, forcePos); // Cross product for torque
    // Reduce the force before applying it
    if (forcePos == glm::vec3(0)) 
    {
        TotalLinearForce += LinearForce; // Adjusted force scale factor
    }

    AngularForce += torque;
}

void RigidBody3d::resetForce()
{
    TotalLinearForce = glm::vec3(0);
    AngularForce = glm::vec3(0);
}
