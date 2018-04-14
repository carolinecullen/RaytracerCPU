#include "Lighting.hpp"
#include <iostream>
using namespace std;
using namespace glm;

Lighting::Lighting()
{
	this->location = vec3(0.f);
	this->color = vec3(0.f);
}

void Lighting::printLight()
{
	cout << "- Location: {" << location.x << " " << location.y << " " << location.z << "}" << endl;
	cout << "- Color: {" << color.x << " " << color.y << " " << color.z << "}" << endl;

	cout << endl << "---" << endl << endl;
}
