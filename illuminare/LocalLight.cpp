#include "LocalLight.h"
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

Scalar LocalLight::GetColor(Scene &scene, Geometry *obj, point &n, point &p, point &vp)
{
	double B = 0,G = 0,R = 0;
	Scalar color = obj -> texture ? obj -> ApplyTexture(p) : obj -> color;
	point L, V;
	n.Normalize();//perche'?
	//for (vector<point>::iterator i = Sources.begin(); i != Sources.end(); i++) {
	for (int i = 0; i < lnum; i++) {
		//L = (*i) - p;
		L = Sources[i]-p;
		L.Normalize();
		V = p - vp;
		V.Normalize();
		if (point::DotProduct(L, n) > 0 && !isShadow(scene, p, Sources[i])) {
			B += 0.8 * color[0] * abs(point::DotProduct(L, n));
			G += 0.8 * color[1] * abs(point::DotProduct(L, n));
			R += 0.8 * color[2] * abs(point::DotProduct(L, n));
		}
		//else {
			//cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<' '<<point::DotProduct(L, n)<<endl;
		//}
		B += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 20.0/255*color[0];//ambient 20
		G += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 20.0/255*color[1];
		R += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 20.0/255*color[2];
	}
	return Scalar(B, G, R);
}

bool LocalLight::isShadow(Scene &scene, point p, point light)
{
	point dir = light - p;
	dir.Normalize();
	Ray ray;
	ray.start = p;
	ray.direction = dir;
	point pi, ni;
	Geometry *obj = 0;
	scene.getIntersection(ray, pi, ni, obj);
	double dp = point::DotProduct(pi - light, light - p);
	if (point::DotProduct(pi - light, light - p) > 0.0001 || obj == 0 || point::Distance2(pi, p) < 0.0001)
		return false;
	else 
		return true;
}

void LocalLight::GetColor1(Scene &scene, Geometry *obj, point &n, point &p, point &vp, Scalar &res)
{
	double B = 0,G = 0,R = 0;
	Scalar color = obj -> texture ? obj -> ApplyTexture(p) : obj -> color;
	point L, V;
	n.Normalize();//perche'?
	//for (vector<point>::iterator i = Sources.begin(); i != Sources.end(); i++) {
	for (int i = 0; i < lnum; i++) {
		//L = (*i) - p;
		L = Sources[i]-p;
		L.Normalize();
		V = p - vp;
		V.Normalize();
		if (point::DotProduct(L, n) > 0 && !isShadow(scene, p, Sources[i])) {
			B += /*0.8 **/ color[0] * abs(point::DotProduct(L, n));
			G += /*0.8 **/ color[1] * abs(point::DotProduct(L, n));
			R += /*0.8 **/ color[2] * abs(point::DotProduct(L, n));
		}
		//else {
			//cout<<color[0]<<" "<<color[1]<<" "<<color[2]<<' '<<point::DotProduct(L, n)<<endl;
		//}
		B += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 70.0/255*color[0];
		G += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 70.0/255*color[1];
		R += 100 * std::pow(point::DotProduct(2*point::DotProduct(L,n) * n - L, V), 100) + 70.0/255*color[2];
	}
	res[0] = B;
	res[1] = G;
	res[2] = R;
}
