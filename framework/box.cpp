#include <glm/vec3.hpp>
#include "shape.hpp"
#include "Box.hpp"
#include "color.hpp"
#include "material.hpp"
#include <string>
#include <utility>
#include <cmath>

#define OWN_PI 3.14159265359


Box::Box(glm::vec3 const& min, glm::vec3 const& max) : Shape{}, min_{ min }, max_{ max } {
};

Box::Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, std::shared_ptr<Material> const& material) :
	Shape{ name, material},
	min_{ min },
	max_{ max } {
	if (max_.x < min_.x) {
		std::swap(max_.x, min_.x);
	}
	if (max_.y < min_.y) {
		std::swap(max_.y, min_.y);
	}
	if (max_.z < min_.z) {
		std::swap(max_.z, min_.z);
	}
}

float Box::area() const{
	glm::vec3 quad = max_ - min_;
	float area = 2 *(abs(quad.x * quad.y) + abs(quad.x * quad.z) + abs(quad.y * quad.z));
	return area;
}

float Box::volume() const{
	glm::vec3 quad = max_ - min_;
	return abs(quad.x * quad.y * quad.z);
}

std::ostream& Box::print(std::ostream& os)const {
	Shape::print(os);
	os << "Minimum: " << "{" << min_.r << "; " << min_.g << "; " << min_.b << "};" << "Maximum: " << "{" << max_.r << "; " << max_.g << "; " << max_.b << "};";
	return os;
}


HitPoint Box::intersect(Ray const& r) {

	HitPoint hitpoint{};

	float dist = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	
	dist = (min_.x - r.origin.x) / r.direction.x; // ray.direction.x * dist + ray.origin.x = min_.x -> umstellen nach dist
	if (hitpoint.distance > dist && dist >= 0.0f) {
		y = r.origin.y + dist * r.direction.y; // y und z werte des Schnittpunktes des rays mit der Ebene bei min_.x
		z = r.origin.z + dist * r.direction.z;

		if (y >= min_.y && y <= max_.y && z >= min_.z && z <= max_.z) {
			glm::normalize(r.direction);
			hitpoint =  HitPoint{ true, dist, Shape::get_n_c().first, Shape::get_n_c().second, glm::vec3{min_.x, y, z}, r.direction };
		}
	}
	
	dist = (max_.x - r.origin.x) / r.direction.x;
	if (hitpoint.distance > dist && dist >= 0.0f) {
		y = r.origin.y + dist * r.direction.y;
		z = r.origin.z + dist * r.direction.z;

		if (y >= min_.y && y <= max_.y && z >= min_.z && z <= max_.z) {
			glm::normalize(r.direction);
			hitpoint = HitPoint{ true, dist, Shape::get_n_c().first, Shape::get_n_c().second, glm::vec3{max_.x, y, z}, r.direction };
		}
	}

	dist = (min_.y - r.origin.y) / r.direction.y;
	if (hitpoint.distance > dist && dist >= 0.0f) {
		x = r.origin.x + dist * r.direction.x;
		z = r.origin.z + dist * r.direction.z;

		if (x >= min_.x && x <= max_.x && z >= min_.z && z <= max_.z) {
			glm::normalize(r.direction);
			hitpoint = HitPoint{ true, dist, Shape::get_name(), Shape::get_material(), glm::vec3{x, min_.y, z}, r.direction};
		}
	}

	dist = (max_.y - r.origin.y) / r.direction.y;
	if (hitpoint.distance > dist && dist >= 0.0f) {
		x = r.origin.x + dist * r.direction.x;
		z = r.origin.z + dist * r.direction.z;

		if (x >= min_.x && x <= max_.x && z >= min_.z && z <= max_.z) {
			glm::normalize(r.direction);
			hitpoint = HitPoint{ true, dist, Shape::get_n_c().first, Shape::get_n_c().second, glm::vec3{x, max_.y, z}, r.direction };
		}
	}

	dist = (min_.z - r.origin.z) / r.direction.z;
	if (hitpoint.distance > dist && dist >= 0.0f) {
		x = r.origin.x + dist * r.direction.x;
		y = r.origin.y + dist * r.direction.y;

		if (x >= min_.x && x <= max_.x && y >= min_.y && y <= max_.y) {
			glm::normalize(r.direction);
			hitpoint = HitPoint{ true, dist, Shape::get_n_c().first, Shape::get_n_c().second, glm::vec3{x, y, min_.z}, r.direction };
		}
	}

	dist = (max_.z - r.origin.z) / r.direction.z;
	if (hitpoint.distance > dist && dist >= 0.0f) {
		x = r.origin.x + dist * r.direction.x;
		y = r.origin.y + dist * r.direction.y;

		if (x >= min_.x && x <= max_.x && y >= min_.y && y <= max_.y) {
			glm::normalize(r.direction);
			hitpoint = HitPoint{ true, dist, Shape::get_n_c().first, Shape::get_n_c().second, glm::vec3{x, y, max_.z}, r.direction };
		}
	}

	return hitpoint;



}

glm::vec3 Box::normale(glm::vec3 const& point)
{
	float eps = 0.1f;

	if (std::abs(point.x - min_.x) < eps) {
		return glm::vec3{-1.0f, 0.0f, 0.0f};
	}
	else if (std::abs(point.x - max_.x) < eps) {
		return glm::vec3{ 1.0f, 0.0f, 0.0f };
	}
	else if (std::abs(point.y - min_.y) < eps) {
		return glm::vec3{ 0.0f, -1.0f, 0.0f };
	}
	else if (std::abs(point.y - max_.y) < eps) {
		return glm::vec3{ 0.0f, 1.0f, 0.0f };
	}
	else if (std::abs(point.z - min_.z) < eps) {
		return glm::vec3{ 0.0f, 0.0f, -1.0f };
	}
	else if (std::abs(point.z - max_.z) < eps) {
		return glm::vec3{ 0.0f, 0.0f, 1.0f };
	}

	//return glm::vec3{0.0f, 0.0f, 0.0f};
}
