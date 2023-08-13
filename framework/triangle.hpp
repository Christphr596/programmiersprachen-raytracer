
#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"



class Triangle : public Shape {
public:
	Triangle() = default;
	Triangle(glm::vec3 const& point1_, glm::vec3 const& point2_, glm::vec3 const& point3_);
	Triangle(std::string const& name, glm::vec3 const& point1_, glm::vec3 const& point2_, glm::vec3 const& point3_, std::shared_ptr<Material> const& material);

	float area() const override;
	float volume() const override;
	HitPoint intersect(Ray const& r) override;

private:
	glm::vec3 point1_ = { 0,0,0 };
	glm::vec3 point2_ = { 0,0,0 };
	glm::vec3 point3_ = { 0,0,0 };
};
