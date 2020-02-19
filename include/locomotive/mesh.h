#ifndef LOCOMOTIVE_MESH_H
#define LOCOMOTIVE_MESH_H

#include <vector>
#include "locomotive/camera.h"
#include "locomotive/material.h"

namespace Locomotive {
	class LOCOMOTIVE_API Mesh {
	public:
		Mesh(const std::vector<glm::vec3> &vertices);

		void draw(Material &mat) const;

	private:
		std::vector<glm::vec3> vertices;
		unsigned int vbo;
		unsigned int vao;
	};
}

#endif