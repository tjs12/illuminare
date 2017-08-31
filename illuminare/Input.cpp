#include "Input.h"
#include <fstream>

using namespace std;

void Input::Read(char *filename, RayTracer &rt, Camera &camera)
{
	ifstream fin(filename);
	fin >> rt.MinWeight >> camera.ViewPoint.x >> camera.ViewPoint.y >> camera.ViewPoint.z;
	for (int i = 0; i < 3; i++)
		fin >> camera.Matrix[i].x >> camera.Matrix[i].y >> camera.Matrix[i].z;
	int n;
	fin >> n;
	Scene &scene = rt.scene;
	point p;
	for (int i = 0; i < n; i++) {
		fin >> p.x >> p.y >> p.z;
		rt.local.addLight(p);
	}
	fin >> n;
	int type;
	Geometry *g;
	for (int i = 0; i < n; i++) {
		type = -1;
		//while (type < 'a' || type > 'z') fin >> type;
		fin >> type;
		g = 0;
		Plane *p;
		Ball *b;
		Triangle *t;
		pBox *pb;
		switch (type) {
		case 0: //'p'
			p = new Plane;
			fin >> (p -> n.x) >> (p -> n.y) >> (p -> n.z) >> (p -> d);
			fin >> p -> O.x >> p -> O.y >> p -> O.z >> p -> x_axis.x >> p -> x_axis.y >> p -> x_axis.z >> p -> y_axis.x >> p -> y_axis.y >> p -> y_axis.z;
			g = p;
			break;
		case 1://'b'
			b = new Ball;
			fin >> b -> Center.x >> b -> Center.y  >> b -> Center.z >> b -> Radius;
			g = b;
			break;
		case 2://'t'
			t = new Triangle;
			fin >> t -> P[0].x >> t -> P[0].y >> t -> P[0].z >> t -> P[1].x >> t -> P[1].y >> t -> P[1].z >> t -> P[2].x >> t -> P[2].y >> t -> P[2].z;
			fin >> t -> O.x >> t -> O.y >> t -> x_axis.x >> t -> x_axis.y >> t -> x_axis.z >> t -> y_axis.x >> t -> y_axis.y >> t -> y_axis.z;
			g = t;
			break;
		case 3://'r'
			pb = new pBox;
			fin >> pb -> p1.x >> pb -> p1.y >> pb -> p1.z >> pb -> p2.x >> pb -> p2.y >> pb -> p2.z;
			g = pb;
			break;
		}
		fin >> g -> color[0] >> g -> color[1] >> g -> color[2] >> g -> wr >> g -> wt >> g -> nr;
		int temp;
		fin >> temp;
		if (temp == 0) {
			g -> texture = 0;
		}
		else if (temp == 1) {
			char texturefile[100];
			g -> texture = new Texture;
			fin >> texturefile >> g -> texture -> dx >> g -> texture -> dy;
			g -> texture -> mat = new cv::Mat();
			*(g -> texture -> mat) = cv::imread(texturefile);
		}
		else if (temp == 2) {
			procedure_Texture *pt = new procedure_Texture;
			fin >> pt -> Type;
			g -> texture = pt;
		}
		scene.add(g);
	}
	fin.close();
}