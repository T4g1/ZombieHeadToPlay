/** \file   Input.cpp
 *  \brief  Impl�mente la classe Input
 */
#include "Input.h"

#include "../Core.h"


/**
 * Constructeur du module Render
 *
 * @param core              Reference vers le Core du programme
 */
Input::Input(Core* core) :
	Module(INPUT, "Input", core)
{
} // Input

/**
 * Destructeur du module Input
 */
Input::~Input()
{
} // ~Input


/**
 * Traitement du module
 */
void Input::frame()
{
	try {
		LOG("Debut de la gestion des entr�es utilisateur");

		SDL_Event SDLevent;

		// Boucle principale de la gestion des entr�es
		while(core->isRunning())
		{
			SDL_WaitEvent(&SDLevent);
			
			State* state = core->currentState();
			if(state) {
				state->input(core->getLogic(), &SDLevent);
				core->getLogic()->DecreaseAccessCount();
			}
		}

		LOG("Fin de la gestion des entr�es utilisateur");
	} catch(string e) {
		LOGERROR(e);
	}
} // frame