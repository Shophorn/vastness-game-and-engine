/*
Shophorn Gaming Industry
Leo Tamminen
09/03/2019
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Shaders.hpp"
#include "Textures.hpp"
#include "../Serialization.hpp"

struct Material
{
	shaderHandle shader;
	std::vector<textureHandle> textures;
};

struct MaterialLoadInfo
{
	std::string name;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::unordered_map<std::string, std::string> textureNames;
};

using MaterialHandle = int;

class MaterialsManager
{
public:
	const Material & get(MaterialHandle handle) const { return _materials[handle]; }
	void addLoadInfo(const serialization::Value & value);

private:
	std::unordered_map<std::string, MaterialLoadInfo> 	_loadInfos{};
	std::unordered_map<std::string, int> 				_loadedMaterialsMap{};
	std::vector<Material> 								_materials{};
};

namespace resources
{
	inline MaterialsManager materials;
}