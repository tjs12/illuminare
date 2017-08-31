#ifndef TEXTURE_H
#define TEXTURE_H

#include <opencv2\core\core.hpp>
#include <cmath>

class Texture
{
public:
	cv::Mat *mat;
	double dx, dy;
	virtual cv::Scalar getColor(double u, double v) 
	{
		int x = abs((int)(u/dx)%mat->cols), y = abs((int)(v/dy)%mat->rows);
		//if (x < 0) x += 256;
		//if (y < 0) y += 256;
		//if (x >= 0 && (int)(u/dx)%256 <= 255 && y>=0 && ((int)(v/dy))%256<=255) {
			return cv::Scalar(mat->at<cv::Vec3b>(y, x)[0],
				mat->at<cv::Vec3b>(y, x)[1],
				mat->at<cv::Vec3b>(y, x)[2]);
		//}
		//else
		//	return cv::Scalar(100,100,100);
		/*return cv::Scalar(mat->at<cv::Vec3b>(100, 200)[0],
			mat->at<cv::Vec3b>(100, 200)[1],
			mat->at<cv::Vec3b>(100, 200)[2]);*/
	}
};

class procedure_Texture : public Texture
{
public:
	int Type; // 0 - marmo/marble; 1 - legno/wood
	cv::Scalar getColor(double u, double v)
	{
		cv::Scalar color;
		if (Type == 0) {//marble
			color[0] = cos(/*u +*/ Perlin(u, v)) * 127.5 + 127.5;
			color[1] = cos(/*u +*/ Perlin(u, v)) * 127.5 + 127.5;
			color[2] = cos(/*u +*/ Perlin(u, v)) * 127.5 + 127.5;
		}
		else if (Type == 1) {//wood
			double g = Perlin(u, v) * 0.7;
			int ig = g > 0 ? (int)g : (int)g - 1;

			color[0] = (g - ig) * (53 - 23) + 23;
			color[1] = (g - ig) * (87 - 67) + 67;
			color[2] = (g - ig) * (140 - 119) + 119;
		}
		return color;
	}
private:
	double int_noise(int x, int y) //random
	{
		int n = x + y * 57;
		n = (n<<13) ^ n;
		return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 2147483647) / 1073741824.0);    
	}
	double InterpolatedNoise(double x, double y)
	{
		if (x < 0) x=-x;
		if (y < 0) y=-y;
		double v1 = int_noise((int)x, (int)y), v2 = int_noise((int)x + 1, (int)y),
		    v3 = int_noise((int)x, (int)y + 1), v4 = int_noise((int)x + 1, (int)y + 1);
		double i1 = (v2 - v1) * (x - int(x)) + v1, 
			   i2 = (v4 - v3) * (x - int(x)) + v3;
		return (i2 - i1) * (y - (int)y) + i1;
	}
	double Perlin(double x, double y)
	{
		double total = 0, amp = 1;
		int fre = 1;
		for (int i = 0; i < 10; i++) {
			total += InterpolatedNoise(x * fre, y * fre) * amp;
			fre *= 2;
			amp /= 2;
		}
		return total;
	}/*http://freespace.virgin.net/hugo.elias/models/m_perlin.htm*/
};
#endif