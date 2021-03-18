#pragma once
#include "GameObject.h"

#include "Draw.h"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

class Bird :public GameObject
{
public:
	Bird(unsigned int width, unsigned int height, const glm::mat4& projection = glm::mat4(1.0f));
	void draw();
	void update(float dt);
	void processInput(GLFWwindow* window,float dt);
	bool isCollidingWithSide();
	glm::vec2& getPos();
	int getRadius();
	bool paused = false;
private:
	void move(glm::vec2 offset);
	
	unsigned int width;
	unsigned int height;
	DrawRects m_drawer;
	int radius;
	glm::vec2 m_pos;
	glm::vec2 m_vel;
	glm::vec2 m_acc;
};

