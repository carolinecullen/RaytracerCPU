#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Parse.hpp"	
#include "Lighting.hpp"
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

bool Parse::tokenParser(string fName)
{
	ifstream FileHandle("../resources/" + fName);
	Camera *cam;

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
		cout << fileString.str() << endl;

		if(token != "")
		{
			if (token == "//")
			{
				continue;
			}
			else if (token == "sphere")
			{
				
			}
			else if (token == "light_source")
			{
				
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


