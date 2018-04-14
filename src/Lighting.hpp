#ifndef LIGHTING_H
#define LIGHTING_H

#include <string>
#include <sstream>
#include <glm/glm.hpp>

class Lighting
{
	public:

		Lighting();
		void printLight();

		glm::vec3 color;
		glm::vec3 location;

};

#endif