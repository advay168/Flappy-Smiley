#pragma once
#include "Constants.h"


#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Draw.h"

#include "glm/gtc/random.hpp"
#include "glm/gtc/noise.hpp"

#include "Bird.h"
#include "Pipe.h"

enum class GameState {
	Welcome,
	Running,
	End
};

class Game
{
public:
	Game(float &WIDTH,float &HEIGHT);
	void processInput(GLFWwindow* window,float dt);
	void update(float dt);
	void draw();

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* /* window */, double /* xpos */, double /* ypos */) {}
	void scroll_callback(GLFWwindow* /* window */, double /* xoffset */, double /* yoffset */) {}
	bool reset = false;
private:
	GameState mode;
	int score = 0;
	glm::mat4 m_projection;
	Bird bird;
	Pipes pipes;
	DrawRects endDrawer;
	DrawRects side_blockDrawer;
	float& WIDTH;
	float& HEIGHT;
	DrawRects gridDrawer;
};

