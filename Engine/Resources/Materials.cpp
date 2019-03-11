#include "Materials.hpp"
#include "Shaders.hpp"
#include "../DEBUG.hpp"


void MaterialsManager::addLoadInfo(const serialization::Value & value)
{
	auto serializedArray = value.GetArray();
	for (const auto & item : serializedArray)
	{
		auto obj = item.GetObject();
		auto name = obj["name"].GetString();
		auto vertexShaderPath = obj["vertex shader"].GetString();
		auto fragmentShaderPath = obj["fragment shader"].GetString();

		shaderHandle shader = resources::shaders.create(vertexShaderPath, fragmentShaderPath);

		for (const auto & texture : obj["textures"].GetArray())
		{
			DEBUG << texture["target"].GetString() << " => " << texture["name"].GetString() << "\n";
		}
	}	
}

MaterialHandle MaterialsManager::getHandle(const std::string & name)
{
	auto it = _loadedMaterialsMap.find(name);
	if (it == _loadedMaterialsMap.end())
	{
		DEBUG << "Load new material";
	}
	return 0;
}
