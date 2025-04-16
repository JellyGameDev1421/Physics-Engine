// CubeClass.cpp

#include "CubeClass.h"

void CubeClass::Draw(glm::vec3 position, glm::vec3 rotation, glm::vec3 colour, glm::vec3 scale)
{
    // Put/Push the matrix on the stack 
    glPushMatrix();

    // Set up the model part of the model-view matrix (position, rotation, scale)
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.z, 0, 0, 1);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.x, 1, 0, 0);
    glScalef(scale.x, scale.y, scale.z);

    // Set the colour of the object
    glColor3f(colour.x, colour.y, colour.z);

    // Draw the cube
    glBegin(GL_TRIANGLES);

    //We are drawing a cube here so we use vertices to create 2 triangles for each face (6 faces total)
    //Top face tri 1
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);

    //Top face tri 2
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    //Front face tri 1
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    //Front face tri 2
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    //Bottom
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);

    //Left
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    //Right
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    //Back
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glEnd();

    // Pop the matrix, forgetting this object's model part
    glPopMatrix();
}
