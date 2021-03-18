#include "Bird.h"

Bird::Bird(unsigned int width, unsigned int height, const glm::mat4& projection) :
	width(width),
	height(height),
	radius(5),
	m_pos(width/4,height/2),
	m_vel(0),
	m_acc(0,0.2),
	m_drawer("res/textures/awesomeface.png",width,height,projection)
{
	m_drawer.Rectangle(m_pos.x-radius, m_pos.y-radius, 2 * radius, 2 * radius);
}

void Bird::update(float dt)
{
	if (paused)
		return;
	m_vel += m_acc * dt;
	m_pos += m_vel;

	m_drawer.Clear();
	m_drawer.Rectangle(m_pos.x - radius, m_pos.y - radius, 2 * radius, 2 * radius);
}

void Bird::processInput(GLFWwindow* window,float dt)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		move(glm::vec2(0.0f,-80.0f)*dt);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		move(glm::vec2(0.0f,-80.0f)*dt);
}

bool Bird::isCollidingWithSide()
{
	if (m_pos.y + radius > height) {
		return true;
	}
	if (m_pos.y - radius <0) {
		return true;
	}
	return false;
}

glm::vec2& Bird::getPos()
{
	return m_pos;
}

int Bird::getRadius()
{
	return radius;
}

void Bird::draw()
{
	m_drawer.Draw();
}

void Bird::move(glm::vec2 offset)
{
	m_pos += offset;
	m_vel = {0.0f,0.0f};
	m_drawer.Clear();
	m_drawer.Rectangle(m_pos.x - radius, m_pos.y - radius, 2 * radius, 2 * radius);
}