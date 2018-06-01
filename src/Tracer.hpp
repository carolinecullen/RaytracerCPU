#ifndef TRACER_H
#define TRACER_H

#include "Scene.hpp"
#include "Ray.hpp"
#include "Object.hpp"
#include "BBHTree.hpp"

class Tracer { 

	public:

		Scene *scene;
		int width;
		int height; 

		Tracer();
		Tracer(Scene *, int, int);

		void castRays();
		void traceRays(int);
		void printrays(int, int);
		glm::vec3 getColor(ray*, int, bool, int, float&);
		void traceRaysSuper(int);
		float calcFresnel(float, glm::vec3, glm::vec3);
		ray* calcRefractionRay(glm::vec3, glm::vec3&, glm::vec3, Object*, bool, bool&);
		//float checkForIntersection(glm::vec3, glm::vec3, Object *);
		float checkForIntersection(ray *);
		float checkForIntersection(ray *, Object *);
		float computeDiffuse(glm::vec3, Object*, glm::vec3, glm::vec3);
		float computeSpecular(glm::vec3, Object*, glm::vec3, glm::vec3);

};

#endif