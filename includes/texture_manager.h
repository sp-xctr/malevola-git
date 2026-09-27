#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// finish unload all and implement TMan

class TMan {
public:
	const fs::path resources_path = "resources/images";

	void Walk();
	Texture2D *GetTexture(const char* key) { return &texture_map[key]; }
	void SetTexture(std::string key, const char* path);
	void UnloadAll();

private:
	std::unordered_map<std::string, Texture2D> texture_map;
};
