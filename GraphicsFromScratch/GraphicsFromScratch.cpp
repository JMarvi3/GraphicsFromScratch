#include "gui.h"
#include "sphere.h"
#include "vector.h"
#include "light.h"
#include <iostream>
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


pair<double, double> intersectRaySphere(const vector &o, const vector &d, const sphere &sphere) {
    double r = sphere.radius;
    vector co = o - sphere.center;
    double a = d.dot_product(d), b = 2 * co.dot_product(d), c = co.dot_product(co) - r * r;
    double disc = b * b - 4 * a * c;
    if (disc < 0) {
        return {INFINITY, INFINITY};
    }

    return { (-b + sqrt(disc)) / (2 * a), (-b - sqrt(disc)) / (2 * a) };
}

pair<const sphere*, double> traceRay(const vector &o, const vector &d, double t_min, double t_max) {
    double closest_t = INFINITY;
    const sphere *closest_sphere = NULL;
    for (auto it = spheres.begin(); it != spheres.end(); ++it) {
        //cout << d << " : " << *it << endl;
        pair<double, double> t = intersectRaySphere(o, d, **it);
        if (t.first >= t_min && t.first <= t_max && t.first < closest_t) {
            closest_t = t.first;
            closest_sphere = *it;
        }
        if (t.second >= t_min && t.second <= t_max && t.second < closest_t) {
            closest_t = t.second;
            closest_sphere = *it;
        }
    }
    return {closest_sphere, closest_t};
}

double compute_lighting(vector point, vector normal)
{
    double i = 0.0;
    for(auto it = lights.begin(); it != lights.end(); ++it)
    {
        light *this_light = *it;
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
            //cout << x << ", " << y << ": " << d << endl;
            pair<const sphere*, double> result = traceRay(o, d, 1, INFINITY);
            if (result.first != nullptr)
            {
                vector point = o + d * result.second;
            	vector normal = point - result.first->center;
                normal = normal / normal.length();
                const int color = (const int)(result.first->color*compute_lighting(point, normal));
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