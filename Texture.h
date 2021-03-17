#pragma once

#include <string>

#include "glm/vec4.hpp"

class Texture
{
public:
	Texture(std::string filePath);
	Texture(const glm::vec4& color);

	void Bind(int slot = 0);
private:
	unsigned int ID;
};

