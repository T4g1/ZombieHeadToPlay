/** \file   Logic.cpp
 *  \brief  Implémente la classe Logic
 */
#include "Logic.h"

#include "../Core.h"
#include "../states/State.h"
#include "../states/IntroState.h"


/**
 * Constructeur du module Logic
 *
 * @param core              Reference vers le Core du programme
 */
Logic::Logic(Core* core) :
	Module(LOGIC, "Logic", core)
{
	lock = SDL_CreateMutex();

	mutexStateCountAccess = SDL_CreateMutex();
	mutexStateAccessPermitted = SDL_CreateMutex();

	stateAccessPermitted = true;

	accessCount = 0;

	condAccess = SDL_CreateCond();
} // Logic

/**
 * Destructeur du module Logic
 */
Logic::~Logic()
{
    SDL_DestroyMutex(lock);

    SDL_DestroyMutex(mutexStateCountAccess);
    SDL_DestroyMutex(mutexStateAccessPermitted);

	SDL_DestroyCond(condAccess);
} // ~Logic


/**
 * Traitement du module
 */
void Logic::frame()
{
	try {
		LOG("Debut de la gestion logique");

		changeState(IntroState::instance());

		// Boucle principale de la gestion logique
		while(core->isRunning())
		{
			State* state = currentState();
			if(state) {
				state->logic(this);
				DecreaseAccessCount();
			}
		}

		LOG("Fin de la gestion logique");
	} catch(string e) {
		LOGERROR(e);
	}
} // frame

// Gestion des états
/**
 * Change l'état en cours et supprime l'état courant
 *
 * @param state		Nouvel état en cours
 */
void Logic::changeState(State* state) 
{
	// Empeche l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = false;
	SDL_UnlockMutex(mutexStateAccessPermitted);
	
	// Attend qu'il n'y ai plus d'acces a l'etat courant
	SDL_LockMutex(mutexStateCountAccess);
	while(accessCount > 1)
		SDL_CondWait(condAccess, mutexStateCountAccess);

	// Détruit l'état courant
	if(!l_states.empty() ) {
		l_states.back()->cleanUp();
		l_states.pop_back();
	}

	// Stock et lance le nouvel état
	l_states.push_back(state);
	l_states.back()->init();

	SDL_UnlockMutex(mutexStateCountAccess);
	
	// Retablit l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = true;
	SDL_UnlockMutex(mutexStateAccessPermitted);
}

/**
 * Stocke un état dans la pile et switch sur celui-ci
 *
 * @param state		Nouvel état en cours
 */
void Logic::pushState(State* state)
{
	// Empeche l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = false;
	SDL_UnlockMutex(mutexStateAccessPermitted);
	
	// Attend qu'il n'y ai plus d'acces a l'etat courant
	SDL_LockMutex(mutexStateCountAccess);
	while(accessCount > 1)
		SDL_CondWait(condAccess, mutexStateCountAccess);

	// Met état courant en pause
	if(!l_states.empty())
		l_states.back()->pause();

	// Stock et lance le nouvel état
	l_states.push_back(state);
	l_states.back()->init();

	SDL_UnlockMutex(mutexStateCountAccess);
	
	// Retablit l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = true;
	SDL_UnlockMutex(mutexStateAccessPermitted);
}

/**
 * Supprime un état de la pile et lance celui qui le précédait
 */
void Logic::popState()
{
	// Empeche l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = false;
	SDL_UnlockMutex(mutexStateAccessPermitted);
	
	// Attend qu'il n'y ai plus d'acces a l'etat courant
	SDL_LockMutex(mutexStateCountAccess);
	while(accessCount > 1)
		SDL_CondWait(condAccess, mutexStateCountAccess);

	// cleanup the current state
	if(!l_states.empty() ) {
		l_states.back()->cleanUp();
		l_states.pop_back();
	}

	// resume previous state
	if(!l_states.empty())
		l_states.back()->resume();

	SDL_UnlockMutex(mutexStateCountAccess);
	
	// Retablit l'acces a l'etat courant
	SDL_LockMutex(mutexStateAccessPermitted);
	stateAccessPermitted = true;
	SDL_UnlockMutex(mutexStateAccessPermitted);
}


// Mutateurs
/**
 * Arrete le programme
 */
void Logic::stop()
{
	core->stop();
}


/**
 * Indique qu'on accéde à l'état courant
 */
void Logic::IncreaseAccessCount()
{
	SDL_LockMutex(mutexStateCountAccess);
	accessCount += 1;
	SDL_UnlockMutex(mutexStateCountAccess);
}


/**
 * Indique qu'on accéde plus a l'état courant
 */
void Logic::DecreaseAccessCount()
{
	SDL_LockMutex(mutexStateCountAccess);
	accessCount -= 1;
	SDL_UnlockMutex(mutexStateCountAccess);

	SDL_CondSignal(condAccess);
}


// Accesseurs
/**
 * Donne l'état de jeu en cours
 *
 * @return NULL si n'existe pas, pointeur vers l'état en cours sinon
 */
State* Logic::currentState()
{
	State* temp = NULL;
	bool accessPermited;

	SDL_LockMutex(mutexStateAccessPermitted);
	accessPermited = stateAccessPermitted;
	SDL_UnlockMutex(mutexStateAccessPermitted);

	// Verifie que l'on peut acceder a la ressource	
	if(accessPermited) {
		if(!l_states.empty()) {
			// Indique qu'un acces est en cours
			IncreaseAccessCount();

			temp = l_states.back();
		}
	}

	return temp;
}