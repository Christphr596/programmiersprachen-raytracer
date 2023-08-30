#include "hitpoint.hpp"

HitPoint transform(glm::mat4 const& mat, HitPoint const& hp) {
	glm::vec4 point{ hp.point, 1.0f };
	glm::vec4 direction{ hp.direction, 0.0f };
	glm::vec4 normale{hp.normale , 0.0f};

	point = mat * point;
	direction = mat * direction;
	normale = glm::inverse(glm::transpose(mat)) * normale;

	return HitPoint{ hp.cut, hp.distance, hp.name, hp.material, glm::vec3{point.x, point.y, point.z}, glm::normalize(glm::vec3{direction.x, direction.y, direction.z}), glm::normalize(glm::vec3{normale.x, normale.y, normale.z}) };

}