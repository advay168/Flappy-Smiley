#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Game.h"

float WIDTH = 800, HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Game* game;

int main()
{
	// setting up window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow((int)WIDTH, (int)HEIGHT, "Flappy Smiley", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	game = new Game(WIDTH,HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {game->framebuffer_size_callback(window, width, height); });
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {game->mouse_callback(window, xpos, ypos); });
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {game->scroll_callback(window,xoffset,yoffset); });
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		game->processInput(window,deltaTime);
		game->update(deltaTime);
		game->draw();

		if (game->reset)
		{
			delete game;
			game = new Game(WIDTH, HEIGHT);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete game;
	glfwTerminate();
	return 0;
}