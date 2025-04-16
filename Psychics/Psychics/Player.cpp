#include "Player.h"

using namespace std;

Player::Player(Mesh* m, float mass, glm::vec3 position, float _speed, float r) :
    GameObject(m, mass ,position, r, scale, color)
{
    color = glm::vec3 (0.5);
    scale = glm::vec3 (0.5);
	speed = _speed;
}

void Player::Inputs() 
{

    //Inputs being done here always nice and a new way to do it
    //Debugging to make sure they are moving

    if (GameObject::KeyInputs[GLFW_KEY_W] == true) 
    {
        rigidbody->Addforce(rigidbody->heading * speed);
        //std::cout << "rVelocity: " << glm::to_string(rigidbody->rVelocity) << std::endl;
        //std::cout << "Velocity: " << glm::to_string(rigidbody->velocity) << std::endl;
    }

    if (GameObject::KeyInputs[GLFW_KEY_S] == true) 
    {
        rigidbody->Addforce(-rigidbody->heading * speed);
        //std::cout << "rVelocity: " << glm::to_string(rigidbody->rVelocity) << std::endl;
        //std::cout << "Velocity: " << glm::to_string(rigidbody->velocity) << std::endl;
    }

    if (GameObject::KeyInputs[GLFW_KEY_A] == true) 
    {
        rigidbody->Addforce(rigidbody->GetRight() * 20.0f,
            glm::rotate({ -30,0,1 }, glm::radians(rigidbody->orientation.y), glm::vec3(0, 1, 0)));
        //std::cout << "rVelocity: " << glm::to_string(rigidbody->rVelocity) << std::endl;
        //std::cout << "Velocity: " << glm::to_string(rigidbody->velocity) << std::endl;

    }

    if (GameObject::KeyInputs[GLFW_KEY_D] == true) 
    { 
        rigidbody->Addforce(-rigidbody->GetRight() * 20.0f,
            glm::rotate({ 30,0,1 }, glm::radians(rigidbody->orientation.y), glm::vec3(0, 1, 0)));
        //std::cout << "rVelocity: " << glm::to_string(rigidbody->rVelocity) << std::endl;
        //std::cout << "Velocity: " << glm::to_string(rigidbody->velocity) << std::endl;
    }

    if (GameObject::KeyInputs[GLFW_KEY_LEFT_SHIFT] == true) 
    {
        // Define a force magnitude
        float shiftForce = 10.0f;
        // Add force in the direction of the player's heading
        rigidbody->Addforce(rigidbody->heading * shiftForce);
    }

    if (GameObject::KeyInputs[GLFW_KEY_R] == true) 
    {
        rigidbody->position = glm::vec3(0);
        sphereCollider->pos = rigidbody->position;
    }

    // Define the jump force
    float jumpForce = 10.0f;

    // Check for spacebar input
    if (GameObject::KeyInputs[GLFW_KEY_SPACE] == true)
    {
        // Apply an upward force to simulate jumping
        rigidbody->Addforce(glm::vec3(0.0f, jumpForce, 0.0f));
    }
    // Check for C input
    if (GameObject::KeyInputs[GLFW_KEY_C] == true)
    {
        // Apply an upward force to simulate jumping
        rigidbody->Addforce(glm::vec3(0.0f, -jumpForce, 0.0f));
    }
}


void Player::Update(float deltaTime) {

	Inputs();

	rigidbody->Update(deltaTime);

    sphereCollider->pos = pos;

    pos = rigidbody->position;

    rotation = rigidbody->orientation;
}