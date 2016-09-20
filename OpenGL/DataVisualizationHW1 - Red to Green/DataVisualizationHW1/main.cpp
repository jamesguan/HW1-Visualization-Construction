/**
Author: James Guan

Using OpenGL to render the Diffusion Tensor Imaging.
This will produce two visualizations side by size.
SDL2 uses openGL to generate the graphics.

http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2041910/

This generates the image with red, and green because I think
it transitions nicely and shows a very good image of the 
changing data points.

Totally safe to run using Visual Studio 2015
Dependencies are SDL2, SDL2_ttf, Glew, and OpenGL

Totally didn't forkbomb myself by accident earlier

*/
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>

#include <SDL_ttf.h>

#include <SDL.h>

#include <glew.h>

#include <SDL_opengl.h>


#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}

// Need to include glew32s.lib to statically link
//#define GLEW_STATIC

// The size of the window
const GLint WIDTH = 800, HEIGHT = 600;

// This actually reads the data and draws it as it reads it.
void readDataFile(char * file, SDL_Renderer * renderer) {


	std::ifstream infile(file);
	std::string line = "";

	// This goes through every row
	int i = 0;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);

		float value;

		// This goes through every column in the row
		int j = 0;
		while (iss >> value) {
			if (value == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Renderer that relies on OpenGL
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255 - (value * 255), value * 255, 0, 255); // Renderer that relies on OpenGL
			}
			SDL_Rect rect = { j, i, 3, 3 }; // Generate rectangles 9 pixels thick
			SDL_RenderFillRect(renderer, &rect);
			j += 3; // Making rectangles 9 pixels thick so must move by 3 every time to draw, this goes along the x
		}
		i += 3; // Making rectangles 9 pixels thick so must move by 3 every time to draw, this goes along the y
		//std::cout << "\n";

	}

	// Generate the scale and legend
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { 99, 499, 257, 22 };
	SDL_RenderDrawRect(renderer, &rect);

	// Make a gradient for the legend
	for (int i = 100; i < 100 + 255; i++) {
		SDL_SetRenderDrawColor(renderer, 255 - (i - 100), (i - 100), 0, 255);
		for (int j = 500; j < 500 + 20; j++) {
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

}

int main(int argc, char * argv[])
{

	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() == -1)
	{
		std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
		return false;
	}


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 2056);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 1);

	SDL_Renderer * renderer;
	SDL_Window * window;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOWPOS_CENTERED, &window, &renderer);
	SDL_SetWindowTitle(window, "HW1: Diffusion Tensor Imaging - Red to Blue");

	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glMatrixMode(GL_MODELVIEW);


	glViewport(0, 0, WIDTH, HEIGHT);

	// Reads the data file
	readDataFile("data.txt", renderer);

	// Generates the scale
	TTF_Font * font = TTF_OpenFont("OpenSans-Regular.ttf", 25);
	if (font == nullptr)
	{
		std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
		return false;
	}
	const char * error = TTF_GetError();
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = surface = TTF_RenderText_Solid(font, "0                                 1", color);
	SDL_Texture * texture = texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 98, 520, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

	SDL_RenderPresent(renderer); // Displays the draws

	// Exit when user clicks x
	SDL_Event event;
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}


	// Clean up
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;

}