#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Parse.hpp"
#include "Sphere.hpp"	
using namespace std;
using namespace glm;

string Parse::tokenizeHelper(ifstream &FileHandle, string &holdBuf)
{
	if(getline(FileHandle, holdBuf))
	{
		string token;
		stringstream fileString;

		fileString << holdBuf;
		fileString >> token;

		fileString.flush();
		return token;
	}
	else
	{
		return NULL;
	}
}

vector<float> Parse::getFloats(string buf)
{
	int pos = 0;
	vector<float> floatVals;
	while(pos < buf.size())
	{
		char cur = buf[pos];
		bool flag = false;
		char actualNum[640];

		int i = 0;
		while(cur == '.'|| (cur <= '9' && cur >= '0') || cur == '-')
		{
			flag = true;
			actualNum[i] = cur;
			i++;
			pos++;
			cur = buf[pos];
		}

		if(flag)
		{
			actualNum[i] = '\0';
			float f = strtof(actualNum, 0);
			floatVals.push_back(f);
		}
		pos++;
	}

	return floatVals;
}

Camera* Parse::placeCamera(ifstream &FileHandle)
{
	Camera* cam = new Camera;

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "location")
		{
			vector<float> locVals;
			locVals = Parse::getFloats(buf);

			if(locVals.size() > 3 || locVals.size() < 3)
			{
				cout << "Malformed Camera location in POV file." << endl;
				return NULL;
			}
			cam->location = vec3(locVals[0], locVals[1], locVals[2]);
		}

		if(tok == "up")
		{
			vector<float> upVals;
			upVals = Parse::getFloats(buf);

			if(upVals.size() > 3 || upVals.size() < 3)
			{
				cout << "Malformed Camera up in POV file." << endl;
				return NULL;
			}
			cam->up = vec3(upVals[0], upVals[1], upVals[2]);
		}

		if(tok == "right")
		{
			vector<float> rightVals;
			rightVals = Parse::getFloats(buf);

			if(rightVals.size() > 3 || rightVals.size() < 3)
			{
				cout << "Malformed Camera right in POV file." << endl;
				return NULL;
			}
			cam->right = vec3(rightVals[0], rightVals[1], rightVals[2]);
		}

		if(tok == "look_at")
		{
			vector<float> lookVals;
			lookVals = Parse::getFloats(buf);

			if(lookVals.size() > 3 || lookVals.size() < 3)
			{
				cout << "Malformed Camera look_at in POV file." << endl;
				return NULL;
			}
			cam->lookat = vec3(lookVals[0], lookVals[1], lookVals[2]);
		}

		buf = "";	
	}

	return cam;
}

Lighting* Parse::lightInsertion(string line)
{
	Lighting* light = new Lighting;
	vector<float> lVals;

	lVals = Parse::getFloats(line);

	if(lVals.size() > 6 || lVals.size() < 6)
	{
		cout << "Malformed lighting color in POV file." << endl;
		return NULL;
	}
	light->location = vec3(lVals[0], lVals[1], lVals[2]);
	light->color = vec3(lVals[3], lVals[4], lVals[5]);
	
	return light;
}

Sphere* Parse::sphereInsertion(ifstream &FileHandle, string line)
{
	Sphere* s = new Sphere();
	vector<float> sVals = Parse::getFloats(line);
	s->center = vec3(sVals[0], sVals[1], sVals[2]);
	s->radius = sVals[3];

	string tok;
	string buf;
	while((tok = Parse::tokenizeHelper(FileHandle, buf)) != "}")
	{
		if(tok == "pigment")
		{
			vector<float> pVals;
			pVals = Parse::getFloats(buf);

			if(pVals.size() > 3 || pVals.size() < 3)
			{
				cout << "Malformed Camera location in POV file." << endl;
				return NULL;
			}
			s->pigment = vec3(pVals[0], pVals[1], pVals[2]);
		}

		if(tok == "finish")
		{
			vector<float> fVals;
			fVals = Parse::getFloats(buf);

			if(fVals.size() > 2 || fVals.size() < 2)
			{
				cout << "Malformed Camera up in POV file." << endl;
				return NULL;
			}
			s->ambient = fVals[0];
			s->diffuse = fVals[0];
		}

		if(tok == "translate")
		{
			vector<float> tranVals;
			tranVals = Parse::getFloats(buf);

			if(tranVals.size() > 3 || tranVals.size() < 3)
			{
				cout << "Malformed Camera right in POV file." << endl;
				return NULL;
			}
			s->translate = vec3(tranVals[0], tranVals[1], tranVals[2]);
		}

		buf = "";	
	}

	return s;
}

bool Parse::tokenParser(string fName)
{
	ifstream FileHandle("../resources/" + fName);
	Camera *cam;
	vector<Lighting *> allLights;
	vector<Object *> Scene;

	if(!FileHandle)
	{
		printf("Problem opening file!\n");
		return false;
	}

	string holdBuf;

	while(getline(FileHandle, holdBuf))
	{
		string token;
		stringstream fileString;

		fileString << holdBuf;
		fileString >> token;

		if(token != "")
		{
			if (token == "//")
			{
				continue;
			}
			else if (token == "sphere")
			{
				Sphere *s = sphereInsertion(FileHandle, holdBuf);
				Scene.push_back(s);
				// s->printSphere();
			}
			else if (token == "light_source")
			{
				Lighting *light = lightInsertion(holdBuf);
				allLights.push_back(light);
				light->printLight();
			}
			else if (token == "plane")
			{

			}
			else if (token == "camera")
			{
				cam = placeCamera(FileHandle);
				cam->printCamera();
			}
		}

		fileString.flush();
		holdBuf = "";
	}


	return true;
}


