//Using a different loader library to 5028CEM as this allows legacy OpenGL usage (this uses GLEW), but uses the same windowing library GL3W
#include "GL/glew.h" //Needed to use the GLEW library and it's function
#include "GLFW/glfw3.h" //Needed to use the GL3W library and it's functions
#include "glm/glm.hpp"
#include "Object.h"
#include "CubeClass.h"
#include "SphereClass.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Particle.h"
#include "Player.h"
#include "RigidBody3d.h"
#include "SphereCollider.h"

#include <iostream>
#include <vector>
using namespace std;

int windowWidth = 1080;
int windowHeight = 640;

double oldTime;
double currentTime;

const float bg[] = { 0.1, 0.1, 0.1, 1.0 };
float nearPlane = 0.01f;
float farPlane = 1000.0f;
float fovDegrees = 30.0f;

//CubeClass Cube1;
//SphereClass Sphere1;

CubeClass player1;
CubeClass cube1;
SphereClass sphere1;

Particle ParticleForce;

std::vector<GameObject*> object;

void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) //If a key is pressed
    {
        GameObject::KeyInputs[key] = true; //Set the map key to the key int and value to true
        //We can use glfwGetKeyName() to get the actual char of the key being pressed
        //cout << glfwGetKeyName(key, scancode) << " pressed." << endl;
    }
    else if (action == GLFW_RELEASE) //If a key is de-pressed
    {
        GameObject::KeyInputs[key] = false; //Get the key in the map and set it's value to false
       // cout << glfwGetKeyName(key, scancode) << " de-pressed." << endl;
    }

    //We still want the hardcoded escape key to close the window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}

int main(int argc, char** argv)
{
    ///// ----- THE SETUP PHASE -----
    /// --- LIBRARY SETUP ---
    //Initializes the GLFW library, 
    //Needs to be the first GLFW function called 
    //as it sets up data structures required by later GLFW functions
    glfwInit();

    //Use a legacy version of OpenGL - 2.1, 
    //The machine this runs on must be compatible with this version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    /*
        Configures the window we want to use
            Paramaters are (width of window,
            height of window,
            title of window,
            NULL for windowed mode, NULL for sharing resources)

        Also creates an OpenGL context which is
        associated with the window (we only have 1 window at the moment)
    */
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "5025CEM Renderer", NULL, NULL);

    /*
       While not needed for the running of the program,
       this will help us in case there is an error with using GLFW
       The return -1 will stop the program and give us a readable error message
   */

    if (!window)
    {
        throw std::exception("ERROR: No window was created!");
    }

    /*
        Make the OpenGL context of the window made above current
            The current context is the one that processes any commands
            given to it as well as holding OpenGL state / information
    */
    glfwMakeContextCurrent(window);

    /*
        Initialize the GLEW library (after the OpenGL context has been created)
        This allows the use of legacy OpenGL features only
    */

    glewExperimental = GL_TRUE;
    glewInit();

    //How often the buffer should swap - 1 = do everytime there is a screen update
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, KeyboardInput);

    Mesh* sphereMesh = new SphereClass();
    Mesh* player = new CubeClass();
    Mesh* Item = new CubeClass();
    Mesh* Wall = new CubeClass();

    // Sphere
    GameObject* SphereObj1 = new GameObject(sphereMesh, 0.5f, glm::vec3(0.0f, 0.0f, 4.0f), 0, glm::vec3 (0.5), glm::vec3(1, 1, 1));
    SphereObj1->sphereCollider = new SphereCollider(sphereMesh, 1, SphereObj1->pos);
    SphereObj1->mesh = &sphere1;

    // Instantiate player
    GameObject* playerObj = new Player(player, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0);
    playerObj->sphereCollider = new SphereCollider(player, 0.5f, playerObj->pos); // Create a collider for the player

    //Instansitate a Item
    GameObject* ItemObj = new GameObject(Item, 0.5f, glm::vec3(4.0f, 0.0f, 0.0f), 0, glm::vec3(0.5), glm::vec3(1, 1, 1));
    ItemObj->sphereCollider = new SphereCollider(Item, 0.5f, ItemObj->pos);

    //Instantiate a wall
    GameObject* WallObj = new GameObject(Wall, 0.5f, glm::vec3(-4.0f, 0.0f, 0.0f), 0, glm::vec3(2.0), glm::vec3(1, 1, 1));
    WallObj->sphereCollider = new SphereCollider(Wall, 1.0f, WallObj->pos);

    // Create a vector to store sphere colliders
    vector <SphereCollider*> SphereColliderList;
    // Add the sphere collider of SphereObj1 to the list
    SphereColliderList.push_back(SphereObj1->sphereCollider);

    // Add the sphere object and player object to the object list
    object.push_back(SphereObj1);
    object.push_back(playerObj);
    object.push_back(ItemObj);
    object.push_back(WallObj);

    //Assigning tags
    playerObj-> tag = Tags::Player;
    SphereObj1->tag = Tags::Bouncy;
    ItemObj->tag    = Tags::Item;
    WallObj->tag    = Tags::Wall;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //set to the identity matrix
    
    ///// ----- THE GAME LOOP PHASE -----
    //A loop that allows the window to refresh and display content. 

    //if the window should close, this will be while(false) 
    //and leave the while loop. Otherwise, continue looping.
 
    // Define a variable to keep track of the time elapsed since the item was collected
    float itemResetTimer = 0.0f;

    while (!glfwWindowShouldClose(window))
    {

        //Calculating DeltaTime
        oldTime = currentTime; //take a record of the "old" time
        currentTime = glfwGetTime(); //get the "new" current time

        double deltaTime = currentTime - oldTime; //find out the difference between old and new time

        glViewport(0, 0, windowWidth, windowHeight);

        // clear the window to a background color, clear the depth buffer
        glClearBufferfv(GL_COLOR, 0, bg);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //(FoV in radians, aspectRation, nearPlane, farPlane)

        gluPerspective(glm::radians(fovDegrees), float(windowWidth) / windowHeight, nearPlane, farPlane);

        // Set the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // set to the identity matrixZASD

        glm::vec3 ObjectsPos = playerObj->pos;
        glm::vec3 ObjectDir = playerObj->rigidbody->heading;
        glm::vec3 cameraPos = ObjectsPos - ObjectDir * 550.0f; // Move the camera 100 units back

        gluLookAt(cameraPos.x, cameraPos.y + 150, cameraPos.z,
            ObjectsPos.x, ObjectsPos.y, ObjectsPos.z,
            0.0f, 1.0f, 0.0f);

        //Drawing Shapes
        for (int i = 0; i < object.size(); i++)
        {
            object[i]->Update(deltaTime);
            object[i]->Draw();
        }

        // Declare a boolean flag to track whether the object has collided in the current frame
        bool alreadyCollided = false;

        // Increment the timer by the elapsed time
        itemResetTimer += deltaTime;

        // Check for collisions
        for (int i = 0; i < object.size(); i++) {
            for (int j = 0; j < object.size(); j++) {
                if (i != j) {
                    bool collided = object[i]->sphereCollider->CheckCollision(object[j]->sphereCollider);

                    if (collided) {
                        if (object[j]->tag == Tags::Bouncy && !alreadyCollided) 
                        {
                            // Change the color of the collided object
                            object[j]->color = glm::vec3(1.0f, 0.0f, 0.0f); // Red color
                            object[i]->rigidbody->Addforce(glm::vec3(0, 0, -10));
                            cout << "Boing" << endl;
                        }
                        if (object[j]->tag == Tags::Item && !alreadyCollided) 
                        {
                            ItemObj->pos = glm::vec3(100, 100, 100);
                            ItemObj->sphereCollider->pos = ItemObj->pos;
                            cout << "You have collected a point" << endl;
                        }

                        // Check if 10 seconds have passed since the item was collected
                        if (itemResetTimer >= 10.0f) {
                            // Reset the position of the item and its sphere collider
                            ItemObj->pos = glm::vec3(4.0f, 0.0f, 0.0f); // Reset to initial position
                            ItemObj->sphereCollider->pos = ItemObj->pos; // Reset collider position
                            cout << itemResetTimer << endl;
                            // Reset the timer to zero for the next countdown
                            itemResetTimer = 0.0f;
                        }

                        if (object[j]->tag == Tags::Wall && !alreadyCollided)
                        {
                            cout << "Wall collision detected!" << endl;
                            // Stop the player's velocity
                            playerObj->rigidbody->velocity = glm::vec3(0, 0, 0);
                            alreadyCollided = true;
                        }

                    }
                }
            }
        }

        // Draw lines X, Y, Z
        glPushMatrix();
        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(3, 0, 0); // positive x axis

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 3, 0); // positive y axis

        glColor3f(1, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 3); // positive z axis
        glEnd();
        glPopMatrix();

        // Check for any events/incoming messages from the Operating System
        glfwPollEvents();

        // Redraw the contents of the window and present it to the user ("paints the screen")
        glfwSwapBuffers(window);
    }
    ///// ----- THE CLEANUP PHASE -----
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}