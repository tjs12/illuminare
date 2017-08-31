#include <iostream>
#include "Camera.h"
#include "RayTracer.h"
#include "Octree.h"
#include "Input.h"

#include <time.h>

#define DEPTH false
#define ANTIALIASE true
#define TESTSCENE true

using namespace std;
using namespace cv;

int main(int argn, char** argv)
{
	RayTracer rt;
	Camera c;
#ifdef TESTSCENE //使用内置场景
		Ball *b = new Ball;
		b -> Center = point(0.0, 0.0, 80.0);
		b -> Radius = 10;
		b -> color = Scalar(255,0,0);
		b -> wr = 0.2;
		b -> wt = 0;
		rt.scene.add(b);

		Plane *p = new Plane;
		p->n = point(0,-1,0);
		p->d = 20;
		p -> color = Scalar(100,100,100);
		p -> wr = 0.3;
		p -> wt = 0;
		p -> O = point(0,20,0);
		p -> x_axis = point(1,0,0);
		p -> y_axis = point(0,0,1);
		p -> texture = new Texture;
		Mat ptexture = imread("bianco-carrara_cd1.jpg"/*"marmoscuro.png"*/);
		p -> texture -> mat = &ptexture;
		p -> texture -> dx = 0.05;
		p -> texture -> dy = 0.05;
		rt.scene.add(p);

		Plane *p1 = new Plane;
		p1->n = point(0,0,-1);
		p1->d = 200;
		p1 -> color = Scalar(50,0,255);
		p1 -> wr = 0.1;
		p1 -> wt = 0;
		rt.scene.add(p1);

		Plane *p2 = new Plane;
		p2->n = point(0,0,1);
		p2->d = 400;
		p2 -> color = Scalar(100,100,100);
		p2 -> wr = 0.11;
		p2 -> wt = 0;
		rt.scene.add(p2);

		Plane *p3 = new Plane;
		p3->n = point(1,0,0);
		p3->d = 70;
		p3 -> color = Scalar(200,50,50);
		p3 -> wr = 0.01;
		p3 -> wt = 0;
		rt.scene.add(p3);

		Plane *p4 = new Plane;
		p4->n = point(-1,0,0);
		p4->d = 70;
		p4 -> color = Scalar(100,200,100);
		p4 -> wr = 0.11;
		p4 -> wt = 0;
		rt.scene.add(p4);

		Plane *p5 = new Plane;
		p5->n = point(0,1,0);
		p5->d = 70;
		p5 -> color = Scalar(200,200,200);
		p5 -> wr = 0;//.11;
		p5 -> wt = 0.5;
		p5 -> nr = 1;
		p5 -> O = point(0,-70,0);
		p5 -> x_axis = point(1,0,0);
		p5 -> y_axis = point(0,0,1);
		p5 -> texture = new Texture;
		Mat ptexture5 = imread("cielo.jpg");
		p5 -> texture -> mat = &ptexture5;
		p5 -> texture -> dx = 1;
		p5 -> texture -> dy = 1;
		rt.scene.add(p5);

		Plane *p6 = new Plane;
		p6->n = point(0,0,-1);
		p6->d = 190;
		p6 -> color = Scalar(200,50,50);
		p6 -> wr = 0;
		p6 -> wt = 0;
		p6 -> nr = 1;
		p6 -> texture = new Texture;
		p6 -> O = point(50, 100, 190);
		p6 -> x_axis = point(1, 0, 0);
		p6 -> y_axis = point(0, 1, 0);
		Mat ptexture6 = imread("20140507_180539.jpg");
		p6 -> texture -> mat = &ptexture6;
		p6 -> texture -> dx = 0.07;
		p6 -> texture -> dy = 0.07;
		rt.scene.add(p6);

		Ball *b1 = new Ball;
		b1 -> Center = point(3,0,50);
		b1 -> Radius = 3;
		b1 -> color = Scalar(0,255,0);
		b1 -> wr = 0.06;
		b1 -> wt = 0;
		rt.scene.add(b1);

		Ball *b2 = new Ball;
		b2 -> Center = point(-20,0,60);
		b2 -> Radius = 8;
		b2 -> color = Scalar(255,255,255);//(0,255,255);
		b2 -> wr = 0.2;
		b2 -> wt = 0.7;
		b2 -> nr = 1.05;
		rt.scene.add(b2);

		Ball *b3 = new Ball;
		b3 -> Center = point(20,9,120);
		b3 -> Radius = 4;
		b3 -> color = Scalar(200,107,200);//(0,255,255);
		b3 -> wr = 0;
		b3 -> wt = 0;
		b3 -> nr = 1.05;
		Mat text = imread("tex.bmp");
		b3 -> texture = new Texture;
		b3 -> texture -> dx = 0.001;
		b3 -> texture -> dy = 0.001;
		b3 -> texture -> mat = &text;
		rt.scene.add(b3);

		Triangle *t1 = new Triangle;
		t1 -> P[0] = point(-10, 20, 40);
		t1 -> P[1] = point(10, 20, 40);
		t1 -> P[2] = point(0, 0, 40);
		t1 -> color = Scalar(100, 200, 70);
		t1 -> wr = 0;
		t1 -> wt = 0;
		t1 -> nr = 1;
		procedure_Texture *pt = new procedure_Texture;
		t1 -> x_axis = point(1,0,0);
		t1 -> y_axis = point(0,1,0);
		t1 -> O = point(-10,20,40);
		t1 -> texture = pt;
		pt -> Type = 1;
		//rt.scene.add(t1);

		pBox *pb = new pBox;
		pb -> p1 = point(-30,20,25);
		pb -> p2 = point(-10, 10, 40);
		pb -> color = Scalar(255, 255, 200);
		pb -> wr = 0;
		pb -> wt = 0.1;
		pb ->nr = 1;
		//rt.scene.add(pb);

		Triangle *t2 = new Triangle, *t3 = new Triangle;
		t2 ->P[0] = point(1, 20, 30);t2->P[1]=point(9, 20, 20);t2->P[2]=point(5,0,25);	
		t3 ->P[0] = point(-12, 10, 30);t3->P[1]=point(-19, 10, 30);t3->P[2]=point(-15,0,31);
		t2 -> color  = Scalar(220,100,200);
		t2 -> texture = 0;
		t2 -> wr = 0;
		t2 -> wt = 0;
		t3 -> color  = Scalar(220,100,200);
		t3 -> texture = 0;
		t3 -> wr = 0;
		t3 -> wt = 0;
		Octree *ot = new Octree, *ot1 = new Octree, *ot2 = new Octree, *ot3 = new Octree, *ot4 = new Octree;
		//ot ->objects.add(pb);
		//rt.scene.add(ot);
		ot1 -> p1 = point(-11,51,0);
		ot1 -> p2 = point(50, -50, 40);
		//ot1 -> objects.add(t2);
		ot2 -> p1 = point(-50,51,0);
		ot2 -> p2 = point(-11, -50, 40);
		ot2 -> objects.add(t3);
		//ot2 -> objects.add(pb);
		ot3 -> p1 = point(-11,21,40);
		ot3 -> p2 = point(50, -50, 200);
		ot3 -> objects.add(b);
		ot3 -> objects.add(b3);
		ot3 -> objects.add(b1);
		//ot3 -> objects.add(t1);
		ot4 -> p1 = point(-50,21,40);
		ot4 -> p2 = point(-11, -50, 200);
		ot4 -> objects.add(b2);
		ot->children[0] = ot1;
		ot->children[1] = ot2;
		ot->children[2] = ot3;
		ot->children[3] = ot4;
		//rt.scene.add(t2);
		rt.scene.add(t3);

		Octree *Oct = new Octree;
		//Oct->GetObj("in.obj");
		//rt.scene.add(Oct);

		rt.MinWeight = 0.09;
		//rt.local.addLight(point(0, -30, 10));
		//rt.local.addLight(point(0, 0, -30));
		rt.local.addLight(point(-10,-60,-20));
		

#else //从文件读入场景
		Input::Read("in.txt", rt, c);
#endif

	c.dx = 0.025; //设置相机
	c.dy = 0.025;
#ifdef TESTSCENE
	c.Matrix[0] = point(1,0,0);
	c.Matrix[1] = point(0,1,0);
	c.Matrix[2] = point(0,0,1);
	c.ViewPoint = point(0,0,-20);
#endif

	Mat m = Mat::zeros(800, 800, CV_8UC3);

	time_t t0 = time(0); //计时

	Plane focal_plane;
	focal_plane.n = point(0, 0, 1);
	focal_plane.d = -60; //景深效果的焦平面

	for (int i = 0; i <= 800; i++) {
		for (int j = 0; j <= 800; j++) {

			
					if (i == 447 && j == 557) {
						int abj;
						abj = 0;
					}

			if (!ANTIALIASE) {
				if (!DEPTH) {
					Ray r;
					c.Project1(i - 400, j - 400, r);
					Scalar color = rt.RayTrace(r, 1);
					line(m, Point(i, j) , Point(i, j), color);
				}
				else {//景深
					const int volta = 15;//每次随机取volta个点
					Scalar color;
					Ray r0;
					point focal_intersection, fn, d1;
					bool fvalid;
					c.Project1(i - 400, j - 400, r0, 0, 0, false);
					focal_plane.Intersect(r0, focal_intersection, fn, fvalid);//寻找中心光线与焦平面的交点
					//d1 = point(point::DotProduct(c.Matrix[0],r0.direction), point::DotProduct(c.Matrix[1],r0.direction), point::DotProduct(c.Matrix[2],r0.direction));

					for (int k = 0; k < volta; k++) {//随机产生光线
						Ray r;
						point d1;
						double dx = rand() / (double)RAND_MAX - 0.5;
						double dy = rand() / (double)RAND_MAX - 0.5;
						//while ()
						//c.Project1(i - 400, j - 400, r, dx*0.04, dy*0.04);
						r.start = r0.start + point(dx * 1, dy * 1);
						d1 = focal_intersection - r.start;
						r.direction = point(point::DotProduct(c.Matrix[0],d1), point::DotProduct(c.Matrix[1],d1), point::DotProduct(c.Matrix[2],d1));
						r.direction.Normalize();
						color += rt.RayTrace(r, 1);
					}
					color /= volta;
					line(m, Point(i, j) , Point(i, j), color);
				}
			}
			else {
				if (!DEPTH) {
					Ray r, r1, r2, r3;
					c.Project1(i - 400, j - 400, r);
					Scalar color = rt.RayTrace(r, 1);//get the color of the point

					point n_p, n_n;
					//Scalar color1, color2;
					Geometry *obj1, *obj2, *obj3, *obj4;
					c.Project2((i - 400) - 0.2, j - 400 - 0.2, r);//选取投影屏幕上四周围的点，发射光线
					c.Project2((i - 400) + 0.2, j - 400 + 0.2, r1);
					c.Project2((i - 400) - 0.2, j - 400 + 0.2, r2);
					c.Project2((i - 400) + 0.2, j - 400 - 0.2, r3);
					rt.scene.getIntersection(r,n_p, n_n, obj1);//与物体相交
					rt.scene.getIntersection(r1,n_p, n_n, obj2);
					rt.scene.getIntersection(r2,n_p, n_n, obj3);
					rt.scene.getIntersection(r3,n_p, n_n, obj4);
					//color1 = rt.RayTrace(r, rt.MinWeight);
					//color2 = rt.RayTrace(r1, rt.MinWeight);
					if (obj1 != obj2 || obj3 != obj4 || obj1 != obj3 || obj1 != obj4 || obj2 != obj3 || obj2 != obj4) {//if the ray hits a edge
						color += rt.RayTrace(r, 1);
						color += rt.RayTrace(r1, 1);
						color += rt.RayTrace(r2, 1);
						color += rt.RayTrace(r3, 1);
						color /= 5;
					}
					line(m, Point(i, j) , Point(i, j), color);
				}
				else {
					const int volta = 6;
					Scalar color;
					Ray r0;
					point focal_intersection, fn;
					bool fvalid;
					c.Project1(i - 400, j - 400, r0);
					focal_plane.Intersect(r0, focal_intersection, fn, fvalid);

					for (int k = 0; k < volta; k++) {
						Scalar color1(0, 0, 0);
						Ray r;
						double dx = rand() / (double)RAND_MAX - 0.5;
						double dy = rand() / (double)RAND_MAX - 0.5;
						while (dx * dx + dy * dy > 0.25) {
							dx = rand() / (double)RAND_MAX - 0.5;
							dy = rand() / (double)RAND_MAX - 0.5;
						}
						//c.Project1(i - 400, j - 400, r, dx*0.04, dy*0.04);
						r.start = r0.start + point(dx * 0.5, dy * 0.5);
						r.direction = focal_intersection - r.start;
						r.direction.Normalize();
						color1 += rt.RayTrace(r, 1);
						r.start = r0.start + point(dx * 0.5, dy * 0.5) + point(0.05, 0.05);
						color1 += rt.RayTrace(r, 1);
						r.start = r0.start + point(dx * 0.5, dy * 0.5) - point(0.05, 0.05);
						color1 += rt.RayTrace(r, 1);
						color += color1 / 3.0;
					}
					color /= volta;
					line(m, Point(i, j) , Point(i, j), color);
				}
			}
		}
	}

	cout<<time(0) - t0;
	if (argv[2][0] != '0') {
		namedWindow( "Display window", WINDOW_AUTOSIZE );
		imshow("Display window", m);
	}
	//imwrite("r.bmp",m);
	imwrite(argv[1], m);
	if (argv[2][0] != '0') 
		waitKey(0);
	return 0;
}