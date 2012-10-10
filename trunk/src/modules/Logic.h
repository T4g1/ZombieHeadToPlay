/** \file   Logic.h
 *  \brief  Définit la classe Logic
 */
#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <SDL/SDL_mutex.h>

#include "Module.h"

using namespace std;

class Core;
class State;

/** \class  Logic
 *  \brief  Gére toute la partie logique du jeu
 */
class Logic :
    public Module
{
    public:
		Logic(Core* core);
		~Logic();

        void frame();

		// Gestion des états
		void changeState(State* state);
		void pushState(State* state);
		void popState();

		// Mutateurs
		void stop();
		void IncreaseAccessCount();
		void DecreaseAccessCount();

		// Accesseurs
		State* currentState();
    protected:
    private:
		SDL_mutex* lock;

		// Indique si l'on peu taccéder à l'état courant ou non
		SDL_mutex* mutexStateAccessPermitted;
		bool stateAccessPermitted;

		// Mutex pour protéger le compteur d'acces a l'état courant
		SDL_mutex* mutexStateCountAccess;
		int accessCount;

		// Variable de condition qui empeche le changement d'état si
		// accessCount est plus grand que 0
		SDL_cond* condAccess;

		// Pile d'état
		vector<State*> l_states;
};

#endif // LOGIC_H