#include "Object.hpp"

class Sphere : public Object { 

public:

	Sphere();

	void parse_sphere(FILE *fp);

	void parse(FILE *fp) {
		GeomObject::parse(fp); 

		parse_sphere(fp);
	}

private:

	float cx, cy, cz;
	float rad;

};