#include "Ray.hpp"

using namespace glm;

ray::ray()
{
	this->location = vec3(0.f);
	this->direction = vec3(0.f);
}

void ray::createRay(vec3 location, vec3 direction)
{
	this->location = location;
	this->direction = direction;
}