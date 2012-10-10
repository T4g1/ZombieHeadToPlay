/** \file   MenuState.cpp
 *  \brief  Impl�mente la classe PlayState
 */
#include "PlayState.h"

#include "../Logger.h"
#include "../ErrorMessage.h"

PlayState PlayState::playState;


/**
 * Constructeur de PlayState
 */
PlayState::PlayState()
{
	// ctor
} // PlayState

/**
 * Destructeur de PlayState
 */
PlayState::~PlayState()
{
	// dtor
} // ~PlayState


/**
 * Initialise le jeu
 */
void PlayState::init()
{
	LOG("Initialisation du jeu");

	// Cr�ation des objets n�cessaires
	player = new Player();
	level = new Level();

	// Cr�ation des mutex
	playerMutex = SDL_CreateMutex();
	levelMutex = SDL_CreateMutex();

	try {
		level->load("media/level/city_level.tmx");
	} catch(ErrorMessage e) {
		e.what();
	}
} // init


/**
 * Termine le menu
 */
void PlayState::cleanUp()
{
	LOG("Fermeture du jeu");

	// D�structions des objets
	delete player;
	delete level;

	// Lib�re les mutex
	SDL_DestroyMutex(playerMutex);
	SDL_DestroyMutex(levelMutex);
} // cleanUp


/**
 * Met le jeu en pause
 */
void PlayState::pause()
{
	LOG("Mise en pause");
} // pause


/**
 * Sort le jeu de pause
 */
void PlayState::resume()
{
	LOG("Sortie de pause");
} // resume


/**
 * Gestion des entr�es
 */
void PlayState::input(Logic* logic, SDL_Event* SDLevent)
{	
	switch (SDLevent->type) {
		case SDL_QUIT:
			LOG("Fermeture de la fen�tre");
			logic->stop();
			break;

		case SDL_MOUSEMOTION:
			// R�oriente le joueur
			SDL_Rect mousePosition;
			mousePosition.x = SDLevent->motion.x;
			mousePosition.y = SDLevent->motion.y;

			SDL_LockMutex(playerMutex);
			player->updateOrientation(mousePosition);
			SDL_UnlockMutex(playerMutex);
			break;
	}
} // input


/**
 * Gestion de la logique du jeu
 */
void PlayState::logic(Logic* logic)
{
	Uint8* keystate = SDL_GetKeyState(NULL);

	// D�placements du joueur
	SDL_LockMutex(playerMutex);
	SDL_LockMutex(levelMutex);
	player->walk(
			level,
			keystate[SDLK_UP] == 1,
			keystate[SDLK_DOWN] == 1,
			keystate[SDLK_LEFT] == 1,
			keystate[SDLK_RIGHT] == 1
	);
	SDL_UnlockMutex(levelMutex);
	SDL_UnlockMutex(playerMutex);
} // logic


/**
 * Gestion de l'affichage
 */
void PlayState::render(Logic* logic, SDL_Surface* screen) const
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

	drawLevel(screen);

	drawPlayer(screen);

	SDL_Flip(screen);
} // render


/**
 * Donne un pointeur sur une instance PlayState
 *
 * @return		Objet PlayState
 */
PlayState* PlayState::instance()
{
	return &playState;
} // instance


/**
 * Affiche le niveau
 */
void PlayState::drawLevel(SDL_Surface* screen) const
{
	SDL_LockMutex(playerMutex);
	SDL_Rect playerPosition = player->getPosition();
	SDL_UnlockMutex(playerMutex);

	SDL_LockMutex(levelMutex);
	level->draw(screen, playerPosition);
	SDL_UnlockMutex(levelMutex);
}


/**
 * Affiche le joueur
 */
void PlayState::drawPlayer(SDL_Surface* screen) const
{
	SDL_LockMutex(playerMutex);
	// Joueur orient�
	SDL_Surface* playerRotated = player->getRotatedSprite();

	// Calcul l'endroit ou l'on affiche le joueur
	SDL_Rect playerPosition;
	playerPosition.x = screen->w / 2 - playerRotated->w / 2;
	playerPosition.y = screen->h / 2 - playerRotated->h / 2;

	// Affiche le joueur
	SDL_BlitSurface(playerRotated, NULL, screen, &playerPosition);
	SDL_UnlockMutex(playerMutex);
}