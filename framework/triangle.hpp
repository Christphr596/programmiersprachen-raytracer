#pragma once

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "color.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"


class Triangle : public Shape {
public:
	Triangle() = default;
	Triangle(std::string const& name, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, std::shared_ptr<Material> const& material);

	float area() const override;
	float volume() const override;
	//std::ostream& print(std::ostream& os) const;
	HitPoint intersect(Ray const& r) override;

	glm::vec3 normale(glm::vec3 const& point) override;

	//~Box();

private:
	glm::vec3 p1_ = { 0,0,0 };
	glm::vec3 p2_ = { 0,0,0 };
	glm::vec3 p3_ = { 0,0,0 };
};

#endif