#include "Object.hpp"

class Sphere : public Object { 

public:

	float radius;
	glm::vec3 center;

	Sphere();

	float intersect(const ray &r) = 0;
	void createSphere(const glm::vec3, const float);

};