#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "../glm/glm/glm.hpp"

class Camera
{
	public:

		glm::vec3 lookat;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 location;

		Camera();
		void printCamera();
};

#endif