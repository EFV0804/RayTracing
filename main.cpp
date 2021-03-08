#include <iostream>
#include <fstream>
#include "Ray.h"
#include "Sphere.h"
/*bool IsSphereHit(const Vec3& center, float radius, const Ray& r)
{    
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}*/
Vec3 color(const Ray& r){    
	/*if (IsSphereHit(Vec3(0,0,-1), 0.5, r))
	{
		return Vec3(1, 0, 0);
	}*/
	Vec3 unitDirection = unitVector(r.direction());
	float t = 0.5*(unitDirection.y() + 1.0);
	return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);}

int main() {
	std::ofstream output;
    output.open("output.ppm");
	//Sphere sphere = Sphere(Vec3(0, 0, -1), 0.5);

	int nx = 200;
	int ny = 100;
	output << "P3\n" << nx << "" << ny << "\n255\n";
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);
	for(int j = ny-1; j>=0; j--)
	{
		for(int i = 0; i < nx; i++)
		{
			float u = float(i) / float (nx);
			float v = float(j) / float (ny);
			Ray r (origin, lower_left_corner + u*horizontal + v*vertical);
			Vec3 col = color(r);
			int ir = int (255.99*col[0]);
			int ig = int (255.99*col[1]);
			int ib = int (255.99*col[2]);
			output << ir << " " << ig << " " << ib << "\n";
		}
	}
	output.close();
	return 0;
}
