#include "Draw.h"

#include <glad/glad.h>

#include "glm/gtx/string_cast.hpp"

float vertices[] = {
		-0.5f,-0.5f, 0.0f,0.0f,
		 0.5f, 0.5f, 1.0f,1.0f,
		 0.5f,-0.5f, 1.0f,0.0f,
		-0.5f,-0.5f, 0.0f,0.0f,
		 0.5f, 0.5f, 1.0f,1.0f,
		-0.5f, 0.5f, 0.0f,1.0f
};

void DrawRects::Rectangle(float x, float y, float width, float height)
{
	float adjustedx, adjustedy, adjustedWidth, adjustedHeight;
	adjustedx = 2.0f * x / pixelWidth - 1;
	adjustedWidth = 2.0f * width / pixelWidth;
	adjustedy = -2.0f * y/ pixelHeight + 1;
	adjustedHeight = 2.0f * height / pixelHeight;
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, glm::vec3(adjustedx + adjustedWidth / 2, adjustedy - adjustedHeight / 2, 0.0));
	transform = glm::scale(transform, glm::vec3(adjustedWidth, adjustedHeight, 1.0f));
	m_coords.push_back(transform);
}

void DrawRects::Draw()
{
	m_shader.use();
	m_shader.setInt("tex", 0);
	m_tex.Bind();
	glBindVertexArray(m_VAO);
	for (auto& transform : m_coords)
	{
		m_shader.setMat4("transform", m_projection * transform*1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void DrawRects::Clear()
{
	m_coords.clear();
}

DrawRects::DrawRects(const char* textureName, int width, int height, const glm::mat4& projection):
	m_tex(textureName), m_shader("res/shaders/Rect.vs.glsl", "res/shaders/Rect.fs.glsl"), pixelWidth(width), pixelHeight(height),m_projection(projection)
{
	unsigned int VBO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

DrawRects::DrawRects(const glm::vec4& color, int width, int height, const glm::mat4& projection) :
	m_tex(color), m_shader("res/shaders/Rect.vs.glsl", "res/shaders/Rect.fs.glsl"), pixelWidth(width), pixelHeight(height) , m_projection(projection)
{
	unsigned int VBO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}
