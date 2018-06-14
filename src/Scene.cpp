#include "Scene.hpp"

using namespace std;

Scene::Scene()
{
	this->cam = NULL;
	this->bht = new BBHTree();
	this->aperture = 0.f;
	this->focalLength = 0.f;
}

void Scene::createScene(Camera *c, vector<Lighting *> l, vector<Object *> objs)
{
	this->cam = c;
	this->lights = l;
	this->sceneObjects = objs;
}

void Scene::addFocal(float a, float f)
{
	this->aperture = a;
	this->focalLength = f;
}
