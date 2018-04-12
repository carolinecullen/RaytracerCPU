#include "Parse.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

using namespace std;
using namespace glm;


vec3 cameraPos; 
vec3 lightSource;

void tokenParser(string fName)
{

	stringstream fileString;

	ifstream FileHandle("../resources/" + fName);
	string stringRead;

	FileHandle.seekg(0, std::ios::end);
	stringRead.reserve((uint) FileHandle.tellg());
	FileHandle.seekg(0, std::ios::beg);
	stringRead.assign((istreambuf_iterator<char>(FileHandle)), istreambuf_iterator<char>());

	fileString.str() = stringRead;
	fileString.seekg(0, ios::beg);

	while(!fileString.eof())
	{
		string token;
		fileString >> token;

		printf("%s\n", token.c_str());

		if (token == "sphere")
		{
			printf("sphere\n");
		}
		if (token == "light_source")
		{
			printf("sphere\n");
		}
		if (token == "plane")
		{
			printf("sphere\n");
		}
		else if (token.substr(0,2) == "//")
		{
			printf("comment\n");
			string toss;
			getline(fileString, toss);
		}
	}
}

int main(int argc, char** argv)
{
	if(argc < 3 || argc > 7)
	{
		cout << "Invalid run commands." << endl;
		cout << "Choose raycast, sceneinfo, pixelray, firsthit with the proper parameters." << endl;
		return -1;
	}

	// put file into a string 

	if(strncmp(argv[1], "raycast", 7) == 0)
	{
		if(argc != 3)
		{
			cout << "Invalid run commands: ./raytrace raycast <input_filename>" << endl;
			return -1;
		}
		tokenParser(argv[2]);

	}
	else if(strncmp(argv[1], "sceneinfo", 9) == 0)
	{
		if(argc != 3)
		{
			cout << "Invalid run commands: ./raytrace sceneinfo <input_filename>" << endl;
			return -1;
		}
	}
	else if(strncmp(argv[1], "pixelray", 8) == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace pixelray <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}
	}
	else if(strncmp(argv[1], "firsthit", 8) == 0)
	{
		if(argc != 7)
		{
			cout << "Invalid run commands: ./raytrace firsthit <input_filename> <width> <height> <x> <y>" << endl;
			return -1;
		}
	}
	else
	{
		cout << "Invalid command: use raycast, sceneinfo, pixelray, firsthit run with proper parameters." << endl;
		return -1;
	}



}

// needed for precision and rounding in order to match dunns outputs

// cout << std::setiosflags(std::ios::fixed);
// cout << std::setprecision(4);
// cout << "Pixel: [" << X << ", " << Y << "] Ray: " << Ray << endl;
// unsigned int red = (unsigned int) std::round(color.r * 255.f);
// unsigned int green = (unsigned int) std::round(color.g * 255.f);
// unsigned int blue = (unsigned int) std::round(color.b * 255.f);
