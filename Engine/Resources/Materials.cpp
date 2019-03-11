#include "Materials.hpp"
#include "Shaders.hpp"
#include "Textures.hpp"
#include "../DEBUG.hpp"

Material & MaterialHandle::get() const
{
	return resources::materials.get(*this);
}

void MaterialsManager::addLoadInfo(const serialization::Value & value)
{
	auto serializedArray = value.GetArray();
	for (const auto & item : serializedArray)
	{
		auto obj = item.GetObject();

		MaterialLoadInfo info;
		info.name = obj["name"].GetString();
		info.vertexShaderPath = obj["vertex shader"].GetString();
		info.fragmentShaderPath = obj["fragment shader"].GetString();

		for (const auto & texture : obj["textures"].GetArray())
		{
			info.textures.emplace_back(
				textureInfo{
					texture["target"].GetString(),
					texture["name"].GetString()
			});
		}
		_loadInfos.emplace(info.name, info);
	}	
}

MaterialHandle MaterialsManager::getHandle(const std::string & name)
{
	// Return existing
	auto it = _loadedMaterialsMap.find(name);
	if (it != _loadedMaterialsMap.end())
		return it->second;

	assert (_loadInfos.find(name) != _loadInfos.end() && "That material is not found.");

	// Create new
	auto info = _loadInfos[name];
	auto shader = resources::shaders.create(info.vertexShaderPath, info.fragmentShaderPath);
	auto texture = resources::textures.getHandle(info.textures[0].name);
	auto tex1 = resources::textures.getHandle(info.textures[1].name);

	auto index = _materials.size();
	MaterialHandle handle {index};
	_materials.emplace_back ( Material {shader, texture, tex1} );
	_loadedMaterialsMap.emplace(name, handle);
	return handle;
}
