#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <GL\glew.h>
#include <sdl2\SDL.h>
#include <sdl2\SDL_opengl.h>
#include <fstream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}


const GLint WIDTH = 800, HEIGHT = 800;

class SystemManager {
public:
	// Here we will just have a couple public members for example purposes.
	bool running;
	SDL_Event events;
	void inputManager(); // Handle input.
	void renderingManager(); // Handle drawing pretty pictures.
};

/*
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -0.5f);
	glEnd();

}
*/

void SystemManager::inputManager() {
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_QUIT)
			running = false;
	}
}

void SystemManager::renderingManager() {
	// Draw pretty pictures...
}

/*
void readDataFile (char * file) {
	std::ifstream infile(file);
	std::string line = "";
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		char c;

		float value;
		while (iss >> value) {
			std::string temp = std::to_string(value);
			DBOUT(" " << value);
		}

		DBOUT("\n");

	}
}
*/

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	/*
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to init GLEW\n");
		return -1;
	}
	*/

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window *window;                    // Declare a pointer

										   //SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		WIDTH,                               // width, in pixels
		HEIGHT,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);


	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{

		std::cout << "FAILED TO INITIALIZE GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, WIDTH, HEIGHT); 





	SDL_Event windowEvent;
	/*
	while (true)
	{
		if (SDL_PollEvent(&windowEvent)) {
			if (SDL_QUIT == windowEvent.type) {
				break;
			}

		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}
	*/

	/*

	SystemManager sysMgr;
	sysMgr.running = true;
	// Game Loop:
	while (sysMgr.running) {
		sysMgr.inputManager();
		sysMgr.renderingManager();
		readDataFile("data.txt");
		break;
	}
	*/
	// The window is open: could enter program loop here (see SDL_PollEvent())

	//SDL_Delay(15000);  // Pause execution for 3000 milliseconds, for example

					  // Close and destroy the window
	//SDL_DestroyWindow(window);

	// Clean up
	//SDL_Quit();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	//std::cout << "FUCK" << std::endl;
	atexit(SDL_Quit);

	return EXIT_SUCCESS;
}