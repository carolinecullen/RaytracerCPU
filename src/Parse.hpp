#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <vector>
#include "Camera.hpp"
#include "Lighting.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"

using namespace std;

class Parse
{

	public:

		Parse() {}

		// static members are independant of objects and can be called with the :: operator 

		static bool tokenParser(std::string, Scene *);

		static Camera* placeCamera(std::ifstream &);

		static std::string tokenizeHelper(std::ifstream &, std::string &);

		static vector<float> getFloats(std::string);

		static Lighting* lightInsertion(std::string);

		static Sphere* sphereInsertion(std::ifstream &, std::string);

		static Plane* planeInsertion(std::ifstream &, std::string);

		static void parse_plane_finish(Plane *, std::string);

		static void parse_sphere_finish(Sphere *, std::string);

		static void parse_triangle_finish(Triangle *, std::string);

		static void parse_plane_pigment(Plane *, std::string);

		static void parse_sphere_pigment(Sphere *, std::string);

		static void parse_triangle_pigment(Triangle *, std::string);

		static Triangle* triangleInsertion(std::ifstream &, std::string);

};