#ifndef LOCOMOTIVE_PHONG_H
#define LOCOMOTIVE_PHONG_H

#include "locomotive/locomotive.h"
#include "locomotive/material.h"

#include "glm/vec3.hpp"

namespace Locomotive {
	class LOCOMOTIVE_API Phong : public Material {
	public:
		Phong(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);

		const glm::vec3 &getAmbient() const;
		void setAmbient(const glm::vec3 &val);
		const glm::vec3 &getDiffuse() const;
		void setDiffuse(const glm::vec3 &val);
		const glm::vec3 &getSpecular() const;
		void setSpecular(const glm::vec3 &val);
		float getShininess() const;
		void setShininess(float v);

	private:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}

#endif