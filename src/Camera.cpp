#include "Camera.hpp"
#include <iostream>
using namespace std;
using namespace glm;

Camera::Camera()
{
	this->lookat = vec3(0.f);
	this->up = vec3(0.f);
	this->right = vec3(0.f);
	this->location = vec3(0.f);
}

void Camera::printCamera()
{
	cout << "Camera:" << endl;
	cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << endl;
	cout << "- Up: {" << up.x << " " << up.y << " " << up.z << "}" << endl;
	cout << "- Right: {" << right.x << " " << right.y << " " << right.z << "}" << endl;
	cout << "- Look at: {" << lookat.x << " " << lookat.y << " " << lookat.z << "}" << endl;

	cout << endl << "---" << endl << endl;

}


