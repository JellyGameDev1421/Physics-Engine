#pragma once
#include "GameObject.h"
#include "Particle.h"
#include <iostream>
#include "RigidBody3d.h"
#include "glm/gtx/rotate_vector.hpp"
#include<glm/gtx/string_cast.hpp>
#include "SphereClass.h"

class Player : public GameObject
{

public:

	//For my player  

	float speed = 5.0f;

	//Similar to GameObject but takes in speed for movement as well as float r for radius of the sphere collider
	Player(Mesh* m, float mass, glm::vec3 position, float speed, float r);

	~Player(){}

	//Using keyboard inputs kinda cool
	void Inputs();

	void Update(float deltaTime) override;

	static std::map<int, bool> KeyInputs;
};

