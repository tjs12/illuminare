#include "Geometry.h"
#include <iostream>
#define PI 3.1415926535897932384626433832795

using namespace std;

void Ball::Intersect(Ray &r, point &p, point &n, bool &valid)
{
	double loc2 = point::Distance2(r.start, Center);
	double tca = point::DotProduct(Center - r.start, r.direction);
	double thc2 = Radius*Radius - loc2 + tca*tca;
	valid = true;
	if (thc2 < -0.0001) {
		valid = false;
	}
	else if (thc2 >= -0.0001 && thc2 <= 0.0001) {
		p = Center + tca * r.direction;
		n = 1/(double)Radius * (p - Center);
	}
	else if (thc2 > 0.0001) {
		double t1 = tca + sqrt(thc2);
		double t2 = tca - sqrt(thc2);
		point p1 = r.start + t1 * r.direction;
		point p2 = r.start + t2 * r.direction;
		if (point::Distance2(p1, r.start) < 0.0001 && point::Distance2(p2, r.start) > 0.0001 && t2 > 0.0001)
			p = p2;
		else if (point::Distance2(p2, r.start) < 0.0001 && point::Distance2(p1, r.start) > 0.0001 && t1 > 0.0001)
			p = p1;
		else if (point::DotProduct((p2 - p1), (p2 - r.start)) > 0.0001 && t1 > 0.0001)
			p = p1;
		else if (t2 > 0.0001)
			p = p2;
		else 
			valid = false;
		n = 1.0/Radius * (p - Center);//cout<<"b\n";
	}
	/*if (point::Distance2(r.start, Center) < Radius * Radius + 0.0001)
		n = -1.0 * n;*/
}

cv::Scalar Ball::ApplyTexture(point &p)
{
	if (!texture) return color;
	double dxy2 = (p.x - Center.x)*(p.x - Center.x) + (p.y - Center.y)*(p.y - Center.y);
	double phi = acos(sqrt(dxy2/Radius/Radius));
	point dirtheta = point(Center.x, Center.y, p.z) - p;
	dirtheta.Normalize();
	double theta = point::DotProduct(point(1,0,0), dirtheta);
	return texture ->getColor(theta / PI, phi / 2 / PI);
}


void Plane::Intersect(Ray &r, point &p, point &n, bool &valid) {
	if (abs(point::DotProduct(this -> n, r.direction)) < 0.0001) {
		valid = false;
		return;
	}
	double t = -(d + point::DotProduct(this -> n, r.start))/point::DotProduct(this -> n, r.direction);
	if (t > 0.0001) {
		valid = true;
		p = r.start + t * r.direction;
		n = this -> n;
		//std::cout << "p" << p.x << ' ' << p.y<<endl;
		//if (point::DotProduct(this ->n, p)
		if (point::Distance2(p,r.start)<0.0001) valid = false;
	}
	else 
		valid = false;
}

cv::Scalar Plane::ApplyTexture(point &p)
{
	if (!texture) return color;
	point p1 = p - O;
	double u = point::DotProduct(p1, x_axis);
	double v = point::DotProduct(p1, y_axis);
	return texture -> getColor(u, v);
}

double Triangle::det(point p1, point p2, point p3)
{
	return (p1.x * p2.y * p3.z + p1.y * p2.z * p3.x + p1.z * p2.x * p3.y 
		  - p1.z * p2.y * p3.x - p1.y * p2.x * p3.z - p1.x * p2.z * p3.y);
}

void Triangle::Intersect(Ray &r, point &p, point &n, bool &valid)
{
	point normal = point::VecProduct(P[0] - P[1], P[0] - P[2]);
	point e1 = P[0] - P[1], e2 = P[0] - P[2], s = P[0] - r.start;
	double t = det(s, e1, e2) / det(r.direction, e1, e2);
	double beta = det(r.direction, s, e2) / det(r.direction, e1, e2);
	double gamma = det(r.direction, e1, s) / det(r.direction, e1, e2);
	if (t > 0.0001 && beta >= 0.0000 && beta <= 1 && gamma >=0.0000 && gamma <= 1 && beta + gamma <= 1) {
		valid = true;
		p = (1 - beta - gamma) * P[0] + beta * P[1] + gamma * P[2];
		if (point::Distance2(p, r.start) < 0.0001)
			valid = false;
		n = normal;
		point test = r.start + t* r.direction;//p = test;
		n.Normalize();
		//if (point::DotProduct(n, r.direction) > 0.0001) n = -1 * n;

	}
	else 
		valid = false;
}

cv::Scalar Triangle::ApplyTexture(point &p)
{
	if (!texture) return color;
	point p1 = p - O;
	double u = point::DotProduct(p1, x_axis);
	double v = point::DotProduct(p1, y_axis);
	return texture -> getColor(u, v);
}
/*
void pBox::Intersect(Ray &r, point &p, point &n, bool &valid)
{
	valid = false;
	if (r.start.x >= p1.x - 0.0001 && r.start.y <= p1.y + 0.0001 && r.start.z >= p1.z - 0.0001 && r.start.x <= p2.x + 0.0001 && r.start.y >= p2.y - 0.0001  && r.start.z <= p2.z + 0.0001)
		return;
	double t[6];
	double d[6];
	d[0] = point::DotProduct(point(0,0,-1), r.direction);
	d[1] = point::DotProduct(point(0,1,0), r.direction);
	d[2] = point::DotProduct(point(1,0,0), r.direction);
	d[3] = point::DotProduct(point(0,0,1), r.direction);
	d[4] = point::DotProduct(point(0,-1,0), r.direction);
	d[5] = point::DotProduct(point(-1,0,0), r.direction);
	//t[0] = -(p1.z + point::DotProduct(point(0,0,-1), r.start))/point::DotProduct((0,0,-1), r.direction);
	//t[1] = -(-p1.y + point::DotProduct(point(0,1,0), r.start))/point::DotProduct((0,1,0), r.direction);
	//t[2] = -(-p1.x + point::DotProduct(point(1,0,0), r.start))/point::DotProduct((1,0,0), r.direction);
	//t[3] = -(-p2.z + point::DotProduct(point(0,0,1), r.start))/point::DotProduct((0,0,1), r.direction);
	//t[4] = -(p2.y + point::DotProduct(point(0,-1,0), r.start))/point::DotProduct((0,-1,0), r.direction);
	//t[5] = -(p2.x + point::DotProduct(point(-1,0,0), r.start))/point::DotProduct((-1,0,0), r.direction);
	t[0] = (p1.z - r.start.z) / r.direction.z;
	t[1] = (p1.y - r.start.y) / r.direction.y;
	t[2] = (p1.x - r.start.x) / r.direction.x;
	t[3] = (p2.z - r.start.z) / r.direction.z;
	t[4] = (p2.y - r.start.y) / r.direction.y;
	t[5] = (p2.x - r.start.x) / r.direction.x;
	double maxt = 0;
	int maxtn = -1;
	for (int i = 0; i < 6; i++) {
		//if ((maxt > t[i] || maxtn == -1) && t[i] > 0 && abs(d[i]) > 0.0001){
		//	maxt = t[i];
		//	maxtn = i;
		//}
		p = r.start + t[i] * r.direction;
		if (p.x >= p1.x - 0.0001 && p.y <= p1.y + 0.0001 && p.z >= p1.z - 0.0001 && p.x <= p2.x + 0.0001 && p.y >= p2.y - 0.0001  && p.z <= p2.z + 0.0001 && point::Distance2(r.start, p) > 0.0001) {
			if (maxt > t[i] || maxtn == -1) {
				maxt = t[i];
				maxtn = i;
				valid = true;
				switch (i) {
				case 0:
					n = point(0,0,-1);break;
				case 1:
					n = point(0,1,0);break;
				case 2:
					n = point(-1,0,0);break;
				case 3:
					n = point(0,0,1);break;
				case 4:
					n = point(0,-1,0);break;
				case 5:
					n = point(1,0,0);break;	
				}
			}
		}
	}
	
	//p = r.start + maxt * r.direction;
	//if (maxt != 0) {
	//		int abc;
	//		abc = 1;
	//		//cout << p.x << ' ' << p.y << ' '<<p.z<< endl;
	//}
	//if (p.x >= p1.x && p.y <= p1.y && p.z >= p1.z && p.x <= p2.x && p.y >= p2.y && p.z <= p2.z && maxtn != -1) {
	//	valid = true;
	//	switch (maxtn) {
	//	case 0:
	//		n = (0,0,-1);break;
	//	case 1:
	//		n = (0,1,0);break;
	//	case 2:
	//		n = (-1,0,0);break;
	//	case 3:
	//		n = (0,0,1);break;
	//	case 4:
	//		n = (0,-1,0);break;
	//	case 5:
	//		n = (1,0,0);break;	
	//	}
	//}
	//else 
	//	valid = false;

}
*/
void pBox::Intersect(Ray &r, point &p, point &n, bool &valid)
{
	valid = false;
	//if (r.start.x >= p1.x - 0.0001 && r.start.y <= p1.y + 0.0001 && r.start.z >= p1.z - 0.0001 && r.start.x <= p2.x + 0.0001 && r.start.y >= p2.y - 0.0001  && r.start.z <= p2.z + 0.0001)
	//	return;
	double t[6];
	double d[6];
	d[0] = r.direction.z;
	d[1] = r.direction.y;
	d[2] = r.direction.x;
	d[3] = r.direction.z;
	d[4] = r.direction.y;
	d[5] = r.direction.x;
	t[0] = (p1.z - r.start.z) / r.direction.z;
	t[1] = (p1.y - r.start.y) / r.direction.y;
	t[2] = (p1.x - r.start.x) / r.direction.x;
	t[3] = (p2.z - r.start.z) / r.direction.z;
	t[4] = (p2.y - r.start.y) / r.direction.y;
	t[5] = (p2.x - r.start.x) / r.direction.x;
	double maxt = 0;
	int maxtn = -1;
	for (int i = 0; i < 6; i++) {
		p = r.start + t[i] * r.direction;


		bool inplane;
		switch (i) {
		case 0:
			inplane = p.x >= p1.x && p.x <= p2.x && p.y <= p1.y && p.y >= p2.y;break;
		case 1:
			inplane = p.x >= p1.x && p.x <= p2.x && p.z >= p1.z && p.z <= p2.z;break;
		case 2:
			inplane = p.z >= p1.x && p.z <= p2.x && p.y <= p1.y && p.y >= p2.y;break;
		case 3:
			inplane = p.x >= p1.x && p.x <= p2.x && p.y <= p1.y && p.y >= p2.y;break;
		case 4:
			inplane = p.x >= p1.x && p.x <= p2.x && p.z >= p1.z && p.z <= p2.z;break;
		case 5:
			inplane = p.z >= p1.x && p.z <= p2.x && p.y <= p1.y && p.y >= p2.y;break;
		}
		switch (i) {
		case 0:
			n = point(0,0,-1);break;
		case 1:
			n = point(0,1,0);break;
		case 2:
			n = point(-1,0,0);break;
		case 3:
			n = point(0,0,1);break;
		case 4:
			n = point(0,-1,0);break;
		case 5:
			n = point(1,0,0);break;	
		}
		if (inplane && (maxt > t[i] || maxtn == -1)) {
			maxt = t[i];
			maxtn = i;
			valid = true;
		}
	}

	
	


}


cv::Scalar pBox::ApplyTexture(point &p)
{
	return color;
}

