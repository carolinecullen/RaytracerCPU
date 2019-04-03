#ifndef OBJECT_H
#define OBJECT_H

//#include "BBH.hpp"
class BBH;
#include <iostream>
#include <string>
#include <iomanip>
#include "../glm/glm/glm.hpp"
#include "Ray.hpp"

class Object 
{

	public:

		std::string type;
		float ambient;
		float diffuse;
		float specular;
		float roughness;
		glm::vec3 pigment;
		float filter;
		glm::vec3 normal;
		float ior;
		float reflection;
		float refraction;
		int id;

		glm::mat4 M;
		glm::mat4 IM;

		Object() {};

		virtual float intersect(const ray &r) = 0;
		virtual void print() = 0;
		virtual BBH* makeBoundingBox() = 0;
		virtual glm::vec3 getCenter() = 0;

};

#endif
