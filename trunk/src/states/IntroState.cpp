/** \file   IntroState.cpp
 *  \brief  Impl�mente la classe IntroState
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
 * Initialise l'�tat d'intro
 */
void IntroState::init()
{
	LOG("Initialisation de l'introduction");

	splashScreen = IMG_Load("media/splashscreen.png");
} // init


/**
 * Termine l'�tat d'intro
 */
void IntroState::cleanUp()
{
	LOG("Fermeture de l'introduction");

	SDL_FreeSurface(splashScreen);
} // cleanUp


/**
 * Met l'�tat d'intro en pause
 */
void IntroState::pause()
{
	LOG("Mise en pause");
} // pause


/**
 * Sort l'�tat d'intro de pause
 */
void IntroState::resume()
{
	LOG("Sortie de pause");
} // resume


/**
 * Gestion des entr�es
 */
void IntroState::input(Logic* logic, SDL_Event* SDLevent)
{	
	switch (SDLevent->type) {
		case SDL_KEYDOWN:
			LOG("Touche press�e");
			logic->changeState(MenuState::instance());
			break;

		case SDL_QUIT:
			LOG("Fermeture de la fen�tre");
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