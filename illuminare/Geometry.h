#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Basics.h"
//#include "LocalLight.h"
#include "Texture.h"
//#include "Scene.h"

class Geometry
{
public:
	virtual void Intersect(Ray &r, point &p, point &n, bool &valid) = 0;
	virtual void Intersect(Ray &r, point &p, point &n, bool &valid, Geometry *&obj) {Intersect(r, p, n, valid); obj = this;}
	double wr, wt, nr;
	cv::Scalar color;
	Texture *texture;
	virtual cv::Scalar ApplyTexture(point &p) = 0;
	Geometry() {texture = 0;}
};

class Ball : public Geometry
{
public:
	point Center;
	double Radius;
	void Intersect(Ray &r, point &p, point &n, bool &valid);
	cv::Scalar ApplyTexture(point &p);
};

class Plane : public Geometry
{
public:
	point n;
	double d;
	double distance(point p) {return point::DotProduct(n, p) + d;}
	void Intersect(Ray &r, point &p, point &n, bool &valid);
	cv::Scalar ApplyTexture(point &p);
	point O;		//for texture
	point x_axis;   //for texture
	point y_axis;	//for texture
};

class Triangle : public Geometry
{
public:
	point P[3];
	void Intersect(Ray &r, point &p, point &n, bool &valid);
	cv::Scalar ApplyTexture(point &p);
	point O;		//for texture
	point x_axis;   //for texture
	point y_axis;	//for texture
private:
	double det(point, point, point);
};

class pBox : public Geometry
{
public:
	point p1, p2;
	void Intersect(Ray &r, point &p, point &n, bool &valid);
	cv::Scalar ApplyTexture(point &p);
};


#endif