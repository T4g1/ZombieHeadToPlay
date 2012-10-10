/** \file   State.h
 *  \brief  Définit la classe State
 */
#ifndef STATE_H
#define STATE_H

#include "../modules/logic.h"

#include <SDL/SDL.h>

using namespace std;


/** \class  State
 *  \brief  Classe de base pour les états de jeu
 */
class State
{
    public:
        State();
        ~State();

		virtual void init() = 0;
		virtual void cleanUp() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void input(Logic* logic, SDL_Event* SDLevent) = 0;
		virtual void logic(Logic* logic) = 0;
		virtual void render(Logic* logic, SDL_Surface* screen) const = 0;

		void changeState(Logic* logic, State* state);
    protected:
    private:
};

#endif // STATE_H
