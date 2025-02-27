
//#pragma once

#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "color.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"
#include <vector>

class Composite : public Shape {
public:
	Composite(std::string const& name);

	void add_shape(std::shared_ptr<Shape> shape);
	std::vector<std::shared_ptr<Shape>> get_children()const;

	HitPoint intersect(Ray const& r) override;
	glm::vec3 normale(glm::vec3 const& point) override;



private:
	std::string name_ = "";
	std::vector<std::shared_ptr<Shape>> children_;
};

#endif