#ifndef LOCOMOTIVE_MESH_H
#define LOCOMOTIVE_MESH_H

#include <vector>
#include "locomotive/phong.h"
#include "locomotive/gameobject.h"

namespace Locomotive {
namespace Components {
	class LOCOMOTIVE_API Mesh : public Component {
	public:
		class Shape {
		public:
			Shape(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
			Shape(const Shape& other);
			~Shape();

			Shape& operator=(const Shape& rhs);

			Phong material;
			std::vector<glm::vec3> vertices;
			std::vector<unsigned int> indices;
			unsigned int vbo;
			unsigned int ibo;
			unsigned int vao;

			void init();
		};

		Mesh(const std::string& modelPath);

		std::vector<Shape>& getShapes();
		void draw();

	private:
		std::vector<Shape> shapes;
	};
}
}

#endif
