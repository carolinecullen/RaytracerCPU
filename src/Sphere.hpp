#ifndef SPHERE_H
#define SPHERE_H

#include "Object.hpp"
#include "BBH.hpp"

class Sphere : public Object { 

public:

	float radius;
	glm::vec3 center;

	Sphere();

	float intersect(const ray &r);
	void createSphere(const glm::vec3, const float);
	void calcNormal(glm::vec3);
	void print();
	glm::vec3 getCenter();
	BBH* makeBoundingBox();

};

#endif