#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "Ray.hpp"

class Object {

public:

	std::string type;
	glm::vec3 finish;
	glm::vec3 pigment;

	Object() {};

	virtual float intersect(const ray &r) = 0;

};
