#include "Camera.h"
#include "Basics.h"

Ray &Camera::Project(int x, int y)
{
	Ray *re = new Ray;
	point incamera = point(x * dx, y * dy, 0.0) - ViewPoint;
	incamera.Normalize();
	re -> direction = point(point::DotProduct(Matrix[0],incamera), point::DotProduct(Matrix[1],incamera), point::DotProduct(Matrix[2],incamera));
	//re -> start = point(point::DotProduct(Matrix[0],ViewPoint), point::DotProduct(Matrix[1],ViewPoint), point::DotProduct(Matrix[2],ViewPoint));//optimize?
	re -> start = ViewPoint;
	return *re;
}


void Camera::Project1(int x, int y, Ray &r, double Viewpoint_dx, double Viewpoint_dy, bool to_world)
{
	point incamera = point(x * dx, y * dy, 0.0) - ViewPoint - point(Viewpoint_dx, Viewpoint_dy);
	incamera.Normalize();
	if (to_world) r.direction = 
		point(point::DotProduct(Matrix[0],incamera), point::DotProduct(Matrix[1],incamera), point::DotProduct(Matrix[2],incamera));
	else 
		r.direction = incamera;
	//r.start = point(point::DotProduct(Matrix[0],ViewPoint), point::DotProduct(Matrix[1],ViewPoint), point::DotProduct(Matrix[2],ViewPoint));//optimize?
	r.start = ViewPoint;
}


void Camera::Project2(double x, double y, Ray &r, double Viewpoint_dx, double Viewpoint_dy)
{
	point incamera = point(x * dx, y * dy, 0.0) - ViewPoint - point(Viewpoint_dx, Viewpoint_dy);
	incamera.Normalize();
	r.direction = point(point::DotProduct(Matrix[0],incamera), point::DotProduct(Matrix[1],incamera), point::DotProduct(Matrix[2],incamera));
	//r.start = point(point::DotProduct(Matrix[0],ViewPoint), point::DotProduct(Matrix[1],ViewPoint), point::DotProduct(Matrix[2],ViewPoint));//optimize?
	r.start = ViewPoint;
}

