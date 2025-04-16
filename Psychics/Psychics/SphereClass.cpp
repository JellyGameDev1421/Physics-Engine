#include "SphereClass.h"

void SphereClass::Draw(glm::vec3 position, glm::vec3 rotation, glm::vec3 colour, glm::vec3 scale)
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    //Put/Push the matrix on the stack 
    //(so any changes between this push and a later pop do not affect this matrix)
    //we do this so the view part (defined outside this function) stays the same and we add the model part each object 
    //(and then forget about the model part between objects with a pop)
    glPushMatrix();

    //Set up the model part of the model view matrix (position, rotation, scale)
    //due to the push and pop, the module part is individual to each object
    // 
    //Position the object 
    glTranslatef(position.x, position.y, position.z);

    //Rotate the object
    glRotatef(rotation.z, 0, 0, 1);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.x, 1, 0, 0);

    //Scale the object
    glScalef(scale.x, scale.y, scale.z);

    //Set the colour of the object
    glColor3f(colour.x, colour.y, colour.z);

    //Vertex generation
    float pi = 3.14f;
    float sliceStep = 2.0f * pi / slices;
    float stackStep = pi / stacks;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = 3.14f / 2.0f - i * stackStep;

        float rcos = radius * glm::cos(stackAngle);
        float z = radius * glm::sin(stackAngle);

        for (int j = 0; j <= slices; ++j)
        {
            float sliceAngle = j * sliceStep;

            float x = rcos * glm::cos(sliceAngle);
            float y = rcos * glm::sin(sliceAngle);

            vertices.push_back(glm::vec3(x, y, z));

        }
    }

    //Index generation
    int k1, k2;

    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (slices + 1);
        k2 = k1 + slices + 1;

        for (int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    //Drawing
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < indices.size(); ++i)
    {
        int index = indices[i];
        glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);
    }
    glEnd();

    //forget this objects model part, so only the view part remains for other objects
    glPopMatrix();
}