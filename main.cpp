#include <iostream>
#include <fstream>
#include <limits>
#include "HittableList.h"
#include "Sphere.h"


float MAX_FLOAT = std::numeric_limits<float>::max();

Vec3 color(const Ray& r, Hittable *world){    
	hitRecord record;
	if (world->hit(r, 0.0, MAX_FLOAT, record)){
		return 0.5*Vec3(record.normal.x()+1, record.normal.y()+1, record.normal.z()+1);
	}
	Vec3 unitDirection = unitVector(r.direction());
	float t = 0.5*(unitDirection.y() + 1.0);
	return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);}

int main() {
	std::ofstream output;
    output.open("output.ppm");

	int nx = 200;
	int ny = 100;
	int ns = 100;
	output << "P3\n" << nx << " " << ny << "\n255\n";

	Hittable *list[2];
	list[0] = new Sphere(Vec3(0,0,-1), 0.5);
	list[1] = new Sphere(Vec3(0,-100.5,-1), 100);
	Hittable * world = new HittableList(list, 2);
	//Camera cam;
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
			Ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			Vec3 p = r.pointAtParameter(2.0);
			Vec3 col = color(r, world);
			//col /= float(ns);

			int ir = int (255.99*col[0]);
			int ig = int (255.99*col[1]);
			int ib = int (255.99*col[2]);
			output << ir << " " << ig << " " << ib << "\n";
		}
	}
	output.close();
	return 0;
}
