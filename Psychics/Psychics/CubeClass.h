#pragma once
//Using a different loader library to 5028CEM as this allows legacy OpenGL usage (this uses GLEW), but uses the same windowing library GL3W
#include "GL/glew.h" //Needed to use the GLEW library and it's function
#include "GLFW/glfw3.h" //Needed to use the GL3W library and it's functions
#include "glm/glm.hpp"
#include "Mesh.h"

class CubeClass : public Mesh
{
public:

	CubeClass() {};
	~CubeClass() {};

	void Draw(glm::vec3 position, glm::vec3 rotation, glm::vec3 colour, glm::vec3 scale) override;
};

