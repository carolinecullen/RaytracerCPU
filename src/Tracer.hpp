#ifndef TRACER_H
#define TRACER_H

#include "Scene.hpp"
#include "Ray.hpp"

class Tracer { 

	public:

		Scene *scene;
		int width;
		int height; 

		Tracer();
		Tracer(Scene *, int, int);

		void castRays();
		void traceRays();
		glm::vec3 getColor(ray*, int);
		float checkForIntersection(glm::vec3, glm::vec3);
		float computeDiffuse(glm::vec3, Object*, glm::vec3, glm::vec3);
		float computeSpecular(glm::vec3, Object*, glm::vec3, glm::vec3);

};

#endif