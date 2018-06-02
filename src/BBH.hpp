#ifndef BBH_H
#define BBH_H

#include "Box.hpp"

class BBH : public Box 
{
	public: 

		BBH(){};
		BBH(glm::vec3, glm::vec3);

		void Reset(glm::vec3);
		void AddPoint(glm::vec3);
		void AddBox(BBH &);
		glm::vec3 getCenter(){ return glm::vec3(0.f); };
};

#endif