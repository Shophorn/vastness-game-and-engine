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
	ShaderHandle shader;
	TextureHandle texture;
	TextureHandle tex1;
	// std::vector<TextureHandle> textures;
};

class MaterialsManager
{
public:
	struct Handle
	{
		int index;
		Material & get() const;	
	};

	Handle getHandle(const std::string & name);
	void addLoadInfo(const serialization::Value & value);

private:
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

	std::unordered_map<std::string, MaterialLoadInfo> 	_loadInfos{};
	std::unordered_map<std::string, Handle> 			_loadedMaterialsMap{};
	std::vector<Material> 								_materials{};
};

using MaterialHandle = MaterialsManager::Handle;

namespace resources
{
	inline MaterialsManager materials;
}