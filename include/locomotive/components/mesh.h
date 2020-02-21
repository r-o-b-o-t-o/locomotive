#ifndef LOCOMOTIVE_COMPONENTS_MESH_H
#define LOCOMOTIVE_COMPONENTS_MESH_H

#include <vector>
#include "locomotive/phong.h"
#include "locomotive/gameobject.h"
#include "locomotive/components/camera.h"
#include "locomotive/components/pointlight.h"

namespace Locomotive {
namespace Components {
	class LOCOMOTIVE_API Mesh : public Component {
	public:
		class Shape {
		public:
			Shape(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
			Shape(const Shape& other);
			~Shape();

			Shape &operator=(const Shape &rhs);

			Phong material;
			std::vector<glm::vec3> vertices;
			std::vector<unsigned int> indices;
			unsigned int vbo;
			unsigned int ibo;
			unsigned int vao;

			void init();
		};

		Mesh(const std::string &modelPath);
		Mesh(const Mesh &other);
		~Mesh();

		Mesh &operator=(const Mesh &rhs);

		void draw(Camera &cam);
		void setInstances(std::vector<glm::mat4> &instances);
		void applyPointLight(PointLight &light, int idx);
		void setNbPointLights(int n);
		void applyDirLight(glm::vec3 direction, glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular);

	private:
		std::vector<Shape> shapes;
		std::vector<Shape> &getShapes();
		unsigned int instancesVbo;
		int nbInstances;
	};
}
}

#endif
