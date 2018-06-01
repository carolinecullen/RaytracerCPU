#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.hpp"
#include "BBH.hpp"

class Triangle : public Object
{
	public:

		glm::vec3 A;
		glm::vec3 B;
		glm::vec3 C;

		Triangle();

		float intersect(const ray &r);
		void createTriangle(const glm::vec3, const glm::vec3, const glm::vec3);
		void calcNormal(glm::vec3);
		void print();
		glm::vec3 getCenter();
		BBH* makeBoundingBox();
};

#endif