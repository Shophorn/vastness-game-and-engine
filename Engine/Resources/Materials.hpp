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
	textureHandle texture;
	textureHandle tex1;
	// std::vector<textureHandle> textures;
};

struct textureInfo
{
	std::string target;
	std::string name;
};

struct MaterialLoadInfo
{
	std::string name;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::vector<textureInfo> textures;
};

struct MaterialHandle
{
	int index;
	Material & get() const;
};

class MaterialsManager
{
public:
	Material & get(MaterialHandle handle) { return _materials[handle.index]; }
	MaterialHandle getHandle(const std::string & name);
	void addLoadInfo(const serialization::Value & value);

private:
	std::unordered_map<std::string, MaterialLoadInfo> 	_loadInfos{};
	std::unordered_map<std::string, MaterialHandle> 	_loadedMaterialsMap{};
	std::vector<Material> 								_materials{};
};

namespace resources
{
	inline MaterialsManager materials;
}