#ifndef CAMERA_H
#define CAMERA_H

#include "Geometry.h"

class Camera
{
public:
	point ViewPoint;
	//Plane ViewArea;
	Ray &Project(int x, int y);
	void Project1(int x, int y, Ray &r, double Viewpoint_dx = 0, double Viewpoint_dy = 0, bool to_world = true);
	void Project2(double x, double y, Ray &r, double Viewpoint_dx = 0, double Viewpoint_dy = 0);//发射光线；后面double两个参数没用了，上同。
	double dx, dy;
	point Matrix[3];//坐标变换矩阵
	
};

#endif
