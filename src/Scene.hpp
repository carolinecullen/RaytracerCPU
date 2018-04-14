#ifndef SCENE_H
#define SCENE_H
#include <glm/glm.hpp>
#include <vector>
#include "Camera.hpp"
#include "Lighting.hpp"
#include "Object.hpp"

class Scene {

	public:

		Camera* cam;
		std::vector<Lighting *> lights;
		std::vector<Object *> sceneObjects;

		Scene();
		void createScene(Camera *, std::vector<Lighting *>, std::vector<Object *>);

};

#endif