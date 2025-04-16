#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include <iostream>
#include <vector>
using namespace std;

class RigidBody3d
{
public:
	//Complicated stuff
	//All parameters needed to a rigidbody

	glm::vec3 TotalLinearForce;  // Total linear force acting on the object
	glm::vec3 acceleration;      // Current linear acceleration of the object
	glm::vec3 velocity;          // Current linear velocity of the object
	glm::vec3 position;          // Current position of the object
	float mass;                  // Mass of the object

	glm::vec3 AngularForce;      // Total angular force acting on the object
	glm::vec3 rAcceleration;     // Current angular acceleration (rotation) of the object
	glm::vec3 rVelocity;         // Current angular velocity (rotation speed) of the object
	glm::vec3 orientation;       // Orientation (rotation) of the object
	glm::vec3 heading;           // Direction the object is facing
	float height;                // Height of the object (for collision detection)
	float length;                // Length of the object (for collision detection)
	float width;                 // Width of the object (for collision detection)
	float dampingFactor;         // Damping factor for reducing velocities over time (Making things slower)
	glm::mat3 Intertia;          // Inertia tensor representing the object's resistance to angular acceleration


	RigidBody3d(float m, glm::vec3 pos);

	~RigidBody3d();

	void Update(float deltaTime);

	void resetForce();

	void Addforce(glm::vec3 linearForce, glm::vec3 forcePos = glm::vec3(0));

	glm::vec3 GetRight() {
		return -glm::normalize(glm::cross({ 0,1,0 }, heading));
	}
};

