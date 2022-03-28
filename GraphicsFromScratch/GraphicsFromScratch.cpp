#include "gui.h"
#include "sphere.h"
#include "vector.h"
#include "light.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <utility>

using std::pair;
using std::cout;
using std::endl;

std::vector<sphere*> spheres;
std::vector<light*> lights;

vector canvas_to_viewport(int x, int y, double d, double vw, double vh, int cw, int ch) {
    return {x * vw / cw, y * vh / ch, d};
}


std::vector<double> intersectRaySphere(const vector &o, const vector &d, const sphere &sphere) {
    double r = sphere.radius;
    vector co = o - sphere.center;
    double a = d.dot_product(d), b = 2 * co.dot_product(d), c = co.dot_product(co) - r * r;
    double disc = b * b - 4 * a * c;
    if (disc < 0) {
        return {};
    }

    return { (-b + sqrt(disc)) / (2 * a), (-b - sqrt(disc)) / (2 * a) };
}

std::tuple<const sphere*, double> traceRay(const vector &o, const vector &d, double t_min, double t_max) {
    double closest_t = INFINITY;
    const sphere *closest_sphere = nullptr;
    for (const auto& this_sphere : spheres)
    {
        for(double t : intersectRaySphere(o, d, *this_sphere))
        {
	        if (t >= t_min and t <= t_max and  t < closest_t)
	        {
                closest_t = t;
                closest_sphere = this_sphere;
	        }
        }
    }
    return {closest_sphere, closest_t};
}

double compute_lighting(vector point, vector normal)
{
    double i = 0.0;
    for (const auto this_light : lights)
    {
	    if(dynamic_cast<ambient_light*>(this_light))
	    {
            i += dynamic_cast<ambient_light*>(this_light)->get_intensity();
	    } else
	    {
            vector l;
            if(dynamic_cast<point_light*>(this_light))
		    {
                l = dynamic_cast<point_light*>(this_light)->get_position() - point;
            } else
		    {
                l = dynamic_cast<directional_light*>(this_light)->get_direction();
            }
	    	const double normal_dot_l = normal.dot_product(l);
            if (normal_dot_l > 0)
                i += (this_light->get_intensity() * normal_dot_l) / (normal.length() * l.length());
	    }
    }
    return i;
}

void rayTrace(gui& gui)
{

    spheres.emplace_back(new sphere(vector(0, -1, 3), 1, 0xff0000));
    spheres.emplace_back(new sphere(vector(2, 0, 4), 1, 0x0000ff));
    spheres.emplace_back(new sphere(vector(-2, 0, 4), 1, 0x00ff00));
    lights.emplace_back(new ambient_light(0.2));
    lights.emplace_back(new point_light(0.6, vector(2, 1, 0)));
    lights.emplace_back(new directional_light(0.2, vector(1, 4, 4)));
    vector o = vector(0, 0, 0);
    for(int x = -gui.width/2; x < gui.width/2; ++x)
        for (int y = -gui.height/2 + 1; y <= gui.height / 2; ++y) {
            vector d = canvas_to_viewport(x, y, 1, 1, 1, gui.width, gui.height);
            const sphere *closest_sphere;
            double distance;
            std::tie(closest_sphere, distance) = traceRay(o, d, 1, INFINITY);
            if (closest_sphere)
            {
                const vector point = o + d * distance;
                const vector normal = (point - closest_sphere->center) / closest_sphere->radius;
                const int color = static_cast<const int>(closest_sphere->color * compute_lighting(point, normal));
                gui.set_pixel(x, y, color);
            }
        }
    gui.update();
}

int main()
{
    gui our_gui = gui(400, 400);
    rayTrace(our_gui);
    our_gui.wait_for_exit();
    return 0;
}