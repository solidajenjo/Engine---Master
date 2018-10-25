#include <stdlib.h>
#include "Application.h"
#include "ModuleRender.h"
#include "Globals.h"
#include "ModuleCamera.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			// Esc button is pressed
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				state = MAIN_FINISH;
				break;

			case SDL_WINDOWEVENT:
				if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
				break;
				//User presses a key
			case SDL_KEYDOWN:
			{
				//Select surfaces based on key press
				switch (sdlEvent.key.keysym.sym)
				{
				case SDLK_q:
					App->camera->camPos.y += 0.1f;
					break;

				case SDLK_e:
					App->camera->camPos.y -= 0.1f;
					break;
				
				case SDLK_a:
					App->camera->camPos -= App->camera->s.Normalized() * 0.1f;
					break;

				case SDLK_d:
					App->camera->camPos += App->camera->s.Normalized() * 0.1f;
					break;
				
				case SDLK_w:
					App->camera->camPos += App->camera->f.Normalized() * 0.1f;
					break;

				case SDLK_s:
					App->camera->camPos -= App->camera->f.Normalized() * 0.1f;
					break;

				}
			}
			}
		}
	}
	
	LOG("Bye :)\n");
	delete App;
	return main_return;
}
