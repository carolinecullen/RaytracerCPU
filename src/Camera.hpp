#include <string>
#include <sstream>
#include <glm/glm.hpp>

class Camera
{
	public:

		glm::vec3 lookat;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 location;

		Camera();
		void printCamera();
};