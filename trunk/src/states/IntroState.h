/** \file   IntroState.h
 *  \brief  Définit la classe IntroState
 */
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"

using namespace std;


/** \class  IntroState
 *  \brief  Gestion de l'état d'introduction
 *
 * L'état d'intro est l'état par lequel le programme démarre
 */
class IntroState : 
	public State
{
    public:
		IntroState();
		~IntroState();

		void init();
		void cleanUp();

		void pause();
		void resume();

		void input(Logic* logic, SDL_Event* SDLevent);
		void logic(Logic* logic);
		void render(Logic* logic, SDL_Surface* screen) const;

		static IntroState* instance();
    protected:
    private:
		static IntroState introState;

		SDL_Surface* splashScreen;
};

#endif // INTROSTATE_H
