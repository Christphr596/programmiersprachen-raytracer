#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "composite.hpp"
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include <array>

#define OWN_PI 3.14159265359

Composite::Composite(std::string const& name) : Shape{ name, nullptr } {
};


glm::vec3 Composite::normale(glm::vec3 const& point) {
	glm::vec3 vec{ 0,0,0 };
	return vec;
}

HitPoint Composite::intersect(Ray const& r_original) {
    Ray r = transform(Shape::get_w_t_inv_mat(), r_original);

    HitPoint closest_hp{};

    for (auto s : children_) {
        HitPoint hp = s->intersect(r);
        if (hp.cut) {
            if (hp.distance < closest_hp.distance) {
                closest_hp = hp;
            }
        }

    }
    closest_hp = transform(Shape::get_w_t_mat(), closest_hp);
    return closest_hp;

}

void Composite::add_shape(std::shared_ptr<Shape> shape) {
	children_.push_back(shape);
};

std::vector<std::shared_ptr<Shape>> Composite::get_children()const {

	return children_;
};