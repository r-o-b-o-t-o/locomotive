#include "locomotive/meshloader.h"

namespace Locomotive {
	Components::Mesh* MeshLoader::load(const std::string& path, const std::string& name) {
		auto* m = new Locomotive::Components::Mesh(path);
		meshes[name] = m;
		return m;
	}

	Components::Mesh* MeshLoader::get(const std::string& name) {
		if (meshes.count(name) > 0) {
			return meshes[name];
		}
		return nullptr;
	}

	std::map<std::string, Components::Mesh*> MeshLoader::meshes;
}
