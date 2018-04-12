#include <iostream>
#include <limits>
#include "Parse.hpp"
using namespace std;
using namespace glm;


vec3 Parse::Vector(std::stringstream & Stream)
{
	vec3 v;
	v.x = v.y = v.z = 0.f;
	stringbuf buf;

	Stream.ignore(1, '<');
	Stream.get(buf, '>');
	Stream.ignore(numeric_limits<streamsize>::max(), '>');

	string line = buf.str(); 
	int read = sscanf(line.c_str(), "%f, %f, %f", &v.x, &v.y, &v.z);

	if (read != 3)
	{
		cerr << "Expected to read 3 vector elements but found '" << line << "'" << endl;
	}

	return v;
}
