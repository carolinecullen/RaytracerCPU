#include "Scene.hpp"

using namespace std;

Scene::Scene()
{
	this->cam = NULL;
}

void Scene::createScene(Camera *c, vector<Lighting *> l, vector<Object *> objs)
{
	this->cam = c;
	this->lights = l;
	this->sceneObjects = objs;
}
