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

   struct less_than_0
   {
       inline bool operator() ( Object& struct1,  Object& struct2)
       {
           return (struct1.getCenter()[0] < struct2.getCenter()[0]);
       }
   };

   struct less_than_1
   {
       inline bool operator() ( Object& struct1,  Object& struct2)
       {
           return (struct1.getCenter()[1] < struct2.getCenter()[1]);
       }
   };

   struct less_than_2
   {
       inline bool operator() ( Object& struct1,  Object& struct2)
       {
           return (struct1.getCenter()[2] < struct2.getCenter()[2]);
       }
   };

   BBHTree();

   std::vector<Object *> objects;
   BNode* rootBox;

   void makeSDS(std::vector<Object *>, BNode*, int);  
   void sortObjects(std::vector<Object *> &, int);
	Object* treeDecend(BNode *, const ray &); 

};

#endif
