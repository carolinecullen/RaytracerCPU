#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "Scene.hpp"

class Diagnostic { 

	public:

		Scene *scene;
		int width;
		int height; 

		Diagnostic();
		Diagnostic(Scene *, int, int);

		void sceneInfo();
		void castRays();
		void traceRays();
		void firstHit(int, int, bool, ray *, unsigned char *);
		void pixelRay(int, int);
		glm::vec3 getColor(ray *, Object*, float);
		float checkForIntersection(glm::vec3, glm::vec3);
		void pixelColor(int, int);

};

#endif