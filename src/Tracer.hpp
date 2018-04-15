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
		void firstHit(float, float);


};

#endif