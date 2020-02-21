#pragma once

#include "locomotive/locomotive.h"
#include "locomotive/components/mesh.h"

#include <map>
#include <string>

namespace Locomotive {
	class LOCOMOTIVE_API MeshLoader {
	public:
		static Components::Mesh* load(const std::string& path, const std::string& name);
		static Components::Mesh* get(const std::string& name);

	private:
		static std::map<std::string, Components::Mesh*> meshes;
	};
}
