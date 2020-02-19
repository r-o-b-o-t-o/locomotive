#ifndef LOCOMOTIVE_MATERIAL_H
#define LOCOMOTIVE_MATERIAL_H

#include "locomotive/locomotive.h"
#include "locomotive/shader.h"

namespace Locomotive {
	class LOCOMOTIVE_API Material {
	public:
		Material(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		Shader &getShader();

	protected:
		Shader shader;
	};
}

#endif
