#ifndef SCENE_H
#define SCENE_H
#include "../glm/glm/glm.hpp"
#include <vector>
#include "Camera.hpp"
#include "Lighting.hpp"
#include "Object.hpp"
#include "BBHTree.hpp"

class Scene {

	public:

		Camera* cam;
		float aperture;
		float focalLength;
		BBHTree *bht;
		std::vector<Lighting *> lights;
		std::vector<Object *> sceneObjects;

		Scene();
		void addFocal(float, float);
		void createScene(Camera *, std::vector<Lighting *>, std::vector<Object *>);

};

#endif