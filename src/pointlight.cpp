#include "locomotive/components/pointlight.h"

namespace Locomotive {
namespace Components {
	PointLight::PointLight(glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) :
			ambiant(ambiant),
			diffuse(diffuse),
			specular(specular),
			constant(constant),
			linear(linear),
			quadratic(quadratic) {
	}
}
}
