/** \file   PlayState.h
 *  \brief  Définit la classe PlayState
 */
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL/SDL_mutex.h>

#include "State.h"

#include "../data/Player.h"
#include "../data/Level.h"

using namespace std;


/** \class  PlayState
 *  \brief  Gestion d'une partie en cours
 */
class PlayState : 
	public State
{
    public:
		PlayState();
		~PlayState();

		void init();
		void cleanUp();

		void pause();
		void resume();

		void input(Logic* logic, SDL_Event* SDLevent);
		void logic(Logic* logic);
		void render(Logic* logic, SDL_Surface* screen) const;

		static PlayState* instance();
    protected:
    private:
		static PlayState playState;
		
		Player* player;
		Level* level;
		
		SDL_mutex* playerMutex;
		SDL_mutex* levelMutex;
		
		void drawLevel(SDL_Surface* screen) const;
		void drawPlayer(SDL_Surface* screen) const;
};

#endif // PLAYSTATE_H
