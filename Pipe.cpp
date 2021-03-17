#include "Pipe.h"

#include "glm/gtc/random.hpp"

Pipes::Pipes(unsigned int width, unsigned int height, int n, const glm::mat4& projection) :
	m_width(10),
	m_drawer("res/textures/wall.jpg", width, height,projection),
	m_speed(10.0f),
	width(width),
	height(height),
	n(n)
{
	for (int i = 0; i < n; i++)
	{
		m_poss.push_back({ float(width + width * i / n),0.0f });
		m_gap_heights.push_back(glm::linearRand(20.0f, height * 2.6f / 4));
		m_gap_poss.push_back(glm::linearRand(10.0f, height - 10 - m_gap_heights[i]));
		amScored.push_back(false);
	}
}

void Pipes::draw()
{
	m_drawer.Draw();
}

void Pipes::update(float dt)
{
	m_drawer.Clear();
	for (int i = 0; i < n; i++)
	{
		m_poss[i].x -= m_speed * dt;
		if (isOffScreen(i))
			reset(i);
		m_drawer.Rectangle(m_poss[i].x, 0, m_width, m_gap_poss[i]);
		m_drawer.Rectangle(m_poss[i].x, m_gap_poss[i] + m_gap_heights[i], m_width, height);
	}
}


void Pipes::reset(int i)
{
	m_poss[i].x = width;
	m_gap_heights[i] = glm::linearRand(30.0f, height * 3.0f / 4);
	m_gap_poss[i] = glm::linearRand(10.0f, height - 10 - m_gap_heights[i]);
	amScored[i] = false;
}

bool Pipes::isOffScreen(int i)
{
	return m_poss[i].x + m_width < 0;
}

bool Pipes::isColliding(Bird& bird)
{
	float radius = bird.getRadius();
	glm::vec2 pos = bird.getPos();
	for (int i = 0; i < n; i++)
	{
		glm::vec2 clamped = glm::clamp(pos, m_poss[i], m_poss[i] + glm::vec2(m_width, m_gap_poss[i]));
		if (glm::distance(clamped, pos) < radius - 0.5)
		{
			bird.paused = true;
			m_speed = 0;
			return true;
		}
		clamped = glm::clamp(pos,
			glm::vec2{ m_poss[i].x ,m_gap_poss[i] + m_gap_heights[i] },
			glm::vec2{ m_poss[i].x +m_width,m_gap_poss[i] + m_gap_heights[i] +height});
		if (glm::distance(clamped, pos) < radius - 0.5)
		{
			bird.paused = true;
			m_speed = 0;
			return true;
		}
	}
	return false;
}
bool Pipes::toScore(Bird& bird)
{
	for (int i = 0; i < n; i++)
	{
		if (m_poss[i].x + m_width< bird.getPos().x - bird.getRadius() && !amScored[i]) {
			amScored[i] = true;
			return true;
		}
	}
	return false;
}