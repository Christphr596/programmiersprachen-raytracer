#include <glm/glm.hpp>
#include "Ray.hpp"

Ray transform(glm::mat4 const& mat, Ray const& r) {
	glm::vec4 origin{ r.origin, 1.0f };
	glm::vec4 direction{ r.direction, 0.0f };

	origin = mat * origin;
	direction = mat * direction;

	return Ray{ glm::vec3{origin.x, origin.y, origin.z}, /*glm::normalize(*/glm::vec3{direction.x, direction.y, direction.z}/*)*/};


}