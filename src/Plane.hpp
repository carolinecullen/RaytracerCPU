#ifndef PLANE_H
#define PLANE_H

#include "Object.hpp"
#include "BBH.hpp"

class Plane : public Object { 

public:

	float distance;

	Plane();

	float intersect(const ray &r);
	void createPlane(const glm::vec3, const float);
	void print();
	glm::vec3 getCenter(){ return glm::vec3(0.f); };
	BBH* makeBoundingBox(){ return NULL; };

};

#endif