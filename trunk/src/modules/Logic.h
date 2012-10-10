/** \file   Logic.h
 *  \brief  D�finit la classe Logic
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
 *  \brief  G�re toute la partie logique du jeu
 */
class Logic :
    public Module
{
    public:
		Logic(Core* core);
		~Logic();

        void frame();

		// Gestion des �tats
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

		// Indique si l'on peu tacc�der � l'�tat courant ou non
		SDL_mutex* mutexStateAccessPermitted;
		bool stateAccessPermitted;

		// Mutex pour prot�ger le compteur d'acces a l'�tat courant
		SDL_mutex* mutexStateCountAccess;
		int accessCount;

		// Variable de condition qui empeche le changement d'�tat si
		// accessCount est plus grand que 0
		SDL_cond* condAccess;

		// Pile d'�tat
		vector<State*> l_states;
};

#endif // LOGIC_H