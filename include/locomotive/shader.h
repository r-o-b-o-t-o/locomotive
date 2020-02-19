#ifndef LOCOMOTIVE_SHADER_H
#define LOCOMOTIVE_SHADER_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "locomotive/locomotive.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace Locomotive {
	class LOCOMOTIVE_API Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		Shader(const Shader &other);
		~Shader();

		Shader &operator=(const Shader &rhs);

		void use() const;
		unsigned int getId() const;
		static void deleteShaders();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec2(const std::string &name, const glm::vec2 &vec) const;
		void setVec2(const std::string &name, float x, float y) const;
		void setVec3(const std::string &name, const glm::vec3 &vec) const;
		void setVec3(const std::string &name, float x, float y, float z) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;

	private:
		unsigned int id;
		unsigned int vertex;
		unsigned int fragment;
		unsigned int geometry;
		bool hasGeometryShader;

		static std::map<std::string, unsigned int> compiledShaders;

		void build();
		int getUniformLocation(const std::string &name) const;
		std::string readShaderFile(const char* path) const;
		unsigned int getShader(const char* path, unsigned int shaderType);
	};
}

#endif
