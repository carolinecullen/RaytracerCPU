#ifndef TRACER_H
#define TRACER_H

#include "Scene.hpp"

class Tracer { 

	public:

		Scene *scene;
		int width;
		int height; 

		Tracer();
		Tracer(Scene *, int, int);

		void castRays();
		void traceRays();
		void firstHit(int, int, bool, ray *, unsigned char *);
		void pixelRay(int, int);
		glm::vec3 getColor(ray *, Object*, float);
		float checkForIntersection(glm::vec3, glm::vec3);
		void pixelColor(int, int);
		float computeDiffuse(glm::vec3, Object*, glm::vec3);
		float computeSpecular(glm::vec3, Object*, glm::vec3);

};

#endif