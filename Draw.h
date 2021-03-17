#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Texture.h"
#include "Shader.h"


class DrawRects
{
public:
	DrawRects(const char* textureName,int width, int height,const glm::mat4& projection = glm::mat4(1.0f));
	DrawRects(const glm::vec4& color, int width, int height,const glm::mat4& projection = glm::mat4(1.0f));
	template<typename t1,typename t2>
	void Rectangle(t1 x, t1 y, t2 width, t2 height) { Rectangle((float)x, (float)y, (float)width, (float)height); }
	void Rectangle(float x, float y, float width, float height);
	void Draw();
	void Clear();
private:
	const glm::mat4& m_projection ;
	int pixelWidth, pixelHeight;
	std::vector<glm::mat4> m_coords;
	Texture m_tex;
	Shader m_shader;
	unsigned int m_VAO;
};

