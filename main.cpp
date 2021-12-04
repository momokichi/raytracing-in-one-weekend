#include <iostream>

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

using namespace std;

double hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  return (discriminant < 0 ? -1.0 : ((-half_b - sqrt(discriminant)) / a));
}

color ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  if (depth <= 0) return color(0, 0, 0);

  if (world.hit(r, 0.001, infinity, rec)) {
    point3 target = rec.p + rec.normal + random_unit_vector();
    return 0.5 * ray_color(ray(rec.p, target - rec.p), world, --depth);
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 384;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera cam;

  cout << "P3\n" << image_width << " " << image_height << "\n255" << endl;

  for (int j = image_height - 1; j >= 0; --j) {
    cerr << "\rScanlines remaining: " << j << " " << flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }
  cerr << "\nDone." << endl;
}
