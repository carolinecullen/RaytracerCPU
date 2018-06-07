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
		void traceRays(int, int);
		void printrays(int, int);
		glm::vec3 getColor(ray*, int, bool, int, float&, int, int);
		void traceRaysSuper(int);
		float calcFresnel(float, glm::vec3, glm::vec3);
		ray* calcRefractionRay(glm::vec3, glm::vec3&, glm::vec3, Object*, bool, bool&);
		float checkForIntersection(ray *, Object *, int);
		float computeDiffuse(glm::vec3, Object*, glm::vec3, glm::vec3);
		float computeSpecular(glm::vec3, Object*, glm::vec3, glm::vec3);
		ray* alignSampleVector(glm::vec3, glm::vec3, glm::vec3);
		glm::vec3 generateWeightedPoint(float, float);
		std::vector<glm::vec3> generate_hemisphere_smpl_pts(int);

};

#endif