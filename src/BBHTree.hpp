#ifndef BBHTREE_H_
#define BBHTREE_H_

#include <iostream>
#include <vector>

#include "BBH.hpp"
#include "Box.hpp"

class BBHTree 
{
   public:

   struct BNode 
   {
      BBH boundBox;
      std::vector<Object *> objs;
      BNode* right = NULL;
      BNode* left = NULL;
   };

   

   BBHTree();

   std::vector<Object *> objects;
   BNode* rootBox;

   void makeSDS(std::vector<Object *>, BNode*, int);  
   void sortObjects(std::vector<Object *> &, int);
	std::vector<Object *> treeDecend(BNode *, const ray &); 

};

#endif
