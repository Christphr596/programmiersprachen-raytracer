
#include "triangle.hpp"

Triangle::Triangle(glm::vec3 const& point1, glm::vec3 const& point2, glm::vec3 const& point3) : 
	Shape{}, point1_{ point1 }, point2_{ point2 }, point3_{ point3 } {};

Triangle::Triangle(std::string const& name, glm::vec3 const& point1, glm::vec3 const& point2, glm::vec3 const& point3, std::shared_ptr<Material> const& material) :
	Shape{name, material}, point1_{ point1 }, point2_{ point2 }, point3_{ point3 } {};


float Triangle::area() const {
	return 0.0f;
}

float Triangle::volume() const {
	return 0.0f;
}



/*
HitPoint Triangle::intersect(Ray const& ray) {
	HitPoint hitpoint{};
	return hitpoint;
}
*/

HitPoint Triangle::intersect(Ray const& ray) {

	HitPoint hitpoint{};
	float distance = 0.0f;
	glm::normalize(ray.direction);

	glm::vec3 a = point2_ - point1_;
	glm::vec3 b = point3_ - point1_;

	glm::vec3 o = { (a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x) }; //Kreuzprodukt

	float p = o.x * ray.direction.x + o.y * ray.direction.y + o.z * ray.direction.z; //Skalarprodukt
	float value = o.x * point1_.x + o.y * point1_.y + o.z * point1_.z; //Ebenengleichung Wert (=value)


	if(p != 0){
		float r = (-ray.origin.x * o.x - ray.origin.y * o.y - ray.origin.z * o.z + value) / (ray.direction.x * o.x + ray.direction.y * o.y + ray.direction.z * o.z);
			//Werte	
		glm::vec3 cut_e = ray.origin + r * ray.direction;
		float a_be = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
		float b_be = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
		float s = (cut_e.x * a.y - a.y * point1_.x - a.x * cut_e.y + a.x * point1_.y) / (a.y * b.x - a.x * b.y);
		float l = (cut_e.x - point1_.x - s * b.x) / a.x;
		if (l >= 0 || l <= 1 || s >= 0 || s <= 1 || s + l >= 0 || s + l <= 1){
			float distance = sqrt((cut_e.x - ray.origin.x) * (cut_e.x - ray.origin.x) + (cut_e.y - ray.origin.y) * (cut_e.y - ray.origin.y) + (cut_e.z - ray.origin.z) * (cut_e.z - ray.origin.z));
			HitPoint hitpoint = { true, distance, Shape::get_name(), Shape::get_material() , ray.origin + distance * ray.direction, ray.direction};
		}
	}
	return(hitpoint);
}