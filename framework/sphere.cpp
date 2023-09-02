

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


HitPoint Sphere::intersect(Ray const& r_original) {
	Ray r = transform(Shape::get_w_t_inv_mat(), r_original);

	float distance = 0.0f;

	
	//glm::vec3 r_direction_transformed = glm::normalize(r.direction);
	r.direction = glm::normalize(r.direction);

	bool cut = glm::intersectRaySphere(r.origin, r.direction, center_, radius_ * radius_, distance);
	//std::pair<std::string, std::shared_ptr<Material>> n_c = Shape::get_n_c();

	HitPoint hitpoint{ cut, distance,Shape::get_name() /*n_c.first*/, Shape::get_material()/* n_c.second*/, r.origin + distance * r.direction, r.direction, normale(r.origin + distance * r.direction)};

	hitpoint = transform(Shape::get_w_t_mat(), hitpoint);

	
	glm::vec3 dis = hitpoint.point - r_original.origin;
	float dist = glm::distance(hitpoint.point, r_original.origin);
	HitPoint hp {hitpoint.cut, dist, hitpoint.name, hitpoint.material, hitpoint.point, hitpoint.direction, hitpoint.normale};

	return hp;
}


std::ostream& Sphere::print(std::ostream& os)const{
	Shape::print(os);
	os << "Center: " << "{" << center_.r << "; " << center_.g << "; " << center_.b << "}; " << "Radius: " << radius_;
	return os;
}

glm::vec3 Sphere::normale(glm::vec3 const& point)
{	//glm::vec4 center_transformed = Shape::get_w_t_mat() * glm::vec4{ center_, 1.0f };
	return glm::normalize(point - center_/*glm::vec3{center_transformed.x, center_transformed.y, center_transformed.z}*/);

	//glm::vec4 normale{};
	//glm::vec4 point_transformed = Shape::get_w_t_inv_mat() * glm::vec4{ point, 1.0f };
	//normale = glm::normalize(point_transformed - glm::vec4{ center_, 1.0f });
	//normale = glm::transpose(Shape::get_w_t_inv_mat()) * normale;
	//return glm::vec3{ normale.x, normale.y, normale.z };
}
