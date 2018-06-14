#include "BBHTree.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include <algorithm>
using namespace std;
using namespace glm;


BBHTree::BBHTree() 
{
   this->rootBox = new BNode;
}

void BBHTree::makeSDS(vector<Object *> objs, BNode *cur, int axis) 
{
    if (objs.size() <= 1) 
    {
        cur->objs = objs;
        BBH* bbox = objs[0]->makeBoundingBox();
        cur->boundBox.AddBox(*bbox);
        return;
    }

    sortObjects(objs, axis);

    cur->objs = objs;
    cur->left = new BNode;
    cur->right = new BNode;

    vector<Object *> left_half(objs.begin(), (objs.begin()+objs.size()/2));
    makeSDS(left_half, cur->left, (axis+1) % 3);

    vector<Object *> right_half((objs.begin()+objs.size()/2), objs.end());
    makeSDS(right_half, cur->right, (axis+1) % 3);

    BBH newBox = makeBoundBox(objs, axis);
    cur->boundBox = newBox;
}

BBH BBHTree::makeBoundBox(vector<Object *> objs, int axis)
{
    BBH allBox;
    
    for (int i = 0; i < objs.size(); i++)
    {
        BBH newBox;
        if(objs[i]->type == "Sphere")
        {
            Sphere* sptr = (Sphere *)objs[i];
            newBox.Reset(sptr->center - sptr->radius);
            newBox.AddPoint(sptr->center + sptr->radius);

            if (newBox.init()) 
            {
                std::vector<vec3> corners;
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.max.z));

                newBox.min = vec3(-numeric_limits<float>::max());
                newBox.max = vec3( numeric_limits<float>::max());

                for (int i = 0; i < 8; i++) 
                {
                    corners[i] = vec3(sptr->M * vec4(corners[i], 1.f));
                    newBox.AddPoint(corners[i]);
                }

                newBox.updateBox(newBox.min, newBox.max);
            }
            allBox.AddBox(newBox);
        }
        else if(objs[i]->type == "Triangle")
        {
            Triangle* tptr = (Triangle *)objs[i];
            newBox.Reset(tptr->A);
            newBox.AddPoint(tptr->B);
            newBox.AddPoint(tptr->C);

            if (newBox.init()) 
            {
                std::vector<vec3> corners;
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.max.z));

                newBox.min = vec3(-numeric_limits<float>::max());
                newBox.max = vec3( numeric_limits<float>::max());

                for (int i = 0; i < 8; i++) 
                {
                    corners[i] = vec3(tptr->M * vec4(corners[i], 1.f));
                    newBox.AddPoint(corners[i]);
                }

                newBox.updateBox(newBox.min, newBox.max);
            }
            allBox.AddBox(newBox);
        }
        else
        {
            Box* bptr = (Box *)objs[i];
            newBox.AddPoint(bptr->min);
            newBox.AddPoint(bptr->max);

            if (newBox.init()) 
            {
                std::vector<vec3> corners;
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.min.x, newBox.max.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.min.y, newBox.max.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.min.z));
                corners.push_back(vec3(newBox.max.x, newBox.max.y, newBox.max.z));

                newBox.min = vec3(-numeric_limits<float>::max());
                newBox.max = vec3( numeric_limits<float>::max());

                for (int i = 0; i < 8; i++) 
                {
                    corners[i] = vec3(bptr->M * vec4(corners[i], 1.f));
                    newBox.AddPoint(corners[i]);
                }

                newBox.updateBox(newBox.min, newBox.max);
            }
            allBox.AddBox(newBox);
        }
    }
    return allBox;
}
 
void BBHTree::sortObjects(vector<Object *> &objs, int axis) 
{
   if (axis == 0)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[0] > b->getCenter()[0]; 
        });
   }
   else if (axis == 1)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[1] > b->getCenter()[1]; 
        });
   }
   else if (axis == 2)
   {
    std::sort(objs.begin(), objs.end(), [](Object* a, Object* b) -> bool
        { 
            return a->getCenter()[2] > b->getCenter()[2]; 
        });
   }
    

}

vector<Object *> BBHTree::treeDecend(BNode *node, const ray &ray) 
{
	if (node->objs.size() == 1) 
    {
		return node->objs;
	}
	
	if (node->boundBox.intersect(ray) != -1) 
    {
		if (node->left != NULL) 
        {
            if (node->left->boundBox.intersect(ray) != -1) 
            {
			    vector<Object*> lReturn = treeDecend(node->left, ray);
                if (node->right != NULL) 
                {
                    if (node->right->boundBox.intersect(ray) != -1) 
                    {
                        // cout << "Bounding box in right subtree intersection: " << endl;
                        // cout << "--- max:" << node->right->boundBox.max.x << " " << node->right->boundBox.max.y << " " << node->right->boundBox.max.z << " " << endl;
                        // cout << "--- min:" << node->right->boundBox.min.x << " " << node->right->boundBox.min.y << " " << node->right->boundBox.min.z << endl << endl;

                        vector<Object*> rReturn = treeDecend(node->right, ray);
                        rReturn.insert(rReturn.end() , lReturn.begin(), lReturn.end() );
                        return rReturn;
                    }
                    else
                    {
                        // cout << "Bounding box in left tree interstion but no right subtree intersection: " << endl;
                        // cout << "--- max:" << node->left->boundBox.max.x << " " << node->left->boundBox.max.y << " " << node->left->boundBox.max.z << endl;
                        // cout << "--- min:" << node->left->boundBox.min.x << " " << node->left->boundBox.min.y << " " << node->left->boundBox.min.z << endl << endl;
                        return lReturn;
                    }
                }
                else
                {
                    // cout << "Bounding box in left tree interstion cuz right is null: " << endl;
                    // cout << "--- max:" << node->left->boundBox.max.x << " " << node->left->boundBox.max.y << " " << node->left->boundBox.max.z << endl;
                    // cout << "--- min:" << node->left->boundBox.min.x << " " << node->left->boundBox.min.y << " " << node->left->boundBox.min.z << endl << endl;
                    return lReturn;
                }
            }
            else if (node->right != NULL) 
            {
                if (node->right->boundBox.intersect(ray) != -1) 
                {
                    // cout << "Bounding box no left tree interstion but right subtree intersection: " << endl;
                    // cout << "--- max:" << node->right->boundBox.max.x << " " << node->right->boundBox.max.y << " " << node->right->boundBox.max.z << endl;
                    // cout << "--- min:" << node->right->boundBox.min.x << " " << node->right->boundBox.min.y << " " << node->right->boundBox.min.z << endl << endl;
                    return treeDecend(node->right, ray);
                }
                else
                {
                    // cout << "Right node exists but no intersections: " << endl;
                    // cout << "--- max:" << node->boundBox.max.x << " " << node->boundBox.max.y << " " << node->boundBox.max.z << " " << endl;
                    // cout << "--- min:" << node->boundBox.min.x << " " << node->boundBox.min.y << " " << node->boundBox.min.z << " " << endl << endl;
                    return node->objs;
                }
            }
            else
            {
                // cout << "left tree is not null but no intersections: " << endl;
                // cout << "--- max:" << node->boundBox.max.x << " " << node->boundBox.max.y << " " << node->boundBox.max.z << endl;
                // cout << "--- min:" << node->boundBox.min.x << " " << node->boundBox.min.y << " " << node->boundBox.min.z << endl << endl;
                return node->objs;
            }
		}
        if (node->right != NULL) 
        {
            if (node->right->boundBox.intersect(ray) != -1) 
            {
                // cout << "right subtrees intersection: " << endl;
                // cout << "--- max:" << node->right->boundBox.max.x << " " << node->right->boundBox.max.y << " " << node->right->boundBox.max.z << endl;
                // cout << "--- min:" << node->right->boundBox.min.x << " " << node->right->boundBox.min.y << " " << node->right->boundBox.min.z << endl << endl;
                return treeDecend(node->right, ray);
            }
            else
            {
                // cout << "right subtrees is not null but no intersection: " << endl;
                // cout << "--- max:" << node->boundBox.max.x << " " << node->boundBox.max.y << " " << node->boundBox.max.z << endl;
                // cout << "--- min:" << node->boundBox.min.x << " " << node->boundBox.min.y << " " << node->boundBox.min.z << endl << endl;
                return node->objs;
            }
        }
	}
    else
    {
        // cout << "both subtrees are null: " << endl;
        // cout << "--- max:" << node->boundBox.max.x << " " << node->boundBox.max.y << " " << node->boundBox.max.z << endl;
        // cout << "--- min:" << node->boundBox.min.x << " " << node->boundBox.min.y << " " << node->boundBox.min.z << endl << endl;
        return node->objs;
    }

    vector<Object *> nothing;
	return nothing;
}


