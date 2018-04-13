#include "Sphere.hpp"
using namespace glm;

Sphere::Sphere()
{
	this->radius = 0.f;
	this->center = vec3(0.f);

}

float Sphere::intersect(const ray &r)
{
	return 1.0f;
}

void Sphere::createSphere(vec3 c, float r)
{
	this->radius = r;
	this->center = c;
}