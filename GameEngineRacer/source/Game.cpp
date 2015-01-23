#include "Game.h"

float Game::zoom;
bool Game::keys[1024]= {false};

Game::Game(){
	//scene = new CubeScene();
	//scene[1] = new Scene();
	//scene[0] = new Scene();
	//gui = new GUI();
	speed = 0.5f;
	turnSpeed = 5.5f;
	activeScene =0;
	x1 = 0;
	y1=0;
	z1=0;
	rot=0;
	rManager = ResourceManager::getInstance();
}

Game::~Game()
{
	//delete gui;
	//delete[] scene;
}
void Game::Run()
{



	Initialise();
	double lastTime = glfwGetTime();
	//! run the program as long as the window is open
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - lastTime;
		int fps = floor(1.0/elapsedTime);
		handleInput();
		//!Updates the game withing the Refresh Rate.

		float refresh_rate = 1.0f/120.0f;
		if(elapsedTime > refresh_rate)
		{
			Update();
		}

		Render(fps);
		lastTime = currentTime;
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
void Game::Initialise()
{
	width = 1024;
	height = 768;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(width, height, "Most Awesome Game Ever", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);
	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//scene[0]->InitScene("loading","splashmaster");
	//scene[0]->Update(keys);
	Render(0);
	//scene[0]->deleteShader();
	rManager->clearAll();



	//scene[1]->InitScene("menu","basicmaster");
	activeScene =1;	

	//ui.initText2D();


	//gui->setup(width,height, scene[activeScene]);
}

void Game::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
void Game::Update()
{
	//scene[activeScene]->GetCamera()->zoom(zoom);
	zoom = 0;
	glfwGetCursorPos(window,&cursorPositionX,&cursorPositionY);

	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);

	//Using a different way (i.e. instead of callback) to check for LEFT mouse button
	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) )
	{
		//std::cout << "Left button \n";
		//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible
		//scene[activeScene]->GetCamera()->rotate(deltaX*0.001f, deltaY*0.001f);

	}

	//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
	if (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) )
	{
		//std::cout << "Right button \n";
		//Rotate the camera. The 0.01f is a velocity mofifier to make the speed sensible
		//scene[activeScene]->GetCamera()->pan(deltaX*0.01f, deltaY*0.01f);

	}


	//scene[activeScene]->Update(keys);


	//Store the current cursor position
	lastCursorPositionX = cursorPositionX;
	lastCursorPositionY = cursorPositionY;
	int height, width;
	glfwGetWindowSize(window,&width,&height);
	//gui->onResize(width,height);
	//scene[activeScene]->resize(width,height);
}
void Game::Render(int fps)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	gl::ClearColor(0.0f,0.5f,0.7f,1.0f);
	gl::Clear( gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT );


	//scene[activeScene]->Render();
	//gui->saveData();
	/*if(scene[1]->GetGameObjects().size() >1)
	{
		ui.printText2D("FPS"+std::to_string(fps),20,20 ,20);
	}*/
	
	//gui->draw();
	glfwSwapBuffers(window);
	glfwPollEvents();

}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//key callback
{
	if(!TwEventKeyGLFW(key, action))
	{

	}
	glfwSetKeyCallback(window,key_callback);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, gl::TRUE_);

	keys[key] = action;

}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(!TwEventMouseButtonGLFW(button,action))
	{
		//std::cout << "hello/n";
	}
	glfwSetMouseButtonCallback(window,mouse_button_callback);
}

void Game::scroll_callback(GLFWwindow *window, double x, double y)
{
	zoom = (float)y*2.5f;
}
void Game::handleInput()
{
	int startIndex = 0;
	/*int size = scene[activeScene]->GetGameObjects().size() - scene[activeScene]->GetGameObjects().size()+5+startIndex;
	if(keys[GLFW_KEY_W])
	{
		float y = scene[activeScene]->GetGameObjects().at(startIndex)->getTransformComp()->getRotate().y +90.f;
		x1 += sin(y*((float)PI/180.f)) * speed;
		z1 += cos(y*((float)PI/180.f))* speed;
		for(int i =startIndex; i < size; ++i)
		{

			scene[activeScene]->GetGameObjects().at(i)->getTransformComp()->Translate(x1,0.0f,z1);

		}
	}
	if(keys[GLFW_KEY_A])
	{
		rot+= turnSpeed;
		for(int i =startIndex; i < size; ++i)
		{
			scene[activeScene]->GetGameObjects().at(i)->getTransformComp()->Rotate(0.0f,rot,0.0f);

		}
	}
	if(keys[GLFW_KEY_S])
	{

		float y = scene[activeScene]->GetGameObjects().at(startIndex)->getTransformComp()->getRotate().y +90.f;
		x1 -= sin(y*((float)PI/180.f)) * speed;
		z1 -= cos(y*((float)PI/180.f))* speed;
		for(int i =startIndex; i < size; ++i)
		{

			scene[activeScene]->GetGameObjects().at(i)->getTransformComp()->Translate(x1,0.0f, z1);

		}

	}
	if(keys[GLFW_KEY_D])
	{
		rot -= turnSpeed;

		for(int i =startIndex; i < size; ++i)
		{
			scene[activeScene]->GetGameObjects().at(i)->getTransformComp()->Rotate(0.0f,rot,0.0f);

		}

	}
	if(keyPressedOnce(GLFW_KEY_N))
	{
		scene[activeScene]->nextCamera();
	}*/
	rot=0;
	x1 =0;
	y1=0;
	z1=0;
}
bool Game::keyPressedOnce(int key)
{
	static bool pressed = false;
	if(keys[key] == GLFW_PRESS && !pressed)
	{
		pressed = true;
		return true;
	}
	else if(keys[key] == GLFW_RELEASE )
	{
		pressed = false;
		return false;	
	}
	else return false;
}

//void Game::SetZoom(float z)
//{
//	zoom = z;
//}
