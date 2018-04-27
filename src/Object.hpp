#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <glm/glm.hpp>
#include "Ray.hpp"

class Object {

public:

	std::string type;
	float ambient;
	float diffuse;
	float specular;
	float roughness;
	glm::vec3 pigment;
	float ior;

	Object() {};

	virtual float intersect(const ray &r) = 0;
	virtual void print() = 0;

};

#endif
