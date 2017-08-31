#ifndef INPUT_H
#define INPUT_H

#include "Geometry.h"
#include "Octree.h"
#include "RayTracer.h"
#include "Camera.h"

class Input
{
public:
	static void Read(char *filename, RayTracer &rt, Camera &camera);
};

#endif