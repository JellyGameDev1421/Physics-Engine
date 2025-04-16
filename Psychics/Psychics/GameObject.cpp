#include "GameObject.h"

std::map<int, bool> GameObject::KeyInputs;

// GameObject constructor definition
GameObject::GameObject(Mesh* m, float mass, glm::vec3 position, float r, glm::vec3 _scale, glm::vec3 _color)
{
    rotation = glm::vec3(0);
    mesh = m;
    mesh->colour = _color; // Setting the color here
    mesh->position = position;
    scale = _scale;
    particle = new Particle(mass, position);
    rigidbody = new RigidBody3d(mass, pos);
    sphereCollider = new SphereCollider(mesh, r, position);
    // Constructor fills in default values in case I don't give it anything
    pos = position;
}




GameObject::~GameObject()
{

}

// GameObject Draw function definition
void GameObject::Draw()
{
    // Draw the mesh using the particle's position
    mesh->Draw(pos, rotation, glm::vec3(1, 0, 1), scale);
    //sphereCollider->Draw();

    // Draw velocity vector
    glColor3f(0.5f, 0.5f, 0.5f);
    glm::vec3 vel = rigidbody->velocity;
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(vel.x, vel.y, vel.z);
    glEnd();
}

void GameObject::Update(float deltaTime)
{

}
