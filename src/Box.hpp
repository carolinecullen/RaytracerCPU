#ifndef BOX_H
#define BOX_H

class BBH;
#include "../glm/glm/glm.hpp"
#include "Object.hpp"
#include "Ray.hpp"


class Box : public Object {

		public:

		glm::vec3 min, max;

		Box();

		void updateBox(glm::vec3, glm::vec3);
		float intersect(const ray &);
		void updateVals(const ray &, float&, float&, int);
		bool Equals(float const, float const, float const);
		bool init();
		bool isParallel(Box*, const ray &, int);
		void calcNormal(glm::vec3);
		glm::vec3 getCenter();
		void print();
		BBH* makeBoundingBox();
	
};

#endif
