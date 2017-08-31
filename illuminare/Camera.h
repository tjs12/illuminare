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
	void Project2(double x, double y, Ray &r, double Viewpoint_dx = 0, double Viewpoint_dy = 0);//������ߣ�����double��������û���ˣ���ͬ��
	double dx, dy;
	point Matrix[3];//����任����
	
};

#endif
