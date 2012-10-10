/** \file   IntroState.h
 *  \brief  D�finit la classe IntroState
 */
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"

using namespace std;


/** \class  IntroState
 *  \brief  Gestion de l'�tat d'introduction
 *
 * L'�tat d'intro est l'�tat par lequel le programme d�marre
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
