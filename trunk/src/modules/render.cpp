/** \file   Render.cpp
 *  \brief  Implémente la classe Render
 */
#include "Render.h"

#include <time.h>
#include <sstream>
#include <SDL/SDL.h>

#include "../Core.h"
#include "../configuration.h"


/**
 * Constructeur du module Render
 *
 * @param core              Reference vers le Core du programme
 */
Render::Render(Core* core) :
	Module(RENDER, "Render", core)
{
	caption = "Le jeu";
} // Render

/**
 * Destructeur du module Render
 */
Render::~Render()
{
	// dtor
} // ~Render


/**
 * Initialisation du module
 */
void Render::initialize()
{
	Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	if(Configuration::getProperties("game")["mode"] != "windowed")
		flags|=SDL_FULLSCREEN;
	screen = SDL_SetVideoMode(atoi(Configuration::getProperties("game")["width"].c_str()), 
		atoi(Configuration::getProperties("game")["height"].c_str()), 32, flags);
	

    if (screen == NULL)
		throw ERROR("Impossible de créer la surface de l'écran");
    
    SDL_WM_SetCaption(caption.c_str(), NULL);
} // initialize


/**
 * Clotûre la fenêtre propement
 */
void Render::unInitialize()
{
	// dtor
} // unInitialize


/**
 * Traitement du module
 */
void Render::frame()
{
	try {
		LOG("Debut de la gestion de l'affichage");

		initialize();

		// Comptage du FPS
		int updateFPS = 0, frameCount = 0, realFPS;

		// Limitation du FPS
		int fps = atoi(Configuration::getProperties("game")["fps"].c_str());
		int beginTime = 0, endTime = 0, deltaTime, sleepTime;
		int frameTime = (int)((1.0 / (float)fps) * CLOCKS_PER_SEC);

		// Boucle principale de l'affichage
		while(core->isRunning())
		{
			State* state = core->currentState();
			if(state) {
				state->render(core->getLogic(), screen);
				core->getLogic()->DecreaseAccessCount();
			}

			endTime = SDL_GetTicks();

			// Comptage du FPS
			frameCount += 1;
			deltaTime = endTime - updateFPS;
			if(deltaTime > UPDATE_FPS) {
				realFPS = (int)(((float)frameCount / deltaTime) * 1000.f);

				ostringstream captionFPS;
				captionFPS << caption << " - FPS:" << realFPS;

				SDL_WM_SetCaption(captionFPS.str().c_str(), NULL );

				frameCount = 0;
				updateFPS = SDL_GetTicks();
			}
			
			// Limitation du FPS
			endTime = SDL_GetTicks();
			deltaTime = endTime - beginTime;
			beginTime = endTime;
			if(deltaTime < frameTime) {
				sleepTime = frameTime - deltaTime;
				SDL_Delay(sleepTime);
			}
		}

		unInitialize();

		LOG("Fin de la gestion de l'affichage");
	} catch(string e) {
		LOGERROR(e);
	}
} // frame