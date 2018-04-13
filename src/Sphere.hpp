#ifndef SPHERE_H
#define SPHERE_H

#include "Object.hpp"

class Sphere : public Object { 

public:

	float radius;
	glm::vec3 center;
	glm::vec3 translate;

	Sphere();

	float intersect(const ray &r);
	void createSphere(const glm::vec3, const float, const glm::vec3);
	void printSphere();

};

#endif