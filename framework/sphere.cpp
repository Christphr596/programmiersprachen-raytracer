

#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include <string>

#define OWN_PI 3.14159265359


Sphere::Sphere(glm::vec3 const& mid_point, float radius) : Shape{ "", std::make_shared<Material>(Material{}) }, center_{ mid_point }, radius_{ radius } {};


Sphere::Sphere(std::string const& name, glm::vec3 const& center, float radius, std::shared_ptr<Material> const& material) :
	Shape{ name, material },
	center_{ center },
	radius_{ radius } {
	if (radius_ < 0.0f) {
		radius_ = -radius_;
	}

}

float Sphere::area() const{

	return abs(radius_) * abs(radius_) * OWN_PI * 4;
}

float Sphere::volume() const{
	return (4.0f / 3.0f * OWN_PI * abs(radius_) * abs(radius_) * abs(radius_));
}

HitPoint Sphere::intersect(Ray const& ray) {
	float distance = 0.0f;
	glm::normalize(ray.direction);
	bool cut = glm::intersectRaySphere(ray.origin, ray.direction, center_, radius_ * radius_, distance);
	std::pair<std::string, std::shared_ptr<Material>> n_c = Shape::get_n_c();
	HitPoint hitpoint{ cut, distance, n_c.first, n_c.second, ray.origin + distance * ray.direction, ray.direction };
	
	return(hitpoint);
}

std::ostream& Sphere::print(std::ostream& os)const{
	Shape::print(os);
	os << "Center: " << "{" << center_.r << "; " << center_.g << "; " << center_.b << "}; " << "Radius: " << radius_;
	return os;
}

glm::vec3 Sphere::normale(glm::vec3 const& point)
{
	glm::vec4 center_transformed = Shape::get_w_t_mat() * glm::vec4{ center_, 1.0f };
	return glm::normalize(point - glm::vec3{ center_transformed .x, center_transformed .y, center_transformed .z});
}
