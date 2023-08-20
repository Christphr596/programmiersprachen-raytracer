#include "hitpoint.hpp"

HitPoint transform(glm::mat4 const& mat, HitPoint const& hp) {
	glm::vec4 point{ hp.point, 1.0f };
	glm::vec4 direction{ hp.direction, 0.0f };

	point = mat * point;
	direction = mat * direction;

	return HitPoint{ hp.cut, hp.distance, hp.name, hp.material, glm::vec3{point.x, point.y, point.z}, glm::vec3{direction.x, direction.y, direction.z} };

}