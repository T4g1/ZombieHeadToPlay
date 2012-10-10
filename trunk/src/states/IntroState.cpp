/** \file   IntroState.cpp
 *  \brief  Implémente la classe IntroState
 */
#include "IntroState.h"

#include <SDL/SDL_image.h>

#include "../Logger.h"
#include "MenuState.h"

IntroState IntroState::introState;


/**
 * Constructeur de IntroState
 */
IntroState::IntroState()
{
	// ctor
} // IntroState

/**
 * Destructeur de IntroState
 */
IntroState::~IntroState()
{
	// dtor
} // ~IntroState


/**
 * Initialise l'état d'intro
 */
void IntroState::init()
{
	LOG("Initialisation de l'introduction");

	splashScreen = IMG_Load("media/splashscreen.png");
} // init


/**
 * Termine l'état d'intro
 */
void IntroState::cleanUp()
{
	LOG("Fermeture de l'introduction");

	SDL_FreeSurface(splashScreen);
} // cleanUp


/**
 * Met l'état d'intro en pause
 */
void IntroState::pause()
{
	LOG("Mise en pause");
} // pause


/**
 * Sort l'état d'intro de pause
 */
void IntroState::resume()
{
	LOG("Sortie de pause");
} // resume


/**
 * Gestion des entrées
 */
void IntroState::input(Logic* logic, SDL_Event* SDLevent)
{	
	switch (SDLevent->type) {
		case SDL_KEYDOWN:
			LOG("Touche pressée");
			logic->changeState(MenuState::instance());
			break;

		case SDL_QUIT:
			LOG("Fermeture de la fenêtre");
			logic->stop();
	}
} // input


/**
 * Gestion de la logique du jeu
 */
void IntroState::logic(Logic* logic)
{
} // logic


/**
 * Gestion de l'affichage
 */
void IntroState::render(Logic* logic, SDL_Surface* screen) const
{
	SDL_Rect splashPosition;
	splashPosition.x = screen->w / 2 - splashScreen->w / 2;
	splashPosition.y = screen->h / 2 - splashScreen->h / 2;

	SDL_FillRect(screen, 0, SDL_MapRGBA(screen->format, 255, 255, 255, 0));

	SDL_BlitSurface(splashScreen, NULL, screen, &splashPosition);

	SDL_Flip(screen);
} // render


/**
 * Donne un pointeur sur une instance IntroState
 *
 * @return		Objet IntroState
 */
IntroState* IntroState::instance()
{
	return &introState;
} // instance