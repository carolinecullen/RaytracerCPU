#include "BBH.hpp"
#include <algorithm>
#include <vector>

using namespace glm;

BBH::BBH(vec3 min, vec3 max) 
{
    updateBox(min, max);
}


void BBH::AddPoint(vec3 point) 
{
   if(!this->init()) 
   {
      updateBox(point, point);
      return;
   }

   this->min.x = std::min(point.x, std::min(this->min.x, this->max.x));
   this->min.y = std::min(point.y, std::min(this->min.y, this->max.y));
   this->min.z = std::min(point.z, std::min(this->min.z, this->max.z));
   this->max.x = std::max(point.x, std::max(this->min.x, this->max.x));
   this->max.y = std::max(point.y, std::max(this->min.y, this->max.y));
   this->max.z = std::max(point.z, std::max(this->min.z, this->max.z));

   updateBox(this->min, this->max);
}

void BBH::Reset(vec3 point)
{
    this->min = this->max = point;
}

void BBH::AddBox(BBH *box) 
{

   if (!this->init()) {
      updateBox(box->min, box->max);
      return;
   }
   
   this->min.x = std::min(this->min.x, std::min(box->max.x, box->min.x));
   this->min.y = std::min(this->min.y, std::min(box->max.y, box->min.y));
   this->min.z = std::min(this->min.z, std::min(box->max.z, box->min.z));
   this->max.x = std::max(this->max.x, std::max(box->max.x, box->min.x));
   this->max.y = std::max(this->max.y, std::max(box->max.y, box->min.y));
   this->max.z = std::max(this->max.z, std::max(box->max.z, box->min.z));

   updateBox(this->min, this->max);
}

