#pragma once

#include "GameObject.h"

#include <vector>

#include "Draw.h"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Bird.h"

class Pipes
{
public:
	Pipes(unsigned int width, unsigned int height,int n, const glm::mat4& projection = glm::mat4(1.0f));
	void draw();
	void update(float dt);
	bool isColliding(Bird& bird);
	bool toScore(Bird& bird);
private:
	std::vector<bool> amScored;
	void reset(int i);
	bool isOffScreen(int i1);


	float m_width;
	std::vector<float> m_gap_heights;
	std::vector<float> m_gap_poss;
	std::vector<glm::vec2> m_poss;

	DrawRects m_drawer;
	float m_speed;

	unsigned int width;
	unsigned int height;
	
	int n;
};

