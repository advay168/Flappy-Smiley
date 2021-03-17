#include "Game.h"

#define GLT_IMPLEMENTATION
#include "GLtext.h"

Game::Game(float& WIDTH, float& HEIGHT) :
	mode(GameState::Welcome),
	bird(pixW,pixH,m_projection),
	pipes(pixW,pixH, 4,m_projection),
	endDrawer({ 0.3f,1.0f,0.3f , 1.0f }, pixW,pixH,m_projection),
	side_blockDrawer({ 0.0f,0.0f,0.0f,1.0f }, pixW,pixH,m_projection),
	gridDrawer({ 0.3,0.3,1.0,1.0 }, pixW,pixH,m_projection),
	WIDTH(WIDTH), HEIGHT(HEIGHT)
{
	gltInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float aspect = WIDTH / HEIGHT;
	side_blockDrawer.Rectangle(pixW / 2.0f * (-aspect + 1), 0, pixW / 2.0f * (aspect - 1), pixH);
	side_blockDrawer.Rectangle(pixW, 0, pixW / 2.0f * (aspect - 1), pixH);
	endDrawer.Rectangle(0, 0, pixW,pixH);
	int num_Cols_Rows = 10;
	float height = float(pixH) / num_Cols_Rows;
	float width =  float(pixW) / num_Cols_Rows;
	for (int i = 0; i < num_Cols_Rows + 1; i++)
		for (int j = 0; j < num_Cols_Rows + 1; j++)
		{
			gridDrawer.Rectangle(width * i, height * j, 0.5, 0.5);
		}
}

void Game::processInput(GLFWwindow* window, float dt)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	static bool wireframe = false;
	#ifdef MSVC
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		__debugbreak();
	#endif
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		wireframe = !wireframe;
	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		switch (mode)
		{
		case GameState::Welcome:
			mode = GameState::Running;
			break;
		case GameState::Running:
			break;
		case GameState::End:
			reset = true;
			break;
		default:
			break;
		}
	}
	if(mode == GameState::Running)
		bird.processInput(window, dt);
}

void Game::update(float dt)
{
	switch (mode)
	{
	case GameState::Welcome:
	{
		break;
	}
	case GameState::Running:
	{
		bird.update(dt);
		pipes.update(dt);
		if (bird.isCollidingWithSide())
			mode = GameState::End;
		if (pipes.isColliding(bird))
			mode = GameState::End;;
		score += pipes.toScore(bird);

		float aspect = WIDTH / HEIGHT;
		// std::cout << aspect << std::endl;
		m_projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f);
		break;
	}
	case GameState::End:
	{
		break; 
	}
	}
}

void Game::draw()
{
	switch (mode) {
	case GameState::Welcome:
	{
		GLTtext* text = gltCreateText();
		gltSetText(text, "Press Space to start!");
		gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 3.0f);
		gltDrawText2DAligned(text,WIDTH / 2.0f,HEIGHT / 2.0f,3.0f,GLT_CENTER, GLT_CENTER);
		gltEndDraw();
		gltDeleteText(text);
		break;
	}
	case (GameState::Running): {
		gridDrawer.Draw();
		pipes.draw();
		bird.draw();
		side_blockDrawer.Draw();
		
		GLTtext* text = gltCreateText();
		gltSetText(text, ("Score : " + std::to_string(score)).c_str());

		// Begin text drawing (this for instance calls glUseProgram)
		gltBeginDraw();

		// Draw any amount of text between begin and end
		gltColor(1.0f, 1.0f, 1.0f, 3.0f);
		gltDrawText2D(text, 0, 0, 1);

		// Finish drawing text
		gltEndDraw();

		// Deleting text
		gltDeleteText(text);
		break;
	}
	case (GameState::End): {
		GLTtext* text = gltCreateText();
		gltSetText(text, ("Game over.\nPress Space to start a new game!\n Score:" + std::to_string(score)).c_str());
		gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 3.0f);
		gltDrawText2DAligned(text, WIDTH / 2.0f, HEIGHT / 2.0f, 3.0f, GLT_CENTER, GLT_CENTER);
		gltEndDraw();
		gltDeleteText(text);
	}
	}
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WIDTH = width;
	HEIGHT = height;
	float aspect = WIDTH / HEIGHT;
	side_blockDrawer.Clear();
	side_blockDrawer.Rectangle(pixW/2.0f * (-aspect + 1), 0, pixW/2.0f * (aspect - 1), pixH);
	side_blockDrawer.Rectangle(pixW, 0, pixW/2.0f * (aspect - 1), pixH);
}
