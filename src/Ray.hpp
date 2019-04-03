#ifndef RAY_H
#define RAY_H
#include "../glm/glm/glm.hpp"

class ray {

	public:

		glm::vec3 location;
		glm::vec3 direction;

		ray(glm::vec3, glm::vec3);
		glm::vec3 calculate(float);

};

#endif