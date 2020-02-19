#include "locomotive/material.h"

namespace Locomotive {
	Material::Material(const char* vertexPath, const char* fragmentPath, const char* geometryPath) :
			shader(vertexPath, fragmentPath, geometryPath) {

	}

	Shader &Material::getShader() {
		return this->shader;
	}
}
