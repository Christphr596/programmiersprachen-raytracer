#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "Color.hpp"
#include "ray.hpp"
#include <cmath>
#define OWN_PI 3.14159265359

struct Camera {
	std::string name = "";
	float fov_x = 0.0f;
	glm::vec3 eye = { 0,0,0 };
	glm::vec3 dir = { 0,0,0 };
	glm::vec3 up = { 0,0,0 };

	/*

	float Camera::dis(unsigned const width_, unsigned const height_) const {
		float distance = (width_ / 2) / sin((fov_x / 2) * OWN_PI / 180);
		return distance;
	}

	float Camera::height(unsigned const width_, unsigned const height_) const {
		float height = (height_ / 2) / sin((fov_x / 2) * OWN_PI / 180);
		return height * 2;
	}

	Ray Camera::ray_gen(int t, float distance, float height_, unsigned int width_) {
		glm::vec3 act_vec = { height_, width_, distance };
		glm::vec3 vec;
		vec.x = eye.x + t * act_vec.x;
		vec.y = eye.y + t * act_vec.y;
		vec.z = eye.z + t * -distance;
		Ray ray = { eye, act_vec };

		return ray;
	}*/
};