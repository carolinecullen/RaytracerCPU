#ifndef PLANE_H
#define PLANE_H

#include "Object.hpp"

class Plane : public Object { 

public:

	float distance;
	glm::vec3 normal;

	Plane();

	float intersect(const ray &r);
	void createPlane(const glm::vec3, const float);
	void print();

};

#endif