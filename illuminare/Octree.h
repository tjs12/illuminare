#ifndef OCTREE_H
#define OCTREE_H

#include "Scene.h"
#include "SimpleObject.h"

using namespace SimpleOBJ;

class Octree : public pBox
{
public:
	Octree(int n_l = 5, int n_c = 8) : nc(n_c) {children = new Octree*[n_c];memset(children, 0, sizeof(Octree*)*8);/*motion = point(0,0,0);*/}
	int nc;
	Scene objects;//包含的物体，只有叶子结点才用到
	Octree **children;//子树
	void Intersect(Ray &r, point &p, point &n, bool &valid, Geometry *&obj);
	void GetObj(char *file);
	void GetObj1(int, int, Array<int, 3>*, Vec3f *);
	//point motion;
};

#endif