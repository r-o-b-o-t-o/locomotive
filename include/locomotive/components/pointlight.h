#ifndef LOCOMOTIVE_COMPONENTS_POINTLIGHT_H
#define LOCOMOTIVE_COMPONENTS_POINTLIGHT_H

#include "locomotive/components/component.h"
#include "glm/vec3.hpp"

namespace Locomotive {
namespace Components {
	class LOCOMOTIVE_API PointLight : public Component {
	public:
		PointLight(glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

		glm::vec3 ambiant;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
	};
}
}

#endif
