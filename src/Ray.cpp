#include "Ray.hpp"

using namespace glm;

ray::ray(vec3 loc, vec3 dir)
{
	this->location = loc;
	this->direction = dir;
}

vec3 ray::calculate(float t)
{
	return location + t * direction;
}